#include "../../inc/client.h"

// 显示网盘文件列表
bool show_sever_file_list(char * search_path, P_DVI inf_heap)
{
    // 去除本地
    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }

    // 去除天气界面
    if(inf_heap->weather_info_windows != NULL) {
        lv_obj_del(inf_heap->weather_info_windows);
        inf_heap->weather_info_windows = NULL; // 防止悬挂指针
    }
    
    // 刷新网盘
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }

    if(inf_heap->sever_document == NULL) {
        // 网盘首页
        inf_heap->sever_document = lv_list_create(inf_heap->main_windows);
        lv_obj_set_size(inf_heap->sever_document, 638, 440);
        lv_obj_set_pos(inf_heap->sever_document, 162, 40);
    }

    int client_socket_netdisk = connect_to_server();
    if(client_socket_netdisk == -1) {
        // fclose(file);
        return NULL;
    }
    
    if(current_label != NULL)
    {
        lv_obj_del(current_label);
        current_label = NULL;
    }
    current_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(current_label, "网盘");
    lv_obj_set_pos(current_label, 10, 450);
    lv_obj_set_style_text_font(current_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    
    int bytes_received;
    char sever_file_list[BUF_SIZE];

    // 发送获取文件列表的请求
    char * request = "list";
    send(client_socket_netdisk, request, strlen(request), 0);

    // 接收文件列表
    bytes_received = recv(client_socket_netdisk, sever_file_list, BUF_SIZE - 1, 0);
    if(bytes_received < 0) {
        perror("Receive failed");
    } else {
        printf("sever_file_list: %s\n", sever_file_list);

        sever_file_list[bytes_received] = '\0'; // 确保缓冲区以 NULL 结尾
        
        // 将文件列表按行分割
        char * file = strtok(sever_file_list, "\n");
        // 解析并显示文件列表
        // char * saveptr;
        // char * file = strtok_r(sever_file_list, "\n", &saveptr);
            
        printf("--file: %s\n", file);
        while(file != NULL) {
            printf("---------------\n");
            
            // 这里要确保每个按钮都有独立的指针和内存空间
            char *file_name = strdup(file); // 为每个文件名分配独立的内存
            
            lv_obj_t * file_btn = lv_list_add_btn(inf_heap->sever_document, LV_SYMBOL_FILE, file); // 添加到 LVGL 列表
            if (file_btn == NULL) {
                printf("Failed to create LVGL file button.\n");
                break; // 停止循环
            }

            printf("--file创建列表按钮: %s\n", file);

            // 在list_btn上创建按钮
            lv_obj_t * btn = lv_btn_create(file_btn);
            lv_obj_set_size(btn, 70, 30);
            lv_obj_align_to(btn, file_btn, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
            lv_obj_t * lab = lv_label_create(btn);
            lv_obj_set_style_text_font(lab, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
            // lv_label_set_long_mode(lab, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_width(lab, 50);
            lv_obj_set_height(lab, 30);
            lv_label_set_text(lab, "下载");
            lv_obj_set_pos(lab, -5, -3);


            printf("--file创建完标签: %s\n", file);
            // 创建任务结构体并传递给线程
            download_task_t * task = malloc(sizeof(download_task_t));
            if(task == NULL) {
                perror("Memory allocation failed");
                close(client_socket_netdisk);
                return false;
            }
            
            strncpy(task->file_name, file, BUF_SIZE);
            // strncpy(task->file_name, file, sizeof(task->file_name) - 1);
            // task->file_name[BUF_SIZE - 1] = '\0'; // 确保结尾
            printf("--file存入结构体: %s\n", task->file_name);
            // 为下载按钮添加事件回调
            lv_obj_add_event_cb(btn, confirm_download_cb, LV_EVENT_CLICKED, (void *)task);
            free(file_name); // 释放临时文件名指针

            file = strtok(NULL, "\n"); // 继续读取下一行文件名
            // file = strtok_r(NULL, "\n", &saveptr);
        }

    }

    // 关闭套接字
    close(client_socket_netdisk);

    return true;
}

// 下载确认按钮的回调函数
void confirm_download_cb(lv_event_t * e)
{
    // printf("确认下载文件\n");

    // 创建任务结构体并传递给线程
    download_task_t * task = malloc(sizeof(download_task_t));
    if(task == NULL) {
        perror("Memory allocation failed");
        return;
    }
    
    pthread_t download_thread;
    task = (download_task_t *)e->user_data;
    // printf(" --- task->file_name: %s\n", task->file_name);

    // strncpy(task->file_name, file_name, BUF_SIZE);

    // 创建线程进行文件下载
    if(pthread_create(&download_thread, NULL, download_file_thread, (void *)task) != 0) {
        perror("Failed to create thread");
        free(task);
        // }
    }
    pthread_detach(download_thread); // 线程分离，自动回收

    // // 等待所有线程完成
    // for(int i = 0; i < selected_file_count; i++) {
    //     pthread_join(threads[i], NULL);
    // }
}

void * download_file_thread(void * arg)
{
    // printf("111 --- Download file: %s\n", arg);
    download_task_t * task = (download_task_t *)arg;
    // printf(" +++ task->file_name: %s\n", task->file_name);
    download_file_from_server(task->file_name); // 调用下载函数
    free(task);                                 // 释放任务结构体内存
    pthread_exit(NULL);
}


// 将文件下载到指定目录
void download_file_from_server(const char * file_name)
{
    // printf(" --- Downloading %s\n", file_name);
    char buffer[BUF_SIZE];
    ssize_t bytes_received;
    ssize_t total_received = 0;
    size_t file_size = 0;
    ssize_t to_receive = 0;
    
    // 连接服务器
    int client_socket_download = connect_to_server();
    if(client_socket_download == -1) {
        close(client_socket_download);
        return NULL;
    }

    // 发送下载文件请求
    char request[BUF_SIZE];
    snprintf(request, sizeof(request), "download:%s", file_name); // 构建下载请求
    printf("request: %s\n", request);
    send(client_socket_download, request, strlen(request), 0);
    
    // 接收文件大小
    if (recv(client_socket_download, &file_size, sizeof(file_size), 0) != sizeof(file_size)) {
        perror("Failed to receive file size");
        close(client_socket_download);
        return;
    }
    printf("文件大小: %zu\n", file_size);

    // 发送确认信号给服务器，表示准备接收文件
    char ack[] = "READY";
    if (send(client_socket_download, ack, strlen(ack), 0) <= 0) {
        perror("Failed to send READY signal");
        close(client_socket_download);
        return;
    }

    // 创建本地文件路径
    char local_file_path[BUF_SIZE];
    snprintf(local_file_path, sizeof(local_file_path), "%s%s", DOWNLOAD_PATH, file_name);

    // 打开文件以保存数据
    int local_file = open(local_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(local_file < 0) {
        perror("Failed to create local file");
        close(client_socket_download);
        return;
    }
    printf("local_file: %d\n", local_file);
    
    // 接收文件内容并写入本地文件
    while (total_received < file_size) {
        bytes_received = recv(client_socket_download, buffer, sizeof(buffer), 0);
        
        if (bytes_received < 0) {
            perror("File receive failed");
            close(local_file);
            close(client_socket_download);
            return;
        }

        if (bytes_received == 0) {
            // 服务器关闭连接，说明传输完成
            break;
        }

        if (write(local_file, buffer, bytes_received) != bytes_received) {
            perror("Failed to write data to file");
            close(local_file);
            close(client_socket_download);
            return;
        }

        total_received += bytes_received;
        printf("已接收 %zu / %zu 字节\n", total_received, file_size);
    }

    // 检查文件传输是否完成
    if (total_received == file_size) {
        printf("文件传输完成\n");
    } else {
        printf("文件传输未完成，接收了 %zu 字节，预期为 %zu 字节\n", total_received, file_size);
    }

    // 关闭文件和套接字
    close(local_file);
    close(client_socket_download);
    printf("文件 '%s' 下载成功并保存至 '%s' 目录\n", file_name, DOWNLOAD_PATH);

    pthread_exit(NULL); // 退出线程
}


// 文件下载线程函数：接收文件并保存到本地
// void * download_file_thread(void * arg)
// {
//     char * file_name = (char *)arg;

//     // 创建客户端套接字并连接到服务器
//     int client_socket_download = connect_to_server();
//     if(client_socket_download == -1) {
//         return NULL;
//     }

//     // 发送下载请求到服务器
//     char download_cmd[BUF_SIZE];
//     snprintf(download_cmd, sizeof(download_cmd), "download:%s", file_name);
//     send(client_socket_download, download_cmd, strlen(download_cmd), 0);

//     // 先接收文件大小
//     size_t file_size;
//     recv(client_socket_download, &file_size, sizeof(file_size), 0);
//     printf("文件大小: %zu 字节\n", file_size);

//     // 打开文件以写入
//     FILE * file = fopen(file_name, "wb");
//     if(file == NULL) {
//         perror("无法创建文件");
//         close(client_socket_download);
//         return NULL;
//     }

//     char buffer[BUF_SIZE];
//     size_t bytes_received, total_received = 0;

//     // 接收文件数据并写入本地文件
//     while((bytes_received = recv(client_socket_download, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, 1, bytes_received, file);
//         total_received += bytes_received;

//         // 显示下载进度
//         int progress = (total_received * 100) / file_size;
//         printf("文件 %s 下载进度: %d%%\n", file_name, progress);
//     }

//     fclose(file);
//     close(client_socket_download);
//     printf("文件下载完成\n");

//     return NULL;
// }

// // 下载按钮的事件处理函数
// void download_btn_press_task(lv_event_t * e)
// {
//     struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
//     char * file_name                         = click_tmp_inf->new_dir_path;

//     printf("下载文件: %s\n", file_name);

//     // 启动一个新线程来下载文件
//     pthread_t download_thread;
//     pthread_create(&download_thread, NULL, download_file_thread, (void *)file_name);
//     pthread_detach(download_thread); // 线程分离，自动回收
// }

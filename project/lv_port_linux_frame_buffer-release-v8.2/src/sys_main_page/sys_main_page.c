#include "../../inc/client.h"
#include "../../inc/color.h"

int EXIT_MASK = 0;
P_DVI inf_heap;
lv_obj_t * time_label;

// 获取当前时间
static void update_time(lv_timer_t * timer)
{
    time_t now;
    struct tm * time_info;
    char buffer[64];

    time(&now);
    time_info = localtime(&now);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", time_info); // 格式化时间为时:分:秒
    lv_label_set_text(time_label, buffer);
}

/**************************** 创建主画布 ****************************/
bool Dir_View_Init_Windows()
{
    inf_heap = (P_DVI)calloc(1, sizeof(DVI));
    if(inf_heap == (P_DVI)NULL) {
        perror("内存申请失败! \n");
        return (P_DVI)-1;
    }
    // strcpy(inf_heap->list_dir_path, DEFAULET_PATH);

    // 创建主窗口
    inf_heap->main_windows = lv_obj_create(NULL);
    // lv_obj_set_style_bg_color(inf_heap->main_windows, lv_color_hex(0x87CEFA), LV_PART_MAIN);    // 天蓝色
    color_gradient(inf_heap->main_windows);

    // 创建时间显示标签
    time_label = lv_label_create(inf_heap->main_windows);
    lv_obj_align(time_label, LV_ALIGN_BOTTOM_LEFT, 5, -5);
    lv_timer_t * timer = lv_timer_create(update_time, 1000, NULL); // 每秒更新时间

    lv_obj_t * notic_windows = lv_obj_create(inf_heap->main_windows);
    lv_obj_set_size(notic_windows, 450, 380);
    lv_obj_set_pos(notic_windows, 250, 70);
    lv_obj_set_style_bg_opa(notic_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置背景透明
    lv_obj_t * notic_label = lv_label_create(notic_windows);
    lv_label_set_text(notic_label, "欢迎使用");
    lv_obj_set_style_text_font(notic_label, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(notic_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_color(notic_label, lv_color_hex(0xFF0000), LV_STATE_DEFAULT); // 设置红色
    lv_obj_set_pos(notic_label, 150, 130);
    lv_obj_set_style_bg_opa(notic_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置按钮背景透明

    // 显示系统名字
    lv_obj_t * title_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(title_label, "那咋了网盘");
    lv_obj_set_size(title_label, 200, 30);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 50, 10);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFB6C1), LV_STATE_DEFAULT); // 字体浅粉色
    // lv_obj_set_style_text_color(title_label, lv_color_hex(0x0000FF), LV_STATE_DEFAULT); // 字体蓝色
    lv_obj_set_style_text_font(title_label, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);

    // 创建主功能目录
    inf_heap->head_list_windows = lv_list_create(inf_heap->main_windows);
    lv_obj_set_size(inf_heap->head_list_windows, 165, 400);
    lv_obj_set_pos(inf_heap->head_list_windows, 0, 80);
    lv_obj_set_style_bg_opa(inf_heap->head_list_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置列表半透明
    // lv_obj_set_style_opa(inf_heap->head_list_windows, LV_OPA_TRANSP, LV_PART_MAIN);  // 设置列表透明
    // lv_obj_set_style_bg_color(inf_heap->head_list_windows, lv_color_hex(0x87CEFA), LV_PART_MAIN);    // 天蓝色

    // 分隔
    lv_obj_t * null_label_0 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_0, " ");
    lv_obj_set_size(null_label_0, 120, 10);
    /************上传************/
    lv_obj_t * main_funtion_btn_0 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_0, 120, 70);
    lv_obj_t * label_0 = lv_label_create(main_funtion_btn_0);
    lv_obj_set_style_text_font(main_funtion_btn_0, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_0, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_0, 50, 25);
    lv_label_set_text(label_0, "首页");
    lv_obj_set_pos(label_0, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_0, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_0, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_0, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_0, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 0);

    // 分隔
    lv_obj_t * null_label_1 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_1, " ");
    lv_obj_set_size(null_label_1, 120, 10);
    /**************网盘************/
    lv_obj_t * main_funtion_btn_1 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_1, 120, 70);
    // lv_obj_t * label_1_icon = lv_label_create(main_funtion_btn_1);
    // lv_obj_set_style_text_font(label_1_icon, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    // lv_obj_set_size(label_1_icon, 25, 25);
    // lv_label_set_text(label_1_icon, "1");
    // lv_obj_set_pos(label_1_icon, 10, 15);
    lv_obj_t * label_1 = lv_label_create(main_funtion_btn_1);
    lv_obj_set_style_text_font(main_funtion_btn_1, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_obj_set_size(label_1, 50, 25);
    lv_label_set_text(label_1, "网盘");
    lv_obj_set_pos(label_1, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_1, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_1, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_1, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_1, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 1);

    // 分隔
    lv_obj_t * null_label_2 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_2, " ");
    lv_obj_set_size(null_label_2, 120, 10);
    /************上传************/
    lv_obj_t * main_funtion_btn_2 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_2, 120, 70);
    lv_obj_t * label_2 = lv_label_create(main_funtion_btn_2);
    lv_obj_set_style_text_font(main_funtion_btn_2, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_2, 50, 25);
    lv_label_set_text(label_2, "本地");
    lv_obj_set_pos(label_2, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_2, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_2, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_2, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_2, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 2);

    // 分隔
    lv_obj_t * null_label_3 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_3, " ");
    lv_obj_set_size(null_label_3, 120, 10);
    /************传输************/
    lv_obj_t * main_funtion_btn_3 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_3, 120, 70);
    lv_obj_t * label_3 = lv_label_create(main_funtion_btn_3);
    lv_obj_set_style_text_font(main_funtion_btn_3, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_3, 50, 25);
    lv_label_set_text(label_3, "传输");
    lv_obj_set_pos(label_3, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_3, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_3, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_3, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_3, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 3);

    // // 分隔
    // lv_obj_t * null_label_4 = lv_label_create(inf_heap->head_list_windows);
    // lv_label_set_text(null_label_4, " ");
    // lv_obj_set_size(null_label_4, 120, 10);
    // /************聊天************/
    // lv_obj_t * main_funtion_btn_4 = lv_btn_create(inf_heap->head_list_windows);
    // lv_obj_set_size(main_funtion_btn_4, 120, 70);
    // lv_obj_t * label_4 = lv_label_create(main_funtion_btn_4);
    // lv_obj_set_style_text_font(main_funtion_btn_4, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    // lv_label_set_long_mode(label_4, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // lv_obj_set_size(label_4, 70, 70);
    // lv_label_set_text(label_4, "聊天");
    // lv_obj_set_pos(label_4, LV_ALIGN_CENTER, LV_ALIGN_CENTER);
    // lv_obj_set_style_text_color(label_4, lv_color_hex(0x000000), LV_STATE_DEFAULT);    // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_4, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    // // lv_obj_add_event_cb(inf_heap->head_list_windows, list_btn_press_task, LV_EVENT_CLICKED, NULL);

    // 创建左边目录list控件
    // inf_heap->lv_dir_list = lv_list_create(inf_heap->main_windows);
    // lv_obj_set_size(inf_heap->lv_dir_list, 145, 440);
    // lv_obj_set_pos(inf_heap->lv_dir_list, 165, 40);
    // printf("lv_dir_list create success! \n");
    // // 创建右边的小画布
    // inf_heap->lv_little_windows = lv_obj_create(inf_heap->main_windows);
    // lv_obj_set_size(inf_heap->lv_little_windows, 495, 440);
    // lv_obj_set_pos(inf_heap->lv_little_windows, 305, 40);

    lv_scr_load(inf_heap->main_windows);

    return true;
}

void sys_main_page_btn_press_task(lv_event_t * e)
{
    int num_btn = (int)lv_event_get_user_data(e);
    switch(num_btn) {
        case 0:

            printf("点击了首页按钮! \n");
            if(!show_notice_funtion(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 1:

            printf("点击了网盘按钮! \n");
            if(!show_sever_file_list(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 2:

            printf("点击了本地按钮! \n");
            if(!Show_File_List(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 3: printf("点击了传输按钮! \n"); break;

        default: break;
    }
}

bool show_notice_funtion(char * search_path, P_DVI inf_heap)
{
    // 去除网盘
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }

    // 去除本地
    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }

    return true;
}

// 显示网盘文件列表
bool show_sever_file_list(char * search_path, P_DVI inf_heap)
{
    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }

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
    
    // 接收文件大小
    if (recv(client_socket_download, &file_size, sizeof(file_size), 0) <= 0) {
        perror("Failed to receive file size");
        close(local_file);
        close(client_socket_download);
        return;
    }
    printf("文件大小: %zu\n", file_size);

    
    // 开始接收文件内容
    while (total_received < file_size)
    {
        to_receive = file_size - total_received > BUF_SIZE ? BUF_SIZE : file_size - total_received;

        // 接收指定大小的数据块
        bytes_received = recv(client_socket_download, buffer, to_receive, 0);
        if (bytes_received <= 0)
        {
            perror("File receive failed or connection closed");
            break;
        }

        // 写入接收到的文件数据到本地文件
        if (write(local_file, buffer, bytes_received) != bytes_received)
        {
            perror("Failed to write data to file");
            close(local_file);
            close(client_socket_download);
            return;
        }
        total_received += bytes_received;
        printf("已接收: %zd / %zu\n", total_received, file_size);
    }

    if (total_received == file_size)
    {
        printf("文件传输完成，接收到 %zd 字节\n", total_received);
    }
    else
    {
        printf("文件传输未完成或失败，接收到 %zd 字节\n", total_received);
    }

    // 关闭文件和套接字
    close(local_file);
    close(client_socket_download);
    printf("文件 '%s' 下载成功并保存至 '%s' 目录\n", file_name, DOWNLOAD_PATH);

    pthread_exit(NULL); // 退出线程
}

// 显示文件列表
bool Show_File_List(char * search_path, P_DVI inf_heap)
{
    printf("Show_File_List \n");
    // P_DVI inf_heap = inf_heap;
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }
    // free(inf_heap->sever_document);

    printf("Show_File_List ----- 1 \n");

    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }

    if(inf_heap->lv_dir_list == NULL && inf_heap->lv_little_windows == NULL) {
        // 创建左边目录list控件
        inf_heap->lv_dir_list = lv_list_create(inf_heap->main_windows);
        lv_obj_set_size(inf_heap->lv_dir_list, 145, 440);
        lv_obj_set_pos(inf_heap->lv_dir_list, 162, 40);
        printf("lv_dir_list create success! \n");
        // 创建右边的小画布
        inf_heap->lv_little_windows = lv_list_create(inf_heap->main_windows);
        lv_obj_set_size(inf_heap->lv_little_windows, 495, 440);
        lv_obj_set_pos(inf_heap->lv_little_windows, 305, 40);
    }

    printf("------ %s ------ \n", search_path);
    // 打开要检索的目录，初始目录是根目录
    DIR * dp = opendir(search_path);
    if(dp == (DIR *)NULL) {
        perror("打开目录失败! \n");
        return false;
    }

    char base_path[256 * 8];

    // int btn_x = 0;
    // int btn_y = 0;
    // 循环读取目录
    while(1) {
        memset(base_path, 0, 256 * 2);
        struct dirent * eq = readdir(dp);
        if(eq == (struct dirent *)NULL) {
            break;
        }
        if(strcmp(eq->d_name, ".") == 0) // 忽略当前目录
        {
            continue;
        }

        if(strcmp(eq->d_name, "..") == 0) {
            char tmp_path[256 * 2] = "\0";
            strcpy(tmp_path, search_path);
            char * obj_char = strrchr(tmp_path, '/');

            if(obj_char == tmp_path) {
                strcpy(base_path, DEFAULET_PATH);
            } else {
                *obj_char = '\0';
                strcpy(base_path, tmp_path);
            }

        } else {
            if(search_path[strlen(search_path) - 1] == '/') {
                sprintf(base_path, "%s%s", search_path, eq->d_name);
            }

            else {
                sprintf(base_path, "%s/%s", search_path, eq->d_name);
            }
        }
        // 如果是文件，则显示文件名
        if(eq->d_type == DT_REG) {
            // 申请按钮点击传参结构体堆空间
            struct tmp_btn_touch_inf * file_tmp_inf = calloc(1, sizeof(struct tmp_btn_touch_inf));
            file_tmp_inf->inf_heap                  = inf_heap;
            strcpy(file_tmp_inf->new_dir_path, base_path);

            // 在list控件上创建按钮，并设置按钮的文本为文件名
            show_file_view(inf_heap, eq->d_name, file_tmp_inf);

            // btn_x += 90;
            // if(btn_x >= 450) {
            //     btn_x = 0;
            // btn_y += 50;
            // }
        }

        if(eq->d_type == DT_DIR) {
            // 如果是文件夹，则给list控件创建按钮，然后设置按钮的文本为文件夹的名字
            lv_obj_t * btn = lv_list_add_btn(inf_heap->lv_dir_list, LV_SYMBOL_DIRECTORY, eq->d_name);
            // 申请按钮点击传参结构体堆空间
            struct tmp_btn_touch_inf * tmp_inf = calloc(1, sizeof(struct tmp_btn_touch_inf));
            if(tmp_inf == (struct tmp_btn_touch_inf *)NULL) {
                perror("内存申请失败! \n");
                return false;
            }
            // 赋值存储当前目录完整路径以及主控结构体堆空间基地址
            tmp_inf->inf_heap = inf_heap;
            strcpy(tmp_inf->new_dir_path, base_path);

            // 注册当前目录按钮点击事件函数 --- 递归调用自己
            lv_obj_add_event_cb(btn, list_btn_press_task_1, LV_EVENT_CLICKED, (void *)tmp_inf);
        }
    }

    // 关闭目录
    closedir(dp);

    return true;
}

void list_btn_press_task_1(lv_event_t * e)
{
    struct tmp_btn_touch_inf * tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    // printf("传入的是: %s ! \n", tmp_inf->new_dir_path);

    // 清除之前list里面的旧控件
    lv_obj_del(tmp_inf->inf_heap->lv_dir_list);
    tmp_inf->inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    // 清除之前little_windows的旧控件
    lv_obj_del(tmp_inf->inf_heap->lv_little_windows);
    tmp_inf->inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    // 递归调用加载新的目录控件
    Show_File_List(tmp_inf->new_dir_path, tmp_inf->inf_heap);

    return;
}

// 文件上传线程函数
void * upload_file_thread(void * arg)
{
    char * file_path         = (char *)arg;
    char upload_message[256] = "upload:";

    // 连接服务器
    int client_socket_upload = connect_to_server();
    if(client_socket_upload == -1) {
        close(client_socket_upload);
        return NULL;
    }

    // 获取文件名
    const char * file_name = strrchr(file_path, '/');
    if(file_name)
        file_name++;
    else
        file_name = file_path;
    printf("文件名: %s\n", file_name);
    snprintf(upload_message, sizeof(upload_message), "upload:%s", file_name);
    printf("上传信息: %s\n", upload_message);

    // size_t file_message_len = strlen(upload_message);

    // // 1. 发送文件名长度
    // if (send(client_socket_upload, &upload_message, sizeof(upload_message), 0) <= 0) {
    //     printf("发送文件名长度失败。\n");
    //     fclose(file);
    //     close(client_socket_upload);
    //     return NULL;
    // }
    // printf("发送文件名长度成功。\n");
    // // 等待服务器确认文件名长度
    // char ack[10];
    // if (recv(client_socket_upload, ack, sizeof(ack), 0) <= 0 || strcmp(ack, "ACK") != 0) {
    //     printf("服务器未确认文件名长度，上传失败。\n");
    //     fclose(file);
    //     close(client_socket_upload);
    //     return NULL;
    // }

    // // 2. 发送文件名
    // if (send(client_socket_upload, upload_message, file_message_len, 0) <= 0) {
    //     printf("发送文件名失败。\n");
    //     fclose(file);
    //     close(client_socket_upload);
    //     return NULL;
    // }

    // // 等待服务器确认文件名
    // if (recv(client_socket_upload, ack, sizeof(ack), 0) <= 0 || strcmp(ack, "ACK") != 0) {
    //     printf("服务器未确认文件名，上传失败。\n");
    //     fclose(file);
    //     close(client_socket_upload);
    //     return NULL;
    // }

    // // 3. 发送文件数据
    // char buffer[BUF_SIZE];
    // size_t bytes_read, total_sent = 0;
    // fseek(file, 0, SEEK_END);
    // size_t file_size = ftell(file);
    // fseek(file, 0, SEEK_SET);

    // while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
    //     if (send(client_socket_upload, buffer, bytes_read, 0) <= 0) {
    //         printf("发送文件数据失败。\n");
    //         break;
    //     }
    //     total_sent += bytes_read;

    //     // 等待确认
    //     if (recv(client_socket_upload, ack, sizeof(ack), 0) <= 0 || strcmp(ack, "ACK") != 0) {
    //         printf("服务器未确认数据接收，上传失败。\n");
    //         break;
    //     }

    //     // 显示上传进度
    //     int progress = (total_sent * 100) / file_size;
    //     printf("文件 %s 上传进度: %d%%\n", file_name, progress);
    // }

    // fclose(file);
    // close(client_socket_upload);
    // printf("文件上传完成\n");
    // return NULL;

    // char buffer[BUF_SIZE];
    int bytes_read;

    // 发送上传文件请求，格式为 "upload:文件名"
    // snprintf(buffer, sizeof(buffer), "upload:%s", file_name);
    send(client_socket_upload, upload_message, strlen(upload_message), 0);

    printf("----------------\n");
    // 等待服务器的响应
    bytes_read = recv(client_socket_upload, upload_message, sizeof(upload_message) - 1, 0);
    if(bytes_read <= 0) {
        perror("No response from server or connection lost");
        // close(client_socket_upload);
        return;
    } else {
        upload_message[bytes_read] = '\0'; // 确保以 NULL 结尾
        printf("客户端收到的消息: %s, 字节数: %d\n", upload_message, bytes_read);
    }
    
    upload_message[bytes_read] = '\0'; // 确保以 NULL 结尾
    if(strcmp(upload_message, "READY_TO_RECEIVE") != 0) {
        printf("服务器拒绝接收文件：%s\n", upload_message);
        close(client_socket_upload);
        return;
    }

    // 打开本地文件以读取数据
    // char local_file_path[BUF_SIZE];
    // snprintf(local_file_path, sizeof(local_file_path), "%s%s", DOWNLOAD_PATH, file_name);
    int local_file = open(file_path, O_RDONLY);
    if(local_file < 0) {
        perror("Failed to open local file");
        close(client_socket_upload);
        return;
    }

    // 发送文件内容
    while((bytes_read = read(local_file, upload_message, sizeof(upload_message))) > 0) {
        if(send(client_socket_upload, upload_message, bytes_read, 0) < 0) {
            perror("Failed to send file");
            close(local_file);
            close(client_socket_upload);
            return;
        }
    }

    if(bytes_read < 0) {
        perror("Failed to read file");
    }

    // 关闭文件和套接字
    close(local_file);
    close(client_socket_upload);

    printf("文件 '%s' 已成功上传到服务器的 Document 目录\n", file_name);
}

// 上传按钮的事件处理函数
void upload_btn_press_task(lv_event_t * e)
{
    struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    char * file_path                         = click_tmp_inf->new_dir_path;

    printf("上传文件: %s\n", file_path);

    // 启动一个新线程来上传文件
    pthread_t upload_thread;
    // pthread_create(&upload_thread, NULL, upload_file_thread, (void *)file_path);
    if(pthread_create(&upload_thread, NULL, upload_file_thread, (void *)file_path) != 0) {
        perror("Failed to create thread");
        // free(task);
    }
    pthread_detach(upload_thread); // 线程分离，自动回收
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

bool show_file_view(P_DVI inf_heap, char * btn_text, struct tmp_btn_touch_inf * file_tmp_inf)
{
    lv_obj_t * list_btn = lv_list_add_btn(inf_heap->lv_little_windows, LV_SYMBOL_FILE, btn_text);
    // sprintf(file_tmp_inf->new_dir_path, "%s/%s", file_tmp_inf->new_dir_path, btn_text);
    printf("传入的是: %s ! \n", file_tmp_inf->new_dir_path);
    lv_obj_set_size(list_btn, 440, 50);
    lv_obj_add_event_cb(list_btn, file_btn_press_task, LV_EVENT_CLICKED, (void *)file_tmp_inf->new_dir_path);

    // 在list_btn上创建按钮
    lv_obj_t * btn = lv_btn_create(list_btn);
    lv_obj_set_size(btn, 70, 30);
    lv_obj_align_to(btn, list_btn, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_obj_t * lab = lv_label_create(btn);
    lv_obj_set_style_text_font(lab, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    // lv_label_set_long_mode(lab, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(lab, 50);
    lv_obj_set_height(lab, 30);
    lv_label_set_text(lab, "上传");
    lv_obj_set_pos(lab, -5, -3);
    // 为上传按钮添加事件回调
    lv_obj_add_event_cb(btn, upload_btn_press_task, LV_EVENT_CLICKED, file_tmp_inf);

    // lv_obj_set_pos(list_btn, 0, abs_y);

    // lv_obj_t * label = lv_label_create(list_btn);

    // lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // lv_obj_set_width(label, 50);

    // lv_label_set_text(label, btn_text);
    // lv_obj_center(label);

    return true;
}

void file_btn_press_task(lv_event_t * e)
{
    struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    printf("click的是: %s ! \n", click_tmp_inf->new_dir_path);

    if((strstr(click_tmp_inf->new_dir_path, ".jpg")) || (strstr(click_tmp_inf->new_dir_path, ".png"))) {
        printf("点击的是图片文件!\n");
        // 清除之前little_windows的旧控件
        //  lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

        // 创建右边的新画布覆盖
        lv_obj_t * new_little_windows = lv_obj_create(click_tmp_inf->inf_heap->main_windows);
        lv_obj_set_size(new_little_windows, 800, 480);
        lv_obj_set_pos(new_little_windows, 0, 0);

        printf("new little windows!\n");
        file_show_img(new_little_windows, click_tmp_inf);
    }

    if(strstr(click_tmp_inf->new_dir_path, ".gif")) {
        printf("点击的是gif文件!\n");
        // 清除之前little_windows的旧控件
        //  lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

        // 创建右边的新画布覆盖
        lv_obj_t * new_little_windows = lv_obj_create(click_tmp_inf->inf_heap->main_windows);
        lv_obj_set_size(new_little_windows, 800, 480);
        lv_obj_set_pos(new_little_windows, 0, 0);

        printf("GIF: clear little windows!\n");
        file_show_gif(new_little_windows, click_tmp_inf);
    }

    return;
}

bool file_show_img(lv_obj_t * new_little_windows, struct tmp_btn_touch_inf * click_tmp_inf)
{
    printf("即将显示图片loading······ \n");
    // 清除之前little_windows的旧控件
    //  lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

    char * img_path              = click_tmp_inf->new_dir_path;
    char final_img_path[256 * 2] = "S:";
    sprintf(final_img_path, "%s%s", final_img_path, img_path);
    printf("final_img_path: %s \n", final_img_path);
    lv_obj_t * img_obj = lv_img_create(new_little_windows);

    // 居中
    lv_img_set_src(img_obj, final_img_path);
    lv_obj_center(img_obj);

    pic_back_to_file(new_little_windows);

    img_path = NULL;
    return true;
}

bool file_show_gif(lv_obj_t * new_little_windows, struct tmp_btn_touch_inf * click_tmp_inf)
{
    printf("即将显示图片loading······ \n");
    // 清除之前little_windows的旧控件
    //  lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

    char * gif_path              = click_tmp_inf->new_dir_path;
    char final_gif_path[256 * 2] = "S:";
    sprintf(final_gif_path, "%s%s", final_gif_path, gif_path);
    printf("final_gif_path: %s \n", gif_path);
    lv_obj_t * gif_obj = lv_gif_create(new_little_windows);

    // 居中
    lv_gif_set_src(gif_obj, final_gif_path);
    lv_obj_center(gif_obj);

    pic_back_to_file(new_little_windows);

    gif_path = NULL;
    return true;
}

bool pic_back_to_file(lv_obj_t * new_little_windows)
{
    lv_obj_t * close_btn = lv_btn_create(new_little_windows);
    lv_obj_set_size(close_btn, 30, 30);
    lv_obj_set_pos(close_btn, 720, 0);

    lv_obj_t * close_label = lv_label_create(close_btn);
    lv_label_set_text(close_label, "X");
    lv_obj_center(close_label);

    lv_obj_add_event_cb(close_btn, close_windows_task, LV_EVENT_CLICKED, new_little_windows);

    return true;
}

void close_windows_task(lv_event_t * e)
{
    // struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    // printf("click的是: %s ! \n", click_tmp_inf->new_dir_path);

    printf("关闭new_little_windows!\n");
    // 删除 new_little_windows
    lv_obj_del(e->user_data);
    printf("关闭成功 !\n");

    // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

    return;
}

#include "../../inc/client.h"

// 显示文件列表
bool Show_File_List(char * search_path, P_DVI inf_heap)
{
    printf("Show_File_List \n");
    // P_DVI inf_heap = inf_heap;

    // 去除网盘
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }
    // free(inf_heap->sever_document);

    printf("Show_File_List ----- 1 \n");

    // 去除天气界面
    if(inf_heap->weather_info_windows != NULL) {
        lv_obj_del(inf_heap->weather_info_windows);
        inf_heap->weather_info_windows = NULL; // 防止悬挂指针
    }

    // 刷新本地
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
    
    if(current_label != NULL)
    {
        lv_obj_del(current_label);
        current_label = NULL;
    }
    current_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(current_label, "本地");
    lv_obj_set_pos(current_label, 10, 450);
    lv_obj_set_style_text_font(current_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);

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

#include "main.h"

// 检查并创建web_disk文件夹
// 该函数在服务器启动时调用，确保 web_disk 文件夹存在，如果不存在，则创建该文件夹
void check_and_create_web_disk()
{
    struct stat st = {0};
    if (stat(WEB_DISK_DIR, &st) == -1)
    {
        // 如果 web_disk 文件夹不存在，则创建该目录
        mkdir(WEB_DISK_DIR, 0700); // 创建web_disk目录，权限为 0700（仅所有者可读写）
        log_message("web_disk directory created.");
    }
}

// 该函数由独立线程执行，接收客户端传送的文件并保存到 web_disk 目录
// 异步文件上传处理函数（带有应答机制）
// void *file_upload_handler(void *arg) {
//     int client_sock = *(int *)arg;
//     char filename[BUFFER_SIZE];
//     ssize_t bytes_received;
//     printf("文件上传处理线程启动。11111111111\n");
//     // 1. 接收文件名长度
//     size_t file_name_len;
//     bytes_received = recv(client_sock, &file_name_len, sizeof(file_name_len), 0);
//     if (bytes_received <= 0) {
//         printf("接收文件名长度失败。\n");
//         close(client_sock);
//         return NULL;
//     }
//     printf("文件上传处理线程启动。22222222222222222222222\n");
//     // 发送确认应答
//     if (send(client_sock, "ACK", strlen("ACK"), 0) <= 0) {
//         printf("发送确认应答失败。\n");
//         close(client_sock);
//         return NULL;
//     }

//     // 2. 接收文件名
//     bytes_received = recv(client_sock, filename, file_name_len, 0);
//     if (bytes_received <= 0) {
//         printf("接收文件名失败。\n");
//         close(client_sock);
//         return NULL;
//     }
//     filename[file_name_len] = '\0'; // 确保文件名以null结尾

//     // 发送确认应答
//     if (send(client_sock, "ACK", strlen("ACK"), 0) <= 0) {
//         printf("发送确认应答失败。\n");
//         close(client_sock);
//         return NULL;
//     }

//     // 拼接文件路径
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", WEB_DISK_DIR, filename);

//     // 打开文件以写入
//     FILE *file = fopen(filepath, "wb");
//     if (!file) {
//         perror("无法创建文件");
//         close(client_sock);
//         return NULL;
//     }

//     // 3. 接收文件数据
//     char buffer[BUFFER_SIZE];
//     while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
//         fwrite(buffer, 1, bytes_received, file);
//         // 发送确认应答，确保客户端知道这部分数据已接收
//         if (send(client_sock, "ACK", strlen("ACK"), 0) <= 0) {
//             printf("发送确认应答失败。\n");
//             break;
//         }
//     }

//     fclose(file);
//     close(client_sock);
//     printf("文件 %s 已成功上传并保存到 %s\n", filename, filepath);
//     return NULL;
// }


// 文件上传操作的主函数
// 将上传任务分配给独立线程处理，防止阻塞主线程
void handle_file_upload(int client_sock, const char *file_name)
{
    // pthread_t upload_thread;
    // // 在这里启动新的线程处理上传
    // pthread_create(&upload_thread, NULL, file_upload_handler, &client_sock);
    // pthread_detach(upload_thread); // 使线程分离，不需要主线程等待它结束
    char file_path[BUFFER_SIZE];
    snprintf(file_path, sizeof(file_path), "%s/%s", WEB_DISK_DIR, file_name);
    printf ("文件路径：%s------------\n", file_path);
    // 检查文件是否已经存在
    if (access(file_path, F_OK) == 0)
    {
        // 如果文件已经存在，返回错误信息
        send(client_sock, "FILE_ALREADY_EXISTS", strlen("FILE_ALREADY_EXISTS"), 0);
        return;
    }
    printf("准备接收文件 %s------------\n", file_name);
    // 发送准备接收的信号
    // send(client_sock, "READY_TO_RECEIVE", strlen("READY_TO_RECEIVE"), 0);

    printf("文件 %s 准备接收------\n", file_name);
    int file_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (file_fd < 0)
    {
        perror("无法打开文件进行写入");
        send(client_sock, "无法创建文件", strlen("无法创建文件"), 0);
        return;
    }
    printf("文件 %s 准备写入------\n", file_name);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    printf("文件 %s 准备接收**********\n", file_name);
    // 循环接收来自客户端的文件内容并写入服务器文件
    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) > 0)
    {
        printf("文件 %s 接收中----------------------\n", file_name);
        if (write(file_fd, buffer, bytes_received) != bytes_received)
        {
            perror("文件写入失败");
            send(client_sock, "文件写入失败", strlen("文件写入失败"), 0);
            close(file_fd);
            return;
        }
    }
    printf("文件 %s 接收完成----------------------\n", file_name);
    if (bytes_received < 0)
    {
        perror("文件接收失败");
        send(client_sock, "文件接收失败", strlen("文件接收失败"), 0);
    }
    else
    {
        printf("文件 '%s' 已成功接收并保存到服务器\n", file_name);
        send(client_sock, "文件上传成功", strlen("文件上传成功"), 0);
        printf("文件上传exit\n");
    }

    close(file_fd);
}

// 文件下载处理函数
// 该函数从 web_disk 目录读取文件，并将文件内容发送给客户端
void handle_file_download(int client_sock, const char *file_name)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char file_path[BUFFER_SIZE];

    printf("准备下载文件 %s\n", file_name);
    // 设置要下载的文件的路径
    snprintf(file_path, sizeof(file_path), "%s/%s", WEB_DISK_DIR, file_name);
    printf("文件路径：%s\n", file_path);
    
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        perror("无法打开文件");
        close(client_sock);
        return;
    }
    printf("文件 %s 已打开\n", file_name);
    
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("文件大小：%zu\n", file_size);

    // 发送文件大小给客户端，确保发送完整
    if (send(client_sock, &file_size, sizeof(file_size), 0) != sizeof(file_size)) {
        perror("Failed to send file size");
        fclose(file);
        close(client_sock);
        return;
    }
    printf("文件大小已发送\n");

    // 等待客户端确认收到文件大小
    char ack[10];
    if (recv(client_sock, ack, sizeof(ack), 0) <= 0 || strcmp(ack, "READY") != 0) {
        printf("客户端未确认文件大小\n");
        fclose(file);
        close(client_sock);
        return;
    }

    size_t total_sent = 0;

    // 读取文件数据并发送给客户端
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t bytes_left = bytes_read;
        char *buffer_ptr = buffer;

        // 确保将所有字节发送出去
        while (bytes_left > 0) {
            ssize_t bytes_sent = send(client_sock, buffer_ptr, bytes_left, 0);
            if (bytes_sent <= 0) {
                perror("Failed to send data");
                fclose(file);
                close(client_sock);
                return;
            }

            bytes_left -= bytes_sent;
            buffer_ptr += bytes_sent;
            total_sent += bytes_sent;
        }

        printf("已发送 %zu / %zu 字节\n", total_sent, file_size);
    }

    fclose(file);
    close(client_sock);  // 关闭连接通知客户端传输完毕
    printf("文件 %s 已成功发送给客户端\n", file_name);
}

// 新增：发送文件列表函数
int send_file_list(int client_socket)
{
    DIR *dir;
    struct dirent *entry;
    char file_list[BUFFER_SIZE] = ""; // 用于存储文件列表
    char temp[256];

    printf("准备发送文件列表\n");
    // 打开目录
    dir = opendir(WEB_DISK_DIR);
    if (dir == NULL)
    {
        perror("打开目录失败");
        send(client_socket, "无法访问文件目录", strlen("无法访问文件目录"), 0);
        return -1;
    }
    printf("文件列表准备发送\n");
    // 读取目录中的文件
    while ((entry = readdir(dir)) != NULL)
    {
        // 忽略 "." 和 ".." 目录
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(temp, sizeof(temp), "%s\n", entry->d_name);                 // 格式化文件名
            strncat(file_list, temp, sizeof(file_list) - strlen(file_list) - 1); // 将文件名添加到列表
        }
    }
    closedir(dir);

    printf("-----------------\n");
    // 发送文件列表给客户端
    if (strlen(file_list) > 0)
    {
        printf("发送文件列表：%s\n", file_list);
        send(client_socket, file_list, strlen(file_list), 0);
    }
    else
    {
        send(client_socket, "目录为空", strlen("目录为空"), 0);
    }
}

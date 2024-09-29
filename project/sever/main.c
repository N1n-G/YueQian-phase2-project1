#include "main.h"

// 全局变量初始化
client_node_t *client_list = NULL;
task_queue_t *task_queue;
pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_rwlock_t client_list_lock;

// 初始化服务器函数
// 该函数初始化线程池、任务队列、检查 user_information 和 web_disk 目录是否存在，并写入日志
void init_server()
{
    init_client_list_lock();                   // 初始化客户端链表的读写锁
    task_queue = task_queue_init(MAX_CLIENTS); // 初始化任务队列
    check_and_create_web_disk();               // 检查并创建 web_disk 目录，用于存储上传/下载文件
    check_and_create_user_information_dir();   // 检查并创建 user_information 目录，用于存储用户信息文件
    log_message("Server initialized.");        // 记录服务器初始化日志
}

// 处理客户端消息的主函数
// 该函数会根据客户端的不同请求（上传、下载、登录、注册等）执行相应的操作
void handle_client(int client_sock)
{
    char client_message[BUFFER_SIZE]; // 用于存储客户端消息
    int message_len;

    // 循环接收客户端消息并处理
    while ((message_len = recv(client_sock, client_message, sizeof(client_message), 0)) > 0)
    {
        client_message[message_len] = '\0'; // 确保消息以null结尾，防止乱码
        printf("Client message: %s\n", client_message);

        // 处理文件上传请求
        if (strncmp(client_message, "upload:", 7) == 0)
        {
            char *upload_file_name = strtok(client_message + 7, ":");
            printf("准备接收文件: %s\n", upload_file_name);

            ssize_t bytes_sent = send(client_sock, "READY_TO_RECEIVE", strlen("READY_TO_RECEIVE"), 0);
            if (bytes_sent < 0) {
                perror("发送确认应答失败");
                close(client_sock);
                return NULL;
            } else {
                printf("确认应答已发送，发送字节数：%ld\n", bytes_sent);
            }
            
            handle_file_upload(client_sock, upload_file_name); // 调用接收文件的函数
        }
        // 处理文件下载请求
        else if (strncmp(client_message, "download:", 9) == 0)
        {
            char *download_file_name = strtok(client_message + 9, ":");
            printf("准备下载文件: %s\n", download_file_name);
            handle_file_download(client_sock, download_file_name);
        }
        // 处理登录请求
        else if (strncmp(client_message, "login:", 6) == 0)
        {
            printf("----进入login的请求----\n");
            // char *user_inf = strtok(client_message + 6, " ");
            // printf("用户信息串为: %s\n",user_inf);
            char *username = strtok(client_message + 6, " ");
            printf("用户名为: %s\n",username);
            char *password = strtok(NULL, ":");
            printf("密码串为: %s\n",password);

            printf("----进入login的账号密码比对----\n");
            if (validate_login(username, password))
            {
                printf ("----账号密码比对成功----\n");
                send(client_sock, "登录成功！", 17, 0);
            }

            else
            {
                printf ("----账号密码比对失败----\n");
                send(client_sock, "登录失败！", 13, 0);
            }
        }
        // 处理注册请求
        else if (strncmp(client_message, "register:", 9) == 0)
        {
            printf("----进入register请求----\n");
            char *username = strtok(client_message + 9, " ");
            printf("用户名为: %s\n",username);
            char *password = strtok(NULL, ":");
            printf("密码串为: %s\n",password);
            
            printf("----进入register的账号密码比对----\n");
            if (register_account(username, password))
            {
                send(client_sock, "注册成功！", 24, 0);
            }
            else
            {
                send(client_sock, "注册失败！", 20, 0);
            }
        }
        // 处理客户端注销/退出
        else if (strcmp(client_message, "logout") == 0)
        {
            remove_client_from_list(client_sock);
            close(client_sock); // 关闭客户端连接
            return;
        }
        else if (strcmp(client_message, "list") == 0) // 处理文件列表命令
        {
            send_file_list(client_sock); // 调用函数发送文件列表
        }
        // else
        // {
        //     send(client_sock, "无效的命令！", strlen("无效的命令！"), 0); // 处理未知命令
        // }
    }

    // 检测客户端断开连接或接收失败
    if (message_len == 0)
    {
        printf("Client disconnected.\n");
        remove_client_from_list(client_sock); // 从链表中移除客户端信息
        close(client_sock);
    }
    else if (message_len == -1)
    {
        perror(" Recv 接收失败 ");
    }
}

// 工作线程函数
// 从任务队列中取出任务并处理客户端请求
void *worker_thread(void *arg)
{
    while (1)
    {
        thread_task_t *task = task_queue_get(task_queue); // 从任务队列中获取任务
        handle_client(task->client_sock);                 // 处理客户端请求
        free(task);                                       // 释放任务结构体
    }
    return NULL;
}

// 服务器主函数
// 创建服务器套接字，监听客户端连接，使用线程池并发处理多个客户端请求
int main()
{
    init_server(); // 初始化服务器

    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));

    char client_ip[INET_ADDRSTRLEN];

    // 创建线程池，每个线程从任务队列中取任务处理
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, worker_thread, NULL);
    }

    // 创建服务器端套接字
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("服务器套接字创建失败 \n");
        return 1;
    }
    printf("服务器套接字创建成功 \n");
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVER_PORT);

    // 绑定套接字到端口
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("绑定失败. Error");
        return 1;
    }
    printf("套接字绑定端口完成\n");

    // 监听客户端连接
    if (listen(socket_desc, MAX_CLIENTS) == -1) {
        perror("监听失败");
        close(socket_desc);
        return -1;
    }
    printf("Waiting for client connections...\n");

    c = sizeof(struct sockaddr_in);
    // 循环接受客户端连接
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)) >= 0)
    {
        printf("进入accept等待客户端连接\n");
        inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN); // 获取客户端IP地址
        printf("接受来自IP的连接: %s\n", client_ip);

        // 添加客户端到链表
        add_client_to_list(client_sock, client_ip);

        // 创建新任务并将其添加到任务队列
        thread_task_t *new_task = malloc(sizeof(thread_task_t));
        new_task->client_sock = client_sock;
        add_task_to_queue(task_queue, new_task);

        print_client_list(); // 打印当前已连接的客户端列表
    }

    if (client_sock < 0)
    {
        perror(" Accept 失败 ");
        return 1;
    }
    printf("服务器已close\n");
    close(socket_desc);

    return 0;
}

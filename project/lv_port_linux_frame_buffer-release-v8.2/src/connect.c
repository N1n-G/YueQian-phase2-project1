#include "../inc/login_register.h"


int client_socket; // 套接字全局变量，用于在按钮回调中发送数据到服务器

// 设置套接字为非阻塞模式
void set_socket_nonblocking(int socket)
{
    int flags = fcntl(socket, F_GETFL, 0);
    if(flags == -1) 
    {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    flags |= O_NONBLOCK;
    if(fcntl(socket, F_SETFL, flags) == -1) 
    {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
}


// 初始化客户端链表
void init_client_list()
{
    client_list = (P_CL)calloc(1,sizeof(CL));
    if(client_list == NULL)
    {
        perror("malloc failed \n");
        exit(EXIT_FAILURE);
    }
    client_list->head = NULL;
    pthread_mutex_init(&client_list->mutex, NULL);
}



// 连接服务器
int connect_to_server()
{
    // 创建套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1) 
    {
        perror("socket error \n");
        exit(EXIT_FAILURE);
    }

    // 配置服务器地址
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    // 读取IP地址
    char server_inf[50];
    FILE * config_fp = fopen("/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/lib/config.txt", "r");
    if(config_fp == NULL) 
    {
        perror("无法打开配置文件\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(config_fp, "%s", server_inf); // 从配置文件读取IP地址
    fclose(config_fp);

    char server_ip[50];
    int server_port;
    
        // 分割IP和端口
    if(sscanf(server_inf, "%49[^:]:%d", server_ip, &server_port) != 2) 
    {
        perror("配置文件格式错误\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_port = htons(server_port); // 将端口转换为网络字节序
    
    // 将IP地址转换为网络字节序
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) 
    {
        perror("无效地址或地址不支持\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // 尝试连接服务器
    if(connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        perror("连接失败\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("成功连接到服务器,服务器地址为: %s:%d\n", server_ip, server_port);

    // set_socket_nonblocking(client_socket); // 设置套接字为非阻塞模式

    add_client(client_list, client_socket, server_ip);

    return client_socket;
}


// 添加客户端到链表
void add_client(P_CL client_list, int client_fd, const char *client_ip) 
{
    P_CN new_node = (P_CN)malloc(sizeof(CN));
    if (!new_node) 
    {
        perror("malloc failed");
        return;
    }
    
    new_node->client_fd = client_fd;
    strncpy(new_node->client_ip, client_ip, INET_ADDRSTRLEN);
    new_node->next = NULL;
    new_node->prev = NULL;

    pthread_mutex_lock(&client_list->mutex);
    if (client_list->head == NULL) 
    {
        client_list->head = new_node;
    } 
    else 
    {
        new_node->next = client_list->head;
        client_list->head->prev = new_node;
        client_list->head = new_node;
    }
    pthread_mutex_unlock(&client_list->mutex);
}


void handle_client_disconnect(int client_fd) 
{
    remove_client(client_list, client_fd);  // 从链表中删除客户端
    close(client_fd);  // 关闭套接字
}


// 从链表中删除客户端
void remove_client(P_CL client_list, int client_fd) 
{
    pthread_mutex_lock(&client_list->mutex);
    P_CN current = client_list->head;
    while (current != NULL) 
    {
        if (current->client_fd == client_fd) 
        {
            if (current->prev) 
            {
                current->prev->next = current->next;
            } 
            else 
            {
                client_list->head = current->next;
            }
            
            if (current->next) 
            {
                current->next->prev = current->prev;
            }
            free(current);
            break;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&client_list->mutex);
}


// 查找客户端
P_CN find_client(P_CL client_list, int client_fd) 
{
    pthread_mutex_lock(&client_list->mutex);
    P_CN current = client_list->head;
    while (current != NULL) 
    {
        if (current->client_fd == client_fd) 
        {
            pthread_mutex_unlock(&client_list->mutex);
            return current;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&client_list->mutex);
    return NULL;
}


// 清空客户端链表
void clear_client_list(P_CL client_list) 
{
    pthread_mutex_lock(&client_list->mutex);
    P_CN current = client_list->head;
    while (current != NULL) 
    {
        P_CN temp = current;
        current = current->next;
        free(temp);
    }
    client_list->head = NULL;
    pthread_mutex_unlock(&client_list->mutex);
}


// 销毁互斥锁
void destroy_client_list(P_CL client_list) 
{
    pthread_mutex_destroy(&client_list->mutex);
}


// 发送登录请求给服务器
void send_request_to_server(const char * command, const char * username, const char * password) 
{
    char buffer[BUF_SIZE];
    snprintf(buffer, BUF_SIZE, "%s %s %s", command, username, password);
    printf("此时buffer发送的是: %s\n", buffer);
    if(send(client_socket, buffer, strlen(buffer), 0) == -1) 
    {
        perror("发送失败！\n");
        return;
    }

    // 创建一个定时器，每隔 100ms 轮询服务器的响应
    lv_timer_t * timer = lv_timer_create(poll_server_response, 100, NULL);
}


// 定时器函数，轮询服务器响应
void poll_server_response(lv_timer_t * timer)
{
    char buffer[BUF_SIZE];
    int n = recv(client_socket, buffer, BUF_SIZE, 0);
    if(n > 0) 
    {
        buffer[n] = '\0'; // 确保缓冲区末尾为 NULL 字符
        printf("服务器响应: %s\n", buffer);

        // 处理服务器的响应
        // 登录
        if(strcmp(buffer, "登录成功！") == 0) 
        {
            // lv_obj_add_flag(login_error_label, LV_OBJ_FLAG_HIDDEN); // 隐藏错误提示
            printf("登录成功\n");
            // sleep(1);
            
            if(!(Dir_View_Init_Windows()))
            {
                printf("主页面控件初始化失败!\n");
                return -1;
            }
            
            // P_DVI inf_heap = Dir_View_Init_Windows();
            // if(inf_heap == (P_DVI)-1) {
            //     printf("初始化失败！\n");
            //     return -1;
            // }

            // if(!Show_File_List(DEFAULET_PATH, inf_heap)) {
            //     printf("显示文件列表失败！\n");
            //     return -1;
            // }

        } 
        else if(strcmp(buffer, "登录失败！") == 0) 
        {
            printf("登录失败\n");
            show_error("登录失败！", login_error_label);
        }
        // 注册
        else if(strcmp(buffer, "注册成功！") == 0) 
        {
            printf("注册成功\n");
            // lv_obj_add_flag(register_error_label, LV_OBJ_FLAG_HIDDEN); // 隐藏错误提示
            sleep(1);
        }  
        else if(strcmp(buffer, "注册失败！") == 0) 
        {
            show_error("注册失败!", register_error_label);
            printf("注册失败\n");
        } 

        // 停止定时器
        lv_timer_del(timer);
    } 
    else if(n == 0) 
    {
        // 连接已关闭
        printf("服务器关闭连接\n");
        lv_timer_del(timer);
    } 
    else 
    {
        // 如果没有数据可读，recv 会返回 -1，并且 errno 为 EWOULDBLOCK 或 EAGAIN
        if(errno != EWOULDBLOCK && errno != EAGAIN) 
        {
            perror("recv 错误");
            lv_timer_del(timer);
        }
        // 如果是 EWOULDBLOCK 或 EAGAIN，表示暂时没有数据可读，继续等待
    }
}

// 显示错误提示
void show_error(const char * message, lv_obj_t * error_label)
{
    
    // lv_label_set_text(error_label, message);
    printf("show_error\n");
    // lv_obj_clear_flag(error_label, LV_OBJ_FLAG_HIDDEN); // 显示错误标签
    printf("-------------\n");
    lv_refr_now(NULL);                                  // 强制刷新当前屏幕
}

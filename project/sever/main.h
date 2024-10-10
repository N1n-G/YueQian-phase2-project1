#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <dirent.h> // 新增：用于目录操作
#include <fcntl.h>  // 新增：用于文件操作
#include <sys/socket.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

#include "cJSON.h"  // 天气

#include <bits/pthreadtypes.h>

#define MAX_CLIENTS 10
#define THREAD_POOL_SIZE 5
#define BUFFER_SIZE 10240
#define SERVER_PORT 8888
#define WEB_DISK_DIR "web_disk/" // 定义保存文件的路径


// 链表节点结构，保存客户端的 IP 和 socket 信息
typedef struct client_node {
    int socket;
    char ip_address[INET_ADDRSTRLEN];
    struct client_node *next;
} client_node_t;

// 任务结构体，用于线程池任务队列
typedef struct {
    int client_sock;
} thread_task_t;

// 任务队列结构体（循环队列）
typedef struct {
    int front;
    int rear;
    int size;
    int capacity;
    thread_task_t **tasks;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} task_queue_t;

// 全局变量
extern pthread_rwlock_t client_list_lock;
extern client_node_t *client_list;
extern task_queue_t *task_queue;
extern pthread_t thread_pool[THREAD_POOL_SIZE];

int send_file_list(int client_socket);

// 函数声明
void add_client_to_list(int client_sock, char *ip_address);
void remove_client_from_list(int client_sock);
void print_client_list();
void add_task_to_queue(task_queue_t *queue, thread_task_t *task);
thread_task_t *task_queue_get(task_queue_t *queue);
task_queue_t *task_queue_init(int capacity);
void handle_client(int client_sock);
void *worker_thread(void *arg);
void handle_file_upload(int client_sock, const char *file_name);
void handle_file_download(int client_sock, const char *file_name);
int register_account(const char *username, const char *password);
int validate_login(const char *username, const char *password);
int delete_account(const char *username, const char *password);
void log_message(const char *message);

#endif // MAIN_H

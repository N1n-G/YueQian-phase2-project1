#include "main.h"

// 初始化读写锁
pthread_rwlock_t client_list_lock;

void init_client_list_lock() {
    pthread_rwlock_init(&client_list_lock, NULL);
}

// 添加客户端时使用写锁
void add_client_to_list(int client_sock, char *ip_address) {
    client_node_t *new_client = malloc(sizeof(client_node_t));
    new_client->socket = client_sock;
    strncpy(new_client->ip_address, ip_address, INET_ADDRSTRLEN);
    new_client->next = NULL;

    pthread_rwlock_wrlock(&client_list_lock);  // 使用写锁
    if (client_list == NULL) {
        client_list = new_client;
    } else {
        client_node_t *temp = client_list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_client;
    }
    pthread_rwlock_unlock(&client_list_lock);  // 解锁
    printf("客户端IP: %s 已添加进客户端列表.\n", ip_address);
}

// 删除客户端时使用写锁
void remove_client_from_list(int client_sock) {
    pthread_rwlock_wrlock(&client_list_lock);  // 使用写锁
    client_node_t *temp = client_list;
    client_node_t *prev = NULL;

    while (temp != NULL) {
        if (temp->socket == client_sock) {
            if (prev == NULL) {
                client_list = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    pthread_rwlock_unlock(&client_list_lock);  // 解锁
}

// 获取客户端信息时使用读锁
void print_client_list() {
    pthread_rwlock_rdlock(&client_list_lock);  // 使用读锁
    client_node_t *temp = client_list;
    printf("客户端正常连接:\n");
    while (temp != NULL) {
        printf("客户端 IP: %s, 套接字: %d\n", temp->ip_address, temp->socket);
        temp = temp->next;
    }
    pthread_rwlock_unlock(&client_list_lock);  // 解锁
}

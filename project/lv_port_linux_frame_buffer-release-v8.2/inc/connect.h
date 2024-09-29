#ifndef CONNECT_H
#define CONNECT_H

#include "client.h"

int client_socket; // 套接字全局变量，用于在按钮回调中发送数据到服务器

void init_client_list();
void set_socket_nonblocking(int socket);
void add_client(P_CL client_list, int client_fd, const char *client_ip);
void handle_client_disconnect(int client_fd);
void remove_client(P_CL client_list, int client_fd);
P_CN find_client(P_CL client_list, int client_fd);
void clear_client_list(P_CL client_list);
void destroy_client_list(P_CL client_list);
void send_request_to_server(const char * command, const char * username, const char * password);
void poll_server_response(lv_timer_t * timer);

#endif
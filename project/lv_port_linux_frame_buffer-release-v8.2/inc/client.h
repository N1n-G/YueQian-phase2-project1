#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../lvgl/demos/lv_demos.h"
#include "../lv_drivers/display/fbdev.h"
#include "../lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <linux/input.h>
#include <stdint.h>
#include <strings.h>
#include <semaphore.h>
#include <netdb.h>
#include <sys/select.h>

#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

// #include "weather.h"
#include "cJSON.h"

#include "../lvgl/lvgl.h"

#define DEFAULET_PATH "/"

LV_FONT_DECLARE(source_han_sans_cn_normal_2);
LV_FONT_DECLARE(source_han_sans_cn_normal_22);
// LV_FONT_DECLARE(source_han_sans_cn_normal_24);
LV_FONT_DECLARE(lv_font_SiYuanRouHei_Regular_16_cjk);

LV_FONT_DECLARE(lv_font_simsun_16_cjk);

/**************************** project ****************************/

#define BUF_SIZE 10240
#define DOWNLOAD_PATH "/home/downloads/"
#define MAX_SELECTED_FILES 100 // 最多选中的文件数量

lv_obj_t * selected_file_btns[MAX_SELECTED_FILES]; // 选中的文件按钮数组

#define MAX_CLIENTS 100
static char online_clients[MAX_CLIENTS][BUF_SIZE]; // 存放用户名和IP
static int num_online_clients = 0;                 // 在线客户端数目

lv_obj_t * current_label;

// 结构体传递文件名给线程
typedef struct
{
    char file_name[BUF_SIZE];
} download_task_t;

typedef struct node
{
    char data[256];
    struct node * next;
} Node;

// 链表结点结构，保存客户端信息
typedef struct client_node
{
    int client_fd;                   // 客户端套接字
    char client_ip[INET_ADDRSTRLEN]; // 客户端的IP地址
    char username[50];
    struct client_node *next, *prev; // 双向链表
} CN, *P_CN;

typedef struct client_list
{
    P_CN head;             // 链表头节点
    pthread_mutex_t mutex; // 互斥锁
} CL, *P_CL;

P_CL client_list; // 全局链表

// 文件信息结构体
typedef struct file_info
{
    char name[256];
    long size;
    char creation_time[256];
} FI, *P_FI;

// int create_client_socket();
int connect_to_server();
void confirm_download_cb(lv_event_t * e);
void * download_file_thread(void * arg);
void download_file_from_server(const char * file_name);
void show_weather_inf_press_task(void);

bool Index_Page();

// extern void start_animation(lv_obj_t * parent);
// extern void anim_callback(lv_timer_t * timer);
// extern void create_animation(lv_obj_t * parent);

// 页面结构体 ---------------暂时没用
typedef struct page_inf
{
    lv_obj_t * index_page;
    lv_obj_t * login_page;
    lv_obj_t * register_page;
    lv_obj_t * functionality_page;
    // 可以添加更多页面或状态信息
} app_pages_t;

extern app_pages_t app_pages;

// 初始化页面指针
// void init_app_pages() {
//     app_pages.index_page = index_screen;
//     app_pages.login_page = login_screen;
//     app_pages.register_page = register_screen;
//     app_pages.functionality_page = functionality_screen;
// }

// // 切换页面的函数
// void switch_to_page(lv_obj_t *new_page) {
//     lv_scr_load(new_page);
// }

// // 示例按钮事件处理函数
// void btn_event_handler(lv_event_t * e) {
//     lv_obj_t * btn = lv_event_get_target(e);
//     if (btn == login_btn) {
//         switch_to_page(app_pages.login_page);
//     } else if (btn == register_btn) {
//         switch_to_page(app_pages.register_page);
//     } else if (btn == back_to_index_btn) {
//         switch_to_page(app_pages.index_page);
//     } else if (btn == login_success_btn) {
//         switch_to_page(app_pages.functionality_page);
//     } else if (btn == register_success_btn) {
//         switch_to_page(app_pages.index_page);
//     }
// }

/**************************** 以下为本地文件显示 ****************************/

// typedef struct dir_view_inf
// {
//     lv_obj_t * main_windows;
//     lv_obj_t * lv_dir_list;
//     lv_obj_t * lv_little_windows;
//     // 存放链表头
// } DVI, *P_DVI;
typedef struct dir_view_inf
{
    lv_obj_t * main_windows;         // 主画布
    lv_obj_t * sever_document;       // 网盘界面
    lv_obj_t * head_list_windows;    // 主功能目录
    lv_obj_t * weather_windows;      // 天气窗口
    lv_obj_t * weather_info_windows; // 天气详细信息
    lv_obj_t * btn_back_to_index;    // 返回主页按钮
    lv_obj_t * lv_dir_list;          // 列表
    lv_obj_t * lv_little_windows;    // 右边小画布
    // char list_dir_path[256];

    // 存放链表头
    Node * list_head; // 链表头节点，用于存储目录或文件信息
} DVI, *P_DVI;

// struct tmp_btn_touch_inf
// {
//     char new_dir_path[256];
//     P_DVI inf_heap;
//     // 指针域
// };
struct tmp_btn_touch_inf
{
    char new_dir_path[256];
    P_DVI inf_heap;
    // 指针域
    Node * btn_node; // 关联的链表节点
};

bool Dir_View_Init_Windows();
bool show_notice_funtion(char * search_path, P_DVI inf_heap);
void sys_main_page_btn_press_task(lv_event_t * e);
bool show_sever_file_list(char * search_path, P_DVI inf_heap);

// void * upload_file_thread(void * arg);
// void upload_btn_press_task(lv_event_t * e);
// void * download_file_thread(void * arg);
// void download_btn_press_task(lv_event_t * e);

bool Show_File_List(char * search_path, P_DVI inf_heap);
bool show_file_view(P_DVI inf_heap, char * btn_text, struct tmp_btn_touch_inf * file_tmp_inf);
void list_btn_press_task_1(lv_event_t * e);
void file_btn_press_task(lv_event_t * e);
bool file_show_img(lv_obj_t * little_windows, struct tmp_btn_touch_inf * click_tmp_inf);
bool file_show_gif(lv_obj_t * little_windows, struct tmp_btn_touch_inf * click_tmp_inf);
bool pic_back_to_file(lv_obj_t * little_windows);
void close_windows_task(lv_event_t * e);

#endif
#ifndef _SHOW_SOMETHING_DEMO_H_
#define _SHOW_SOMETHING_DEMO_H_
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
#include "../lvgl/lvgl.h"

#define DEFAULET_PATH "/"

extern int EXIT_MASK;

typedef struct bar_demo_inf
{
    pthread_mutex_t mut; // 互斥锁变量
    lv_obj_t * bar;
} SBD, *P_SBD;

lv_obj_t * screen_init_windows();

// 声明一个线程任务函数用来持续的修改进度条的值
void * set_bar_vau(void * arg);

bool show_pic_demo(lv_obj_t * main_windows);

bool button_demo(lv_obj_t * main_windows);

bool bar_demo(P_SBD sbd, lv_obj_t * main_windows);

bool list_demo(lv_obj_t * main_windows);

void list_btn_press_task(lv_event_t * e);

void list_btn_exit(lv_event_t * e);



typedef struct dir_view_inf
{
    lv_obj_t * mian_windows;
    lv_obj_t * lv_dir_list;
    lv_obj_t * lv_little_windows;
    // 存放链表头
} DVI, *P_DVI;

struct tmp_btn_touch_inf
{
    char new_dir_path[256];
    P_DVI inf_heap;
    // 指针域
};

P_DVI dir_view_init_windows();

bool show_file_list(char * search_path,P_DVI inf_heap);
bool show_file_view(P_DVI inf_heap, char * btn_text, int abs_x, int abs_y,struct tmp_btn_touch_inf * file_tmp_inf);
void list_btn_press_task_1(lv_event_t * e);
void file_btn_press_task(lv_event_t * e);
bool file_show_img(lv_obj_t * little_windows, struct tmp_btn_touch_inf * click_tmp_inf);
bool file_show_gif(lv_obj_t * little_windows, struct tmp_btn_touch_inf * click_tmp_inf);
bool pic_back_to_file(lv_obj_t * little_windows);
void close_windows_task(lv_event_t * e);


#endif
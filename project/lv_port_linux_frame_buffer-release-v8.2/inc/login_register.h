#ifndef _LOGIN_REGISTER_H_
#define _LOGIN_REGISTER_H_

#include "keyboard.h"
#include "connect.h"

// #define Register_Page_IMG "S:/mnt/nfs/workspace/round2/lvgl/lv_port_linux_frame_buffer-release-v8.2/my_lvgl_test/res/register_page.png" // 注册页面的图片
// #define Login_Page_IMG "S:/mnt/nfs/workspace/round2/lvgl/lv_port_linux_frame_buffer-release-v8.2/my_lvgl_test/res/login_page.png"   // 登录页面的图片
// #define Log_Out_Page_IMG "S:/mnt/nfs/workspace/round2/lvgl/lv_port_linux_frame_buffer-release-v8.2/my_lvgl_test/res/login_page.png"

static lv_obj_t * register_error_label = NULL;
static lv_obj_t * login_error_label = NULL;
static lv_obj_t * global_textareas[2]; // 全局或静态数组保存用户名和密码输入框的指针
static int history_index = -1; // 栈顶索引，初始为空栈

void Show_Register_Page();
void register_event_cb();

void Show_Login_Page();
void login_event_cb();

void Log_Off();
void log_off_event_cb();
void Exit();
// void show_error(const char * message, lv_obj_t * error_label);

// void push_page_history(lv_obj_t * page);
// void pop_page_history();
// void return_to_previous_page();


#endif
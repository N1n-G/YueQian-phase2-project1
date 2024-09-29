#include "../../inc/login_register.h"

// 首页图片
#define Index_Page_IMG "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/小小格温.jpg"
    
// 首页
bool Index_Page()
{
    printf("---进入系统loading······ \n");

    // 创建主画布
    lv_obj_t * main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0x87CEFA), LV_PART_MAIN);    // 天蓝色

    // 设计图片
    lv_obj_t * img = lv_img_create(main_screen);
    lv_img_set_src(img, Index_Page_IMG);
    lv_obj_set_pos(img, 0, 0);
    // lv_obj_set_align(img, LV_ALIGN_CENTER);

    // 设计"注册"按钮
    lv_obj_t * register_button = lv_btn_create(main_screen);
    lv_obj_t * register_label  = lv_label_create(register_button);
    lv_label_set_text(register_label, "注册");
    // 按钮透明
    // lv_obj_set_style_bg_opa(register_button, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(register_button, lv_color_hex(0x008080), LV_STATE_DEFAULT);   // 按钮浅粉色
    lv_obj_set_style_text_font(register_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_align(register_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_pos(register_button, 600, 125);
    lv_obj_set_size(register_button, 100, 50);
    lv_obj_add_event_cb(register_button, Show_Register_Page, LV_EVENT_CLICKED, NULL);

    // 设计"登录"按钮
    lv_obj_t * login_button = lv_btn_create(main_screen);
    lv_obj_t * login_label  = lv_label_create(login_button);
    lv_label_set_text(login_label, "登录");
    lv_obj_set_style_bg_color(login_button, lv_color_hex(0x008080), LV_STATE_DEFAULT);   // 按钮浅粉色
    lv_obj_set_style_text_font(login_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_align(login_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_pos(login_button, 600, 215);
    lv_obj_set_size(login_button, 100, 50);
    lv_obj_add_event_cb(login_button, Show_Login_Page, LV_EVENT_CLICKED, NULL);

    // 设计"退出"按钮
    lv_obj_t * exit_button = lv_btn_create(main_screen);
    lv_obj_t * exit_label  = lv_label_create(exit_button);
    lv_label_set_text(exit_label, "退出");
    lv_obj_set_style_bg_color(exit_button, lv_color_hex(0xFF0000), LV_STATE_DEFAULT);   // 按钮红色
    lv_obj_set_style_text_font(exit_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(exit_label, lv_color_hex(0x000000), 0);
    lv_obj_align(exit_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_pos(exit_button, 600, 355);
    lv_obj_set_size(exit_button, 100, 50);
    lv_obj_add_event_cb(exit_button, Exit, LV_EVENT_CLICKED, NULL);

    lv_scr_load(main_screen);
    
    return true;
}

// 退出回调
void Exit()
{
    printf("------程序退出------\n");
    close(client_socket);
    // clear_client_list(client_list); // 清理客户端链表
    // destroy_client_list(client_list); // 销毁互斥锁
    exit(0); // 不需要返回 NULL，程序会终止
}

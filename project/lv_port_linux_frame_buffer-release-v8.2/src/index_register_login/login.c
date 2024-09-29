#include "../../inc/login_register.h"

// 登录页面
void Show_Login_Page()
{
    printf("进入登录界面...\n");
    lv_obj_t * current_screen = lv_scr_act();
    // push_page_history(current_screen); // 保存当前页面到历史栈

    lv_obj_t * login_screen = lv_obj_create(NULL);

    lv_obj_t * login_img = lv_img_create(login_screen);
    // lv_img_set_src(login_img, "Login_Page_IMG");
    lv_obj_set_pos(login_img, 0, 40);

    // 登录界面标题
    lv_obj_t * login_title = lv_label_create(login_screen);
    lv_label_set_text(login_title, "LOGIN");
    lv_obj_set_style_text_font(login_title, &lv_font_simsun_16_cjk, LV_FONT_MONTSERRAT_40);
    lv_obj_set_style_text_color(login_title, lv_color_hex(0x0000FF), LV_STATE_DEFAULT); // 字体蓝色
    lv_obj_set_pos(login_title, 375, 45);

    // 用户名标签和输入框
    lv_obj_t * username_label = lv_label_create(login_screen);
    lv_label_set_text(username_label, "名称:");
    lv_obj_set_pos(username_label, 250, 120);
    lv_obj_set_style_text_font(username_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);

    lv_obj_t * username_ta = lv_textarea_create(login_screen);
    lv_obj_set_pos(username_ta, 300, 105);
    lv_obj_set_size(username_ta, 200, 50);
    // lv_textarea_set_placeholder_text(username_ta, "请输入用户名");
    // lv_obj_set_style_text_font(username_ta, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(username_ta, textarea_event_cb, LV_EVENT_CLICKED, NULL);

    // 密码标签和输入框
    lv_obj_t * password_label = lv_label_create(login_screen);
    lv_label_set_text(password_label, "密码:");
    lv_obj_set_pos(password_label, 250, 215);
    lv_obj_set_style_text_font(password_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);

    lv_obj_t * password_ta = lv_textarea_create(login_screen);
    lv_textarea_set_password_mode(password_ta, true);
    lv_obj_set_pos(password_ta, 300, 200);
    lv_obj_set_size(password_ta, 200, 50);
    // lv_textarea_set_placeholder_text(password_ta, "请输入密码");
    // lv_obj_set_style_text_font(password_ta, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(password_ta, textarea_event_cb, LV_EVENT_CLICKED, NULL);

    // 存储输入框的引用到全局数组
    global_textareas[0] = username_ta;
    global_textareas[1] = password_ta;

    // 登录按钮
    lv_obj_t * login_btn = lv_btn_create(login_screen);
    lv_obj_set_style_bg_color(login_btn, lv_color_hex(0x00FF00), 0);
    lv_obj_t * login_label = lv_label_create(login_btn);
    lv_label_set_text(login_label, "确认登录");
    lv_obj_set_style_text_color(login_label, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(login_btn, 270, 305);
    lv_obj_set_size(login_btn, 100, 50);
    lv_obj_align(login_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(login_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(login_btn, login_event_cb, LV_EVENT_CLICKED, NULL);

    // 返回按钮
    lv_obj_t * return_button = lv_btn_create(login_screen);
    lv_obj_set_style_bg_color(return_button, lv_color_hex(0xFF0000), 0);
    lv_obj_t * return_label = lv_label_create(return_button);
    lv_label_set_text(return_label, "返回");
    lv_obj_set_style_text_color(return_label, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(return_button, 420, 305);
    lv_obj_set_size(return_button, 100, 50);
    lv_obj_align(return_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(return_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(return_button, Index_Page, LV_EVENT_CLICKED, NULL);

    // 错误提示标签，默认隐藏
    login_error_label = lv_label_create(login_screen); // 直接在屏幕上创建标签
    lv_label_set_text(login_error_label, "");          // 设置初始文本
    lv_obj_set_pos(login_error_label, 315, 270);
    lv_obj_set_style_text_font(login_error_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(login_error_label, lv_color_hex(0xFF0000), LV_STATE_DEFAULT); // 设置红色文字
    lv_obj_add_flag(login_error_label, LV_OBJ_FLAG_HIDDEN);                                   // 默认隐藏

    lv_scr_load(login_screen);
}


// 登录按钮回调函数
void login_event_cb()
{
    lv_obj_t * username_ta = global_textareas[0];
    lv_obj_t * password_ta = global_textareas[1];

    const char * username = lv_textarea_get_text(username_ta);
    const char * password = lv_textarea_get_text(password_ta);

    // 校验用户名和密码是否为空
    if(strlen(username) == 0 || strlen(password) == 0) 
    {
        // 显示错误信息
        show_error("请输入信息不能为空!", login_error_label);
        return;
    }
    
    printf("此时登录请求的 用户名: %s 密码: %s\n", username, password);
    // 发送登录请求到服务器
    send_request_to_server("login:", username, password);
}


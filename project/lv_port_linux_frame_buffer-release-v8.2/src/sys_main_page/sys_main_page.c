#include "../../inc/weather.h"
// #include "../../inc/color.h"

int EXIT_MASK = 0;
P_DVI inf_heap;
lv_obj_t * time_label;

// 获取当前时间
static void update_time(lv_timer_t * timer)
{
    time_t now;
    struct tm * time_info;
    char buffer[64];

    time(&now);
    time_info = localtime(&now);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", time_info); // 格式化时间为时:分:秒
    lv_label_set_text(time_label, buffer);
}

/**************************** 创建主画布 ****************************/
bool Dir_View_Init_Windows()
{
    inf_heap = (P_DVI)calloc(1, sizeof(DVI));
    if(inf_heap == (P_DVI)NULL) {
        perror("内存申请失败! \n");
        return (P_DVI)-1;
    }
    // strcpy(inf_heap->list_dir_path, DEFAULET_PATH);

    // 创建主窗口
    inf_heap->main_windows = lv_obj_create(NULL);
    // lv_obj_set_style_bg_color(inf_heap->main_windows, lv_color_hex(0x87CEFA), LV_PART_MAIN);    // 天蓝色
    color_gradient(inf_heap->main_windows);

    // 创建时间显示标签
    time_label = lv_label_create(inf_heap->main_windows);
    // lv_obj_align(time_label, LV_ALIGN_BOTTOM_LEFT, 5, -5);
    lv_obj_set_pos(time_label, 10, 80);
    lv_timer_t * timer = lv_timer_create(update_time, 1000, NULL); // 每秒更新时间

    // 首页内容显示
    lv_obj_t * notic_windows = lv_obj_create(inf_heap->main_windows);
    lv_obj_set_size(notic_windows, 450, 380);
    lv_obj_set_pos(notic_windows, 250, 70);
    lv_obj_set_style_bg_opa(notic_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置背景透明
    lv_obj_t * notic_label = lv_label_create(notic_windows);
    lv_label_set_text(notic_label, "欢迎使用");
    lv_obj_set_style_text_font(notic_label, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(notic_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_color(notic_label, lv_color_hex(0xFF0000), LV_STATE_DEFAULT); // 设置红色
    lv_obj_set_pos(notic_label, 150, 130);
    lv_obj_set_style_bg_opa(notic_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置按钮背景透明
    lv_obj_t * head_pic = lv_gif_create(notic_windows);
    lv_gif_set_src(head_pic, "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/Gwen.gif");
    lv_obj_center(head_pic);

    // 显示系统名字
    lv_obj_t * title_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(title_label, "那咋了网盘");
    lv_obj_set_size(title_label, 200, 30);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 50, 10);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFB6C1), LV_STATE_DEFAULT); // 字体浅粉色
    // lv_obj_set_style_text_color(title_label, lv_color_hex(0x0000FF), LV_STATE_DEFAULT); // 字体蓝色
    lv_obj_set_style_text_font(title_label, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);

    // 创建天气小窗
    inf_heap->weather_windows = lv_btn_create(inf_heap->main_windows);
    lv_obj_set_size(inf_heap->weather_windows, 180, 70);
    lv_obj_set_pos(inf_heap->weather_windows, 0, 0);
    lv_obj_set_style_bg_opa(inf_heap->weather_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置按钮背景透明
    lv_obj_add_event_cb(inf_heap->weather_windows, show_weather_inf_press_task, LV_EVENT_CLICKED, NULL);
    lv_obj_t * weather_icon = lv_img_create(inf_heap->weather_windows);
    lv_obj_set_size(weather_icon, 50, 50);
    lv_obj_set_pos(weather_icon, 5, 0);
    lv_img_set_src(weather_icon, "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/icon/sunny_sun_cloud_weather_cloudy_icon_194267.png");
    lv_obj_t * weather_label = lv_label_create(inf_heap->weather_windows);
    lv_obj_set_size(weather_label, 50, 50);
    lv_obj_set_pos(weather_label, 60, 15);
    lv_label_set_text(weather_label, "天气");
    lv_obj_set_style_text_font(weather_label, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);


    // 创建主功能目录
    inf_heap->head_list_windows = lv_list_create(inf_heap->main_windows);
    lv_obj_set_size(inf_heap->head_list_windows, 165, 380);
    lv_obj_set_pos(inf_heap->head_list_windows, 0, 100);
    lv_obj_set_style_bg_opa(inf_heap->head_list_windows, LV_OPA_TRANSP, LV_PART_MAIN); // 设置列表半透明
    // lv_obj_set_style_opa(inf_heap->head_list_windows, LV_OPA_TRANSP, LV_PART_MAIN);  // 设置列表透明
    // lv_obj_set_style_bg_color(inf_heap->head_list_windows, lv_color_hex(0x87CEFA), LV_PART_MAIN);    // 天蓝色

    // 分隔
    lv_obj_t * null_label_0 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_0, " ");
    lv_obj_set_size(null_label_0, 120, 10);
    /************上传************/
    lv_obj_t * main_funtion_btn_0 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_0, 120, 70);
    lv_obj_t * label_0 = lv_label_create(main_funtion_btn_0);
    lv_obj_set_style_text_font(main_funtion_btn_0, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_0, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_0, 50, 25);
    lv_label_set_text(label_0, "首页");
    lv_obj_set_pos(label_0, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_0, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_0, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_0, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_0, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 0);

    // 分隔
    lv_obj_t * null_label_1 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_1, " ");
    lv_obj_set_size(null_label_1, 120, 10);
    /**************网盘************/
    lv_obj_t * main_funtion_btn_1 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_1, 120, 70);
    // lv_obj_t * label_1_icon = lv_label_create(main_funtion_btn_1);
    // lv_obj_set_style_text_font(label_1_icon, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    // lv_obj_set_size(label_1_icon, 25, 25);
    // lv_label_set_text(label_1_icon, "1");
    // lv_obj_set_pos(label_1_icon, 10, 15);
    lv_obj_t * label_1 = lv_label_create(main_funtion_btn_1);
    lv_obj_set_style_text_font(main_funtion_btn_1, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_obj_set_size(label_1, 50, 25);
    lv_label_set_text(label_1, "网盘");
    lv_obj_set_pos(label_1, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_1, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_1, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_1, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_1, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 1);

    // 分隔
    lv_obj_t * null_label_2 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_2, " ");
    lv_obj_set_size(null_label_2, 120, 10);
    /************上传************/
    lv_obj_t * main_funtion_btn_2 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_2, 120, 70);
    lv_obj_t * label_2 = lv_label_create(main_funtion_btn_2);
    lv_obj_set_style_text_font(main_funtion_btn_2, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_2, 50, 25);
    lv_label_set_text(label_2, "本地");
    lv_obj_set_pos(label_2, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_2, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_2, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_2, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_2, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 2);

    // 分隔
    lv_obj_t * null_label_3 = lv_label_create(inf_heap->head_list_windows);
    lv_label_set_text(null_label_3, " ");
    lv_obj_set_size(null_label_3, 120, 10);
    /************传输************/
    lv_obj_t * main_funtion_btn_3 = lv_btn_create(inf_heap->head_list_windows);
    lv_obj_set_size(main_funtion_btn_3, 120, 70);
    lv_obj_t * label_3 = lv_label_create(main_funtion_btn_3);
    lv_obj_set_style_text_font(main_funtion_btn_3, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    lv_label_set_long_mode(label_3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_size(label_3, 50, 25);
    lv_label_set_text(label_3, "传输");
    lv_obj_set_pos(label_3, 18, 15);
    lv_obj_set_style_bg_color(main_funtion_btn_3, lv_color_hex(0x87CEFA), LV_PART_MAIN); // 按钮天蓝色
    lv_obj_set_style_text_color(label_3, lv_color_hex(0x000000), LV_STATE_DEFAULT);      // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_3, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    lv_obj_add_event_cb(main_funtion_btn_3, sys_main_page_btn_press_task, LV_EVENT_CLICKED, 3);

    // // 分隔
    // lv_obj_t * null_label_4 = lv_label_create(inf_heap->head_list_windows);
    // lv_label_set_text(null_label_4, " ");
    // lv_obj_set_size(null_label_4, 120, 10);
    // /************聊天************/
    // lv_obj_t * main_funtion_btn_4 = lv_btn_create(inf_heap->head_list_windows);
    // lv_obj_set_size(main_funtion_btn_4, 120, 70);
    // lv_obj_t * label_4 = lv_label_create(main_funtion_btn_4);
    // lv_obj_set_style_text_font(main_funtion_btn_4, &source_han_sans_cn_normal_22, LV_STATE_DEFAULT);
    // lv_label_set_long_mode(label_4, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // lv_obj_set_size(label_4, 70, 70);
    // lv_label_set_text(label_4, "聊天");
    // lv_obj_set_pos(label_4, LV_ALIGN_CENTER, LV_ALIGN_CENTER);
    // lv_obj_set_style_text_color(label_4, lv_color_hex(0x000000), LV_STATE_DEFAULT);    // 字体黑色
    // lv_obj_set_style_bg_opa(main_funtion_btn_4, LV_OPA_TRANSP, LV_PART_MAIN);   // 设置按钮背景透明
    // // lv_obj_add_event_cb(inf_heap->head_list_windows, list_btn_press_task, LV_EVENT_CLICKED, NULL);

    // 创建左边目录list控件
    // inf_heap->lv_dir_list = lv_list_create(inf_heap->main_windows);
    // lv_obj_set_size(inf_heap->lv_dir_list, 145, 440);
    // lv_obj_set_pos(inf_heap->lv_dir_list, 165, 40);
    // printf("lv_dir_list create success! \n");
    // // 创建右边的小画布
    // inf_heap->lv_little_windows = lv_obj_create(inf_heap->main_windows);
    // lv_obj_set_size(inf_heap->lv_little_windows, 495, 440);
    // lv_obj_set_pos(inf_heap->lv_little_windows, 305, 40);

    lv_scr_load(inf_heap->main_windows);

    return true;
}

// 天气信息按钮回调函数
void show_weather_inf_press_task(void)
{
    // 去除网盘
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }

    // 去除本地
    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }
    
    printf("显示天气信息! \n");
    if (!show_weather_inf(inf_heap)) {
        printf("显示天气信息失败! \n");
        return false;
    }
    // return;
}

// 主控列表按钮回调函数
void sys_main_page_btn_press_task(lv_event_t * e)
{
    int num_btn = (int)lv_event_get_user_data(e);
    switch(num_btn) {
        case 0:

            printf("点击了首页按钮! \n");
            if(!show_notice_funtion(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 1:

            printf("点击了网盘按钮! \n");
            if(!show_sever_file_list(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 2:

            printf("点击了本地按钮! \n");
            if(!Show_File_List(DEFAULET_PATH, inf_heap)) {
                printf("显示文件列表失败! \n");
                return -1;
            }
            break;

        case 3: printf("点击了传输按钮! \n"); break;

        default: break;
    }
}

// 首页按钮函数
bool show_notice_funtion(char * search_path, P_DVI inf_heap)
{
    // 去除网盘
    if(inf_heap->sever_document != NULL) {
        lv_obj_del(inf_heap->sever_document);
        inf_heap->sever_document = NULL; // 防止悬挂指针
    }

    // 去除本地
    if(inf_heap->lv_dir_list != NULL) {
        lv_obj_del(inf_heap->lv_dir_list);
        inf_heap->lv_dir_list = NULL; // 防止悬挂指针
    }
    if(inf_heap->lv_little_windows != NULL) {
        lv_obj_del(inf_heap->lv_little_windows);
        inf_heap->lv_little_windows = NULL; // 防止悬挂指针
    }
    
    // 去除天气界面
    if(inf_heap->weather_info_windows != NULL) {
        lv_obj_del(inf_heap->weather_info_windows);
        inf_heap->weather_info_windows = NULL; // 防止悬挂指针
    }
    
    if(current_label != NULL)
    {
        lv_obj_del(current_label);
        current_label = NULL;
    }
    current_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(current_label, "首页");
    lv_obj_set_pos(current_label, 10, 450);
    lv_obj_set_style_text_font(current_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);

    return true;
}


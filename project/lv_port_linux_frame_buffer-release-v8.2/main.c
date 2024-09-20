
#include "my_lvgl_test/show_something_demo.h"

#define DISP_BUF_SIZE (128 * 1024)

int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res  = 800;
    disp_drv.ver_res  = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb      = evdev_read;
    lv_indev_t * mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);      /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);        /*Connect the image  object to the driver*/

    /*Create a Demo*/
    // lv_demo_widgets();

    /******************************** 以下为自己的代码 ********************************/

    // if(Show_Gif_Demo() == false) {
    //   printf("显示gif图片失败！\n");
    //   return -1;
    // }

    // if(Show_IMG_Demo() == false) {
    //   printf("显示img图片失败！\n");
    //   return -1;
    // }

    // if(button_demo() == false) {
    //   printf("显示按钮失败！\n");
    //   return -1;
    // }

    // if(show_demo() == false) {
    //   printf("屏幕显示失败！\n");
    //   return -1;
    // }


    // P_SBD sbd = (P_SBD)malloc(sizeof(SBD));
    // if(sbd == (P_SBD)NULL)
    // {
    //   perror("malloc error \n");
    //   return false;
    // }
    // memset(sbd, 0, sizeof(SBD));


    // lv_obj_t *main_draw = List_Demo();

    // if(main_draw == false)
    // {
    //   printf("显示页面失败 \n");
    //   return -1;
    // }

    // P_DVI inf_heap = dir_view_init_windows();
    // if(inf_heap == (P_DVI)-1)
    // {
    //   printf("目录浏览例程初始化失败！ \n");
    //   return -1;
    // }

    // show_file_list(DEFAULT_SEARCH_PATH, inf_heap);

    // if(Show_Check_Box_Demo() == false)
    // {
    //   printf("显示复选框失败！\n");
    //   return -1;
    // }

    // if(Show_Slider_Demo() == false)
    // {
    //   printf("显示滑动条失败！\n");
    //   return -1;
    // }

    P_DVI inf_heap = dir_view_init_windows();
    if(inf_heap == (P_DVI)-1) {
        printf("初始化失败！\n");
        return -1;
    }

    if(!show_file_list(DEFAULET_PATH, inf_heap)) {
        printf("显示文件列表失败！\n");
        return -1;
    }

    /******************************** 以上为自己的代码 ********************************/

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        // pthread_mutex_lock(&sbd->mutex);
        lv_timer_handler();
        // pthread_mutex_unlock(&sbd->mutex);

        usleep(5000);
    }

    // 释放内存控件
    // lv_obj_clean(mian_windows);//清除指定的控件中的子控件
    // lv_obj_del(mian_windows); //删除之前的画布

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

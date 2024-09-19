#include "show_something_demo.h"

int EXIT_MASK = 0;

/**************************** 创建主画布 ****************************/
lv_obj_t * screen_init_windows()
{
    lv_obj_t * main_windows = lv_obj_create(NULL);
    lv_obj_clean(main_windows);
    return main_windows;
}

/**************************** 显示图画 ****************************/
bool show_pic_demo(lv_obj_t * main_windows)
{
    printf("即将显示图片loading······ \n");

    // lv_obj_t * gif_obj = lv_gif_create(main_windows);
    // lv_gif_set_src(gif_obj, "S:/mnt/nfs/9_3/pic/流星.gif");
    // lv_obj_align(gif_obj, LV_ALIGN_CENTER, 0, 0);

    // lv_obj_t * img_obj = lv_img_create(main_windows);
    // lv_img_set_src(img_obj, "S:/mnt/nfs/9_3/pic/kun.jpg");
    // lv_obj_align(img_obj, LV_ALIGN_CENTER, 0, 0); // 设置居中

    // lv_obj_t * gif_obj0 = lv_gif_create(main_windows);
    lv_obj_t * img_obj1 = lv_img_create(main_windows);
    // lv_obj_t * gif_obj2 = lv_gif_create(main_windows);
    lv_obj_t * gif_obj3 = lv_gif_create(main_windows);

    // 左垂直居中
    // lv_gif_set_src(gif_obj0, "S:/mnt/nfs/9_3/pic/11.gif");
    // lv_obj_set_align(gif_obj0, LV_ALIGN_LEFT_MID);

    // 居中
    lv_img_set_src(img_obj1, "S:/mnt/nfs/9_3+9_4/pic/22.png");
    lv_obj_set_align(img_obj1, LV_ALIGN_CENTER);

    // 上水平居中
    // lv_gif_set_src(gif_obj2, "S:/mnt/nfs/9_3/pic/Gwen.gif");
    // lv_obj_set_pos(gif_obj2, 340, 0);

    // 左垂直居中
    lv_gif_set_src(gif_obj3, "S:/mnt/nfs/9_3+9_4/pic/11.gif");
    lv_obj_set_align(gif_obj3, LV_ALIGN_RIGHT_MID);

    // lv_obj_t * img_obj = lv_img_create(main_windows);
    // lv_img_set_src(img_obj, "S:/mnt/nfs/9_3/pic/22.png");
    // lv_obj_align(img_obj, LV_ALIGN_CENTER, 0, 0);   // 设置居中

    return true;
}

/**************************** 创建按钮 ****************************/
bool button_demo(lv_obj_t * main_windows)
{
    /**************************** 调用字库 ****************************/
    // LV_FONT_DECLARE(gen_jyuu_gothic_bold_2);      // 思源柔黑
    LV_FONT_DECLARE(source_han_sans_cn_normal_2); // 思源黑体Normal，汉字较多

    lv_obj_t * btn = lv_btn_create(main_windows);

    lv_obj_set_size(btn, 100, 50);
    lv_obj_set_align(btn, LV_ALIGN_BOTTOM_MID);

    lv_obj_t * lab = lv_label_create(btn);

    // lv_obj_set_style_text_font(lab, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    // 在这里设置btn的字体大小，状态为LV_STATE_PRESSED按下状态
    lv_obj_set_style_text_font(btn, &source_han_sans_cn_normal_2, LV_STATE_FOCUSED);

    lv_label_set_long_mode(lab, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(lab, 100);
    lv_obj_set_height(lab, 20);

    lv_label_set_text(lab, "谁家小孩?我带你们打wdnmd nknmn");
    lv_obj_center(lab);

    return true;
}

/**************************** 创建进度条 ****************************/
bool bar_demo(P_SBD sbd, lv_obj_t * main_windows)
{
    if(pthread_mutex_init(&sbd->mut, NULL) != 0) 
    {
        perror("互斥锁初始化失败! \n");
        return false;
    }

    sbd->bar = lv_bar_create(main_windows);

    lv_obj_set_size(sbd->bar, 200, 20);
    lv_bar_set_range(sbd->bar, 0, 100);
    // lv_bar_set_anim_time(bar, 5000);
    // lv_bar_set_value(bar, 30, LV_ANIM_ON);
    lv_obj_set_pos(sbd->bar, 10, 450); // 设置进度条位置

    // 创建动态进度条线程
    pthread_t pid;
    if(pthread_create(&pid, NULL, set_bar_vau, sbd) != 0) 
    {
        perror("创建线程失败! \n");
        return false;
    }

    return true;
}

/**************************** 进度条线程 ****************************/
void * set_bar_vau(void * arg)
{
    P_SBD sbd = (P_SBD)arg;

    int bar_value = 0;
    while(1) 
    {
        bar_value += 1;
        if(bar_value >= 100) 
        {
            bar_value = 0;
        }
        pthread_mutex_lock(&sbd->mut);
        lv_bar_set_value(sbd->bar, bar_value, LV_ANIM_ON);
        pthread_mutex_unlock(&sbd->mut);

        usleep(50000);
    }

    pthread_exit((void *)0);
}

/**************************** 创建列表 ****************************/
bool list_demo(lv_obj_t * main_windows)
{
    /**************************** 调用字库 ****************************/
    // LV_FONT_DECLARE(gen_jyuu_gothic_bold_2);      // 思源柔黑
    LV_FONT_DECLARE(source_han_sans_cn_normal_2); // 思源黑体Normal，汉字较多

    lv_obj_t * list = lv_list_create(main_windows);
    lv_obj_set_size(list, 180, 415);
    // lv_obj_set_style_text_font(list, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    lv_obj_set_pos(list, 10, 20);

    lv_obj_t * list_btn0 = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    lv_obj_t * list_btn1 = lv_list_add_btn(list, LV_SYMBOL_TRASH, "Trash");
    lv_obj_t * list_btn2 = lv_list_add_btn(list, LV_SYMBOL_BATTERY_3, "Battery3");
    lv_obj_t * list_btn3 = lv_list_add_btn(list, LV_SYMBOL_DRIVE, "Drive");
    lv_obj_t * list_btn4 = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Buletooth");
    lv_obj_t * list_btn5 = lv_list_add_btn(list, LV_SYMBOL_GPS, "GPS");
    lv_obj_t * list_btn7 = lv_list_add_btn(list, NULL, "");

    lv_obj_t * list_btn6 = lv_list_add_btn(list, LV_SYMBOL_EYE_CLOSE, "Eye_close");

    lv_obj_t * list_btn8 = lv_list_add_btn(list, LV_SYMBOL_REFRESH, "Refresh");
    lv_obj_t * list_btn9 = lv_list_add_btn(list, LV_SYMBOL_POWER, "exit");

    // lv_obj_set_style_text_font(list_btn1, &gen_jyuu_gothic_bold_2, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(list_btn0, list_btn_press_task, LV_EVENT_CLICKED, "WiFi");
    lv_obj_add_event_cb(list_btn1, list_btn_press_task, LV_EVENT_CLICKED, "回收站");
    lv_obj_add_event_cb(list_btn2, list_btn_press_task, LV_EVENT_CLICKED, "电量3");
    lv_obj_add_event_cb(list_btn3, list_btn_press_task, LV_EVENT_CLICKED, "设备");
    lv_obj_add_event_cb(list_btn4, list_btn_press_task, LV_EVENT_CLICKED, "蓝牙");
    lv_obj_add_event_cb(list_btn5, list_btn_press_task, LV_EVENT_CLICKED, "GPS");
    lv_obj_add_event_cb(list_btn6, list_btn_press_task, LV_EVENT_CLICKED, "Eye_close");
    lv_obj_add_event_cb(list_btn7, list_btn_press_task, LV_EVENT_CLICKED, "NULL");

    lv_obj_add_event_cb(list_btn8, list_btn_press_task, LV_EVENT_CLICKED, "刷新");
    // lv_obj_add_event_cb(list_btn9, list_btn_exit, LV_EVENT_CLICKED, "退出");

    // return main_windows;
    return true;
}

// void list_btn_exit(lv_event_t * e)
// {

//     //先获取当前按钮控件
//     lv_obj_t * present_btn = e->current_target;

//     printf("即将显示jpg静图！2\n");

//     //获取按钮对应的父类控件 list
//     lv_obj_t * list = lv_obj_get_parent(present_btn);

//     printf("即将显示jpg静图！3\n");

//     //通过list获取老画布
//     lv_obj_t * old_draw = lv_obj_get_parent(list);

//     printf("即将显示jpg静图！4\n");

//     //删除之前的画布
//     lv_obj_del(old_draw);

//     EXIT_MASK = 1;

// }

void list_btn_press_task(lv_event_t * e)
{
    printf("点击的是: %s ! \n", (char *)e->user_data);
    // EXIT_MASK = 1;
    return;
}












P_DVI dir_view_init_windows()
{
    P_DVI inf_heap = (P_DVI)malloc(sizeof(DVI));
    if(inf_heap == (P_DVI)NULL) 
    {
        perror("内存申请失败! \n");
        return (P_DVI)-1;
    }

    memset(inf_heap, 0, sizeof(DVI));
    // 创建主窗口
    inf_heap->mian_windows = lv_obj_create(NULL);
    // 创建左边目录list控件
    inf_heap->lv_dir_list = lv_list_create(inf_heap->mian_windows);
    lv_obj_set_size(inf_heap->lv_dir_list, 300, 480);
    // 创建右边的小画布
    inf_heap->lv_little_windows = lv_obj_create(inf_heap->mian_windows);
    lv_obj_set_size(inf_heap->lv_little_windows, 495, 480);
    lv_obj_set_pos(inf_heap->lv_little_windows, 305, 0);

    lv_scr_load(inf_heap->mian_windows);

    return inf_heap;
}

bool show_file_list(char * search_path, P_DVI inf_heap)
{
    printf("------ %s ------ \n",search_path);
    // 打开要检索的目录，初始目录是根目录
    DIR * dp = opendir(search_path);
    if(dp == (DIR *)NULL) 
    {
        perror("打开目录失败! \n");
        return false;
    }

    char base_path[256 * 8];

    int btn_x = 0;
    int btn_y = 0;
    // 循环读取目录
    while(1) 
    {
        memset(base_path, 0, 256 * 2);
        struct dirent * eq = readdir(dp);
        if(eq == (struct dirent *)NULL) 
        {
            break;
        }
        if(strcmp(eq->d_name, ".") == 0)    // 忽略当前目录
        {
            continue;
        }

        if(strcmp(eq->d_name, "..") == 0)
        {
            char tmp_path[256*2] = "\0";
            strcpy(tmp_path, search_path);
            char * obj_char = strrchr(tmp_path, '/');

            if(obj_char == tmp_path) 
            {
                strcpy(base_path, DEFAULET_PATH);
            }
            else
            {
                *obj_char = '\0';
                strcpy(base_path, tmp_path);
            }
            
        }
        else
        {
            if(search_path[strlen(search_path) - 1] == '/') 
            {
                sprintf(base_path, "%s%s", search_path, eq->d_name);
            } 
            
            else 
            {
                sprintf(base_path, "%s/%s", search_path, eq->d_name);
            }
        }
        // 如果是文件，则显示文件名
        if(eq->d_type == DT_REG) 
        {
            // 申请按钮点击传参结构体堆空间
            struct tmp_btn_touch_inf * file_tmp_inf = malloc(sizeof(struct tmp_btn_touch_inf));
            file_tmp_inf->inf_heap = inf_heap;
            strcpy(file_tmp_inf->new_dir_path, base_path);

            // 在list控件上创建按钮，并设置按钮的文本为文件名
            show_file_view(inf_heap, eq->d_name, btn_x, btn_y,file_tmp_inf);

            btn_x += 90;
            if(btn_x >= 450) 
            {
                btn_x = 0;
                btn_y += 70;
            }
        }

        if(eq->d_type == DT_DIR) 
        {
            // 如果是文件夹，则给list控件创建按钮，然后设置按钮的文本为文件夹的名字
            lv_obj_t * btn = lv_list_add_btn(inf_heap->lv_dir_list, LV_SYMBOL_DIRECTORY, eq->d_name);
            // 申请按钮点击传参结构体堆空间
            struct tmp_btn_touch_inf * tmp_inf = malloc(sizeof(struct tmp_btn_touch_inf));
            if(tmp_inf == (struct tmp_btn_touch_inf *)NULL) 
            {
                perror("内存申请失败! \n");
                return false;
            }
            // 赋值存储当前目录完整路径以及主控结构体堆空间基地址
            tmp_inf->inf_heap = inf_heap;
            strcpy(tmp_inf->new_dir_path, base_path);

            // 注册当前目录按钮点击事件函数 --- 递归调用自己
            lv_obj_add_event_cb(btn, list_btn_press_task_1, LV_EVENT_CLICKED, (void *)tmp_inf);
        }
    }
    // 关闭目录
    closedir(dp);

    return true;
}

void list_btn_press_task_1(lv_event_t * e)
{
    struct tmp_btn_touch_inf * tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    // printf("传入的是: %s ! \n", tmp_inf->new_dir_path);

    // 清除之前list里面的旧控件
    lv_obj_clean(tmp_inf->inf_heap->lv_dir_list);
    //清除之前little_windows的旧控件
    lv_obj_clean(tmp_inf->inf_heap->lv_little_windows);

    // 递归调用加载新的目录控件
    show_file_list(tmp_inf->new_dir_path, tmp_inf->inf_heap);

    return;
}

bool show_file_view(P_DVI inf_heap, char * btn_text, int abs_x, int abs_y,struct tmp_btn_touch_inf * file_tmp_inf)
{
    // 在little_windows上创建按钮
    lv_obj_t * btn = lv_btn_create(inf_heap->lv_little_windows);
    // sprintf(file_tmp_inf->new_dir_path, "%s/%s", file_tmp_inf->new_dir_path, btn_text);
    printf("传入的是: %s ! \n", file_tmp_inf->new_dir_path);

    lv_obj_add_event_cb(btn, file_btn_press_task, LV_EVENT_CLICKED, (void *)file_tmp_inf->new_dir_path);

    lv_obj_set_size(btn, 75, 50);
    lv_obj_set_pos(btn, abs_x, abs_y);

    lv_obj_t * label = lv_label_create(btn);

    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(label, 50);

    lv_label_set_text(label, btn_text);
    lv_obj_center(label);

    return true;
}

void file_btn_press_task(lv_event_t * e)
{
    struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    printf("click的是: %s ! \n", click_tmp_inf->new_dir_path);

    if ((strstr(click_tmp_inf->new_dir_path, ".jpg"))|| (strstr(click_tmp_inf->new_dir_path, ".png")))
    {
        printf("点击的是图片文件!\n");
        //清除之前little_windows的旧控件
        // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

        // 创建右边的新画布覆盖
        lv_obj_t * new_little_windows = lv_obj_create(click_tmp_inf->inf_heap->mian_windows);
        lv_obj_set_size(new_little_windows, 495, 480);
        lv_obj_set_pos(new_little_windows, 305, 0);

        printf("new little windows!\n");
        file_show_img(new_little_windows,click_tmp_inf);
    }
    
    if(strstr(click_tmp_inf->new_dir_path, ".gif"))
    {
        printf("点击的是gif文件!\n");
        //清除之前little_windows的旧控件
        // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

        // 创建右边的新画布覆盖
        lv_obj_t * new_little_windows = lv_obj_create(click_tmp_inf->inf_heap->mian_windows);
        lv_obj_set_size(new_little_windows, 495, 480);
        lv_obj_set_pos(new_little_windows, 305, 0);

        printf("GIF: clear little windows!\n");
        file_show_gif(new_little_windows,click_tmp_inf);
    }

    return;
}


bool file_show_img(lv_obj_t * new_little_windows, struct tmp_btn_touch_inf * click_tmp_inf)
{
    printf("即将显示图片loading······ \n");
    //清除之前little_windows的旧控件
    // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

    char * img_path = click_tmp_inf->new_dir_path;
    char final_img_path[256*2] = "S:" ;
    sprintf(final_img_path, "%s%s", final_img_path, img_path);
    printf("final_img_path: %s \n", final_img_path);
    lv_obj_t * img_obj = lv_img_create(new_little_windows);
   
    // 居中
    lv_img_set_src(img_obj, final_img_path);
    lv_obj_center(img_obj);

    pic_back_to_file(new_little_windows);

    img_path = NULL;
    return true;
}

bool file_show_gif(lv_obj_t * new_little_windows, struct tmp_btn_touch_inf * click_tmp_inf)
{
    printf("即将显示图片loading······ \n");
    //清除之前little_windows的旧控件
    // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);

    char * gif_path = click_tmp_inf->new_dir_path;
    char final_gif_path[256*2] = "S:" ;
    sprintf(final_gif_path, "%s%s", final_gif_path, gif_path);
    printf("final_gif_path: %s \n", gif_path);
    lv_obj_t * gif_obj = lv_gif_create(new_little_windows);
   
    // 居中
    lv_gif_set_src(gif_obj, final_gif_path);
    lv_obj_center(gif_obj);

    pic_back_to_file(new_little_windows);

    gif_path = NULL;
    return true;
}

bool pic_back_to_file(lv_obj_t * new_little_windows)
{
    lv_obj_t * close_btn = lv_btn_create(new_little_windows);
    lv_obj_set_size(close_btn, 30, 30);
    lv_obj_set_pos(close_btn, 420, 0);

    lv_obj_t * close_label = lv_label_create(close_btn);
    lv_label_set_text(close_label,"X");
    lv_obj_center(close_label);

    lv_obj_add_event_cb(close_btn, close_windows_task, LV_EVENT_CLICKED, new_little_windows);

    return true;
}

void close_windows_task(lv_event_t * e)
{
    // struct tmp_btn_touch_inf * click_tmp_inf = (struct tmp_btn_touch_inf *)e->user_data;
    // printf("click的是: %s ! \n", click_tmp_inf->new_dir_path);

    printf("关闭new_little_windows!\n");
    // 删除 new_little_windows
    lv_obj_del(e->user_data);
    printf("关闭成功 !\n");


    // lv_obj_clean(click_tmp_inf->inf_heap->lv_little_windows);


    return;
}

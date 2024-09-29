#include "../../inc/weather.h"
#include "../../inc/color.h"

bool show_weather_inf(P_DVI inf_heap)
{
    printf("show_weather_inf\n");
    inf_heap->weather_info_windows = lv_obj_create(inf_heap->main_windows);
    // lv_obj_set_style_bg_color(inf_heap->weather_info_windows, lv_color_hex(0x87CEFA), LV_STATE_DEFAULT);
    color_gradient1(inf_heap->weather_info_windows);

    lv_obj_set_size(inf_heap->weather_info_windows, 590, 440);
    lv_obj_set_pos(inf_heap->weather_info_windows, 210, 40);
    
    if(current_label != NULL)
    {
        lv_obj_del(current_label);
        current_label = NULL;
    }
    current_label = lv_label_create(inf_heap->main_windows);
    lv_label_set_text(current_label, "天气");
    lv_obj_set_pos(current_label, 10, 450);
    lv_obj_set_style_text_font(current_label, &source_han_sans_cn_normal_2, LV_STATE_DEFAULT);
    
    // 天气文本信息
    lv_obj_t * weather_label = lv_label_create(inf_heap->weather_info_windows);
    lv_label_set_text(weather_label, "");
    lv_obj_set_pos(weather_label, 70, 0);
    lv_obj_set_style_text_font(weather_label, &lv_font_SiYuanRouHei_Regular_16_cjk, LV_STATE_DEFAULT);
    
    // 天气图标
    lv_obj_t *weather_img = lv_img_create(inf_heap->weather_info_windows);
    lv_obj_set_pos(weather_img, 290, 80);

    // 发送天气请求到服务器
    if(!(request_weather_from_server(weather_label, weather_img)))
    {
        return false;
    }
    
    return true;
}

// 向服务器请求天气信息
bool request_weather_from_server(lv_obj_t * label, lv_obj_t *img_obj)
{
    char buffer[BUF_SIZE];
    fd_set read_fds;
    struct timeval timeout;
    
    printf("request_weather_from_server\n");

    // 连接服务器
    int client_socket_weather = connect_to_server();
    if(client_socket_weather == -1) {
        close(client_socket_weather);
        return NULL;
    }
    // int client_socket_weather = socket(AF_INET, SOCK_STREAM, 0);
    
    // 发送天气请求到服务器
    char * cmd = "weather";
    printf("发送天气请求到服务器\n");
    if (send(client_socket_weather, cmd, strlen(cmd), 0) == -1) 
    {
        perror("发送天气请求失败！\n");
        // lv_label_set_text(label, "天气请求发送失败！");
        return;
    }
    
    printf("select\n");
    // 使用 select 等待数据可读
    FD_ZERO(&read_fds);
    FD_SET(client_socket_weather, &read_fds);

    // 设置超时时间为5秒
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;

    printf("select等待中\n");
    int ret = select(client_socket_weather + 1, &read_fds, NULL, NULL, &timeout);
    if (ret == -1) 
    {
        perror("select 失败");
        // lv_label_set_text(label, "获取天气信息失败");
        return;
    } 
    else if (ret == 0) 
    {
        printf("等待超时，未收到服务器响应\n");
        // lv_label_set_text(label, "获取天气信息超时");
        return;
    }

    // 如果套接字可读，读取数据
    if (FD_ISSET(client_socket_weather, &read_fds)) 
    {
        int n = recv(client_socket_weather, buffer, sizeof(buffer) - 1, 0);
        if (n > 0) 
        {
            buffer[n] = '\0';                  // 添加字符串结束符
            printf("天气信息: %s\n", buffer);  // 在终端打印天气数据
            lv_label_set_text(label, buffer); // 在界面显示天气信息

            char today_text_day[50] = {0};
            char *p = strstr(buffer, "--白天天气:");
            if (p != NULL)
            {
                p += strlen("--白天天气:");
                char *end = strchr(p, '\n');
                if (end != NULL)
                {
                    size_t len = end - p;
                    if (len >= sizeof(today_text_day))
                        len = sizeof(today_text_day) - 1;
                    strncpy(today_text_day, p, len);
                    today_text_day[len] = '\0';
                }
                else
                {
                    strncpy(today_text_day, p, sizeof(today_text_day) - 1);
                    today_text_day[sizeof(today_text_day) - 1] = '\0';
                }
            }

            printf("今日白天天气: %s\n", today_text_day);

            char img_path[128];
            if (strcmp(today_text_day, "晴") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/晴天.png");
            }
            else if (strcmp(today_text_day, "多云") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/多云.png");
            }
            else if (strcmp(today_text_day, "中雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/中雨.png");
            }
            else if (strcmp(today_text_day, "阵雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/阵雨.png");
            }
            else if (strcmp(today_text_day, "小雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/小雨.png");
            }
            else if (strcmp(today_text_day, "阴") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/阴天.png");
            }
            else if (strcmp(today_text_day, "大雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/大雨.png");
            }
            else if (strcmp(today_text_day, "雷阵雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/雷阵雨.png");
            }
            else if(strcmp(today_text_day, "暴雨") == 0)
            {
                snprintf(img_path, sizeof(img_path), "S:/mnt/nfs/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/weather/暴雨.png");
            }
            lv_img_set_src(img_obj, img_path);
        } 
        else if(n == 0) 
        {
            // 连接关闭
            printf("服务器关闭了连接\n");
            // lv_label_set_text(label, "服务器关闭了连接");
        } 
        else 
        {
            // 读取错误
            if(errno == EWOULDBLOCK || errno == EAGAIN) 
            {
                printf("资源暂时不可用，请重试\n");
            } 
            else 
            {
                perror("接收天气信息失败");
            }
            // lv_label_set_text(label, "获取天气信息失败");
        }
    }
    return true;
}
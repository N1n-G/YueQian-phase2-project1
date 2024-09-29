#include "main.h"

char *Weather_Http_Request() // 拼接 请求报文中的 请求行+请求头部
{
    char city[20] = "\0";

    static char request[1024] = "GET /v3/weather/daily.json?key=SAewqnjWlC7dvMLfL&location=guangzhou&language=zh-Hans&unit=c&start=0&days=5 HTTP/1.1\r\nHost:api.seniverse.com\r\n\r\n";

    return request;
}


void parse(char *res, int *ok, int *len)
{
    char *retcode = res + strlen("HTTP/1.x ");
    int response_code = atoi(retcode);

    switch (response_code)
    {
    case 200 ... 299:
        *ok = 1;
        printf("查询成功\n");
        break;

    case 400 ... 499:
        *ok = 0;
        printf("客户端错误，响应码：%d\n", response_code);
        break;

    case 500 ... 599:
        *ok = 0;
        printf("服务端错误，响应码：%d\n", response_code);
        break;
    default:
        *ok = 0;
        printf("未知错误, 响应码：%d\n", response_code);
        break;
    }

    char *p = strstr(res, "Content-Length: ");
    if (p != NULL)
    {
        *len = atoi(p + strlen("Content-Length: ")); // 获取响应包体的长度
    }
    else
    {
        *len = 0;
        printf("未找到Content-Length字段！\n");
    }
}


// 发送天气信息
void send_weather_info(int cli_fd)
{
    int cli_weather_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_weather_fd == -1)
    {
        perror("socket 创建失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        return;
    }
    struct hostent *host_inf = gethostbyname("api.seniverse.com");
    if (host_inf == NULL)
    {
        perror("DNS解析失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        close(cli_weather_fd);
        return;
    }

    struct sockaddr_in ser_inf;
    memset(&ser_inf, 0, sizeof(ser_inf));
    ser_inf.sin_family = AF_INET;
    ser_inf.sin_port = htons(80);
    ser_inf.sin_addr.s_addr = inet_addr(inet_ntoa((*(struct in_addr *)host_inf->h_addr_list[0])));

    if (connect(cli_weather_fd, (struct sockaddr *)&ser_inf, sizeof(ser_inf)) == -1)
    {
        perror("连接天气API服务器失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        close(cli_weather_fd);
        return;
    }

    char *request = Weather_Http_Request();
    if (write(cli_weather_fd, request, strlen(request)) == -1)
    {
        perror("发送天气请求失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        close(cli_weather_fd);
        return;
    }

    char res[1024] = {0};
    int total = 0;
    int len = 0;
    int ok = 0;
    while (total < sizeof(res) - 1)
    {
        int n = read(cli_weather_fd, res + total, sizeof(res) - total - 1);
        if (n <= 0)
        {
            perror("读取HTTP头部失败！ \n");
            send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
            close(cli_weather_fd);
            return;
        }
        total += n;
        res[total] = '\0';
        if (strstr(res, "\r\n\r\n"))
        {
            break;
        }
    }

    parse(res, &ok, &len);
    if (!ok)
    {
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        close(cli_weather_fd);
        return;
    }

    char *data = (char *)malloc(len + 1);
    if (data == NULL)
    {
        perror("内存分配失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        close(cli_weather_fd);
        return;
    }

    memset(data, 0, len + 1);
    int received = 0;
    while (received < len)
    {
        int n = read(cli_weather_fd, data + received, len - received);
        if (n <= 0)
        {
            perror("读取天气数据失败！\n");
            send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
            free(data);
            close(cli_weather_fd);
            return;
        }
        received += n;
    }

    cJSON *root = cJSON_Parse(data);
    if (root == (cJSON *)NULL)
    {
        perror("JSON解析失败！\n");
        send(cli_fd, "天气查询失败！", strlen("天气查询失败！"), 0);
        free(data);
        close(cli_weather_fd);
        return;
    }

    /*
        // 这段代码能够实现出来今明后这三天的天气信息
        char *json_data = cJSON_Print(root);
        printf("服务器获取到的天气信息:\n%s\n", json_data); // 服务器端显示天气信息

        send(cli_fd, json_data, strlen(json_data), 0);

        free(json_data);
    */
    // 提取 location 和 today's weather 信息
    cJSON *results = cJSON_GetObjectItem(root, "results");
    if (results != NULL)
    {
        cJSON *location = cJSON_GetObjectItem(cJSON_GetArrayItem(results, 0), "location");
        cJSON *daily = cJSON_GetObjectItem(cJSON_GetArrayItem(results, 0), "daily");
        cJSON *today = cJSON_GetArrayItem(daily, 0);                  // 提取今天的天气
        cJSON *tomorrow = cJSON_GetArrayItem(daily, 1);               // 提取明天的天气
        cJSON *the_day_after_tomorrow = cJSON_GetArrayItem(daily, 2); // 提取明天的天气

        if (location != NULL && today != NULL && tomorrow != NULL)
        {
            const char *country = cJSON_GetObjectItem(location, "country")->valuestring; // 国家
            const char *city = cJSON_GetObjectItem(location, "name")->valuestring;       // 城市

            const char *today_date = cJSON_GetObjectItem(today, "date")->valuestring;                     // 今天日期
            const char *today_text_day = cJSON_GetObjectItem(today, "text_day")->valuestring;             // 今天的白天天气
            const char *today_text_night = cJSON_GetObjectItem(today, "text_night")->valuestring;         // 今天的夜晚天气
            const char *today_high = cJSON_GetObjectItem(today, "high")->valuestring;                     // 今天的最高气温
            const char *today_low = cJSON_GetObjectItem(today, "low")->valuestring;                       // 今天的最低气温
            const char *today_wind_direction = cJSON_GetObjectItem(today, "wind_direction")->valuestring; // 今天的风向
            const char *today_wind_speed = cJSON_GetObjectItem(today, "wind_speed")->valuestring;         // 今天的风速
            const char *today_wind_scale = cJSON_GetObjectItem(today, "wind_scale")->valuestring;         // 今天的风力等级
            const char *today_humidity = cJSON_GetObjectItem(today, "humidity")->valuestring;             // 今天的湿度

            const char *tomorrow_date = cJSON_GetObjectItem(tomorrow, "date")->valuestring;                     // 明天日期
            const char *tomorrow_text_day = cJSON_GetObjectItem(tomorrow, "text_day")->valuestring;             // 明天的白天天气
            const char *tomorrow_text_night = cJSON_GetObjectItem(tomorrow, "text_night")->valuestring;         // 明天的夜晚天气
            const char *tomorrow_high = cJSON_GetObjectItem(tomorrow, "high")->valuestring;                     // 明天的最高气温
            const char *tomorrow_low = cJSON_GetObjectItem(tomorrow, "low")->valuestring;                       // 明天的最低气温
            const char *tomorrow_wind_direction = cJSON_GetObjectItem(tomorrow, "wind_direction")->valuestring; // 明天的风向
            const char *tomorrow_wind_speed = cJSON_GetObjectItem(tomorrow, "wind_speed")->valuestring;         // 明天的风速
            const char *tomorrow_wind_scale = cJSON_GetObjectItem(tomorrow, "wind_scale")->valuestring;         // 明天的风力等级
            const char *tomorrow_humidity = cJSON_GetObjectItem(tomorrow, "humidity")->valuestring;             // 明天的湿度
           // 后天的湿度
            // 格式化今天的天气信息
            char weather_info[512];
            snprintf(weather_info, sizeof(weather_info),
                     "地点:%s--%s\n"
                     "\n"
                     "今天:%s\n"
                     "--白天天气:%s\n"
                     "--夜晚天气:%s\n"
                     "--最高气温:%s\n"
                     "--最低气温:%s\n"
                     "--风向:%s\n"
                     "--风速:%s\n"
                     "--风力等級:%s\n"
                     "--湿度:%s\n"
                    //  "\n"
                     "明天:%s\n"
                     "--白天天气:%s\n"
                     "--夜晚天气:%s\n"
                     "--最高气温:%s\n"
                     "--最低气温:%s\n"
                     "--风向:%s\n"
                     "--风速:%s\n"
                     "--风力等級:%s\n"
                     "--湿度:%s",
                     country, city, today_date, today_text_day, today_text_night, today_high, today_low,
                     today_wind_direction, today_wind_speed, today_wind_scale, today_humidity,
                     tomorrow_date, tomorrow_text_day, tomorrow_text_night, tomorrow_high, tomorrow_low,
                     tomorrow_wind_direction, tomorrow_wind_speed, tomorrow_wind_scale, tomorrow_humidity);

            // 服务器端显示天气信息
            printf("服务器获取到的今天的天气信息:\n%s\n", weather_info);

            // 发送天气信息给客户端
            send(cli_fd, weather_info, strlen(weather_info), 0);
        }
        else
        {
            send(cli_fd, "未能获取今天的天气信息！", strlen("未能获取今天的天气信息！"), 0);
        }
    }
    cJSON_Delete(root);
    free(data);

    close(cli_weather_fd);
}


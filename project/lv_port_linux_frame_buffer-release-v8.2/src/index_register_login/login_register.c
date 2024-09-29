#include "../inc/client.h"



void push_page_history(lv_obj_t * page)
{
    if(history_index < MAX_HISTORY - 1) 
    {
        page_history[++history_index] = page;
    }
}


// 历史页面
void pop_page_history()
{
    if(history_index >= 0) 
    {
        lv_obj_t * previous_page = page_history[history_index--];
        lv_scr_load(previous_page); // 切换到上一个页面
    }
}


// 返回到上一页面
void return_to_previous_page()
{
    // 清空在线用户信息
    num_online_clients = 0; 
    memset(online_clients, 0, sizeof(online_clients)); 
    pop_page_history(); // 从历史栈中取出页面
}



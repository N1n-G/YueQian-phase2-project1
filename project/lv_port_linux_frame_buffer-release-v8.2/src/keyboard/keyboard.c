#include "../../inc/keyboard.h" 

// 文本框点击事件
void textarea_event_cb(lv_event_t * e)
{
    lv_obj_t * textarea = lv_event_get_target(e); // 获取当前点击的文本框

    if(keyboard == NULL) 
    {
        // 创建键盘
        keyboard = lv_keyboard_create(lv_scr_act());

        // 设置键盘事件回调
        lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 绑定键盘事件
    }

    lv_keyboard_set_textarea(keyboard, textarea);          // 将键盘和文本框关联
    lv_obj_set_size(keyboard, LV_HOR_RES, LV_VER_RES / 2); // 设置键盘大小
}

// 键盘点击事件
void keyboard_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);   // 获取事件类型
    lv_obj_t * kb        = lv_event_get_target(e); // 获取触发事件的键盘对象

    // 检查事件类型是否是值改变
    if(code == LV_EVENT_VALUE_CHANGED) 
    {
        const char * txt = lv_btnmatrix_get_btn_text(kb, lv_keyboard_get_selected_btn(kb)); // 获取当前选中按钮的文本

        // 如果点击的是 "Enter" 按钮 (OK) 或 "Close" 按钮 (CLOSE)
        if(strcmp(txt, LV_SYMBOL_OK) == 0 || strcmp(txt, LV_SYMBOL_CLOSE) == 0) 
        {
            close_keyboard(); // 调用关闭键盘函数，销毁键盘对象
        }
    }
}

// 关闭键盘
void close_keyboard()
{
    if(keyboard != NULL) 
    {
        lv_obj_del(keyboard); // 销毁键盘对象
        keyboard = NULL;      // 将全局指针置为 NULL，防止非法访问
    }
}


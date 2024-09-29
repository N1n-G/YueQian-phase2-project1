#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "client.h"

static lv_obj_t * keyboard; // 全局键盘对象，用于多次调用

void textarea_event_cb(lv_event_t * e);
void keyboard_event_cb(lv_event_t * e);
void close_keyboard();
void show_error(const char * message, lv_obj_t * error_label);

#endif
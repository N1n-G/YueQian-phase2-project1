#ifndef _WEATHER_H_
#define _WEATHER_H_

#include "client.h"

bool show_weather_inf(P_DVI inf_heap);
bool request_weather_from_server(lv_obj_t * label, lv_obj_t *img_obj);


#endif
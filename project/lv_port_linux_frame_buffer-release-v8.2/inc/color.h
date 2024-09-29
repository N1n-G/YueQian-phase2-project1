#include "client.h"

void color_gradient(lv_obj_t * color)
{
    lv_obj_set_style_bg_color(color, lv_palette_main(LV_PALETTE_LIGHT_GREEN), 0);            // 设置起始颜色
    lv_obj_set_style_bg_grad_color(color, lv_palette_darken(LV_PALETTE_LIGHT_BLUE, 3), 0); // 设置结束颜色

    lv_obj_set_style_bg_grad_dir(color, LV_GRAD_DIR_VER, 0); // 设置渐变方向（垂直方向）
    // lv_obj_set_style_bg_grad_dir(color, LV_GRAD_DIR_HOR, 0); // 设置渐变方向（水平方向）
}
void color_gradient1(lv_obj_t * color)
{
    lv_obj_set_style_bg_color(color, lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);           // 设置起始颜色
    lv_obj_set_style_bg_grad_color(color, lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3), 0); // 设置结束颜色

    // lv_obj_set_style_bg_grad_dir(color, 300, 0); // 设置渐变方向（垂直方向）
    lv_obj_set_style_bg_grad_dir(color, LV_GRAD_DIR_HOR, 0); // 设置渐变方向（水平方向）
}
void color_gradient2(lv_obj_t * color)
{
    lv_obj_set_style_bg_color(color, lv_palette_main(LV_PALETTE_BLUE), 0);           // 设置起始颜色
    lv_obj_set_style_bg_grad_color(color, lv_palette_darken(LV_PALETTE_CYAN, 3), 0); // 设置结束颜色

    // lv_obj_set_style_bg_grad_dir(color, 300, 0); // 设置渐变方向（垂直方向）
    lv_obj_set_style_bg_grad_dir(color, LV_GRAD_DIR_HOR, 0); // 设置渐变方向（水平方向）
}
void color_gradient3(lv_obj_t * color)
{
    lv_obj_set_style_bg_color(color, lv_palette_main(LV_PALETTE_ORANGE), 0);        // 设置起始颜色
    lv_obj_set_style_bg_grad_color(color, lv_palette_darken(LV_PALETTE_RED, 3), 0); // 设置结束颜色

    // lv_obj_set_style_bg_grad_dir(color, 300, 0); // 设置渐变方向（垂直方向）
    lv_obj_set_style_bg_grad_dir(color, LV_GRAD_DIR_HOR, 0); // 设置渐变方向（水平方向）
}

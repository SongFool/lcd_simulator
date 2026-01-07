#pragma once
#include "stdint.h"
#include "font.h"
typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t *fb;              // framebuffer
    void (*flush)(void);       // PC: StretchDIBits / MCU: lcd_flush
    void (*clean)(uint32_t);
} gui_surface_t;
typedef struct {
    gui_surface_t *surface;

    uint32_t color;            // 当前画笔颜色
    uint32_t bg_color;         // 背景色
    uint16_t rotate;           //方向
    font_t * font;
} gui_ctx_t;

void gui_init(FONT_TYPE type,uint32_t color,uint32_t bg_color,uint16_t rotate);
void gui_draw_line(int x, int y,uint16_t len);
void gui_draw_string(gui_ctx_t *ctx,int x, int y, char* string);
void gui_draw_char_test(int x, int y,char c);
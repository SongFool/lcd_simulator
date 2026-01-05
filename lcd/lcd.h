#pragma once
#include <stdint.h>

void lcd_init(void);
void lcd_clear(uint32_t color);
void lcd_draw_pixel(int x, int y, uint32_t color);

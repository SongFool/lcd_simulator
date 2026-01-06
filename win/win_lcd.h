#pragma once
#include <windows.h>
#include <stdint.h>

void win_lcd_init(HWND hwnd);
void win_lcd_flush(HDC hdc);
uint8_t* win_lcd_get_fb(void);

#include "win_lcd.h"
#include "lcd_conf.h"
#include <stdlib.h>
#include <string.h>

static BITMAPINFO bmi;
static uint8_t* lcd_fb = NULL;

void win_lcd_init(HWND hwnd)
{
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = LCD_WIDTH;
    bmi.bmiHeader.biHeight = -LCD_HEIGHT; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;        // RGB888
    bmi.bmiHeader.biCompression = BI_RGB;

    lcd_fb = (uint8_t*)malloc(LCD_WIDTH * LCD_HEIGHT * 3);
    memset(lcd_fb, 0, LCD_WIDTH * LCD_HEIGHT * 3);
}

uint8_t* win_lcd_get_fb(void)
{
    return lcd_fb;
}

void win_lcd_flush(HDC hdc)
{
    StretchDIBits(
        hdc,
        0, 0, LCD_WIDTH, LCD_HEIGHT,
        0, 0, LCD_WIDTH, LCD_HEIGHT,
        lcd_fb,
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}



#include "lcd.h"
#include "lcd_conf.h"
#include "win_lcd.h"

static uint8_t* fb;

void lcd_init(void)
{
    fb = win_lcd_get_fb();
}

void lcd_clear(uint32_t color)
{
    for (int y = 0; y < LCD_HEIGHT; y++)
    {
        for (int x = 0; x < LCD_WIDTH; x++)
        {
            lcd_draw_pixel(x, y, color);
        }
    }
}

void lcd_draw_pixel(int x, int y, uint32_t color)
{
    if (x < 0 || y < 0 || x >= LCD_WIDTH || y >= LCD_HEIGHT)
        return;

    uint8_t* p = fb + (y * LCD_WIDTH + x) * 3;
    p[0] = color & 0xFF;         // B
    p[1] = (color >> 8) & 0xFF;  // G
    p[2] = (color >> 16) & 0xFF; // R
}

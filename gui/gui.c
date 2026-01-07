#include "lcd.h"
#include "lcd_conf.h"
#include "gui.h"
#include "win_lcd.h"
#include "stdio.h"
gui_surface_t surface;
gui_ctx_t ctx_t;
void gui_draw_point(int x, int y, uint32_t color)
{
    lcd_draw_pixel(x, y, color);
}
void gui_draw_clean(gui_ctx_t *ctx)
{
    lcd_clear(ctx->bg_color);
}
void gui_init(FONT_TYPE type,uint32_t color,uint32_t bg_color,uint16_t rotate)
{
    font_init();
    lcd_init();
    surface.height = LCD_HEIGHT;
    surface.width = LCD_WIDTH;
    surface.fb = win_lcd_get_fb();
    ctx_t.font = font_get(type);
    ctx_t.bg_color = bg_color;
    ctx_t.color = color;
    ctx_t.rotate = rotate;
    ctx_t.surface = &surface;
    gui_draw_clean(&ctx_t);
}
void gui_draw_line(int x, int y,uint16_t len)
{   
    for(int i = y; i < y + len; i++)
        gui_draw_point(x,i,ctx_t.color);
    gui_draw_string(&ctx_t,20,10,"Hello World!");
}
void gui_draw_char_test(int x, int y,char c)
{   
    gui_draw_char(&ctx_t,x,y,c);
}
void gui_draw_char(gui_ctx_t *ctx,int x, int y, char chr)
{
    int x0 = x,y0 = y;
    int size=(ctx->font->h / 8 + ((ctx->font->h % 8) ? 1:0))*(ctx->font->w);
    char chr1 = chr - ' ';
    char (*font)[size] = (char(*)[size])ctx->font->font_tab;
    for(int i = 0; i < size; i++){
        uint8_t temp = font[chr1][i];
        for(char m = 0; m < 8; m++){
			if(temp & 0x01)
			    gui_draw_point(x,y,ctx->color);
			else 
				gui_draw_point(x,y,ctx->bg_color);
			temp>>=1;
			y++;
		}
		x++;
		if((x - x0) == (ctx->font->w)){
		    x = x0;
			y0 = y0 + 8;
		}
		y = y0;
    }
}
void gui_draw_string(gui_ctx_t *ctx,int x, int y, char* string)
{
    char* p_string = string;
	while(*p_string!='\0')
	{		
        gui_draw_char(ctx,x,y,*p_string);
		p_string++;
        x = x + ctx->font->w;
    }
}
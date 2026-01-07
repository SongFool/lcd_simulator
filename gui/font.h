#pragma once
#include "stdint.h"
typedef struct 
{
    uint8_t w;
    uint8_t h;
    uint8_t * font_tab;
}font_t;

typedef enum
{
    FONT_ASCII_2412 = 0,

    FONT_MAX
} FONT_TYPE;


void gui_font_init();
font_t * font_get(FONT_TYPE type);
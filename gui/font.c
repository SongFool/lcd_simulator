#include "font.h"
#include "font_tab.h"

font_t font_tab[FONT_MAX] = {0};

void font_init()
{
    font_tab[FONT_ASCII_2412].font_tab = (uint8_t *)asc2_2412;
    font_tab[FONT_ASCII_2412].h = 24;
    font_tab[FONT_ASCII_2412].w = 12;
}

font_t * font_get(FONT_TYPE type)
{
    if(type >= FONT_MAX)
        return NULL;
    return &font_tab[type];
}
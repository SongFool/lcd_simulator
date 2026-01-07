#include "tty.h"
#include <stdio.h>
#include "gui.h"

uint16_t cursor = 10;
void tty_init(tty_t *tty)
{
    fifo_init(&tty->fifo, tty->buffer, sizeof(tty->buffer));
}

/* 键盘 → TTY */
void tty_rx_char(tty_t *tty, char c)
{
    fifo_put(&tty->fifo, c);
}

/* shell / app → TTY */
int tty_read(tty_t *tty,char *c)
{
    return fifo_get(&tty->fifo,c);
}

void tty_rx_callback(void *ctx, char c) {
    tty_t *tty = (tty_t*)ctx;
    fifo_put(&tty->fifo, c);
}

void tty_display(tty_t *tty)
{
    char c = 0;
    if(tty_read(tty,&c) != -1){
        if(c == 8){
            cursor = cursor - 12;
            gui_draw_char_test(cursor,30,c);
        }else{
            gui_draw_char_test(cursor,30,c);
            cursor = cursor + 12;   
        }

    }
}
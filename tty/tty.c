#include "tty.h"
#include <stdio.h>
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
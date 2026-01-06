#pragma once
#include "fifo.h"
#define BUFFER_MAX 256

typedef struct 
{
    fifo_t fifo;
    char buffer[BUFFER_MAX];
}tty_t;

void tty_init(tty_t *tty);
void tty_rx_char(tty_t *tty, char c);
int tty_read(tty_t *tty,char *c);
void tty_rx_callback(void *ctx, char c);
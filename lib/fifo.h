#pragma once
typedef struct {
    char *buf;
    int size;
    int read;
    int write;
    int len;
} fifo_t;

void fifo_init(fifo_t *f, char *buf, int size);
int fifo_is_empty(fifo_t *f);
int  fifo_put(fifo_t *f, char c);
int  fifo_get(fifo_t *f,char * c);
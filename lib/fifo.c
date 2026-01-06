#include "fifo.h"

void fifo_init(fifo_t *f, char *buf, int size)
{
    f->buf = buf;
    f->size = size;
    f->read = 0;
    f->write = 0;
}

int fifo_is_empty(fifo_t *f)
{
    return f->read == f->write;
}

int  fifo_put(fifo_t *f, char c)
{
    f->buf[f->write] = c;
    f->write = (f->write + 1) % f->size;
    if(fifo_is_empty(f)){
        f->read = (f->read + 1) % f->size;
    }
    return 0;
}
int  fifo_get(fifo_t *f,char * c)
{
    if (fifo_is_empty(f)) {
        return -1; // 队列空
    }
    * c = f->buf[f->read];
    f->read = (f->read + 1) % f->size;
    return 0;
}
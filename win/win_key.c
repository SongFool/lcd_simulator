#include "win_key.h"

void win_key_init(win_key * key_t,void (* on_isr)(void *,char ),void * ctx)
{
    key_t->on_isr = on_isr;
    key_t->ctx = ctx;
}

void win_key_isr(win_key * key_t,char c)
{
    key_t->on_isr(key_t->ctx,c);
}
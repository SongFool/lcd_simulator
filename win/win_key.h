#pragma once
typedef struct 
{
    void (* on_isr)(void *,char );
    void * ctx;
}win_key;

void win_key_init(win_key * key_t,void (* on_isr)(void *,char),void * ctx);
void win_key_isr(win_key * key_t,char c);
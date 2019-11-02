#ifndef __TIMER_H
#define __TIMER_H
#include <stm8s.h>

INTERRUPT_HANDLER(timer_2_irq, 13);
void timer_init();
u32 timer_read();
u32 timer_read_100ms();

#endif
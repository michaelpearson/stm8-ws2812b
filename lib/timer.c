#include <timer.h>

uint32_t time = 0;

INTERRUPT_HANDLER(timer_2_irq, 13) {
    TIM2->SR1 = 0;
    time++;
}

void timer_init() {
    // Prescaler set to CLOCK / 2^10 = 1562.5 (ticks per second).
    TIM2->PSCR = 0b00001010;

    // Set countdown from 1562. 1 Interrupt per second 100ms.
    TIM2->ARRH = 0x06;
    TIM2->ARRL = 0x1A;

    // Turn on overflow interrupt for timer 2.
    TIM2->IER = 0b00000001;

    // Enable timer 2.
    TIM2->CR1 |= 0b00000001;

    enableInterrupts();
}

u32 timer_read() {
    return time / 10;
}

u32 timer_read_100ms() {
    return time;
}
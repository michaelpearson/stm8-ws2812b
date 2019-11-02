#include "main.h"

void main() {
    clock_init();
    ws2812_init();

    // Trigger GPIO
    GPIOB->DDR |= (1 << 4);
    GPIOB->CR1 |= (1 << 4);
    GPIOB->CR2 |= (1 << 4);

    u16 hue = 0;
    u8 index = 0;
    while (1) {
        GPIOB->ODR ^= (1 << 4);
        ws2812_set_color_hsl((u8)(index - 3) % 28, 0, 0, 0);
        ws2812_set_color_hsl(index, hue, 255, 50);
        hue++;
        index++;
        if (hue > 767) {
            hue = 0;
        }
        if (index > 28) {
            index = 0;
        }
        ws2812_write_frame();
        delay(150);
    }
}
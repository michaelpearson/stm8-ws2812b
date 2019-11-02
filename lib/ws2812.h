#ifndef __WS2812_H
#define __WS2812_H

#include <stm8s.h>
#include <spi.h>

void ws2812_init();
void ws2812_set_colour(u8 index, u8 r, u8 g, u8 b);
void ws2812_set_color_hsl(u8 index, u16 hue, u8 sat, u8 val);
void ws2812_write_frame();

#endif
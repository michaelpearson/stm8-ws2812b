#include <ws2812.h>

#define LENGTH 28

u8 red[LENGTH];
u8 green[LENGTH];
u8 blue[LENGTH];

u8 lut[] = {
        0b10001000, // 00
        0b10001110, // 01
        0b11101000, // 10
        0b11101110  // 11
};

void ws2812_set_color_hsl(u8 index, u16 hue, u8 sat, u8 bright) {
    uint16_t r_temp, g_temp, b_temp;
    uint8_t index_mod;
    uint8_t inverse_sat = (sat ^ 255);

    hue = hue % 768;
    index_mod = hue % 256;

    if (hue < 256) {
        r_temp = index_mod ^ 255;
        g_temp = index_mod;
        b_temp = 0;
    } else if (hue < 512) {
        r_temp = 0;
        g_temp = index_mod ^ 255;
        b_temp = index_mod;
    } else if (hue < 768) {
        r_temp = index_mod;
        g_temp = 0;
        b_temp = index_mod ^ 255;
    } else {
        r_temp = 0;
        g_temp = 0;
        b_temp = 0;
    }

    r_temp = ((r_temp * sat) / 255) + inverse_sat;
    g_temp = ((g_temp * sat) / 255) + inverse_sat;
    b_temp = ((b_temp * sat) / 255) + inverse_sat;

    r_temp = (r_temp * bright) / 255;
    g_temp = (g_temp * bright) / 255;
    b_temp = (b_temp * bright) / 255;

    red[index] = (uint8_t) r_temp;
    green[index] = (uint8_t) g_temp;
    blue[index] = (uint8_t) b_temp;
}

void ws2812_init() {
    spi_init();
}

void ws2812_set_colour(u8 index, u8 r, u8 g, u8 b) {
    if (index >= LENGTH) {
        return;
    }
    red[index] = r;
    green[index] = g;
    blue[index] = b;
}

void write_color(u8 r, u8 g, u8 b) {
    spi_write(lut[(g >> 6) & 0b11]);
    spi_write(lut[(g >> 4) & 0b11]);
    spi_write(lut[(g >> 2) & 0b11]);
    spi_write(lut[(g >> 0) & 0b11]);

    spi_write(lut[(r >> 6) & 0b11]);
    spi_write(lut[(r >> 4) & 0b11]);
    spi_write(lut[(r >> 2) & 0b11]);
    spi_write(lut[(r >> 0) & 0b11]);

    spi_write(lut[(b >> 6) & 0b11]);
    spi_write(lut[(b >> 4) & 0b11]);
    spi_write(lut[(b >> 2) & 0b11]);
    spi_write(lut[(b >> 0) & 0b11]);

    spi_write(0);
}

void ws2812_write_frame() {
    for (int a = 0; a < LENGTH; a++) {
        write_color(red[a], green[a], blue[a]);
    }
    spi_write(0);
}
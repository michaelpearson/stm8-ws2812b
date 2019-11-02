#ifndef __SPI_H
#define __SPI_H

#include <stm8s.h>
#include <util.h>
#include <stdio.h>

void spi_init();
u8 spi_read();
void spi_write(uint8_t data);
void spi_write_buffer(const u8 * buffer, u8 len);

#endif
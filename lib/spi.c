#include <spi.h>

void spi_init() {
    SPI->CR2 = 0x01; // SSI?? Seems like a mistake....
    SPI->CR1 = 0b01001100; // Master, CLK/4, Enabled
}

u8 spi_read() {
    // Write a not to read data
    spi_write(0x00);

    // Wait for the byte to leave the buffer
    while ((SPI->SR & SPI_SR_TXE) == 0);

    // Clear the RX buffer
    SPI->DR;

    // Wait for a new byte
    while ((SPI->SR & SPI_SR_RXNE) == 0);

    // Return the new byte in the buffer
    return SPI->DR;
}

void spi_write(u8 data) {
    while ((SPI->SR & SPI_SR_TXE) == 0);
    SPI->DR = data;
}

void spi_write_buffer(const u8 *buffer, u8 len) {
    while (len--) {
        spi_write(*buffer++);
    }
    volatile u8 a = SPI->DR;
}
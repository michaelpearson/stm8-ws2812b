#include <uart.h>

void uart_init() {
  // Set Baud to 115200 with F_CPU = 16MHz
  UART1->BRR2 = 0x0B;
  UART1->BRR1 = 0x08;
  
//  // Set Baud to 921600 with F_CPU = 16MHz
//  UART1->BRR2 = 0x01;
//  UART1->BRR1 = 0x01;
  
  // Enable UART1
  UART1->CR2 |= UART1_CR2_TEN;
}

void putchar(int c) {
    // Wait for the buffer to be ready
    while ((UART1->SR & UART1_SR_TXE) == 0);

    // Write the byte to the tx buffer
    UART1->DR = c;
}


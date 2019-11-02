#include <util.h>

void delay(int32_t ms) {
    for (uint32_t i = 0; i < ((F_CPU / 18 / 10000UL) * ms); i++) {
        nop();
    }
}
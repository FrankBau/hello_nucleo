#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

// microsecond delay, based on cortex-m4 instruction timing, assume default 4 MHz SYSCLK
static inline void delay_us(uint32_t us) {
    __asm volatile (
        "mov r0, %[count]\n"    // Load the delay count into register r0
        "1:\n"                  // Loop label
        "subs r0, r0, #1\n"     // Subtract 1 from r0   (1 CPU cycle)
        "nop\n"                 // No operation needed to make the loop body take 4 cycles = 1 µs
        "bne 1b\n"              // Branch to loop label if r0 is not zero (2 CPU cycles, measured)
        :
        : [count] "r" (us)      // Input: delay_count is the number of iterations
        : "r0"                  // Clobbered register
    );
}

// millisecond delay
static inline void delay_ms(uint32_t ms)
{
    for(uint32_t i=0; i<ms; ++i)
    {
        delay_us(1000);
    }
}

#endif

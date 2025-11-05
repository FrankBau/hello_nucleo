#ifndef __UART_H
#define __UART_H

#include <stm32l432xx.h>

// setup of UART (USART2) peripheral block in the microcontroller

// see STM32L43xxx reference manual (RM0394 Rev 4) for USART2 registers, bits, and function
// see STM32L432KC data sheet (DS11451 Rev 4) for alternate function (AF) and pin assignment
// see Nucleo-32 board user guide (UM1956 Rev 5) for NUCLEO-L432KC board schematics (wiring)

// USB VCP virtual com port connection
// PA2    ------> USART2_TX     pin alternate function: AF7 (see data sheet)
// PA15   ------> USART2_RX     pin alternate function: AF3 (see data sheet)
static inline void uart_init(void) {

    // setup UART pins:

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // enable clock for peripheral component 
    (void)RCC->AHB2ENR; // ensure that the last write command finished and the clock is on

    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) | (2 << GPIO_MODER_MODE2_Pos);   // set AF mode
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFSEL2_Msk) | (7 << GPIO_AFRL_AFSEL2_Pos); // set pin AF7

    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE10_Msk) | (2 << GPIO_MODER_MODE10_Pos);   // set AF mode
    GPIOA->AFR[1] = (GPIOA->AFR[1] & ~GPIO_AFRH_AFSEL15_Msk) | (3 << GPIO_AFRH_AFSEL15_Pos); // set pin AF3

    // setup USART2

    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;   // enable clock for peripheral component 
    (void)RCC->APB1ENR1; // ensure that the last instruction finished and the clock is now on

    USART2->BRR = 4000000 / 115200; // set baud rate = 115200 baud for SYSCLK = 4 MHz
    USART2->CR1 = USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;   // enable UART, RX, TX 
}

static inline void uart_putc(char c) {
    GPIOB->ODR ^= GPIO_ODR_OD3; // toggle user LED
    while (!(USART2->ISR & USART_ISR_TXE)) {
    } // wait until transmit data register is empty
    GPIOB->ODR ^= GPIO_ODR_OD3; // toggle user LED
    USART2->TDR = c;                        // write character to data register
}

#endif

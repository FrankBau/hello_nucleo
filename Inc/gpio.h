#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include <stdlib.h>
#include <stm32l432xx.h>

// pin mode
#define INPUT 0
#define OUTPUT 1
#define ALT 2
#define ANALOG 3
// pull-up / pull-down
#define INPUT_PULLUP 4
#define INPUT_PULLDOWN 5
// output type
#define OUTPUT_OPEN_DRAIN 8

// enable clock for a given GPIO port
static inline void _enable_port_clock(GPIO_TypeDef *GPIOx) {
  if (GPIOx == GPIOA) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
  } else if (GPIOx == GPIOB) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
  } else if (GPIOx == GPIOC) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
  }
  // extend for other ports (GPIOD, GPIOE, etc.)
}

// setup GPIO pin to a specific mode, type, and pull configuration
static inline void gpio_setup(GPIO_TypeDef *GPIOx, int pin, uint8_t setup) {
    _enable_port_clock(GPIOx);

    // MODER: 2 bits per pin
    int shift2 = pin * 2;
    uint32_t mode = setup & 0x3;
    GPIOx->MODER &= ~(0x3u << shift2);   // clear mode bits
    GPIOx->MODER |=  (mode << shift2);   // set new mode

    // PUPDR: 2 bits per pin
    uint32_t pull = (setup >> 2) & 0x3;
    GPIOx->PUPDR &= ~(0x3u << shift2);   // clear pull bits
    GPIOx->PUPDR |=  (pull << shift2);   // set new pull

    // OTYPER: 1 bit per pin
    int shift1 = pin;
    uint32_t type = (setup >> 4) & 0x1;
    GPIOx->OTYPER &= ~(0x1u << shift1);  // clear type bit
    GPIOx->OTYPER |=  (type << shift1);  // set new type
}

// read GPIO pin state
static inline int gpio_read(GPIO_TypeDef *GPIOx, int pin) {
  int shift = pin;
  return (GPIOx->IDR >> shift) & 1u;
}

static inline void gpio_write(GPIO_TypeDef *GPIOx, int pin, int level) {
  int shift = pin;
  if (level) {
    GPIOx->ODR |= (1u << shift);
  } else {
    GPIOx->ODR &= ~(1u << shift);
  }
}

#endif

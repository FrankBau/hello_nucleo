#ifndef __GPIO_H
#define __GPIO_H

#include <stdlib.h>
#include <stm32l432xx.h>


enum GPIO_MODE { INPUT = 0, OUTPUT = 1, ALT = 2, ANALOG = 3 };

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

// set GPIO pin mode to INPUT/OUTPUT/ALT/ANALOG
static inline void gpio_mode(GPIO_TypeDef *GPIOx, int pin, enum GPIO_MODE mode) {
  _enable_port_clock(GPIOx);
  int shift = pin * 2;
  GPIOx->MODER &= ~(0x3u << shift); // clear mode bits
  GPIOx->MODER |= (mode << shift);  // set new mode
}

// read GPIO pin state
static inline int gpio_read(GPIO_TypeDef *GPIOx, int pin) {
  int shift = pin;
  return (GPIOx->IDR >> shift) & 1u;
}

enum GPIO_PULL { PULL_NONE = 0, PULL_UP = 1, PULL_DOWN = 2 };

// configure internal pull-up/pull-down resistors
static inline void gpio_pull(GPIO_TypeDef *GPIOx, int pin, enum GPIO_PULL pull) {
  _enable_port_clock(GPIOx);
  GPIOx->PUPDR = (GPIOx->PUPDR & ~(3u << (2 * pin))) | (pull << (2 * pin));
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

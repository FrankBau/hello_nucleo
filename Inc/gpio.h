#ifndef __GPIO_H
#define __GPIO_H

#include <stm32l432xx.h>

// init a GPIO pin on port GPIOA or GPIOB for digital output. pin number is 0..15
static inline void gpio_init_output(GPIO_TypeDef *gpio, unsigned pin)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN; // enable clock for GPIOO peripheral components
    (void)RCC->AHB2ENR;                  // ensure that the last write command finished and the clock is on
    // set pin to output mode (1). Reset defaults for other registers are okay here
    gpio->MODER = (gpio->MODER & ~(3u << (2*pin))) | (1u << (2*pin));
}

// set GPIO pin high
static inline void gpio_set_hi(GPIO_TypeDef *gpio, unsigned pin)
{
    gpio->ODR = gpio->ODR | (1u << pin);
}

// set GPIO pin low
static inline void gpio_set_lo(GPIO_TypeDef *gpio, unsigned pin)
{
    gpio->ODR = gpio->ODR & ~(1u << pin);
}

#endif

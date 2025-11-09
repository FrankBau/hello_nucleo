#include "gpio.h"
#include "uart.h"
#include "delay.h"

int main(void)
{

    gpio_setup(GPIOB, 3, OUTPUT);
    gpio_setup(GPIOB, 0, INPUT_PULLUP);

    gpio_write(GPIOB, 3, 1);
    delay_ms(1000); // LED self-test
    gpio_write(GPIOB, 3, 0);

    uart_init();
    uart_puts("enter t or press the button to switch the Treppenlicht on.\n");

    /* Loop forever */
	for(;;)
    {
        int c = uart_getc();
        int button = gpio_read(GPIOB, 0);

        if(c=='t' || button==0) {
            gpio_write(GPIOB, 3, 1);
            delay_ms(3000);
            gpio_write(GPIOB, 3, 0);
        }
    }
}

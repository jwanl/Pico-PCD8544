//#include <stdio.h>
#include "pico/stdlib.h"
#include "pcd8544.h"

#define PIN_LED 22

int main()
{
    //stdio_init_all();

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    // Blink led
    /*while (true) {
        gpio_put(PIN_LED, 1);
        sleep_ms(1000);
        gpio_put(PIN_LED, 0);
        sleep_ms(1000);
    }*/
}

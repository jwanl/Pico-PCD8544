//#include <stdio.h>
#include "pico/stdlib.h"
#include "pcd8544.h"

#define PIN_LED 22

int main()
{
    //stdio_init_all();

    pcd8544_init();

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);
    gpio_put(PIN_LED, 0);
    pcd8544_clearDisplay();

    gpio_put(PIN_LED, 1);
    sleep_ms(1000);
    pcd8544_swap_buffers();
    gpio_put(PIN_LED, 0);

    while (true) {
        sleep_ms(1000);
        pcd8544_swap_buffers();
        sleep_ms(1000);
        pcd8544_clearDisplay();
    }
}

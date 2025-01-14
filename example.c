//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pcd8544.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16 // master in, slave out = data from sub (not used in this project)
#define PIN_CS   17 // chip select = active-low signal from main to enable comm with this device
#define PIN_SCK  18 // serial clock = clock signal from main
#define PIN_MOSI 19 // master out, slave in = data from main (MSB first, apparently?)

#define PIN_LED 22



int main()
{
    //stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

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

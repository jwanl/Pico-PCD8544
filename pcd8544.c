#include "pcd8544.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_RST  16 // reset
#define PIN_CS   17 // chip select (enable) = active-low signal from main to enable comm with this device
#define PIN_SCK  18 // serial clock = clock signal from main
#define PIN_MOSI 19 // master out, slave in = data from main (MSB first, apparently?)
#define PIN_DC   20 // mode select, low = command, high = data input

#define PCD8544_USE_VERTICAL_ADDRESSING 0

uint8_t pcd8544_framebuffer[84 * 6] = {
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};

int pcd8544_init()
{
    // Init SPI
    spi_init(SPI_PORT, 4000000);
    gpio_set_function(PIN_RST,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_DC,   GPIO_FUNC_SIO);
    gpio_set_dir(PIN_RST,  GPIO_OUT);
    gpio_set_dir(PIN_CS,   GPIO_OUT);
    //gpio_set_dir(PIN_SCK,  GPIO_OUT);
    //gpio_set_dir(PIN_MOSI, GPIO_OUT);
    gpio_set_dir(PIN_DC,   GPIO_OUT);
    //gpio_put(PIN_CS, 1); // not selected

    // Apply RST signal
    // TODO: apply RST low - wait?? - apply RST high
    gpio_put(PIN_RST, 0);
    sleep_ms(1);
    gpio_put(PIN_RST, 1);

    // Set normal display mode
    // TODO: apply DC low - apply 0b00100(PD)(VERT.ADDR.)(INSTR.SET) => 0b00100000 for testing

    uint8_t normalDispMode[] = { 0x21, 0xB8, 0x04, 0x14, 0b00100000, 0b00001100 };
    for (int i = 0; i < 6; i++) {
        // Go into command mode
        gpio_put(PIN_DC, 0);
        // Activate chip
        gpio_put(PIN_CS, 0);
        // Apply normal display mode
        
        int bytes_written = spi_write_blocking(spi0, &normalDispMode[i], 1);
        gpio_put(PIN_CS, 1);
    }

    return 0;//bytes_written - 1;
}

int pcd8544_swap_buffers()
{
    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(spi0, pcd8544_framebuffer, 504);
    //sleep_ms(10);
    gpio_put(PIN_CS, 1);

    return 0;
}

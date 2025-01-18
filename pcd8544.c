#include "pcd8544.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_RST  16 // reset
#define PIN_CS   17 // chip select = active-low signal from main to enable comm with this device
#define PIN_SCK  18 // serial clock = clock signal from main
#define PIN_MOSI 19 // master out, slave in = data from main (MSB first, apparently?)

#define PCD8544_USE_VERTICAL_ADDRESSING 0

int pcd8544_init()
{
    // Init SPI
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_RST,  GPIO_FUNC_SIO);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    // Apply RST signal
    // TODO: apply RST low - wait?? - apply RST high

    // Set normal display mode
    // TODO: apply DC low - apply 0b00100(PD)(VERT.ADDR.)(INSTR.SET) => 0b00100000 for testing
    return 0;
}

int pcd8544_swap_buffers()
{
    return 0;
}

// needs more meow? me thinks :3

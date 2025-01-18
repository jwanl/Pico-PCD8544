#ifndef PCD8544_DRIVER_H
#define PCD8544_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

/** Initializes SPI connection and applies reset signal to display */
int pcd8544_init();

// maybe not required?
//int pcd8544_close();

/** Send current framebuffer to display */
int pcd8544_swap_buffers();

#endif /* PCD8544_DRIVER_H */
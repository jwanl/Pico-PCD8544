#ifndef PCD8544_DRIVER_H
#define PCD8544_DRIVER_H

uint8_t pcd8544_framebuffer[84 * 6];

/** Initializes SPI connection */
int pcd8544_init();

// maybe not required?
//int pcd8544_close();

/** Send current framebuffer to display */
int pcd8544_swap_buffers();

#endif /* PCD8544_DRIVER_H */
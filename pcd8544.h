#ifndef PCD8544_DRIVER_H
#define PCD8544_DRIVER_H

#include "pico/stdlib.h"
#include "pico/divider.h"
#include "hardware/spi.h"

#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48

/** Framebuffer of size WIDTH * HEIGHT / 8. One byte is 8 pixels */
extern uint8_t pcd8544_framebuffer[];

/** Initializes SPI connection and applies reset signal to display */
int pcd8544_init();

// maybe not required?
//int pcd8544_close();

/** Send current framebuffer to display */
int pcd8544_swap_buffers();

/** Send given command to display */
void pcd8544_command(uint8_t command);

/** Sets target pixel as one */
inline void pcd8544_setPixel(int x, int y) {
    divmod_result_t div = divmod_u32u32(y, 8);
    pcd8544_framebuffer[(uint32_t)(div) * SCREEN_WIDTH + x] |= (1 << (uint32_t)(div >> 32U));
}

/** Sets target pixel as zero */
inline void pcd8544_clearPixel(int x, int y) {
    divmod_result_t div = divmod_u32u32(y, 8);
    pcd8544_framebuffer[(uint32_t)(div) * SCREEN_WIDTH + x] &= (~(uint8_t)(1 << (uint32_t)(div >> 32U)));
}

/** Gets current value of specified pixel */
inline int pcd8544_getPixel(int x, int y) {
    divmod_result_t div = divmod_u32u32(y, 8);
    return (pcd8544_framebuffer[(uint32_t)(div) * SCREEN_WIDTH + x] >> (uint32_t)(div >> 32U)) & 0x01U;
}

void pcd8544_clearDisplay();

#endif /* PCD8544_DRIVER_H */
# Pico-PCD8544

PCD8544 LCD screen driver/API for Raspberry Pi Pico written in C.


## Connection between PCD8544 driver board and Pico:

| PCD8544 | explanation  | Pico pin |
| ------- | ------------ | -------- |
| RST   | reset          | 16 |
| CE    | chip enable    | 17 |
| DC    | mode select    | 20 |
| DIN   | serial data in | 19 |
| CLK   | serial clock   | 18 |
| VCC   | 3.3V           | 3.3V |
| LIGHT | backlight 3.3V |    |
| GND   | ground         | ground |

Reset: Resets device, apply to initialize chip, clears registers. Active low
Chip enable: Active low
Mode select: Either command/address (low) or data input (high)
Serial data in: MSB first
Serial clock: 0.0 to 4.0 Mbit/s

"Immediately following power-on, the contents of all internal
registers and of the RAM are undefined. A RES pulse
must be applied. Attention should be paid to the
possibility that the device may be damaged if not properly
reset."
After this, the chip is in power down mode.
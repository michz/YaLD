#ifndef __PWMOUT_H
#define __PWMOUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>

/**
 * Initializes the i2c output to the LED drivers.
 */
void pwmout_init_output();

/**
 * Translates the given 8bit data to 12bit and writes it to the LED drivers.
 */
void pwmout_write_output(volatile uint8_t source[]);

extern long PWMData[32];

#ifdef __cplusplus
}
#endif

#endif

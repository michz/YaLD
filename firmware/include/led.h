/**
 * @file
 * @author  Michael Zapf
 */

#ifndef __LED_H
#define __LED_H

#include <avr/io.h>
#include <util/delay.h>


#define LED_GREEN_PIN   (DDB2)
#define LED_RED_PIN     (DDB3)


void initLEDs(void);
void LEDgreenOn(void);
void LEDredOn(void);
void LEDgreenOff(void);
void LEDredOff(void);
void blink(void);
void blinkGreen(void);
void blinkRed(void);


#endif // __LED_H

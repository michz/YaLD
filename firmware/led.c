#include "led.h"

void initLEDs(void) {
    DDRB    |=  ((1 << LED_GREEN_PIN) | (1 << LED_RED_PIN));
}

void LEDgreenOn(void) {
    PORTB   &=  ~(1 << LED_GREEN_PIN);
}

void LEDredOn(void) {
    PORTB   &=  ~(1 << LED_RED_PIN);
}

void LEDgreenOff(void) {
    PORTB   |=  (1 << LED_GREEN_PIN);
}

void LEDredOff(void) {
    PORTB   |=  (1 << LED_RED_PIN);
}

void blink(void) {
    LEDgreenOn();
    LEDredOn();
    _delay_ms(50);
    LEDgreenOff();
    LEDredOff();
}
void blinkGreen(void) {
    LEDgreenOn();
    _delay_ms(50);
    LEDgreenOff();
}
void blinkRed(void) {
    LEDredOn();
    _delay_ms(50);
    LEDredOff();
}

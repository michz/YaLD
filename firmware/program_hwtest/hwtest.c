#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "pwmout.h"
#include "led.h"

#include "suart.h"

#include "irmp.h"
#include "ir_mode.h"
#include "millis.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_CHANNEL_COUNT 32

static inline void initDIPs(void);
void get_dips(void);
volatile uint16_t DmxAddress;
volatile uint8_t testData[TEST_CHANNEL_COUNT];
volatile uint8_t testDataPoint = 0;

int main(void) {
    wdt_disable();                  // disable watchdog for boot
    cli();                          // disable interrupts for boot

    for (uint8_t i = 0; i < TEST_CHANNEL_COUNT; i++) {
        testData[i] = 0;
    }

#ifdef DEBUG
    suart_init();
    printf("Initializing YaLD...\n");
#endif

    initLEDs();
    initDIPs();

    get_dips();

    sei();                          // enable interrupts

    pwmout_init_output();

    // init timer for IRMP
    OCR2   =  (uint8_t) (((F_CPU / F_INTERRUPTS) / 8) - 1 + 0.5);  // Compare Register OCR2
    TCCR2  = (1 << WGM21) | (1 << CS21);                           // CTC Mode, prescaler = 8
    TIMSK  = 1 << OCIE2;                                           // enable timer2 interrupt
    irmp_init();

    millis_init();                  // changes timer config

    // init watchdog
    wdt_enable(WDTO_2S);

#ifdef DEBUG
    printf("Initialization complete.\n");
    suart_init();
#endif

    // Signalize on board that program is initialized
    blink();

    while(1) {
        _delay_ms(100);
        get_dips();

        blinkGreen();

        for (uint8_t i = 0; i < 32; i++) {
            if (i == testDataPoint) {
                testData[i] = 255;
            } else {
                testData[i] = 0;
            }
        }

        testDataPoint++;
        if (testDataPoint >= 32) {
            testDataPoint = 0;
        }

        // Write output
        pwmout_write_output(testData);

        // reset watchdog
        wdt_reset();
    }
}

// call ISR of IR module
ISR(TIMER2_COMP_vect) {
    (void) irmp_ISR();
}

static inline void initDIPs(void) {
    // init DIP ports as inputs
    DDRA |= 0x0; // all inputs
    DDRB &= ~((1 << DDB0) | (1 << DDB1));

    // activate pull-ups
    PORTA = 0xFF;
    PORTB |= ((1 << DDB0) | (1 << DDB1));
}
#ifdef __cplusplus
}
#endif


// ************* get DMX start address **************
void get_dips(void)
{
    uint16_t tmp;

tmp = (
    (!(PINB & (1<<PINB1)) << 0) |
    (!(PINB & (1<<PINB0)) << 1) |
    (!(PINA & (1<<PINA0)) << 2) |
    (!(PINA & (1<<PINA1)) << 3) |
    (!(PINA & (1<<PINA2)) << 4) |
    (!(PINA & (1<<PINA3)) << 5) |
    (!(PINA & (1<<PINA4)) << 6) |
    (!(PINA & (1<<PINA5)) << 7) |
    (!(PINA & (1<<PINA6)) << 8)
    );

    DmxAddress = tmp;
}

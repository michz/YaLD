#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "dmxled.h"
#include "pwmout.h"
#include "led.h"

#ifndef TARGET_UART_SIMPLE
#include "irmp/irmp.h"
#include "ir_mode.h"
#include "dmx/C/lib_dmx_in.h"
#else
#include "uart_simple.h"
#endif

#ifdef DEBUG
#include "suart.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

volatile uint8_t gGlobalState;
volatile uint32_t dmxIdleTicks = 0;

static inline void initDIPs(void);

#ifndef TARGET_UART_SIMPLE
int main(void) {
    wdt_disable();                  // disable watchdog for boot
    gGlobalState = INIT;
    cli();                          // disable interrupts for boot

#ifdef DEBUG
    suart_init();
    printf("Initializing YaLD...\n");
#endif

    initLEDs();
    initDIPs();

    //DmxAddress = 1;               // Just for debugging/testing with no dips / fixed address
    init_DMX_RX();
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
        get_dips();

        if (gGlobalState == EADDR) {
            blinkRed();
            _delay_ms(150);
            blinkRed();
            _delay_ms(800);
        }
        else if (gGlobalState == EADDR) {
            blinkRed();
            _delay_ms(800);
        }
        else if (gGlobalState == MODE_IR ||
                (gGlobalState == MODE_DMX && dmxIdleTicks >= (F_INTERRUPTS))) {

            // reset dmx idle counter to avoid overflow
            if (dmxIdleTicks > ((uint32_t)3 * (uint32_t)F_INTERRUPTS)) {
                dmxIdleTicks = ((uint32_t)3 * (uint32_t)F_INTERRUPTS);
            }

            ir_mode();
            pwmout_write_output(ir_raw);
        }
        else if (gGlobalState == MODE_DMX) {
            pwmout_write_output(DmxRxField);
        }

        // reset watchdog
        wdt_reset();
    }
}

// call ISR of IR module
ISR(TIMER2_COMP_vect) {
    dmxIdleTicks++;
    (void) irmp_ISR();
}
#else
int main(void) {
    wdt_disable();                  // disable watchdog for boot
    cli();                          // disable interrupts for boot

#ifdef DEBUG
    suart_init();
    printf("Initializing YaLD...\n");
#endif

    initLEDs();
    initDIPs();

    uart_simple_init();

    sei();                          // enable interrupts

    pwmout_init_output();

    // init watchdog
    wdt_enable(WDTO_2S);

#ifdef DEBUG
    printf("Initialization complete.\n");
    suart_init();
#endif

    // Signalize on board that program is initialized
    blink();

    while(1) {
        // Wait a little bit to slow down
        _delay_ms(1);

        pwmout_write_output(uart_simple_buffer);

        // reset watchdog
        wdt_reset();
    }
}

// call ISR of IR module
ISR(TIMER2_COMP_vect) {
}
#endif // #ifndef TARGET_UART_SIMPLE

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

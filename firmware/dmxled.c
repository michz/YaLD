#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "dmxled.h"
#include "led.h"
#include "ir_mode.h"
#include "pca9685.h"
#include "i2c/i2cmaster.h"
#include "dmx/C/lib_dmx_in.h"
#include "irmp/irmp.h"

#ifdef DEBUG
#include "suart.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

const static int dmx_pwm[] = {
    0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,
    7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,11,11,12,12,12,13,13,14,14,
    15,15,15,16,17,17,18,18,19,19,20,21,21,22,23,24,24,25,26,27,
    28,29,30,31,32,33,34,35,36,37,39,40,41,43,44,45,47,48,50,52,
    53,55,57,59,61,63,65,67,69,72,74,77,79,82,84,87,90,93,96,99,
    103,106,110,113,117,121,125,129,133,138,142,147,152,157,162,
    168,173,179,185,191,197,204,210,217,225,232,240,248,256,264,
    273,282,292,301,311,322,332,343,355,366,379,391,404,417,431,
    446,460,476,491,508,525,542,560,579,598,618,638,659,681,704,
    727,751,776,802,828,856,884,913,944,975,1007,1041,1075,1111,
    1148,1186,1225,1266,1308,1351,1396,1442,1490,1539,1590,1643,
    1697,1754,1812,1872,1934,1998,2064,2133,2203,2277,2352,2430,
    2511,2594,2680,2769,2860,2955,3053,3154,3259,3367,3479,3594,
    3713,3836,3964,4095};

/* PWM data variables, 16bit vide, 12bit used*/
/*volatile*/ long PWMData[32] = {
    0x0,    // Channel 0
    0x0,    // Channel 1
    0x0,    // Channel 2
    0x0,    // Channel 3
    0x0,    // Channel 4
    0x0,    // Channel 5
    0x0,    // Channel 6
    0x0,    // Channel 7
    0x0,    // Channel 8
    0x0,    // Channel 9
    0x0,    // Channel 10
    0x0,    // Channel 11
    0x0,    // Channel 12
    0x0,    // Channel 13
    0x0,    // Channel 14
    0x0,    // Channel 15
    0x0,    // Channel 16
    0x0,    // Channel 17
    0x0,    // Channel 18
    0x0,    // Channel 19
    0x0,    // Channel 20
    0x0,    // Channel 21
    0x0,    // Channel 22
    0x0,    // Channel 23
    0x0,    // Channel 24
    0x0,    // Channel 25
    0x0,    // Channel 26
    0x0,    // Channel 27
    0x0,    // Channel 28
    0x0,    // Channel 29
    0x0,    // Channel 30
    0x0     // Channel 31
};

volatile uint8_t gGlobalState;
volatile uint32_t dmxIdleTicks = 0;

static inline void initDIPs(void);

int main(void) {
    wdt_disable(); // disable watchdog for boot
    gGlobalState = INIT;
    cli();                          // disable interrupts

#ifdef DEBUG
    suart_init();
    printf("Initializing YaLD...\n");
#endif

    initLEDs();
    initDIPs();

    //DmxAddress = 1;
    init_DMX_RX();
	get_dips();

    sei();                          // enable interrupts

    pca9685_init(LEDDRV1);
    pca9685_init(LEDDRV2);

    // init timer for IRMP
    OCR2   =  (uint8_t) (((F_CPU / F_INTERRUPTS) / 8) - 1 + 0.5);   // Compare Register OCR2
    TCCR2  = (1 << WGM21) | (1 << CS21);                           // CTC Mode, prescaler = 8
    TIMSK  = 1 << OCIE2;                                           // enable timer2 interrupt
    irmp_init();

    millis_init(); // changes timer config

    // init watchdog
    wdt_enable(WDTO_2S);

#ifdef DEBUG
    printf("Initialization complete.\n");
    suart_init();
#endif

    blink();

    while(1) {
	    get_dips(); // TODO: so regelmäßig?

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
            if (dmxIdleTicks > ((uint32_t)3 * (uint32_t)F_INTERRUPTS))
                dmxIdleTicks = ((uint32_t)3 * (uint32_t)F_INTERRUPTS);

            ir_mode();

            for (int i = 0; i < 32; ++i) {
                PWMData[i] = dmx_pwm[ir_raw[i]];
            }

            pca9685_send_all(LEDDRV1, PWMData);
            pca9685_send_all(LEDDRV2, PWMData+16);
        }
        else if (gGlobalState == MODE_DMX) {
            for (int i = 0; i < 32; ++i) {
                PWMData[i] = dmx_pwm[DmxRxField[i]];
            }

            pca9685_send_all(LEDDRV1, PWMData);
            pca9685_send_all(LEDDRV2, PWMData+16);
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

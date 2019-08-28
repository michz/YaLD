/**
 * For debugging purposes, a software UART transmitter(!) is implemented here.
 * Source: http://rn-wissen.de/wiki/index.php/Software-UART_mit_avr-gcc
 *
 * Stripped and modified by Michael Zapf.
 */

#ifdef DEBUG

#include "suart.h"

static FILE mystdout = FDEV_SETUP_STREAM(suart_putc_printf, NULL, _FDEV_SETUP_WRITE);

// temporary buffer for char to send
static volatile uint16_t outframe;

// Initialisierung für einen ATmega8 
// Für andere AVR-Derivate sieht dies vermutlich anders aus: 
// Registernamen ändern sich (zB TIMSK0 anstatt TIMSK, etc). 
void suart_init(void)
{
    uint8_t tifr = 0;
    uint8_t sreg = SREG;
    cli();

    stdout = &mystdout;

    // Mode #4 für Timer1 
    // und volle MCU clock 
    // IC Noise Cancel 
    // IC on Falling Edge 
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10) | (0 << ICES1) | (1 << ICNC1);

    // OutputCompare für gewünschte Timer1 Frequenz 
    OCR1A = (uint16_t) ((uint32_t) F_CPU/BAUDRATE);

    // TIMSK &= ~(1 << TICIE1);

    // TX
    tifr |= (1 << OCF1A);
    SUART_TXD_PORT |= (1 << SUART_TXD_BIT);
    SUART_TXD_DDR  |= (1 << SUART_TXD_BIT);
    outframe = 0;

    TIFR = tifr;

    SREG = sreg;

}

void suart_putc(const char c)
{
    do
    {
        sei(); nop(); cli(); // yield(); 
    } while (outframe);

    // frame = *.P.7.6.5.4.3.2.1.0.S   S=Start(0), P=Stop(1), *=Endemarke(1) 
    outframe = (3 << 9) | (((uint8_t) c) << 1);

    TIMSK |= (1 << OCIE1A);
    TIFR   = (1 << OCF1A);

    sei();
}

void suart_puts(const char *s) {
    const char* c = s;
    while(*c != 0x0) { // TODO: Testen
        suart_putc(*c);
        c++;
    }
}

void suart_nputs(const char *s, int n) {
    for (int i = 0; i < n; ++i ){
        suart_putc(s[i]);
    }
}

int suart_putc_printf(const char var, FILE *stream) {
    suart_putc(var);
    return 0;
}

ISR (TIMER1_COMPA_vect)
{
    uint16_t data = outframe;
   
    if (data & 1)      SUART_TXD_PORT |=  (1 << SUART_TXD_BIT);
    else               SUART_TXD_PORT &= ~(1 << SUART_TXD_BIT);
   
    if (1 == data)
    {
        TIMSK &= ~(1 << OCIE1A);
    }   
   
    outframe = data >> 1;
}

#endif  // DEBUG

/**
 * For debugging purposes, a software UART transmitter(!) is implemented here.
 * Source: http://rn-wissen.de/wiki/index.php/Software-UART_mit_avr-gcc
 *
 * Stripped and modified by Michael Zapf.
 */

#ifdef DEBUG

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


#define BAUDRATE 19200
#define SUART_TXD_PORT PORTC
#define SUART_TXD_DDR  DDRC
#define SUART_TXD_BIT  PC3


#define nop() __asm volatile ("nop")


void suart_init(void);
void suart_putc(const char c);
void suart_puts(const char *s);
void suart_nputs(const char *s, int n);
int suart_putc_printf(const char var, FILE *stream);

#endif  // DEBUG

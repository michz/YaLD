#include "uart_simple.h"

#include <avr/interrupt.h>
#include <avr/io.h>



uint8_t uart_simple_buffer[UART_SIMPLE_CHANNEL_COUNT];
uint8_t uart_simple_buffer_pos = 0;


void uart_simple_init() {
    for (uint8_t i = 0; i < UART_SIMPLE_CHANNEL_COUNT; i++) {
        uart_simple_buffer[i] = 0;
    }

    // init uart baud rate
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;

    UCSRA = 0x00;                                 // Clear the UASRT status register
    UCSRB = (1<<RXEN) | (1<<RXCIE);   // Enable RX and RX IRQ
    UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); // Mode: Asynchronous 8N1
}

ISR(USART_RXC_vect)
{
    uint8_t USARTstate = UCSRA; // get state before data! Shameless stolen from DMX routines
    uint8_t read = UDR;

    if (USARTstate & (1<<FE)) {         // check for break
        UCSRA &= ~(1<<FE);              // reset flag (necessary for simulation in AVR Studio)
        uart_simple_buffer_pos =  0;    // reset channel counter
    } else {
        // Only read UART_SIMPLE_CHANNEL_COUNT bytes at max
        if (uart_simple_buffer_pos >= UART_SIMPLE_CHANNEL_COUNT) {
            return;
        }

        uart_simple_buffer[uart_simple_buffer_pos] = read;
        uart_simple_buffer_pos++;
    }
}

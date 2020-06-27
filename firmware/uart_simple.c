#include "uart_simple.h"

#include <avr/interrupt.h>
#include <avr/io.h>

uint8_t uart_simple_buffer[UART_SIMPLE_CHANNEL_COUNT];
uint8_t uart_simple_buffer_length = 0;
uint8_t temp_buffer[2] = { 0, 0 };
uint8_t temp_buffer_pos = 0;
uint8_t sync_found = 0;

void uart_simple_init() {
    uart_simple_buffer_length = sizeof(uart_simple_buffer) * sizeof(uint8_t);
    for (uint8_t i = 0; i < uart_simple_buffer_length; i++) {
        uart_simple_buffer[i] = 0;
    }

    // init uart baud rate
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;

    UCSRA = 0x00;                                 // Clear the UASRT status register
    UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);   // Enable RX, TX and RX IRQ
    UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); // Mode: Asynchronous 8N1
}

ISR(USART_RXC_vect)
{
    uint8_t read = UDR;

    temp_buffer[temp_buffer_pos] = read;
    temp_buffer_pos++;

    // if first of two bytes, return now
    if (temp_buffer_pos % 2 == 1) {
        return;
    }

    // Reset temporary buffer position pointer
    temp_buffer_pos = 0;

    if (temp_buffer[0] == 0xFF && temp_buffer[1] == 0xFF) {
        // Found sync bytes, everything ok.
        sync_found = 1;
    } else if (temp_buffer[0] >= uart_simple_buffer_length) {
        // Failure, wait for next sync bytes
        // (expected address, but got too large value)
        sync_found = 0;
    } else if (sync_found) {
        // Assume first received byte is address, second is value
        uart_simple_buffer[temp_buffer[0]] = temp_buffer[1];
    }
}




/*

// Debug this by using the following program:


// This simulates reading chars from uart
int current = 0;
uint8_t backlog[] = {
    0,
    0,
    1,
    10,
    2,
    20,
    3,
    30,
    0xFF,
    0xFF,
    4,
    40,
    250,   // byte error, should be 5
    50,
    6,
    60,
    0xFF,
    0xFF,
    7,
    70,
    8,
    80,
    9,
    90,
};
uint8_t read_next_char() {
    uint8_t read = backlog[current];
    current++;
    if (current >= sizeof(backlog)) {
        current = 0;
    }
    return read;
}

int main(int argc, char* argv) {
    int i = 0;
    for (i = 0; i < 36; i++) {
        usart_rx_irq();
    }

    for (i = 0; i < sizeof(temp_buffer); i++) {
        printf("%d  ", temp_buffer[i]);
    }
    printf("\n");

    for (i = 0; i < sizeof(uart_simple_buffer); i++) {
        printf("%d  ", uart_simple_buffer[i]);
    }
    printf("\n");

    return 0;
}
*/

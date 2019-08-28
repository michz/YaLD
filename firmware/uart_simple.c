#include "uart_simple.h"

#include "stdint.h"


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

uint8_t read_buffer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

uint8_t temp_buffer[2] = { 0, 0 };
uint8_t temp_buffer_pos = 0;
uint8_t sync_found = 0;

void usart_rx_irq() {
    uint8_t read = read_next_char();
    printf("Read: %d\n", read);

    temp_buffer[temp_buffer_pos] = read;
    temp_buffer_pos++;

    // if first of two bytes, return
    if (temp_buffer_pos % 2 == 1) {
        printf("Return\n");
        return;
    }

    // Reset temporary buffer position pointer
    temp_buffer_pos = 0;

    if (temp_buffer[0] == 0xFF && temp_buffer[1] == 0xFF) {
        // Sync bytes, everything ok.
        sync_found = 1;
        printf("SYNC FOUND ...\n");
    } else if (temp_buffer[0] >= sizeof(read_buffer)) {
        // Failure, wait for next sync bytes
        // (expected address, but got too large value)
        sync_found = 0;
    } else if (sync_found) {
        // Assume first received byte is address, second is value
        read_buffer[temp_buffer[0]] = temp_buffer[1];
    }
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

    for (i = 0; i < sizeof(read_buffer); i++) {
        printf("%d  ", read_buffer[i]);
    }
    printf("\n");

    return 0;
}

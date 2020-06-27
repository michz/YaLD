#ifndef __UART_SIMPLE_H
#define __UART_SIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>

#define UART_SIMPLE_CHANNEL_COUNT 32

#define BAUD 19200UL
//#define BAUD 38400UL

// Calculations
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
#error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch!
#endif

void uart_simple_init();

extern uint8_t uart_simple_buffer[];

#ifdef __cplusplus
}
#endif

#endif

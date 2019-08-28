/**** A P P L I C A T I O N   N O T E   ************************************
*
* Title			: DMX512 reception library
* Version		: v1.3
* Last updated	: 13.04.09
* Target		: Transceiver Rev.3.01 [ATmega8515]
* Clock			: 8MHz, 16MHz
*
* written by hendrik hoelscher, www.hoelscher-hi.de
***************************************************************************
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version2 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 General Public License for more details.

 If you have no copy of the GNU General Public License, write to the
 Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 For other license models, please contact the author.

;***************************************************************************/

#include "lib_dmx_in.h"
#include "dmxled.h"
#include "led.h"

volatile uint8_t     DmxRxField[DMX_COUNT]; 		// array of DMX vals (raw)
volatile uint16_t    DmxAddress;			        // start address

// ********************* local definitions *********************

enum {IDLE, BREAK, STARTB, STARTADR};			//DMX states

volatile uint8_t 	    gDmxState;
extern volatile uint8_t gGlobalState;
extern volatile uint32_t dmxIdleTicks;

// *************** DMX Reception Initialisation ****************
void init_DMX_RX(void)
{
    DDRD  |= (1<<2);
    PORTD &= ~(1<<2);
    UBRRH  = 0;										//enable reception
    UBRRL  = ((F_OSC/4000000)-1);						//250kbaud, 8N2
    //UBRRL  = 3;										//250kbaud bei 16MHz
    UCSRC  = (1<<URSEL)|(3<<UCSZ0)|(1<<USBS);		// 8N2
    UCSRB  = (1<<RXEN)|(1<<RXCIE);
    gDmxState= IDLE;
}



// ************* get DMX start address **************
void get_dips(void)
{
#ifdef USE_DIP
    uint16_t tmp;			//start address

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

if (tmp > 511) {
    gGlobalState = EADDR;
}
else if (tmp == 0) {
    gGlobalState = MODE_IR;
	UCSRB &= ~(1<<RXCIE);       //disable Receiver if start address = 0
}
else {
    gGlobalState = MODE_DMX;

    //if receiver was disabled -> enable and wait for break
	if (!(UCSRB &(1<<RXCIE))) {
		gDmxState= IDLE;
		UCSRB |= (1<<RXCIE);
	}
}

DmxAddress = tmp;

#endif
}



// *************** DMX Reception ISR ****************
ISR (USART_RXC_vect) {
    static  uint16_t DmxCount;
    uint8_t  USARTstate = UCSRA;        // get state before data!
    uint8_t  DmxByte    = UDR;          // get data
    uint8_t  DmxState   = gDmxState;    // just load once from SRAM to increase speed


    if (USARTstate & (1<<FE)) {						//check for break
        UCSRA &= ~(1<<FE);							//reset flag (necessary for simulation in AVR Studio)
        DmxCount =  DmxAddress;						//reset channel counter (count channels before start address)
        gDmxState = BREAK;
    }
    else if (DmxState == BREAK) {
        if (DmxByte == 0) {
            gDmxState = STARTB;		//normal start code detected
        }
        else {
            gDmxState = IDLE;
        }
    }
    else if (DmxState == STARTB)
    {
        dmxIdleTicks = 0;                       // reset idle counter
        if (--DmxCount == 0)						// start address reached?
        {
            DmxCount = 1;							// set up counter for required channels
            DmxRxField[0] = DmxByte;				// get 1st DMX channel of device
            gDmxState = STARTADR;
        }
    }
    else if (DmxState == STARTADR)
    {
        DmxRxField[DmxCount++] = DmxByte;           // get channel
        if (DmxCount >= DMX_COUNT)                  // all ch received?
        {
            gDmxState = IDLE;                       // wait for next break
            gGlobalState = MODE_DMX;
        }
    }
}

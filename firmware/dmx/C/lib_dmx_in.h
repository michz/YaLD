#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define  USE_DIP

#define  DMX_COUNT			(32)

extern volatile uint8_t     DmxRxField[DMX_COUNT]; 		// array of DMX vals (raw)
extern volatile uint16_t    DmxAddress;			        // start address

extern void    init_DMX_RX(void);
extern void    get_dips(void);

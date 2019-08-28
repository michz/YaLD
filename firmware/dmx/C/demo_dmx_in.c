
#include "lib_dmx_in.h"

int main(void)
{
cli();
DDRD |= (1<<PD7);					//red LED pin is output
init_DMX_RX();
// DmxAddress= 1;
sei();
for(;;)
	{
	get_dips();						//get start address
	if (DmxRxField[0] >= 127)		//enable LED if 1st DMX val is >127
		{
		PORTD &= ~(1<<PD7);			//LED ON
		}
	else
		{
		PORTD |= (1<<PD7);			//LED OFF
		}
	}
}


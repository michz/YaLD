// Example of dmx_in usage
// 04.06.06
// (c)Hendrik Hölscher		

.include "m8515def.inc"

		#define SREGbuf	 	 R2
		#define tempL		 R16
		#define tempH		 R17
		
		#define DMX_FIELD	 0x60	//base address of DMX array
		#define DMX_CHANNELS 2		//no. of channels
		#define DMXstate	 R18	//status reg for DMX-ISR (r16-r31)

		#define F_OSC		 8000  	//oscillator freq. in kHz (typical 8MHz or 16MHz)
		#define USE_DIP				//should get start address from DIPs?

/* ****set interrupt-routines */

.org 0
	rjmp reset 				/* reset vector address */
	reti					/* External Interrupt0 Vector Address */
	reti 					/* External Interrupt1 Vector Address */
	reti					/* Input Capture1 Interrupt Vector Address */
	reti 					/* Output Compare1A Interrupt Vector Address */
	reti					/* Output Compare1B Interrupt Vector Address */
	reti 					/* Overflow1 Interrupt Vector Address */
	reti					/* Overflow0 Interrupt Vector Address */
	reti					/* SPI Interrupt Vector Address */
	rjmp get_byte			/* UART Receive Complete Interrupt Vector Address */
	reti					/* UART Data Register Empty Interrupt Vector Address */
	reti					/* UART Transmit Complete Interrupt Vector Address */
	reti 					/* Analog Comparator Interrupt Vector Address */
	reti					/* External Interrupt2 Vector Address */
	reti					/* Output Compare0 Interrupt Vector Address */
	reti					/*  EEPROM Interrupt Vector Address */
	reti					/*  SPM complete Interrupt Vector Address */
	reti					/*  SPM complete Interrupt Vector Address */	

reset:

cli

/* ***** set stackpointer */
	ldi		tempL,  low(RAMEND)
	ldi 	tempH, high(RAMEND)
	out		SPL,tempL
	out 	SPH,tempH

/* **** LED port */
	ser 	tempL
	out		DDRE, tempL
	out		PortE, tempL

/* **** init DMX receiver */
	rcall	init_dmx

	sei								;allow interrupts


main:
	rcall	eval_dmx				;eval dmx data
	rjmp	main

  
  eval_dmx:
	lds		tempL, DMX_FIELD		;get 1st ch (2nd is DMX_FIELD +1)
	cpi		tempL, 127				;is temp >127?
	brsh	led_on
	sbi		PortE, PE0				;switch LED1 off
	ret
   led_on:
    cbi		PortE, PE0				;switch LED1 on
	ret



/* ***** include lib */
.include "lib_dmx_in.asm"

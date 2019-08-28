;**** A P P L I C A T I O N   N O T E   ************************************
;*
;* Title		: DMX512 reception library
;* Version		: v1.3
;* Last updated	: 21.04.07
;* Target		: Transceiver Rev.3.01 [ATmega8515]
;* Clock		: 8MHz, 16MHz
;*
;* written by hendrik hoelscher, www.hoelscher-hi.de
;***************************************************************************
; This program is free software; you can redistribute it and/or 
; modify it under the terms of the GNU General Public License 
; as published by the Free Software Foundation; either version2 of 
; the License, or (at your option) any later version. 
;
; This program is distributed in the hope that it will be useful, 
; but WITHOUT ANY WARRANTY; without even the implied warranty of 
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
; General Public License for more details. 
;
; If you have no copy of the GNU General Public License, write to the 
; Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 
;
; For other license models, please contact the author.
;
;***************************************************************************


 /************* Definitions in main source **********************
		
		#define USE_DIP				//use DIPs for addressing
		#define DMX_FIELD	 0x60	//base address of DMX array
		#define DMX_CHANNELS 8		//no. of channels
		#define DMXstate	 R18	//status reg for DMX-ISR (r16-r31)
	  //X-Pointer reserved for DMX ISR!!

		#define F_OSC		 8000  	//oscillator freq. in kHz (typical 8MHz or 16MHz)

 **************************************************************/

	
init_dmx:
	;**** PortD
		sbi		DDRD,  PD2
		cbi		PortD, PD2				;enable reception

	;**** USART
    	ldi 	tempL, ((F_OSC/4000)-1) 	;set Usart to 250 kbaud
    	out 	UBRRL, tempL
    	clr 	tempL
    	out 	UBRRH, tempL
    	ldi 	tempL, (1<<URSEL)|(3<<UCSZ0)|(1<<USBS)
    	out 	UCSRC, tempL			
		in		tempL,UDR
 		clr		tempL
		out		UCSRA,tempL		
		sbi 	UCSRB,RXCIE
		sbi 	UCSRB,RXEN			

#ifdef USE_DIP
	;**** PortC
		clr 	tempL
		out 	DDRC, tempL
		ser 	tempL
		out 	PortC, tempL  				;Inputs with PullUp for DipSwitch
	
	;**** PortE
		in		tempL, DDRE
		cbr	 	tempL, (1<<1)|(1<<2)
		out 	DDRE, tempL
		in		tempL, PortE
		sbr	 	tempL, (1<<1)|(1<<2)
		out 	PortE, tempL 				;PE2 & OPTION Pullup
#endif

	;**** memory
		ldi		XH, high(DMX_FIELD)
		ldi		XL,  low(DMX_FIELD)
		clr		tempL						;set all channels to 0
		ldi 	DMXstate, DMX_CHANNELS
	write_RxD:	
		st 		X+,tempL
		dec		DMXstate
		brne	write_RxD

	//	clr 	DMXstate					;set DMXstate to 'wait for Reset' (done by counting ;-)
		ret


/* ***********************************************************************************************************
 *					DMX reception ISR
 ************************************************************************************************************/
get_byte:
		in      SREGbuf, SREG
		push	tempH
		push	tempL		

		in		tempL,UCSRA		;get status register before data register
		in		tempH,UDR

		sbrc	tempL,FE		;check for frame error -> got reset
		rjmp	dmx_frame_error	
		
		cpi		DMXstate, 1   	;check for startbyte (must be 0)
		breq	dmx_startbyte

  		cpi 	DMXstate, 2   	;check for start adress
		breq    dmx_startadr
  		
 		cpi 	DMXstate, 3	
  		brsh	dmx_handle_byte

	dmx_finish:
		pop		tempL
		pop		tempH
		out     SREG, SREGbuf	
		reti			

	dmx_startbyte:
		tst 	tempH	 				;if null-> Startbyte
		brne 	dmx_err
		inc  	DMXstate 				;next -> start address

#ifdef USE_DIP
		in 		XL, PinC 				;get start address
		com     XL
		clr		XH
		sbis	PinE, PE2				;9th bit
		inc		XH
#else
		rcall	get_address
#endif
		rjmp	dmx_finish

 	dmx_startadr:
		sbiw	XH:XL, 1
		brne	dmx_finish
		ldi 	XH, high(DMX_FIELD)
		ldi		XL,  low(DMX_FIELD)
		inc  	DMXstate 				;next-> data handler
		
	dmx_handle_byte:			
		st		X+, tempH

		cpi		XL, low(DMX_FIELD +DMX_CHANNELS)
		brne	dmx_finish
		cpi		XH, high(DMX_FIELD +DMX_CHANNELS)
		brne	dmx_finish	
		clr		DMXstate
		rjmp	dmx_finish
	
 	dmx_frame_error:
		ldi 	DMXstate, 1				;FE detected as break
		cbi		UCSRA,FE				;further framing errors, caused by longer breaks
		rjmp	dmx_finish

	dmx_err:
	 	clr 	DMXstate				;wait for frame-error			
		rjmp	dmx_finish

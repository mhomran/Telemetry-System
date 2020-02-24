/*
 * Timer1.c
 *
 * Created: 10/14/2019 11:34:16 PM
 *  Author: Mohamed_Hassanin
 */ 

#include "Timer1.h"
#include "USART.h"

extern volatile uint8_t current;

void 
Timer1_Init(void)
{	
	TIMSK1 |= 1 << OCIE1A; //interrupt enable at overflow
	
	TCCR1B |= 1 << WGM12;
	OCR1A = 2000;

	TCCR1B |= 1 << CS10 | 1 << CS12;
}

ISR
(TIMER1_COMPA_vect)
{
	//enable nested interrupts for other important interrupts
	sei();
	
	if (Send == 1)
	{

	//byte 0x3 means the end of the frame, so don't put it as a data and put it as a combination
	USART_TX(((uint8_t)(KMPH)) + 1);
	USART_TX(((uint8_t)((RPM & 0x01) ? ((RPM >> 1) + 1) : (RPM >> 1))) + 1);
	USART_TX(((uint8_t)(RPM >> 1)) + 1);
	USART_TX((uint8_t)(current) +1);
	
	//delimiter	
	USART_TX(((uint8_t) 0x0));
	}
}

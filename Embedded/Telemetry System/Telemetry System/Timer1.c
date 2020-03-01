/*
 * Timer1.c
 *
 * Created: 10/14/2019 11:34:16 PM
 *  Author: Mohamed_Hassanin
 */ 

#include "Timer1.h"



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
	//enable nested interrupts for Hall sensor
	sei();
	
	if (Send == 1)
	{
	After_Send = 1;	

    //byte 0x1B means the end of the frame
	// so don't put it as a data and put it as a combination
	
	send_RPM(RPM);        //Sending the RPM value
	
	send_KMPH(KMPH);      //Sending the KMPH value
    
    send_Current(current);//Sending the Current value 
  
	USART_TX(0x1B);		  //Send delimiter -> End of Package
	}
}

void
send_RPM(uint32_t RPM)
{
	uint8_t RPMDig3 = (RPM / 100) % 10;			     //Getting Digit X3
	
	USART_TX(  RPM % 10 + 0x30);                     //Send X0
	USART_TX( (RPM / 10) - RPMDig3 * 10 + 0x30);     //Send X1
	USART_TX(  RPMDig3 + 0x30);                      //Send X2
}

void 
send_KMPH(float KMPH)
{
  float KMPHDig10 = (KMPH - (int) KMPH) * 100;      //Getting Digits X1 & X0 (e.g. : 35)
  
  USART_TX( (uint8_t) KMPHDig10 % 10 + 0x30 );         //Send X0
  USART_TX( (uint8_t) KMPHDig10 / 10 + 0x30 );         //Send X1
  USART_TX( (uint8_t) KMPH % 10 + 0x30 );              //Send X2
  USART_TX( ((uint8_t) KMPH / 10) % 10 + 0x30 );       //Send X3
}


void
send_Current(float current)
{
  uint8_t currentDig43   = (int) current % 100;			     //Getting Digits X4 & X3 (e.g. : 35)
  uint8_t currentDig4    = currentDig43 / 10; 
  uint16_t currentDig210 = (current - (int) current) * 1000; //Getting Digits X3 & X2 & X1 (e.g. : 143)
  uint8_t currentDig1    = currentDig210 / 10 - (currentDig210 / 100) * 10;
  
  USART_TX(( (currentDig210) %10 + 0x30 ));				  //Send X0
  USART_TX(( (currentDig1) + 0x30 ));					  //Send X1
  USART_TX(( (currentDig210 / 100) + 0x30 ));			  //Send X2
  USART_TX(( (currentDig43 % 10 + 0x30 )));				  //Send X3
  USART_TX(( (currentDig4 + 0x30)));					  //Send X4
}

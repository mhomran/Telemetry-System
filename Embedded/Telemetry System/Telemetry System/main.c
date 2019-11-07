#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <math.h>
#include "USART.h"
#include "Timer1.h"
#include "Timer3.h"

volatile uint32_t RPM, Two_Succesive, KMPH; 
volatile uint8_t After_Send;

int main()
 { 
	RPM = 0;
  KMPH = 0;
   
	INIT_UART();
	Timer1_Init();
	Timer3_Init();
	
	ADMUX   |= 1 << REFS0 | (1 << MUX0) | (1 << MUX1); //AVCC with external capacitor at AREF pin, MUX = 0011, ArduinoUno "A3"
	ADCSRA  |= 1 << ADEN | 1 << ADPS2;  //N = 16
	
	//interrupt
	PCICR |= 1 << PCIE2;
	PCMSK2 |= (1 << PCINT18);
	
	DDRB |= 1 << PINB5;
	PORTB &= ~(1 << PINB5);

   
	sei();
	while (1)
      ;
   return 0;
 }
 
 ISR
 (PCINT2_vect)
 {
	//source: hall sensor 50% duty -> half of the freq = elec. rev.
	Two_Succesive = TCNT3;
	Two_Succesive = (((unsigned long) 16000000) / 1024 / Two_Succesive);		 
	RPM = ((Two_Succesive/2.0)/24) * 60;
  
  KMPH = (uint32_t)(RPM * .08859291283);

  if (RPM <= 15)
  {
  RPM = 0;
  KMPH = 0;  
  }
  	 
	//Reset timer0 count for next speed measurement:
	TCNT3 = 0;
}

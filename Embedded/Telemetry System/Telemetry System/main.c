//This code measure the RPM and KMPH of a BLDC motor and the current consumed by it.
//the current sensor used to measure the current is ACS712 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "USART.h"
#include "Timer1.h"
#include "Timer3.h"

volatile uint32_t RPM, Rotor_Freq, KMPH; 

volatile uint16_t adc_val = 0;
volatile uint64_t acc = 0;
volatile uint8_t adcAvg = 0;
volatile uint8_t current = 0;
volatile uint8_t count = 0;

int 
main()
{ 
	RPM = 0;
  KMPH = 0;
   
	INIT_UART();
	Timer1_Init();
	Timer3_Init();
	
	//ADC
	ADMUX |= 1 << REFS0 | (1 << MUX0) | (1 << MUX1);	//AVCC with external capacitor at AREF pin, MUX = 0011, ArduinoUno "A3"
	ADCSRA |= 1 << ADEN | 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;	//N = 128 -> 125kHz sampling rate
																																//25 samples in 5kHz pulse
	ADCSRA |= 1 <<  ADIE;	//enable end of conversion interrupt
	ADCSRA |= 1 << ADSC;	//start the first conversion
	
	//interrupt
	EICRA |= 1 << ISC01 | 1 << ISC00;
	EIMSK |= 1 << INT0;
	
	DDRB |= 1 << PINB5;
	PORTB &= ~(1 << PINB5);
  
	sei();	//enable global interrupt
	
	while (1)
      ;
   return 0;
}
 
 ISR
 (INT0_vect)
 {
	//source: hall sensor 50% duty -> half of the freq = elec. rev.
	Rotor_Freq = TCNT3;
	Rotor_Freq = (((unsigned long) 16000000) / 1024 / Rotor_Freq);		 
	RPM = (Rotor_Freq / 24.0) * 60;	//Hz_elec_rev to RPM_mech_rev -> (rotor_freq/pair_poles) * 60 
  KMPH = (uint32_t)(RPM * .08859291283);

  if (RPM <= 15)
  {
		RPM = 0;
		KMPH = 0;
		current = 1;
  }
  else
  {
		//multiply current by 10 so to avoid sending floating numbers.
		//5V * (1/slope of output voltage vs sensored current) * 10
    adcAvg = (adcAvg / 1024.0) * 5 * 5.33 * 10;
    current = adcAvg;  	 
  }
	
	TCNT3 = 0; //Reset timer0 count for next speed measurement
	
	adcAvg = acc / count; //Get Average
	count = 0;
	acc = 0;
}

ISR
(ADC_vect)
{
	count++;	
	adc_val = ADC - 500;	//500 because the measured current is positive
	acc += adc_val;
	ADCSRA |= 1<< ADSC;
}

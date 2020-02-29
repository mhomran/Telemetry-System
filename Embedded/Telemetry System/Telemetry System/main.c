#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <math.h>
#include "USART.h"
#include "Timer1.h"
#include "Timer3.h"

volatile uint32_t RPM, Rotor_Freq;
volatile float   KMPH; 

volatile uint8_t After_Send;

volatile uint16_t adc_val = 0;
volatile uint64_t acc	  = 0;
volatile float adcAvg     = 0;
volatile float current    = 0;
volatile uint8_t count    = 0;

int main()
 { 
    RPM = 0;
    KMPH = 0.00;
   
	INIT_UART();
	Timer1_Init();
	Timer3_Init();
	
	//ADC
	ADMUX   |= 1 << REFS0 | (1 << MUX0) | (1 << MUX1); //AVCC with external capacitor at AREF pin, MUX = 0011, ArduinoUno "A3"
	ADCSRA  |= 1 << ADEN | 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;  //N = 128 -> 125kHz sampling rate
																																//25 samples in 5kHz pulse
	//enable end of conversion interrupt
	ADCSRA |= 1 <<  ADIE;
	//start first conversion
	ADCSRA |= 1<< ADSC;
	
	//interrupt
	EICRA |= 1 << ISC01 | 1 << ISC00;
	EIMSK |= 1 << INT0;
	
	DDRB |= 1 << PINB5;
	PORTB &= ~(1 << PINB5);
  
	//enable global interrupt
	sei();
	
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
  RPM = (Rotor_Freq/24.0) * 60;
  
  KMPH = (RPM * .08859291283);
  
  adcAvg = (float)acc/count; //Getting  Average
  
  if (RPM <= 15)
  {
	//Set initial Values  
	 RPM = 0;
	 KMPH = 0;  
	 current = 0.12;
  }
  else
  {
    //5.33 is inverse slope (refer to current sensor DS)
    adcAvg = (adcAvg/1024.0)*5.0*5.33;
     	 
    current = adcAvg;
  }
	//Reset timer0 count for next speed&current measurement:
	TCNT3 = 0;
	count = 0;
	acc   = 0;
	
}

ISR
(ADC_vect)
{
	count++;
	adc_val = ADC - 505; //505 is Hard-coded
	acc += adc_val;
	ADCSRA |= 1<< ADSC;
}

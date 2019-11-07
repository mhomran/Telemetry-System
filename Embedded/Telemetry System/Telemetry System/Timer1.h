/*
 * Timer_1.h
 *
 * Created: 10/14/2019 11:34:27 PM
 *  Author: Mohamed_Hassanin
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer1_Init(void);

volatile uint16_t temp;

extern volatile uint8_t Send;
extern volatile uint8_t After_Send;
extern volatile uint32_t RPM, KMPH;

#endif /* TIMER1_H_ */

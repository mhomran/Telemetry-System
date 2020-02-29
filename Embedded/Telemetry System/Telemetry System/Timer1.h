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
#include "USART.h"

/*
*Function Name: send_RPM
* Purpose      : Sending RPM with precision xxx (0 -> 999)
* Input        : RPM 
* Output       : None
*/
void send_RPM(uint32_t RPM);
/*
*Function Name: send_KMPH
* Purpose      : Sending KMPH with precision xx.xx (0 -> 99.99)
* Input        : KMPH
* Output       : None
*/
void send_KMPH(float KMPH);
/*
*Function Name: send_Current
* Purpose      : Sending current with precision xx.xxx (0 -> 99.999)
* Input        : Current
* Output       : None
*/
void send_Current(float current);

void Timer1_Init(void);

volatile uint16_t temp;

extern volatile uint8_t Send;
extern volatile uint8_t After_Send;

//Declaring external Variables sent in the package 
extern volatile uint32_t RPM;
extern volatile float current;
extern volatile float KMPH;

#endif /* TIMER1_H_ */

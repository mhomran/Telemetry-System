#ifndef _USART_H
#define _USART_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000ul
#define BAUD 9600

volatile uint8_t data_rx;

void INIT_UART(void);
void USART_TX(uint8_t ch);
void USART_PRINTF(const char *str);

volatile uint8_t Send;

#endif


#include "USART.h"


void 
INIT_UART(void)
{
	UBRR0 = (F_CPU/16UL/BAUD)-1;
	UCSR0B |= 1 << TXEN0 | 1 << RXCIE0 | 1 << RXEN0;
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= 1 << UCSZ00 | 1 << UCSZ01;
	
	Send = 0;
}

void 
USART_TX(uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void 
USART_PRINTF(const char *str)
{
	int x =0;
	while (str[x]){
	USART_TX(str[x]);
	x++;
	}
}

ISR
(USART0_RX_vect)
{
	if (UDR0 == 1)
	{
		Send = 1;
	}
	else
	{
		Send = 0;
	}
}

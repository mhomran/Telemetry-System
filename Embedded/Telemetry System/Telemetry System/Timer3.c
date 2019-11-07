/*
 * Timer0.c
 *
 * Created: 10/15/2019 6:00:53 PM
 *  Author: Mohamed_Hassanin
 */ 

#include "Timer3.h"

//for speed
void 
Timer3_Init(void)
{
	TCCR3B |= 1 << CS30 | 1 << CS32;
}

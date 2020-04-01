/*
 * toggleProject.c
 *
 * Created: 2/26/2020 10:02:43 AM
 * Author : argk4
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#define SW1 PINA0
#define SW2 PINA1
#define SW3 PINA2
#define SW4 PINA3

int main(void)
{
    DDRD = 0xFF;
	DDRA = 0x00;
	PORTA = 0xFF;
	unsigned char temp = 0x00; 
	unsigned char num1 = 0x00; 
	unsigned char num2 = 0x00;
	
    while (1) 
    {
		PORTD = 0xFF;
		if ( ( ~PINA & ( 1 << SW1 ) ) ) 
		{
			num1 += 0b00000001;
		}
		if ( ( ~PINA & ( 1 << SW2 ) ) )
		{
			num1 += 0b00000010;
		}
		if ( ( ~PINA & ( 1 << SW3 ) ) )
		{
			num1 += 0b00000100;
		}
		if ( ( ~PINA & ( 1 << SW4 ) ) )
		{
			num1 += 0b00001000;
		}
		PORTD = ~temp;
		_delay_ms(1000);
    }
}


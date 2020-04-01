/*
 * lab5.c
 *
 * Created: 3/11/2020 11:12:04 AM
 * Author : argk4
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while () 
    {
		PORTD ^= 0xFF;
		delay_normal();
    }
}

void delay_normal()
{
	TCCR1A = 0;
	TCCR1A |= (0<<WGM11) | (WGM10);
	
	TCCR1B = 0;
	TCCR1B |= (0<<WGM13) | (WGM12);
	
	TCCR1C = 0;
	
	TCNT1 = 0xFFFF - 0xF424;
	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10);
	
	while ( TIFR1 & ( 1<<TOV0 ))
	{
		//
	}
	
	TIFR1 |= (1<<TOV1); // clear TOV flag
	TCCR1B &= ~( 1<<CS12 ) | ( 1<<CS11 ) | (1<<CS10); //tc off
	TCNT1 = 0x00;
}

void delay_ctc()
{
	TCCR1A = 0x00;
	TCCR1A |= (0<<WGM11) | (0<<WGM10); // CTC mode
	
	TCCR1B = 0x00;
	TCCR1B |= (0<<WGM13) | (1<<WGM12); // CTC mode
	
	TCCR1C = 0x00;
	
	OCR1A = 0xF424;
	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10);
	
	while ( TIFR1 & ( 1<<OCF1A ))
	{
	}
	
	TIFR1 |= (1<<OCF1A); // clear TOV flag
	TCCR1B &= ~( 1<<CS12 ) | ( 1<<CS11 ) | (1<<CS10); //tc off
	TCNT1 = 0x00;
}


/*
 * _3bitMult.c
 *
 * Created: 2/26/2020 11:21:18 AM
 *  Author: argk4
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "util/delay.h"

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	DDRA = 0x00;
	PORTA = 0xFF;
	unsigned char temp = 0x00; 
	unsigned char num1 = 0x00; 
	unsigned char num2 = 0x00;
	
	while (1)
	{
		temp = ~PINA;
		temp = (temp & 0b11110000) >> 4 | (temp & 0b00001111) << 4;
		temp = (temp & 0b11001100) >> 2 | (temp & 0b00110011) << 2;
		temp = (temp & 0b10101010) >> 1 | (temp & 0b01010101) << 1;
		num1 = (temp & 0b00000111);
		num2 = (temp & 0b11100000) >> 5;
		temp = 0;
		
		for( ;num2 > 0; num2-- )
		{
			temp += num1;
		}
		
		temp = (temp & 0b11110000) >> 4 | (temp & 0b00001111) << 4;
		temp = (temp & 0b11001100) >> 2 | (temp & 0b00110011) << 2;
		temp = (temp & 0b10101010) >> 1 | (temp & 0b01010101) << 1;
		num1 = (temp & 0b00000111);
		num2 = (temp & 0b11100000) >> 5;
		temp = 0;
		
		for( ;num2 > 0; num2-- )
		{
			temp += num1;
		}
		
		PORTD = ~temp;
		_delay_ms(1000);
	}
}
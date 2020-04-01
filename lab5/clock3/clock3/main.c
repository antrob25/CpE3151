/*
 * clock3.c
 *
 * Created: 4/1/2020 10:11:51 AM
 * Author : Anthony
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "lcd_libs.h"

void timer_init(void);
void output_time(void);

void pushbutton_poll_init(void); // for pulling operation
void pushbutton_poll(void);	

void external_int_init(void); // for external interrupt operation
ISR(INT0_vect);
ISR(INT1_vect);

ISR(TIMER1_COMPA_vect);

volatile unsigned char HR = 0;
volatile unsigned char MIN = 0;
volatile unsigned char SEC = 0;

int main(void)
{
	lcd_ioinit();
	lcd_init();
	timer_init();
	//pushbutton_poll_init();
	external_int_init();
	sei(); // SREG |= (1<<I);
	
	output_time();
	
    while (1) 
    {
		//pushbutton_poll();
		output_time();
    }
}

void external_int_init(void)
{
	DDRD &= ~( () | () );
	PORTD |= ( () | () );
	
	MCUCR |= ( 1<<ISC11 ) | ( 1<<ISC10 ) | ( 1<<ISC01 ) | ( 1<<ISC00 );
	GICR |= ( 1<<INT1 ) | ( 1<<INT0 );
}

void pushbutton_poll(void)
{
	if (bit_is_clear(PIND, PD2))
	{
		while (bit_is_clear(PIND, PD2));
		HR++;
	}
	
	if (bit_is_clear(PIND, PD3))
	{
		while (bit_is_clear(PIND, PD3));
		HR--;
	}
	
	if (bit_is_clear(PIND, PD2))
	{
		while (bit_is_clear(PIND, PD2));
		MIN++;
	}
	
	if (bit_is_clear(PIND, PD3))
	{
		while (bit_is_clear(PIND, PD3));
		MIN--;
	}
	
	if (bit_is_clear(PIND, PD0))
	{
		while (bit_is_clear(PIND, PD0));
		SEC++;
	}
	
	if (bit_is_clear(PIND, PD1))
	{
		while (bit_is_clear(PIND, PD1));
		SEC--;
	}
}

void pushbutton_poll_init(void)
{
	DDRD &= ~( (1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0) ); // input mode 
	PORTD |= ( (1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0) ); // enable pullup
}

void timer_init()
{
	TCCR1A = 0x00;
	TCCR1A |= (0<<WGM11) | (0<<WGM10); // CTC mode
	
	TCCR1B = 0x00;
	TCCR1B |= (0<<WGM13) | (1<<WGM12); // CTC mode
	
	TCNT1 = 0;
	
	OCR1A = 0xF424;
	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10);
	
	// enable interrupts for compare match with OCR1A
	TIMSK |= (1<<OCR1A);
	
}

ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;
	SEC++;
	if (SEC>59)
	{
		SEC = 0;
		MIN++;
	}
	
	if (MIN>59)
	{
		MIN = 0;
		HR++;
	}
	
	if (HR>23)
	{
		HR = 0;
	}
	
	//update on LCD
	output_time();
}

void output_time(void)
{
	lcd_cmd_write(0x02);
	lcd_write_data( (HR/10) + '0' ); 
	lcd_write_data( (HR%10) + '0' );
	lcd_write_data( ':' );
	
	lcd_write_data( (MIN/10) + '0' );
	lcd_write_data( (MIN%10) + '0' );
	lcd_write_data( ':' );
	
	lcd_write_data( (SEC/10) + '0' );
	lcd_write_data( (SEC%10) + '0' );
}
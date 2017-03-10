/*

Harry Beadle
D4 Thames
Timer (timer.c)

Timers used for PWM output of the controller.
Note: due to hack used to get high precision
output from an 8-bit timer the output is 
required to be low-pass filterd. This has been
tested with a 2K7 R and 6N8 C, and works with
our ESC.

Rotor  Timer  Match Pin
------ ------ ----- -----
Rotor1 Timer0 A     PB3
Rotor2 Timer0 B     PB4
Rotor3 Timer1 A     PD7
Rotor4 Timer1 B     PD6

*/

#include "inc/timer.h"

void update_rotor(rotor* r, uint16_t value)
{
	uint8_t cc = value >> 8;
	uint8_t cp = value | 0xFF;
	if (cc > r->max_cc) {
		cc = r->max_cc;
		if (cp > r->max_cp) {
			cp = r->max_cp;
		}
	}
	if (cc < r->min_cc) {
		cc = r->min_cc;
		if (cp < r->min_cp) {
			cp = r->min_cp;
		}
	}
	r->clear_cycle = cc;
	r->clear_position = cp;
}

void init_timer(void)
{
	// Initalise Timer0
	// Fast PWM, TOP = 0xFF
	TCCR0A = 3;
	// Clear OC0{A, B} on Compare Match
	TCCR0A |= _BV(COM0A1) | _BV(COM0B1);
	// Prescaler: f/8
	TCCR0B = _BV(CS01);
	// Enable Overflow interrupt.
	TIMSK0 = _BV(TOIE0);
	TIFR0 = _BV(TOV0);

	// Initalise Timer2
	// Fast PWM, TOP = 0xFF
	TCCR2A = 3;
	// Clear OC2{A, B} on Compare Match
	TCCR2A |= _BV(COM2A1) | _BV(COM2B1);
	// Prescaler: f/8
	TCCR2B = _BV(CS21);
	// Enable Overflow interrupt.
	TIMSK2 = _BV(TOIE2);
	TIFR2 = _BV(TOV2);

	// Globally enable interrupts.
	sei();
	
	// Set output ports as pullup outputs.
	DDRB = 0xFF;
	PORTB = 0xFF;
	DDRD |= (1<<6 | 1<<7);
	PORTD |= (1<<6 | 1<<7);

}

ISR(TIMER0_OVF_vect)
{
	n0++;
	if (n0 == 117) n0 = 0;
	
	if (n0 == Rotor1.clear_cycle) { 
		OCR0A = Rotor1.clear_position;
	}
	else if (n0 < Rotor1.clear_cycle) {
		OCR0A = 0xFF;
	}
	else {
		OCR0A = 0x00;
	}

	if (n0 == Rotor2.clear_cycle) { 
		OCR0B = Rotor2.clear_position;
	}
	else if (n0 < Rotor2.clear_cycle) {
		OCR0B = 0xFF;
	}
	else {
		OCR0B = 0x00;
	}
}

ISR(TIMER2_OVF_vect)
{
	n2++;
	if (n2 == 117) n2 = 0;

	if (n2 == Rotor3.clear_cycle) { 
		OCR2A = Rotor3.clear_position;
	}
	else if (n2 < Rotor3.clear_cycle) {
		OCR2A = 0xFF;
	}
	else {
		OCR2A = 0x00;
	}

	if (n2 == Rotor4.clear_cycle) { 
		OCR2B = Rotor4.clear_position;
	}
	else if (n2 < Rotor4.clear_cycle) {
		OCR2B = 0xFF;
	}
	else {
		OCR2B = 0x00;
	}
}

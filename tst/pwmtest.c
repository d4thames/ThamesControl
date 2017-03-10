#include <avr/io.h>
#include <avr/interrupt.h>

#include "debug.h"

uint8_t n0 = 0;
uint8_t n2 = 0;
uint8_t A0k, A0p;
uint8_t B0k, B0p;
uint8_t A2k, A2p;
uint8_t B2k, B2p;

ISR(TIMER0_OVF_vect)
{
//	printf("%d\n", OCR0A);

	n0++;
	// Frame en0d: reset n0
	if (n0 == 117) n0 = 0; //117
	
	// Cycle to clear A0
	if (n0 == A0k) OCR0A = A0p;
	else if (n0 < A0k) OCR0A = 0xFF;
	else OCR0A = 0x00;
	// Cycle to clear B0
	if (n0 == B0k) OCR0B = B0p;
	else if (n0 < B0k) OCR0B = 0xFF;
	else OCR0B = 0x00;
}

ISR(TIMER2_OVF_vect)
{
//	printf("%d\n", OCR0A);

	n2++;
	// Frame end: reset n
	if (n2 == 117) n2 = 0; //117

	// Cycle to clear A2
	if (n2 == A2k) OCR2A = A2p;
	else if (n2 < A2k) OCR2A = 0xFF;
	else OCR2A = 0x00;
	// Cycle to clear B2
	if (n2 == B2k) OCR2B = B2p;
	else if (n2 < B2k) OCR2B = 0xFF;
	else OCR2B = 0x00;
}

int main(void)
{
	init_debug_uart0();
	
	// Initalise Timer0
	// Fast PWM, TOP = 0xFF
	TCCR0A = 3;
	// Clear OC0{A, B} on Compare Match
	TCCR0A |= _BV(COM0A1) | _BV(COM0B1);
	// div8 Prescaler
	TCCR0B = _BV(CS01);
	TIMSK0 = _BV(TOIE0);
	TIFR0 = _BV(TOV0);

	// // Initalise Timer2
	TCCR2A = 3;
	// // Clear OC2{A, B} on Compare Match
	TCCR2A |= _BV(COM2A1) | _BV(COM2B1);
	// div8 Prescaler
	TCCR2B = _BV(CS21);
	TIMSK2 = _BV(TOIE2);
	TIFR2 = _BV(TOV2);

	sei();
	
	DDRB = 0xFF;
	PORTB = 0xFF;
	DDRD |= (1<<6 | 1<<7);
	PORTD |= (1<<6 | 1<<7);
	
	printf("Initalised\n");

	int d = 1;

	// High Values
	A0k = B0k = A2k = B2k = 12;
	A0p = B0p = A2p = B2p = 52;
	// Wait for Input
	while ( !(UCSR0A & (1<<RXC0)) );
	UDR0;
	// Low Values	
	A0k = B0k = A2k = B2k = 5;
	A0p = B0p = A2p = B2p = 220;

	while (1) {
		while ( !(UCSR0A & (1<<RXC0)) );
		A0p += d * 15;
		if ((A0p < 10) && (d == 1)) A0k++;
		if ((A0p > 245) && (d == -1)) A0k--;
		//if ((A0k = 5) && (A0p < 220) && (d == -1)) d = 1;
		if ((A0p > 20) && (A0k == 12)) d = -1;
		UDR0;

		while ( !(UCSR0A & (1<<RXC0)) );
		B0p += d * 15;
		if ((B0p < 10) && (d == 1)) B0k++;
		if ((B0p > 245) && (d == -1)) B0k--;
		//if ((B0k = 5) && (B0p < 220) && (d == -1)) d = 1;
		if ((B0p > 20) && (B0k == 12)) d = -1;
		UDR0;

		while ( !(UCSR0A & (1<<RXC0)) );
		A2p += d * 15;
		if ((A2p < 10) && (d == 1)) A2k++;
		if ((A2p > 245) && (d == -1)) A2k--;
		//if ((A2k = 5) && (A2p < 220) && (d == -1)) d = 1;
		if ((A2p > 20) && (A2k == 12)) d = -1;
		UDR0;

		while ( !(UCSR0A & (1<<RXC0)) );
		B2p += d * 15;
		if ((B2p < 10) && (d == 1)) B2k++;
		if ((B2p > 245) && (d == -1)) B2k--;
		//if ((B2k = 5) && (B2p < 220) && (d == -1)) d = 1;
		if ((B2p > 20) && (B2k == 12)) d = -1;
		UDR0;
	}
}
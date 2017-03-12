/*

Harry Beadle
D4 Thames
Communications (comms.c)

Input                    Perf   Pin
------------------------ ------ -----
UART Rx from MPU Decoder UART0  PD0 (I think)
UART Tx from MPU Decoder UART0  PD1 (I think)
UART Rx from Controller  UART1  PD2 (I think)

*/

#include "inc/comms.h"

void init_comms(void)
{
	// Initialise UART0 and UART1
	// Set Badu Rate.
	UBRR0H = (F_CPU/(57600*16L)-1) >> 8;
	UBRR1H = (F_CPU/(BAUD*16L)-1) >> 8;
	UBRR0L = (F_CPU/(57600*16L)-1);
	UBRR1L = (F_CPU/(BAUD*16L)-1);
	// Enable Tx, Rx, Tx Interupt, Rx Interupt.
	UCSR0B = _BV(RXEN0) | _BV(RXCIE0) | _BV(TXEN0) | _BV(TXCIE0);
	UCSR1B = _BV(RXEN1) | _BV(RXCIE1) | _BV(TXEN1) | _BV(TXCIE1);
	// 1 Start, 8 Data and 1 Stop bit.
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
	UCSR1C = _BV(UCSZ10) | _BV(UCSZ11);

	state = control;
	nstate = control;
}

// MPU Decoder
ISR(USART0_RX_vect)
{
	// UART Entry from MPU Decoder
	state = nstate;
	temp_byte = UDR0;
	switch (state) {
		case control:
			PORTB |=  _BV(PB0);
			// If valid control bit, store it and go onto the next
		    // byte, if not keep waiting for a valid one, we *should*
			// eventually sync up.
			// bad_control = 1;
			if ((temp_byte & 0xF0) == 0xF0) {
			// 	// Top nibble is 0xF
			// 	if ((temp_byte & 0x0F) != 0x00) {
			// 		// Data nibble is not 0
			// 		if ((temp_byte & 0x0F) <= 0x03) {
			// 			// Data nibble is not above 3
							// bad_control = 0;
							control_byte = temp_byte;
							nstate = high;
					// }
				// } 
			}
			// if (bad_control) {
			// 	// Invalid Control Byte
			// 	PORTB |= _BV(PB1);
			// 	nstate = control;
			// }
			PORTB &= ~_BV(PB0);
			break;
		case high:
			// Store the high byte, wait for the low byte.
			high_byte = temp_byte;
			nstate = low; 
			break;
		case low:
			// Store the low byte, switch on the control byte, put the
			// Rx'd data wherever it belongs, and tell the control
			// System it's been updated.
			low_byte = temp_byte;
			switch (control_byte) {
				case PITCH_SYMBOL:
					pitch = high_byte << 8 | low_byte;
					pitch_update = 1;
					break;
				case ROLL_SYMBOL:
					roll = high_byte << 8 | low_byte;
					roll_update = 1;
					break; 
				case YAW_SYMBOL:
					yaw = high_byte << 8 | low_byte;
					yaw_update = 1;
					break;
				default:
					break;
			}
			nstate = control;
			break;
	}
}

// Remote Controller Communications
ISR(USART1_RX_vect)
{
	temp_byte_rc = UDR1;
	control_code = 0xC0 & temp_byte_rc;
	data_byte = 0x3F & temp_byte_rc; 
	switch (control_code) {
		case S_THROTTLE:
			if (data_byte != 0) {
				thrust = 1495 + data_byte * 25;
			}
			break; 
		case S_PITCH:
			pitch_system.setpoint = data_byte;
			break;
		case S_ROLL:
			roll_system.setpoint = data_byte;
			break;
		case S_YAW:
			yaw_system.setpoint = data_byte;
			break;
	}
}

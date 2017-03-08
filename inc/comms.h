/*

Harry Beadle
D4 Thames
Communications (comms.h)

Headerfile for UART ISRs and initalisation.

*/

#ifndef _COMMS_H_
	#define _COMMS_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>

	#include "rc-symbols.h"
	#include "mpu-symbols.h"
	#include "drone.h"

	#define BAUD 9600

	// MPU Decoder Communications
	uint8_t temp_byte, control_byte, low_byte, high_byte;
	enum {control, high, low} state, nstate;
	ISR(USART0_RX_vect);

	// Remote Controller Communications
	uint8_t temp_byte_rc, control_code, data_byte;
	ISR(USART1_RX_vect);

	#include "../comms.c"

#endif
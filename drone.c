/*

Harry Beadle
D4 Thames
Drone (drone.c)

Combines the function of all other modules into a complete system.

Rotor numbers and directions:

\ /  \ /   /\   1 and 4 are Clockwise
 1    2    /\   2 and 3 are Anticlockwise
/ \==/ \   /\  
  ====     /\   1 = thrust + pitch + roll + yaw
\ /==\ /   /\   2 = thrust + pitch - roll - yaw
 3    4    /\   3 = thrust - pitch + roll - yaw
/ \  / \   /\   4 = thrust - pitch - roll + yaw

Control systems are utilised to control the pitch roll and yaw of the
drone. The output of the controller is in servo-compliant PWM:

50Hz, 1ms pulse low, 2ms pulse high.
1ms -> ???? on CM register.
2ms -> ???? on CM register.

Outputs are restricted to "Compare Match" outputs on the AVR. You need
four of them and the m644p gives you four symmetrical 8-bit ones.

Rotor  Timer  Match Pin
------ ------ ----- -----
Rotor1 Timer0 A     PB3
Rotor2 Timer0 B     PB4
Rotor3 Timer1 A     PD7
Rotor4 Timer1 B     PD6

*/

int main(void) {
	// Initialise
	// Initialise Counter 0
	// Initialise Counter 2

	// Loop Forever
	while (1) {
		// Update Control Systems
		if (pitch_update) {
			pitch_adjust = tick_control(pitch, pitch_system);
			pitch_update = 0;
		} 
		else {
			pitch_adjust = 0;
		}
		
		if (roll_update) {
			roll_adjust = tick_control(roll, roll_system);
			roll_update = 0;
		} 
		else {
			roll_adjust = 0;
		}
		if (yaw_update) {
			yaw_adjust = tick_control(yaw, yaw_system);
			yaw_update = 0;
		} 
		else {
			yaw_adjust = 0;
		}
		// Update PWM Outputs
		rotor1 = thrust + pitch_adjust + roll_adjust + yaw_adjust;
		rotor2 = thrust + pitch_adjust - roll_adjust - yaw_adjust;
		rotor3 = thrust - pitch_adjust + roll_adjust - yaw_adjust;
		rotor4 = thrust - pitch_adjust - roll_adjust + yaw_adjust;
	}
}


/*

Communications

Input                    Perf   Pin
------------------------ ------ -----
UART Rx from MPU Decoder UART0  PD0 (I think)
UART Tx from MPU Decoder UART0  PD1 (I think)
UART Rx from Controller  UART1  PD2 (I think)

*/

// MPU Decoder
ISR(USART0_RX_vect)
{
	// UART Entry from MPU Decoder
	state = nstate;
	temp_byte = UDR0;
	switch (mode) {
		case control:
			// If valid control bit, store it and go onto the next
		    // byte, if not keep waiting for a valid one, we *should*
			// eventually sync up.
			if ((temp_byte & 0xF0)            // Control Upper Nibble
				&& (temp_byte & 0x0F <= 3)    // Symbol Nibble <= 3
				&& (temp_byte & 0x0F >= 1)) { // Symbol Nibble >= 1
				// Valid Control Byte
				control_byte = temp_byte;
				nstate = high;
			}
			else {
				// Invalid Control Byte
				nstate = control;
			}
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
				case ROLL_SYBOL:
					roll = high_byte << 8 | low_byte;
					roll_update = 1;
					break; 
				case YAW_SYMBOL:
					yaw = high_byte << 8 | low_byte;
					yaw_update = 1;
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
	data = 0x3F & temp_byte_rc; 
	switch (control_code) {
		case S_THROTTLE:
			throttle = data;
			break; 
		case S_PITCH:
			pitch.setpoint = data;
			break;
		case S_ROLL:
			roll.setpoint = data;
			break;
		case S_YAW:
			yaw.setpoint = data;
			break;
	}
}

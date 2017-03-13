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
drone. The output of the controller is in servo-compliant PWM.

Rotor  Timer  Match Pin
------ ------ ----- -----
Rotor1 Timer0 A     PB3
Rotor2 Timer0 B     PB4
Rotor3 Timer2 B     PD6
Rotor4 Timer2 A     PD7

*/

#include "inc/drone.h"

#define S_R1 0xF4
#define S_R2 0xF5
#define S_R3 0xF6
#define S_R4 0xF7

buffer8 rotor_buffer;

void update_rotor(uint8_t r, uint16_t t)
{
	while (!(UCSR1A & _BV(UDRE1)));
	UDR1 = r;
	while (!(UCSR1A & _BV(UDRE1)));
	UDR1 = t >> 8;
	// UDR1 = 0;
	while (!(UCSR1A & _BV(UDRE1)));
	UDR1 = t;
	// UDR1 = 0;
}

ISR(USART1_TX_vect)
{
	if (buffer8_rdy(&rotor_buffer)) {
		UDR1 = buffer8_pop(&rotor_buffer);
	}
}

int main(void)
{	
	// Initalise
	init_comms();
	// Gloally Enable interrupts.
	sei();

	// Loop Forever
	while (1) {
		// Update Control Systems
		pitch_adjust = tick_control(pitch, &pitch_system);
		roll_adjust = tick_control(roll, &roll_system);
		//yaw_adjust = tick_control(yaw, &yaw_system);
		// Update Rotors
		update_rotor(S_R1, thrust + pitch_adjust + roll_adjust + yaw_adjust);
		update_rotor(S_R2, thrust + pitch_adjust - roll_adjust - yaw_adjust);
		update_rotor(S_R3, thrust - pitch_adjust + roll_adjust - yaw_adjust);
		update_rotor(S_R4, thrust - pitch_adjust - roll_adjust + yaw_adjust);
	}
}

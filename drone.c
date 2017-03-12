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

int main(void)
{	
	// Initalise
	init_timer();
	init_comms();
	// Gloally Enable interrupts.
	sei();

	// Loop Forever
	while (1) {
		// Update Control Systems
		pitch_adjust = tick_control(pitch, &pitch_system);
		roll_adjust = tick_control(roll, &roll_system);
		yaw_adjust = tick_control(yaw, &yaw_system);
		// Update Rotors
		update_rotor(&Rotor1, thrust + pitch_adjust + roll_adjust + yaw_adjust);
		update_rotor(&Rotor2, thrust + pitch_adjust - roll_adjust - yaw_adjust);
		update_rotor(&Rotor3, thrust - pitch_adjust + roll_adjust - yaw_adjust);
		update_rotor(&Rotor4, thrust - pitch_adjust - roll_adjust + yaw_adjust);
	}
}

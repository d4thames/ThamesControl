/*.

Harry Beadle
D4 Thames
Drone (drone.c)

Combines the function of all other modules into a complete system.

*/

#include "drone.h"

int main(void)
{
	// Initialise Buffers
	// ***TODO*** This should be in the communications file.
	buffer8 controlBuf;
	buffer16 thrustBuf;
	buffer16 pitchBuf;
	buffer16 rollBuf;
	buffer16 yawBuf;

	// Initialise Mode
	mode = flight;

	while (1) {
		switch (mode) {
			case flight:
				if (buffer16_rdy(pitchBuf)) {
					// Control pitch
				}
				if (buffer16_rdy(rollBuf)) {
					// Control roll
				}
				if (buffer16_rdy(yawBuf)) {
					// Control yaw
				}
				if (buffer16_rdy(thrustBuf)) {
					// Adjust thrust
				}
				/// Update the system
				// Change the comparator registers to change PWM
				// duty cycle.
				// ***TODO*** 
				break;
			case tuning:
				if (control_buffer_ready()) {
					control_data = control_buffer_pop();
					switch (control_data) {
						default:
							break;
					}
				}
				break;
		}
	}
}
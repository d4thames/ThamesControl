/*

Harry Beadle
D4 Thames
Drone (drone.h)

Headerfile combineing all other modules into a complete system.

*/

#ifndef _DRONE_H_
	#define _DRONE_H_

		#include <avr/io.h>

		// Main Control Loop
		uint16_t thrust = 50000;
		uint16_t pitch = 0;
		uint16_t roll = 0;
		uint16_t yaw = 0;

		uint8_t pitch_update = 0;
		uint8_t roll_update = 0;
		uint8_t yaw_update = 0;

		double pitch_adjust, roll_adjust, yaw_adjust;

		// Include System Specifications
		#include "control.h"
		#include "pitch.h"
		#include "roll.h"
		#include "yaw.h"

		// Include 
		#include "rc-symbols.h"
		#include "comms.h"
		#include "buffer.h"

		int main(void);

#endif
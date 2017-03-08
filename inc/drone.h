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
		volatile uint16_t pitch, roll, yaw, thrust;
		volatile uint8_t pitch_update, roll_update, yaw_update;
		uint8_t pitch_adjust, roll_adjust, yaw_adjust;

		// Include System Specifications
		#include "control.h"
		#include "pitch.h"
		#include "roll.h"
		#include "yaw.h"

		// Include 
		#include "rc-symbols.h"
		#include "comms.h"
		#include "timer.h"

		int main(void);

#endif
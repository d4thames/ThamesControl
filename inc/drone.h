/*

Harry Beadle
D4 Thames
Drone (drone.h)

Headerfile including all subsystems.

*/

#ifndef _DRONE_H_
	#define _DRONE_H_
		
		// Include Control Loops
		#include "control.h"

		// Include Default Control Configurations
		#include "pitch.h"
		#include "roll.h"
		#include "yaw.h"

		// Include Buffer Systems
		// TODO
		
		enum {flight, tuning} mode;

		char control_data;

#endif
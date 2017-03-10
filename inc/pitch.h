/*

Harry Beadle
D4 Thames
Pitch Control (pitch.h)

Pitch control system.

*/

#ifndef _PITCH_H_
	#define _PITCH_H_

		system pitch_system = {
			.setpoint = 0,
			.time_period = 0,

			.o_max = 0,
			.o_min = 0,

			.k_p = 0.3,
			.k_i = 0.1,
			.k_d = 0.2,

			.i_max = 1,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
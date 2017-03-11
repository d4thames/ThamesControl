/*

Harry Beadle
D4 Thames
Pitch Control (pitch.h)

Pitch control system.

*/

#ifndef _PITCH_H_
	#define _PITCH_H_

		system pitch_system = {
			.setpoint = 0x0022,
			.time_period = 0.004,

			.o_max = 300,
			.o_min = -300,

			.k_p = 2.5,
			.k_i = 0,
			.k_d = 0.5,

			.i_max = 0,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
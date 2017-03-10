/*

Harry Beadle
D4 Thames
Roll Control (roll.h)

Roll control system.

*/

#ifndef _ROLL_H
	#define _ROLL_H

		system roll_system = {
			.setpoint = 0,
			.time_period = 0.004,

			.o_max = 150,
			.o_min = -150,

			.k_p = 10,
			.k_i = 0,
			.k_d = 0,

			.i_max = 1,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
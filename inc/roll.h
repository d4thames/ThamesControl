/*

Harry Beadle
D4 Thames
Roll Control (roll.h)

Roll control system.

*/

#ifndef _ROLL_H
	#define _ROLL_H

		system roll_system = {
			.setpoint = 0x0000,
			.time_period = 0.004,

			.o_max =  10000,
			.o_min = -10000,

			.k_p = 5,
			.k_i = 0,
			.k_d = 0,

			.i_max = 0,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
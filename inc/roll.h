/*

Harry Beadle
D4 Thames
Roll Control (roll.h)

Roll control system.

*/

#ifndef _ROLL_H
	#define _ROLL_H

		system roll_system = {
			.setpoint = 327682,
			.time_period = 0,

			.o_max = 0,
			.o_min = 0,

			.k_p = 10,
			.k_i = 10,
			.k_d = 10,

			.i_max = 1,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
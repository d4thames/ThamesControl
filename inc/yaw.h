/*

Harry Beadle
D4 Thames
Yaw Control (yaw.h)

Yaw control system.

*/

#ifndef _YAW_H_
	#define _YAW_H_

		system yaw_system = {
			.setpoint = 0,
			.time_period = 0,

			.o_max = 10,
			.o_min = -10,

			.k_p = 0.3,
			.k_i = 0.1,
			.k_d = 0.2,

			.i_max = 1,

			.e_p = 0,
			.e_i = 0,
			.e_d = 0
		};

#endif
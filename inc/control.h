/*

Harry Beadle
D4 Thames
Control (control.h)

PID Control

*/
#ifndef _CONTROL_H_
	#define _CONTROL_H_

		typedef struct {
			double setpoint, time_period;
			double o_max, o_min;
			double k_p, k_i, k_d;
			double i_max;
			double e_p, e_i, e_d;
		} system;

		int tick_control(int input, system* s);

#endif
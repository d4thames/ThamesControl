/*

Harry Beadle
D4 Thames
Control (control.c)

PID Control

*/

#include "inc/control.h"

TIR0 = (uint8_t) tick_control(yaw_buffer_pop(), yaw);


double tick_control(double input, system* s)
{
	// Calculate Errors on this tick.
	double current_error;
	current_error = s->setpoint - input;
	s->e_d = (current_error - s->e_p)/s->time_period;
	s->e_i += s->k_i * s->e_p * s->time_period;
	s->e_p =  current_error;

	// Handle Maximum Integral Error
	if (s->e_i > s->i_max || s->e_i < -s->i_max) 
		s->e_i = 0;

	// Calculate Output
	double output;
	output += s->k_p * s->e_p;
	output += s->e_i; // k_i already applied.l
	output += s->k_d * s->e_d;

	// Handle Maximum Output
	if (output > s->o_max)
		output = s->o_max;
	if (output < s->o_min)
		output = s->o_min;

	return output;
}


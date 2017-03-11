/*

Harry Beadle
D4 Thames
Control (control.c)

PID Control

*/

#include "inc/control.h"

double tick_control(uint16_t in_value, system* s)
{
	// Right and left aligned inputs;
	double input_r, input_l, input;
	input_r = in_value;
	input_l = 65535 - in_value;
	if (input_r < input_l) input = input_r;
	else input = -input_l;

	// Calculate Errors on this tick.
	double current_error = s->setpoint - input;
	s->e_d = (current_error - s->e_p);
	s->e_i += s->k_i * current_error * s->time_period;
	s->e_p = current_error;

	// Handle Maximum Integral Error
	if (s->e_i > s->i_max || s->e_i < -s->i_max) 
		s->e_i = 0;

	// Calculate Output
	double output = 0;
	output += s->k_p * s->e_p;
	output += s->e_i; // k_i already c.
	output += s->k_d * s->e_d;

	// Handle Maximum Output
	if (output > s->o_max)
		output = s->o_max;
	if (output < s->o_min)
		output = s->o_min;

	return output;
}


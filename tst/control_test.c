/*

Harry Beadle
D4 Thames
Control Test (control_test.c)

Test for PID Control

*/

#include <stdio.h>
#include "../inc/control.h"

system s1;

double update_system(double input, double s)
{
	double max = 0.5;
	double a;
	if (input > max)
		a = max;
	else if (input < -max)
		a = -max;
	else
		a = input;

	return s + a;
}

int main(void)
{
	double sys = 10;
	double i;

	s1.setpoint = 5;
	s1.time_period = 1; 
	s1.o_max = 20;
	s1.o_min = -20;
	s1.k_p = 1.5;
	s1.k_i = 0.3; 
	s1.k_d = 0.5;
	s1.i_max = 1;
	s1.e_p = 0; 
	s1.e_i = 0;
	s1.e_d = 0;

	printf("t, System, Error_p, Error_i, Error_d, input\n");
	for (int t = 0; t < 100; t++) {
		i = tick_control(sys, &s1);
		sys = update_system(i, sys);
		printf("%d, %f, %f, %f, %f, %f\n", t, sys, s1.e_p, s1.e_i, s1.e_d, i);
	}

	return 0;
}
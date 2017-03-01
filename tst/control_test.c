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
	//double max = 20;
	double a;

	//input *= 1.1;
	//if (input > max)
	//	a = max;
	//else if (input < -max)
	//	a = -max;
	//else
	//	a = input;

	return s + input * 1.61;
}

int main(void)
{
	double sys = 10;
	double i;

	s1.setpoint = 5;
	s1.time_period = 1; 
	s1.o_max = 200;
	s1.o_min = -200;
	s1.k_p = 0.982;
	s1.k_i = 0.512; 
	s1.k_d = 0.123;
	s1.i_max = 2;
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
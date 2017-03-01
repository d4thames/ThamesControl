/*

Harry Beadle
D4 Thames
Roll Control (roll.h)

Roll control system.

*/

system roll;

roll.setpoint = 0;
roll.time_period = 0;

roll.o_max = 10
roll.o_min = -10

roll.k_p = 0.3
roll.k_i = 0.1
roll.k_d = 0.2

roll.i_max = 1

roll.e_p = 0
roll.e_i = 0
roll.e_d = 0
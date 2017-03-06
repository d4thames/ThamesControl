/*

Harry Beadle
D4 Thames
Roll Control (roll.h)

Roll control system.

*/

system roll_system;

roll_system.setpoint = 0;
roll_system.time_period = 0;

roll_system.o_max = 10
roll_system.o_min = -10

roll_system.k_p = 0.3
roll_system.k_i = 0.1
roll_system.k_d = 0.2

roll_system.i_max = 1

roll_system.e_p = 0
roll_system.e_i = 0
roll_system.e_d = 0
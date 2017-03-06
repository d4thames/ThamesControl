/*

Harry Beadle
D4 Thames
Pitch Control (pitch.h)

Pitch control system.

*/

system pitch_system;

pitch_system.setpoint = 0;
pitch_system.time_period = 0;

pitch_system.o_max = 10
pitch_system.o_min = -10

pitch_system.k_p = 0.3
pitch_system.k_i = 0.1
pitch_system.k_d = 0.2

pitch_system.i_max = 1

pitch_system.e_p = 0
pitch_system.e_i = 0
pitch_system.e_d = 0
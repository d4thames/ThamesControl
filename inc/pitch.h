/*

Harry Beadle
D4 Thames
Pitch Control (pitch.h)

Pitch control system.

*/

system pitch;

pitch.setpoint = 0;
pitch.time_period = 0;

pitch.o_max = 10
pitch.o_min = -10

pitch.k_p = 0.3
pitch.k_i = 0.1
pitch.k_d = 0.2

pitch.i_max = 1

pitch.e_p = 0
pitch.e_i = 0
pitch.e_d = 0
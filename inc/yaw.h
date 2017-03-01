/*

Harry Beadle
D4 Thames
Yaw Control (yaw.h)

Yaw control system.

*/

system yaw;

yaw.setpoint = 0;
yaw.time_period = 0;

yaw.o_max = 10
yaw.o_min = -10

yaw.k_p = 0.3
yaw.k_i = 0.1
yaw.k_d = 0.2

yaw.i_max = 1

yaw.e_p = 0
yaw.e_i = 0
yaw.e_d = 0
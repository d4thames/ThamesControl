/*

Harry Beadle
D4 Thames
Yaw Control (yaw.h)

Yaw control system.

*/

system yaw_system;

yaw_system.setpoint = 0;
yaw_system.time_period = 0;

yaw_system.o_max = 10
yaw_system.o_min = -10

yaw_system.k_p = 0.3
yaw_system.k_i = 0.1
yaw_system.k_d = 0.2

yaw_system.i_max = 1

yaw_system.e_p = 0
yaw_system.e_i = 0
yaw_system.e_d = 0
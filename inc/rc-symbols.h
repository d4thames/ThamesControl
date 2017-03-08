/*

Harry Beadle
D4 Thames
Remote Control Symbols (rc-symbols.h)

Control (n), Data (D), Control Code: 
00DD DDDD 0x00
01DD DDDD 0x40
10DD DDDD 0x80
11DD DDDD 0xC0

*/

#ifndef _RC_SYMBOLS_H_
	#define _RC_SYMBOLS_H_

		// Remote Control Input Symbols
		#define S_THROTTLE 0x00
		#define S_PITCH    0x80
		#define S_ROLL     0xC0
		#define S_YAW      0x40

#endif
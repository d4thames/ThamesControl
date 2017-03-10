/*

Harry Beadle
D4 Thames
Timer (timer.h)

Headerfile for the timers outputting PWM to the motors.

*/

#ifndef _TIMER_H_
	#define _TIMER_H_

		#include <avr/io.h>
		#include <avr/interrupt.h>

		uint8_t n0 = 0;
		uint8_t n2 = 0;

		typedef struct {
			uint8_t clear_cycle;
			uint8_t clear_position;
			uint8_t min_cc;
			uint8_t min_cp;
			uint8_t max_cc;
			uint8_t max_cp;
		} rotor;

		rotor Rotor1 = {
			.clear_cycle = 5,
			.clear_position = 215,
			.max_cc = 12,
			.max_cp = 40,
			.min_cc = 5,
			.min_cp = 215
		}; 
		rotor Rotor2 = {
			.clear_cycle = 5,
			.clear_position = 215,
			.max_cc = 12,
			.max_cp = 40,
			.min_cc = 5,
			.min_cp = 215
		}; 
		rotor Rotor3 = {
			.clear_cycle = 5,
			.clear_position = 215,
			.max_cc = 12,
			.max_cp = 40,
			.min_cc = 5,
			.min_cp = 215
		}; 
		rotor Rotor4 = {
			.clear_cycle = 5,
			.clear_position = 215,
			.max_cc = 12,
			.max_cp = 40,
			.min_cc = 5,
			.min_cp = 215
		};

		void init_timer(void);
		void update_rotor(rotor* r, uint16_t value);

		ISR(TIMER0_OVF_vect);
		ISR(TIMER2_OVF_vect);

		#include "../timer.c"

#endif
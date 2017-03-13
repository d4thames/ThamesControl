/*

Harry Beadle
D4 Thames
Buffer (buffer.h)

Rotational FIFO buffers for sensor, RC and tuning data.

*/

#ifndef _BUFFER_H_
	#define _BUFFER_H_

		#include <avr/io.h>
		#define BUFFER_SIZE 128

		// 8-Bit Buffer
		typedef struct {
			uint8_t buffer[128];
			uint8_t index;
			uint8_t outdex;
		} buffer8;
		uint8_t buffer8_pop(buffer8* b);
		void buffer8_add(buffer8* b, uint8_t c);
		int buffer8_rdy(buffer8* b);

		// 16-Bit Buffer
		typedef struct {
			uint16_t buffer[128];
			uint8_t index;
			uint8_t outdex;
		} buffer16;
		uint16_t buffer16_pop(buffer16* b);
		void buffer16_add(buffer16* b, uint16_t);
		int buffer16_rdy(buffer16* b);

		#include "../buffer.c"

#endif
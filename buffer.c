/*

Harry Beadle
D4 Thames
Buffer (buffer.c)

Rotational FIFO buffers for sensor, RC and tuning data.

*/

#include "inc/buffer.h"

//////////////////
// 8-Bit Buffer //
//////////////////

uint8_t buffer8_pop(buffer8* b)
{
	// Store the value at the outdex ready 
	// for return and increment outdex.
	uint8_t rv = b->buffer[b->outdex];
	b->outdex++;
	// If we're at the end of the buffer, 
	// go back to the start.
	if (b->outdex == BUFFER_SIZE)
		b->outdex = 0;
	// Return the stored value.
	return rv;
}

void buffer8_add(buffer8* b, uint8_t c)
{
	// Set the value at the index location
	// of the buffer to the input value and
	// increment the index.
	b->buffer[b->index] = c;
	b->index++;
	// If we're at the end of the buffer, 
	// go back to the start.
	if (b->index == BUFFER_SIZE)
		b->index = 0;
}

int buffer8_rdy(buffer8* b)
{
	// If the buffer is ready the index
	// will not equal the outdex.
	return b->index != b->outdex;
}

///////////////////
// 16-Bit Buffer //
///////////////////

uint16_t buffer16_pop(buffer16* b)
{
	// Store the value at the outdex ready 
	// for return and increment outdex.
	uint16_t rv = b->buffer[b->outdex++];
	// If we're at the end of the buffer, 
	// go back to the start->
	if (b->outdex == BUFFER_SIZE)
		b->outdex = 0;
	// Return the stored value.
	return rv;
}
void buffer16_add(buffer16* b, uint16_t c)
{
	// Set the value at the index location
	// of the buffer to the input value and
	// increment the index.
	b->buffer[b->index++] = c;
	// If we're at the end of the buffer, 
	// go back to the start->
	if (b->index == BUFFER_SIZE)
		b->index = 0;
}

int buffer16_rdy(buffer16* b)
{
	// If the buffer is ready the index
	// will not equal the outdex.
	return b->index != b->outdex;
}
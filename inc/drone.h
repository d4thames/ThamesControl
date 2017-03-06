// Include 
#include "rc-symbols.h"
#include "control.h"

// Include System Specifications
#include "pitch.h"
#include "roll.h"
#include "yaw.h"

// Main Control Loop
static volatile uint16_t pitch, roll, yaw, thrust;
static volatile uint8_t pitch_update, roll_update, yaw_update;
uint8_t pitch_adjust, roll_adjust, yaw_adjust;
uint8_t rotor1, rotor2, rotor3, rotor4;
int main(void);

// MPU Decoder Communications
uint8_t temp_byte, control_byte, low_byte, high_byte;
enum {control, high, low} state, nstate;
ISR(USART0_RX_vect);

// Remote Controller Communications
uint8_t control_code, data_byte;
ISR(USART1_RX_vect);
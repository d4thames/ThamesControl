# ThamesControl

Control System for the Thames Drone.

## Drone (`drone.c`)

The drone file is the wrapper for the whole system, it relates each of the sub
modules together and executes the main control sequence.

Therefore this file contains the `main` function, which simply applies the control systems to their respective parameters and then adjust the outputs of the system accordingly.

## Timers (`timer.c`)

Because the `m644p` device being used only has one 16-bit timer, we have to use the two 8-bit timers instead in order to output PWM to the ECSs to control the motors.

The system runs at 50Hz, with the low point of the symbol occurring at 1ms and the high at 2ms, a classical servo signal. 

This is achieved by running in fast PWM mode and running multiple cycles of the timer per frame. The timer is set to run at 5.8kHz, which means for ~50Hz we need 117 cycles per frame.

At the start of each frame the Output Compare Match Register (`OCRnx`) is set to `0xFF` causing the signal to be high for the entire frame, in the frame in which we need to clear `OCRnx` is set to the clear position, and after that cycle `OCRnx` is set to `0x00` in order to keep the signal low.

This does cause a small amount of noise at 5.8kHz, as there is an amount of time where the timer is reset before the Output Compare Match pin is set or cleared. This is circumvented by low pass filtering the output of the system with a 2.7k resistor and a 5.8nF Capacitor.

Each of the four motors is given it's own `rotor` structure where it's current speed is stored as the frame and position in the frame where the output must be cleared, they also have high and low values to avoid triggering a ESC to panic while in flight.

## Communications (`comms.c`)

The communication scheme takes advantage of both of the `m644p`'s hardware USART peripherals. `USART0` is used to receive data from the MPU Decoder module and `USART1` is used to receive remote control data.

The data schema for each of these systems can be found in `mpu-symbols.h` and `rc-symbols.h`.

Interrupts are used for both systems, the MPU data is simply fed into the telemetry registers and the remote control data is used to change the set-points in each of the control systems for the three degrees of freedom (DOFs).

## Control (`control.c`)

The third and final aspect of the control module is the PID control itself. This is actually the simplest part of the system, consisting of a `system` structure that defines proportional, integral and differential coefficients, running errors, the set-point, time period of sensor data, and the integral threshold.

When `tick_control()` is called on a system the errors are calculated using the previous errors stored in the structure, and the output is generated.

In order to prevent integral wind up there has been an integral threshold set where the integral part of the control only comes into play where there is a small amount of steady state error.

A system for each of the three DOFs is defined in their respective header files: `pitch.h`, `roll.h` and `yaw.h`.

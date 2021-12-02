/*
 * ping.h
 *
 *  Created on: Oct 26, 2021
 *      Author: jminardi
 */

#ifndef PING_H_
#define PING_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"

enum states
{
    LOW, HIGH, DONE
}; // Set by ISR

/*
 * Method used to initialize ping sensor's GPIO registers and timer
 * registers based on settings such as capture mode, selecting timer#,
 * selecting both positive and negative edge detection, etc.
 */
void ping_init(void);

/*
 * Method to initilize and start up timer interrupt registers.
 */
void ping_interrupt_init(void);

/*
 * Called when rising or falling event occurs for Timer
 */
void ping_timer3b_handler(void);

/*
 * Disables interrupt, sets PB3 to GPIO output, sends trigger,
 * sets PB3 back to TIMER input device, clears interrupts, enables interrupt
 *
 *  returns distance (Distance in cm)
 */
float ping_read(void);

/*
 * Method used to send an output signal or "trigger"
 * in order for signal to bounce off of object
 */
void ping_send_trigger(void);

#endif /* PING_H_ */

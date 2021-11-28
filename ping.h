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

void ping2_init(void);
void ping_interrupt_init(void);
void ping_timer3b_handler(void);
float ping_read(void);
void ping_send_trigger(void);



#endif /* PING_H_ */

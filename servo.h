/*
 * servo.h
 *
 *  Created on: Nov 2, 2021
 *      Author: jminardi
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>


void servo_init1(void);
int servo_move1(int degrees);
int convertDegreesBOT13(int degrees);


#endif /* SERVO_H_ */

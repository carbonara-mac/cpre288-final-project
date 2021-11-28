/*
 *  servo.c
 *
 *  Servo motor functionality
 *
 *  Created on: Nov 2, 2021
 *  Author: James Minardi
 *
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "math.h"
#include "timer.h"

/*
 * Used to convert degrees to the match value used in servo_move
 */
extern int right_calibration_value; // from main.c
extern int left_calibration_value;

/*
 * Current angle of the servo motor
 * READ ONLY
 */
int currentAngle;

/*
 *  Initialize servo motor
 */
void servo_init1(void);

/*
 * Move servo motor to specified degrees
 */
int servo_move1(int degrees);

/*
 * Convert degrees to match value for timer device
 */
int degrees_to_match(int degrees);


#endif /* SERVO_H_ */

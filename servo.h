/*
 *  servo.h
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
extern int right_calibration_value; // main.c
extern int left_calibration_value;  // main.c

/*
 * Current angle of the servo motor
 * READ ONLY
 */
int currentAngle;

/*
 *  Initialize servo motor using Port B pin 5, and Timer 1B
 *  Timer 1B is set to split 16-bit count down, periodic, PWM timer
 */
void servo_init1(void);

/*
 * Moves servo motor to specified degrees.
 *
 * @param degrees - Degrees to move servo motor to
 * @return match - Value for the specified degrees for debugging
 */
int servo_move1(int degrees);

/**
 * Converts degrees to match value for the timer. Uses the left_calibration_value and right_calibration_value set by the user by using
 * servo_calibration() in scan.h
 *
 * @param degrees - Degrees to convert to timer match value
 * @return timer - Match value for @param degrees
 */
int degrees_to_match(int degrees);


#endif /* SERVO_H_ */

/*
 * calibration.h
 *
 *  Small program to calibrate the servo motor.
 *  User moves servo to 0 and 180 degrees and sets those values to
 *  right_calibration_value and left_calibration_value in main.c
 *
 *  Note: Intended to run entirely independent
 *      _SERVO_CALIBRATION 1
 *      _IR_CALIBRATION 0
 *      _MAIN 0
 *
 *  Created on: Nov 30, 2021
 *      Author: jminardi
 *
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_
#include "button.h"
#include "lcd.h"
#include "servo.h"
#include "Timer.h"
#include "ping.h"
#include "adc.h"

void servo_calibration(void);
void IR_calibration(void);

#endif /* CALIBRATION_H_ */

/**
 * main.c
 */

// Run each independently of each other
#define _SERVO_CALIBRATION 0
#define _IR_CALIBRATION 1
#define _MAIN 0

#include <stdio.h>
#include "scan.h"
#include "adc.h"
#include "lcd.h"
#include "Timer.h"
#include "servo.h"
#include "ping.h"

/*
 * Run _SERVO_CALIBRATION by itself to find values for these. Currently set for bot06
 */
int right_calibration_value = 313984; // Run _SERVO_CALLIBRATION by itself to find values
int left_calibration_value = 286848;

int main(void)
{

#if _SERVO_CALIBRATION
    servo_calibration();
#endif // _SERVO_CALIBRATION

#if _IR_CALIBRATION
    IR_calibration();
#endif // _IR_CALIBRATRION

#if _MAIN

#endif // _MAIN

}

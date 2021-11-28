/**
 * main.c
 */

#define _SERVO_CALLIBRATION 1
#define _IR_CALLIBRATION 0
#define _MAIN 0

#include <stdio.h>
#include "scan.h"

/*
 * Run _SERVO_CALIBRATION by itself to find values for these. Currently set for bot06
 */
int right_calibration_value = 313984; // Run _SERVO_CALLIBRATION by itself to find values
int left_calibration_value = 286848;

int main(void)
{

#if _SERVO_CALLIBRATION
    servo_calibration();
#endif // _SERVO_CALLIBRATION

#if _IR_CALLIBRATION

#endif // _IR_CALLIBRATRION

#if _MAIN

#endif // _MAIN

}

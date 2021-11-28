/*
 * scan.h
 *
 *  Created on: Nov 27, 2021
 *      Author: jminardi
 */

#ifndef SCAN_H_
#define SCAN_H_

#include "button.h"
#include "lcd.h"
#include "servo.h"
#include "Timer.h"
    // These will be different for each physical CyBOT servo
    // where 0 degrees (right), and 180 degrees (left) is located
    // These values can be found by running the servo_calibrate function.
    // Once you know the values, then you can set them in main().
    int right_calibration_value;
    int left_calibration_value;


    // Return a struct containing the right (0 degree), and
    // left (180 degree) values that can be used to set
    // right_calibration_value, and left_calibration_value
    // NOTE: If servo is not enabled, then returns -1 for right and left.
    void servo_callibration(void);



#endif /* SCAN_H_ */

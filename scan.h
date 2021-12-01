/*
 *  scan.c
 *
 *  Created on: Nov 27, 2021
 *  Author: James Minardi
 *
 */

#ifndef SCAN_H_
#define SCAN_H_

#include "button.h"
#include "lcd.h"
#include "servo.h"
#include "Timer.h"
#include "ping.h"
#include "adc.h"

extern BOT; // main.c

float adc_to_cm(float raw);


float adc_to_cm_1(float raw);
float adc_to_cm_2(float raw);
float adc_to_cm_3(float raw);
float adc_to_cm_4(float raw);
float adc_to_cm_5(float raw);
float adc_to_cm_6(float raw);
float adc_to_cm_7(float raw);
float adc_to_cm_8(float raw);
float adc_to_cm_9(float raw);
float adc_to_cm_10(float raw);
float adc_to_cm_11(float raw);
float adc_to_cm_12(float raw);
float adc_to_cm_13(float raw);
float adc_to_cm_14(float raw);
float adc_to_cm_15(float raw);


#endif /* SCAN_H_ */

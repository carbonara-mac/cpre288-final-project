/*
 *  adc.c
 *
 * 	ADC and IR sensor functionality
 *
 *  Created on: Oct 19, 2021
 *  Author: James Minardi
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"

/*
 * Raw IR sample updated after every call to adc_read
 * Must be converted using adc_
 * Note: Read only
 * TODO: Put in a struct with sonar?
 */
int IR_raw_sample;

/*
 * Initialize ADC using GPIO port B pin 4, ADC Module 0, and SS1
 */
void adc_init(void);

/*
 * Complete ADC conversion and read the sample, assigning it to IR_raw_sample
 */
void adc_read(void);

#endif /* ADC_H_ */

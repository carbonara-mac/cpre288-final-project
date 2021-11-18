/*
 * adc.h
 *
 *  Created on: Oct 19, 2021
 *      Author: jminardi
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

void adc_init(void);
void adc_read(void);

#endif /* ADC_H_ */

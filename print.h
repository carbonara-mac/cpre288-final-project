/*
 * print.h
 *
 *  Created on: Oct 13, 2021
 *      Author: jminardi
 */

#ifndef PRINT_H_
#define PRINT_H_


#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "object.h"
#include "open_interface.h"


void printScan(int currAngle, float IR_distance, float sound_distance);
void printObjects(object* objectArray, int *numObjects);
void printObjectHeader();
void printScanHeader();
void printBattery(oi_t *sensor_data);


#endif /* PRINT_H_ */

/*
 * print.c
 *
 *  Created on: Oct 13, 2021
 *      Author: jminardi
 */
#ifndef PRINT_C_
#define PRINT_C_

#include "print.h"
#include "open_interface.h"

void printScan(int currAngle, float IR_distance, float sound_distance)
{
    char toPutty[50];
    sprintf(toPutty, "%d\t%f\t%f\r\n", currAngle, IR_distance, sound_distance);

    int i = 0;
    while (toPutty[i] != '\n')
    { //when it hits new line, move on to next scan
        uart_sendChar(toPutty[i]);
        //timer_waitMillis(1); //DON"T REMOVE, print won't work for some reason without it?

        i++;

    }

    uart_sendChar('\n');
}

void printObjects(object *objectArray, int *numObjects)
{
    int i;
    char toPutty2[100];
    for (i = 0; i < *numObjects; i++) // Print object post-processed
    {
        sprintf(toPutty2, "%d\t%f\t%d\t%d\t%f\r\n", i + 1,
                objectArray[i].distance, objectArray[i].startAngle,
                objectArray[i].radialWidth, objectArray[i].linearWidth); //i+1 is the object number

        int j = 0;
        while (toPutty2[j] != '\n')
        { //when it hits new line, move on to next scan
            uart_sendChar(toPutty2[j]);
            j++;
        }
        uart_sendChar('\n');
    }
}

void printObjectHeader()
{ // Print each object in
    uart_sendChar('\n');
    int i = 0;
    char objectStats[] = "Object#\tDistance\tEdge\tRadial\tLinear\r\n";
    while (objectStats[i] != '\n')
    {
        uart_sendChar(objectStats[i]);
        i++;
    }
    uart_sendChar('\n');
}

void printScanHeader()
{
    uart_sendChar('\n');
    int i = 0;
    char columnNames[] = "Angle\tIR_Distance\tSonar\r\n";
    while (columnNames[i] != '\n')
    {
        uart_sendChar(columnNames[i]);
        i++;
    }
    uart_sendChar('\n');
}

void printBattery(oi_t *sensor_data)
{
    lcd_printf("Battery: %.2f\nVersion: %d", (float) (sensor_data->batteryCharge * (1.0) / sensor_data->batteryCapacity), (int) cyBOT_scan_version());
}

#endif /* PRINT_C_ */

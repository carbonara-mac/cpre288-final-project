/*
 *  scan.c
 *
 *  Created on: Nov 27, 2021
 *  Author: James Minardi
 *
 */

#include "scan.h"

float adc_to_cm(int raw)
{
    float centimeters;
    switch (BOT)
    {
    case 1:
        centimeters = adc_to_cm_1(raw);
        break;
    case 2:
        centimeters = adc_to_cm_2(raw);
        break;
    case 3:
        centimeters = adc_to_cm_3(raw);
        break;
    case 4:
        centimeters = adc_to_cm_4(raw);
        break;
    case 5:
        centimeters = adc_to_cm_5(raw);
        break;
    case 6:
        centimeters = adc_to_cm_6(raw);
        break;
    case 7:
        centimeters = adc_to_cm_7(raw);
        break;
    case 8:
        centimeters = adc_to_cm_8(raw);
        break;
    case 9:
        centimeters = adc_to_cm_9(raw);
        break;
    case 10:
        centimeters = adc_to_cm_10(raw);
        break;
    case 11:
        centimeters = adc_to_cm_11(raw);
        break;
    case 12:
        centimeters = adc_to_cm_12(raw);
        break;
    case 13:
        centimeters = adc_to_cm_13(raw);
        break;
    case 14:
        centimeters = adc_to_cm_14(raw);
        break;
    case 15:
        centimeters = adc_to_cm_15(raw);
        break;
    default:
        centimeters = adc_to_cm_1(raw);
        break;

    }
    return centimeters;
}

float adc_to_cm_6(int raw)
{
    return -1;
}

void adc_to_cm_7(void)
{
    return -1;
}
void adc_to_cm_8(void)
{
    return -1;
}
void adc_to_cm_9(void)
{
    return -1;
}
void adc_to_cm_10(void)
{
    return -1;
}
void adc_to_cm_11(void)
{
    return -1;
}
void adc_to_cm_12(void)
{
    return -1;
}

float adc_to_cm_13(int raw)
{
    if (raw < 420)
    {
        return 100.0;
    }
    else
    {
        return ((31103.3 / (raw - 115.697)) - 2.09641);
    }
}

float adc_to_cm_14(float raw)
{
    return -1;
}
float adc_to_cm_15(float raw)
{
    return -1;
}

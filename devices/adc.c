/*
 * adc.c
 *
 *  Created on: Oct 19, 2021
 *      Author: jminardi
 */

#include "adc.h"

int IR_raw_sample;
void adc_init(void)
{

    // GPIO Initialization
    SYSCTL_RCGCGPIO_R |= 0b000010; //enable port B
    SYSCTL_RCGCADC_R |= 0x1; //enable adc module 0

    GPIO_PORTB_AFSEL_R |= 0b00010000; //set PB4 as alternate function
    GPIO_PORTB_DEN_R &= 0b11101111; // disable PB4 digital function
    GPIO_PORTB_AMSEL_R |= 0b00010000; // Enables PB4 for analog function
    GPIO_PORTB_DIR_R &= 0b11101111; // Set PB4 to input

    // Initialize ADC Module 0 - ADC0
    GPIO_PORTB_ADCCTL_R = 0x00; // Default trigger source

    // Initialize ADC Registers
    ADC0_ACTSS_R &= 0b1101; // disables SS1
    ADC0_EMUX_R = 0x0; //Default
    ADC0_SSMUX1_R |= 0x000A; // First sample AIN10
    ADC0_SSCTL1_R |= 0x00006; // TS0, IE0, only need to sample once
    ADC0_SAC_R = 0b100;
    ADC0_ACTSS_R |= 0b0010; //enable SS1, disables SS0, SS2, SS3

}

void adc_read(void)
{

    ADC0_PSSI_R |= 0b0010; // Initiate SS1

    while ((ADC0_RIS_R & 0b0010) == 0) // Poll wait for ADC conversion to be done
    {
    }

    IR_raw_sample = ADC0_SSFIFO1_R; // Read sample from AIN10
    ADC0_ISC_R |= 0b0010; // Clear the interrupt in RIS

}

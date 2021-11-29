/*
 *  adc.c
 *
 * 	ADC and IR sensor functionality
 *
 *  Created on: Oct 19, 2021
 *  Author: James Minardi
 */

#include "adc.h"

/*
 * Initialize ADC using GPIO port B pin 4, ADC Module 0, and SS1
 */
void adc_init(void)
{

    // GPIO Initialization
    SYSCTL_RCGCGPIO_R |= 0b000010; 			// Enable GPIO port B
    SYSCTL_RCGCADC_R |= 0x1; 				// Enable ADC module 0

    GPIO_PORTB_AFSEL_R |= 0b00010000; 		// Set PB4 to alternate function
    GPIO_PORTB_DEN_R &= 0b11101111; 		// disable PB4 digital function
    GPIO_PORTB_AMSEL_R |= 0b00010000; 		// Enables PB4 for analog function
    GPIO_PORTB_DIR_R &= 0b11101111; 		// Set PB4 to input

    // Initialize ADC Module 0 - ADC0
    GPIO_PORTB_ADCCTL_R = 0x00; 			// Default

    // Initialize ADC Registers
    ADC0_ACTSS_R &= 0b1101; 				// Disable SS1 to stop sampling
    ADC0_EMUX_R = 0x0; 						// Default
    ADC0_SSMUX1_R |= 0x000A; 				// First sample AIN10
    ADC0_SSCTL1_R |= 0x00006; 				// Only need to sample once
    ADC0_SAC_R = 0b100;						// 16x sample averaging
    ADC0_ACTSS_R |= 0b0010; 				// enable SS1, disables SS0, SS2, SS3

} // END adc_init

/*
 * Complete ADC conversion and read the sample, assigning it to IR_raw_sample
 */
void adc_read(void)
{

    ADC0_PSSI_R |= 0b0010; 					// Enable SS1 sampling

    while ((ADC0_RIS_R & 0b0010) == 0) 		// Poll wait for ADC conversion to be done
    {
    }

    IR_raw_sample = ADC0_SSFIFO1_R; 		// Read sample from AIN10 and set to IR_raw_sample
    ADC0_ISC_R |= 0b0010; 					// Clear the interrupt in RIS

} // END adc_read

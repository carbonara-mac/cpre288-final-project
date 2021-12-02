/*
 *  button.c
 *
 *  Button input functionality on lcd screen
 *
 *  Created on: Dec 2, 2021
 *  Author: James Minardi
 *
 */
 

#include "button.h"


/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
	static uint8_t initialized = 0;

	//Check if already initialized
	if(initialized){
		return;
	}

	SYSCTL_RCGCGPIO_R |= 0b010000; // Enable Port E clock
	
	GPIO_PORTE_DIR_R &= 0b11110000; // Set buttons as inputs
	
	GPIO_PORTE_DEN_R |= 0b00001111; // Set button inputs to digital functionality

	initialized = 1;
}



/**
 * Returns the position of the leftmost button being pushed.
 * @return the position of the leftmost button being pushed. 4 is the leftmost button, 1 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton() {

	// TODO: What button order is priority. Fix javadoc
	if ((GPIO_PORTE_DATA_R & 0b0001000) == 0b00000000) {

	    return 4;
	}

    if ((GPIO_PORTE_DATA_R & 0b0000100) == 0b00000000) {
	    return 3;
    }

    if ((GPIO_PORTE_DATA_R & 0b0000010) == 0b00000000) {
	    return 2;
	}

	if ((GPIO_PORTE_DATA_R & 0b0000001) == 0b00000000) {
	    return 1;
	}

	return 0;
}






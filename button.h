/*
 *  button.h
 *
 *  Button input functionality on lcd screen
 *
 *  Created on: Dec 2, 2021
 *  Author: James Minardi
 *
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init();

/**
 * Returns the position of the leftmost button being pushed.
 * @return the position of the leftmost button being pushed. 4 is the leftmost button, 1 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton();

#endif /* BUTTON_H_ */

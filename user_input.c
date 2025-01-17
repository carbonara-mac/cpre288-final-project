/*
 *  user_inptut.c
 *
 *  Parses and executes commands received from user input
 *  
 *  Created on: Nov 30, 2021
 *  Author: Ainara Machargo, James Minardi
 */

#include "user_input.h"


/* 
 * Parses given char pointer by the following formats:
 * 		"[Function],[Parameter]\0"
 *		"[Function]\0"
 * [Function] is a single char representing a function to complete: W,A,S,D,M,Z
 * [Parameter] is an integer value to give to the desired function: Distance or Angle
 * 
 *  @param command - Null terminated char pointer to parse
 */
void ui_parse(oi_t *sensor_data, char command[])
{
    char function = *(command);
    int parameter;
    command++;

    if (*command == '\0')
    {
        // One character command (ex. Scan0-180 (m) and quit (z))
        parameter = -1;
    }
    else
    {
        command++; // Skip ',' character
        parameter = (int) strtol(command, NULL, 10);
        if (parameter < 0) // No parameter should be < 0
        {
            parameter = -1;
        }
    }
    ui_execute(sensor_data, function, parameter);

} // END ui-parse


/*
 * Execute desired function with given integer parameter.
 * 		w: Move forward, s: move backward, a: rotate counter clockwise, d: rotate clockwise
 *		m: scan 0-180 degrees or specified degrees
 *		z: finish program
 *	
 * @param function - Single char to represent desired instructions to execute
 * 		  parameter - Integer value to give the function call as a distance or angle
 */
void ui_execute(oi_t *sensor_data, char function, int parameter) {
	switch(function) {
		case 'w':
			// Move forward parameter centimeters
		    move_forward(sensor_data, parameter);
			break;
		case 's':
			// Move backward parameter centimeters
		    move_backward(sensor_data, parameter);
			break;
		case 'a':
			// Rotate counter clockwise parameter degrees
			rotate_counterClockwise(sensor_data, parameter);
		    break;
		case 'd':
			// Rotate clockwise parameter degrees
		    rotate_clockwise(sensor_data, parameter);
			break;
		case 'm':
			if (parameter == -1) {
				// Scan 0 to 180	
			} else {
				// Scan at parameter degrees
			    scan(&get_scan, parameter);
			}
			break;
		case 'z':
			// Program completion
			break;
		default:
			// Shouldn't ever go here
			break;
	}
} // END ui_execute

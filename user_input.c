/*
 *  user_inptut.c
 *
 *  Created on: Nov 30, 2021
 *  Author: Ainara Machargo, James Minardi
 */

#include "user_input.h"

void ui_parse(char *command)
{
    char function = *command;
    int parameter;
    command++;

    if (&command == '\0')
    {
        // One character command (ex. Scan0-180 (m) and quit (z))
        parameter = -1;
        ui_execute()
    }
    else
    {
        command++; // Skip ',' character
        parameter = (int) strol(command, NULL, 10);
        if (parameter < 0) // No parameter should be < 0
        {
            parameter = -1;
        }
    }

}

void ui_execute(char function, int parameter) {

    // Case statements for function argument
    //      -> Call different functions based on function arg and the parameter int
    //      -> Ex. function=w and paramter=25, then call moveForward for 25 centimeters

}


main(void) {

volatile  char uart_data;  // Your UART interupt code can place read data here
volatile  char flag;       // Your UART interupt can update this flag
                           // to indicate that it has placed new data
                           // in uart_data
						    // ISSUE WITH oi_init() function. Program stops there...THIS ONLY HAPPENS WHEN ROOMBA IS OFF (PRESS "CLEAN" BUTTON)
oi_t *sensor_data = oi_alloc();
oi_init(sensor_data);

//cyBot_uart_init(); // initialize connection via wifi from Putty to CyBot
uart_init(115200);
uart_interrupt_init();

lcd_init(); // initialize lcd screen

ping_init();
adc_init();
servo_init();

char keyPressMsg[] = "Got an  \n\r";
int valIndex = 7; //num for message
char fbMsg[] = "How many milis?";
char lrMsg[] = "How many degrees?";

int inputNum = 0;
while (1){

  if (flag) {
            flag = 0;

            lcd_clear();
            lcd_putc(uart_data); // displays byte from putty
            keyPressMsg[valIndex] = uart_data; // updates putty string with current keypress
            uart_sendStr(keyPressMsg);
        }

	//forward
	if(uart_data == 'w' ){

	inputNum = uart_data;

	oi_setWheels(inputNum, inputNum);
	}
	//backward
	if(uart_data == 's' ){
	uart_sendStr(fbMsg);
	inputNum = uart_data;
	oi_setWheels( -1 * inputNum, -1 * inputNum);
	inputNum=0;
	}
	//rotate right
	if(uart_data == 'd' ){
	uart_sendStr(lrMsg);
	inputNum = uart_data;
	oi_setWheels( -1 * inputNum, inputNum);
	inputNum=0;
	}
	//rotate left
	if(uart_data == 'a' ){
	uart_sendStr(lrMsg);
	inputNum = uart_data;

	oi_setWheels(inputNum, -1* inputNum);
	inputNum=0;
	}

	//TODO
	//scan 0-180
	//scan in general
	//print diagnostics
	//music command
	//end command

}
}

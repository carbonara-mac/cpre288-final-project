/*
 * servo.c
 *
 *  Created on: Nov 2, 2021
 *      Author: jminardi
 */

#include "servo.h"
#include "math.h"
#include "timer.h"

int done;
int currentAngle;

/*
 * Ideal 0 degrees = 304000
 * Ideal 180 degrees = 288000
 *
 */

/********CALIBRATION INFORMATION***************
 *
 *  Bot 13:
 *      0 = 312300 = 0x4C3EC
 *     90 = 297600 = 0x48A80
 *    180 = 284000 = 0x45560
 */

void servo_init1(void)
{
    done = 0;
    SYSCTL_RCGCGPIO_R |= 0b000010; // enable port B clock
    SYSCTL_RCGCTIMER_R |= 0b000010; // enable Timer 1 clock

    GPIO_PORTB_AFSEL_R |= 0b100000; // Sets PB5 to alternate function
    GPIO_PORTB_PCTL_R |= 0x00700000; // Selects timer 1 (T1CCP1)
    GPIO_PORTB_PCTL_R &= 0xFF7FFFFF;
    GPIO_PORTB_DEN_R |= 0b00100000; // enable PB5 digital function
    GPIO_PORTB_DIR_R |= 0b00100000; // Set PB5 to output

    TIMER1_CTL_R &= 0b011111111; // disable timer1B to config
    TIMER1_CFG_R |= 0x4; //Use split 16-bit timers
    TIMER1_TBMR_R |= 0b01010; //Set as count down, periodic, PWM mode
    TIMER1_TBMR_R &= 0b01010;
    TIMER1_TBPR_R = 0x04; // Loads MSBs of 0x4E200 (320,000)
    TIMER1_TBILR_R = 0xE200; // Loads 8 LSBs of 0x4E200 (Period = 320,000 clock cycles)

//    Theoretical Match Value ->    TIMER1_TBMATCHR_R = 0xA380; // Sets match to 304,000 (1ms = 0 degrees)
//                                  TIMER1_TBPMR_R = 0x04; // Prescalar for 304,000

    TIMER1_CTL_R |= 0b100000000; // Enable timer b

    servo_move1(90); //Input 90 degrees for initialization
}

int servo_move1(int degrees)
{
    if (degrees < 0) //For situations where input degrees may be less than 0
    {
        degrees = 0;
    }
    if (degrees > 180) //For situations where input degrees may be more than 0
    {
        degrees = 180;
    }

    int match = convertDegreesBOT13(degrees); //Equation function to convert the degree into the match value

    TIMER1_CTL_R &= 0b011111111;
    TIMER1_TBMATCHR_R = match; // Match value for specified degree
    TIMER1_TBPMR_R = match >> 16; //Prescale Value for specified degree
    TIMER1_CTL_R |= 0b100000000; // Enable timer b

    timer_waitMillis((abs(degrees - currentAngle) / 200) / 1000);
    timer_waitMillis(50); //Delay for the ping and IR sensors to have enough time to gather information

    currentAngle = degrees;
    return match;

}

int convertDegreesBOT13(int degrees)
{
    //TODO: Implement calibration method to have match equation consistent through out different bots
    int match = 0.0679012 * pow((degrees - 1247.73), 2) + 206590; //IMPORTANT: Equation for Bot13
    return match;
}


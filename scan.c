/*
 * scan.c
 *
 *  Created on: Nov 27, 2021
 *  Author: James Minardi
 *  Last Updated: 11/27/21
 */

#include "scan.h"

void servo_callibration(void)
{
    timer_init();
    lcd_init();
    servo_init1();
    button_init();
    int match = 0x4A380; // Theoretical 0 degrees: 304,000 (1ms = 0 degrees)
    TIMER1_CTL_R &= 0b011111111; // Disable timer b
    TIMER1_TBMATCHR_R = match;
    TIMER1_TBPMR_R = match >> 16;
    TIMER1_CTL_R |= 0b100000000; // Enable timer b

    int fast = 0;
    int right = 1;
    lcd_printf("1=L 2=R 3=Cont.\nRight Val: %d", match);
    while (1)
    {


        int button = button_getButton();
        if (button == 1)
        {
            match = fast ? match - 512 : match - 128;
        }
        else if (button == 2)
        {
            match = fast ? match + 512 : match + 128;
        }
        else if (button == 3)
        {
            if (right == 1)
            {
                right_calibration_value = match;
                right = 0;
                timer_waitMillis(1000);
            }
            else if (right == 0)
            {
                left_calibration_value = match;
                timer_waitMillis(500);
                break;
            }
        }
        else if (button == 4)
        {
            fast = fast ? 0 : 1;
            timer_waitMillis(500);
        }

        TIMER1_CTL_R &= 0b011111111; // Disable timer b
        TIMER1_TBMATCHR_R = match;
        TIMER1_TBPMR_R = match >> 16;
        TIMER1_CTL_R |= 0b100000000; // Enable timer b
        if (right)
        {
            lcd_printf("1=L 2=R 3=Cont.\nRight Val: %d", match);
        }
        else if (right == 0)
        {
            lcd_printf("1=L 2=R 3=Done\nLeft Val: %d", match);
        }
        timer_waitMillis(200);
    }

    lcd_printf("Right: %d\nLeft: %d", right_calibration_value,
               left_calibration_value);
}


/**
 * main.c
 */

// Run each independently of each other
#define _SERVO_CALIBRATION 0
#define _IR_CALIBRATION 0
#define _MAIN 1

#include <stdio.h>
#include "scan.h"
#include "adc.h"
#include "lcd.h"
#include "Timer.h"
#include "servo.h"
#include "ping.h"
#include "calibration.h"
#include "scan.h"
#include "uart.h"

extern int current_angle; // servo.h
extern volatile int uart_receive_flag;

/*
 * Run _SERVO_CALIBRATION by itself to find values for these. Currently set for bot06
 */
int right_calibration_value = 313984;
int left_calibration_value = 286848;
int BOT = 6;

scan_t get_scan;
oi_t *sensor_data;

int main(void)
{

#if _SERVO_CALIBRATION
    servo_calibration();
#endif // _SERVO_CALIBRATION

#if _IR_CALIBRATION
    IR_calibration();
#endif // _IR_CALIBRATRION

#if _MAIN
    timer_init();
    lcd_init();
    uart_init();
    servo_init();
    adc_init();
    ping_init();
    button_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    char command[20];
    for (size_t i = 0; i < sizeof(command); i++)
    {
        command[i] = 0;
    }
    int i = 0;
    while (1)
    {
        if (uart_receive_flag == 1)
        {
            uart_receive_flag = 0;
            command[i] = uart_data;
            if (command[i] == '\0')
            {
                ui_parse(command);
                for (size_t i = 0; i < sizeof(command); i++)
                {
                }
            }
        }

    }





    // Test for scan method in scan.h
    int ang = 0;
    while (1) {
        if (ang <= 180) {
            scan(ang, &get_scan);
            ang += 1;
        }
    }

#endif // _MAIN

}

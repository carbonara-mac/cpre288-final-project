/*
 * ping.c
 *
 *  Created on: Oct 26, 2021
 *      Author: jminardi
 */

#include "ping.h"
#include "lcd.h"

volatile enum states state; // Set by ISR
volatile unsigned int rising_time; // Pulse start time: Set by ISR
volatile unsigned int falling_time; // Pulse end time: Set by ISR

void ping2_init(void) //named ping2_init since there is already an instance of ping in libcybotscan
{
    state = LOW;
    //GPIO Initialization
    SYSCTL_RCGCGPIO_R |= 0b000010; //enable port B clock
    SYSCTL_RCGCTIMER_R |= 0b001000; // enable Timer clock

    GPIO_PORTB_AFSEL_R &= 0b11110111; //disable PB3 as alternate function, set to GPIO

    // Sets PB3 to GPIO output
    GPIO_PORTB_PCTL_R |= 0x00007000; // Selects timer (T3CCP1)
    GPIO_PORTB_PCTL_R &= 0xFFFF7FFF;

    GPIO_PORTB_DEN_R |= 0b00001000; // enable PB3 digital function
    GPIO_PORTB_DIR_R |= 0b00001000; // Set PB3 to output

    TIMER3_CTL_R &= 0b011111111; // disable timer3 B to config interrupts

    //Initialize Timer Registers
    TIMER3_CTL_R |= 0b110000000000; //Enable both edge trigger for T(b)EVENT
    TIMER3_CFG_R |= 0x4; //Use split 16-bit timers
    TIMER3_TBPR_R |= 0xFF;
    TIMER3_TBMR_R |= 0b0111; //Set for Capture mode
    TIMER3_TBMR_R &= 0b0111;
    TIMER3_TBILR_R |= 0xFFFF;  //Read from both TBPS and TBR and shift

    ping_interrupt_init();

}

void ping_interrupt_init(void)
{
    TIMER3_ICR_R |= 0b010000000000; // Clears interrupt flags
    TIMER3_IMR_R |= 0b010000000000; // enable capture interrupt for timer B

    NVIC_EN1_R |= 0b00010000; // Enable 16/32bit timer3B interrupt in NVIC_EN#_R (int# 36)

    NVIC_PRI9_R |= 0x20;

    IntRegister(INT_TIMER3B, ping_timer3b_handler); // Bind ISR
    IntMasterEnable();

    TIMER3_CTL_R |= 0b100000000; // Reenable timer3 B
}

/*
 * Called when rising or falling event occurs for Timer
 */
void ping_timer3b_handler(void)
{
//    if (TIMER3_MIS_R & TIMER_MIS_CBEMIS == 1) // Check if Capture mode event interrupt is 1
//    {
    if (state == LOW)
    { // If current state is low, set state to high and store start time
        rising_time = TIMER3_TBR_R;
        state = HIGH;
    }
    else if (state == HIGH) // If current state is high, set state to done and store end time
    {
        falling_time = TIMER3_TBR_R;
        state = DONE;
    }

    TIMER3_ICR_R |= 0b010000000000; // Clear timer3B capture mode event interrupt
//    }

}

/*
 * Disables interrupt, sets PB3 to GPIO output, sends trigger,
 * sets PB3 back to TIMER input device, clears interrupts, enables interrupt
 *
 *  returns distance Distance in cm
 */
float ping_read(void)
{
    ping_send_trigger(); // Send ping
    while (1)
    {
        if (state == DONE)
        {
//            unsigned long time_diff;
//            int overflow = 0;

            state = LOW;
            //int deltaTime = (rising_time - falling_time) * 62.5; // Delta time is in nanoseconds TODO Overflow
            //deltaTime = (deltaTime / 1000000000); // Delta time is in seconds now
            //return (17000 * deltaTime); // Distance is in cm (17000 is speed of sound in cm/s divided by 2)
            long deltaTime = 0;
            if (falling_time > rising_time) // Overflow occurred
            //if (rising_time > falling_time)
            {
                deltaTime += (long) 1 << 24;
            }
            deltaTime += (rising_time - falling_time); // deltaTime in clock cycles
            //deltaTime += (falling_time - rising_time); // deltaTime in clock cycles

            float time_ms = (float) deltaTime * 0.0000625; // deltaTime in milliseconds
            float distance = (time_ms * ((340.0 * 100.0) / 1000.0) / 2.0); // distance in centimeters

            //lcd_printf("dCC: %d\ndSeconds: %.3f\nDistanceCM: %f", (int)deltaTime, time_ms, distance);
            return distance;

        }
    }

}

/*
 *
 */
void ping_send_trigger(void)
{
    TIMER3_IMR_R &= 0b101111111111; // Mask Timer B Capture Mode Event Interrupt (disable)

    // Set PB3 to GPIO output device
    GPIO_PORTB_AFSEL_R &= 0b11110111; //disable PB3 as alternate function, set to GPIO
    GPIO_PORTB_DIR_R |= 0b00001000; // Set PB3 to output

    // TRIGGER
    GPIO_PORTB_DATA_R |= 0b00001000; //PB3 set to high (1)
    timer_waitMillis(0.01); //wait 10 microseconds
    GPIO_PORTB_DATA_R &= 0b11110111; //PB3 set to low (0)

    // Set PB3 back to TIMER input device
    GPIO_PORTB_AFSEL_R |= 0b00001000; // set PB3 to alternate function (Timer)
    GPIO_PORTB_DIR_R &= 0b11110111; // Set PB3 to input

    TIMER3_ICR_R |= 0b010000000000; // Clear timer3B capture mode event interrupt
    TIMER3_IMR_R |= 0b010000000000; // Unmask timer3B capture mode event interrupt

    //timer_waitMillis(0.01); //wait for ISR to capture rising and falling edge time ????
}

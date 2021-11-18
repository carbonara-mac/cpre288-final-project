/*
 *
 *   uart.c
 *
 *
 *
 *
 *
 *   @author
 *   @date
 */

#include "uart.h"
#include "timer.h"
#define REPLACE_ME 0x00

volatile int transmit_event;
volatile int receive_event;
volatile char receive_data;

void uart_init(void)
{

    SYSCTL_RCGCGPIO_R |= 0b00000010;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R = 0b00000011; // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R = 0x00000011; // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_DEN_R = 0b00000011;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R = 0b00000001;        // sets pb0 as output, pb1 as input

    //compute baud values [UART clock= 16 MHz]
    double fbrd;
    int ibrd;

    fbrd = 16000000.0 / (16.0 * 115200.0); // page 903;
    ibrd = (int) fbrd;
    fbrd = (int) ((fbrd - ibrd) * 64 + 0.5);

    UART1_CTL_R &= 0xFE;      // disable UART1 (page 918)
    UART1_IBRD_R = ibrd;        // write integer portion of BRD to IBRD
    UART1_FBRD_R = fbrd;   // write fractional portion of BRD to FBRD
    UART1_LCRH_R = 0b01100000; // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R = 0b0000;          // use system clock as clock source (page 939)
    UART1_CTL_R |= 0b1100000001; // enable UART1
    //UART1_DR_R = 0x00;

}

void uart_sendChar(char data)
{

    while (UART1_FR_R & 0b00100000 == 0)
    { //wait here as long as the FIFO Transmit is full.

    }

    UART1_DR_R = data; //send data
    timer_waitMillis(1); // DO NOT REMOVE: Does not work without
}

char uart_receive(void)
{

    char data = 0;

    while (UART1_FR_R & 0b00010000)
    { //keep waiting as long as FIFO receive is empty

    }

    data = (char) (UART1_DR_R & 0xFF); //mask the 4 error bits and grab only 8 data bits

    return data;

}

void uart_sendStr(const char *data)
{
    //for reference see lcd_puts from lcd.c file

    //While not equal to null
    while (*data != '\0')
    {
        uart_sendChar(*data);
        data++;
    }
}

void uart_interrupt_init()
{
    // turn off uart1 while setting up
    UART1_CTL_R &= 0b0111111110;

    //clear interrupt flags
    UART1_ICR_R = UART1_ICR_R | 0b11111110000;

    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b010000; //enable interrupt on receive - page 924

    //NVIC_PRI1_R |= 0x00200000;

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R &= 0x00000040;
    NVIC_EN0_R |= 0x00000040; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number
    IntMasterEnable();

    UART1_CTL_R |= 0b1100000001; // enable uart
}

void uart_interrupt_handler()
{
    if (UART1_MIS_R & 0b010000)
    { // Has UART receive interrupt been signaled?

        // Copy received data
        uart_data = (char) (UART1_DR_R & 0xFF);
        flag = 1;

        // Clear receive bit interrupt (1 clears interrupt)
        UART1_ICR_R = UART1_ICR_R | 010000;
    }
}

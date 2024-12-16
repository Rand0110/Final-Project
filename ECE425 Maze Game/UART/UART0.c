/**
 * @file UART0.c
 *
 * @brief Source code for the UART0 driver.
 *
 * This file contains the function definitions for the UART0 driver.
 *
 * @note For more information regarding the UART module, refer to the
 * Universal Asynchronous Receivers / Transmitters (UARTs) section
 * of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the frequency of the system clock is 50 MHz.
 *
 * @author Randy Ortiz
 */

#include "UART0.h"
#include "SysTick_Delay.h"
#include "string.h"

#define MAZE1_ROWS 11
#define MAZE1_COLS 11
#define MAZE2_ROWS 13
#define MAZE2_COLS 13
#define MAZE3_ROWS 23
#define MAZE3_COLS 23



void UART0_Init(void)
{
    // Enable the clock to the UARTO module by setting the
    // RO bit (Bit 0) in the RCGCUART register
	SYSCTL->RCGCUART |= 0x01;

    // Enable the clock to Port A by setcing the
    // RO bit (BIt 0) in the RCGGPIO register
	SYSCTL->RCGCGPIO |= 0x01;

    // Disable the UARTO module before configuration by clearing
    // the UARTEN bit (Bit 0) in the CTL regiater
	UART0->CTL &= ~0x0001;

    // Configure the UARTO module to use the system clock (50 MHz)
    // divided by 16 by clearing the HSE bit (Bit 5) in the CTL register
	UART0->CTL &= ~0x0020;

    // Set the baud rate by writing to che DIVINT field (Bits 15 to 0)
    // and che DIVERAC field (Bits 5 to 0) in che IBRD and EBRD registers, respectivels
    // The integer part of the calculated constant will be written to che IBRD reglater
    // While che fractional part will be written to the FBRD register.
    // I BRD = (System Clock Frequency) / (16 * Baud Rate)
    // BRDI - (50,000, 000)
    // (16 * 115200) = 27.12673611 (IBRD = 27)
    // BRDE = ((0.12673611 * 64) + 0.5) = 8.611 (FBRD = 8)
	UART0->IBRD = 27;
	UART0->FBRD = 8;

    //Configure the data length of the UART packet to be 8 bits by writing a value of 0x3 to
    // the WLEN field (Bits 6 to 5) in the LCRH register.
	UART0->LCRH |= 0x60;

    // Enable the Transmit FIFO and the Receive FIFO by setting the FEN bit (Bit 4) in the
    // LCRH register.
	UART0->LCRH |= 0x10;

    // Select one stop bit to be transmitted at the end of a UART frame by clearing the
    // STP2 bit (Bit 3) in the LCRH register.
	UART0->LCRH &= ~0x08;

    // Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register.
	UART0->LCRH &= ~0x02;

    // Enable the UART0 module after configuration by setting the UARTEN bit (Bit 0) in
    // the CTL register.
	UART0->CTL |= 0x01;

    // Select the alternate function for the PA1 and PA0 pins by setting Bits 1 to 0 in the
    // AFSEL register. The pins will be configured as TX and RX pins, respectively.
	GPIOA->AFSEL |= 0x03;

    // Clear the PMC1 (Bits 7 to 4) and PMC0 (Bits 3 to 0) fields in the PCTL register for
    // Port A before configuration.
	GPIOA->PCTL &= ~0x000000FF;

    // Configure the PA1 pin to operate as a U0TX pin by writing 0x1 to the PMC1 field
    // (Bits 7 to 4) in the PCTL register.
	GPIOA->PCTL |= 0x00000010;

    // Configure the PA0 pin to operate as a U0RX pin by writing 0x1 to the PMC0 field
    // (Bits 3 to 0) in the PCTL register.
	GPIOA->PCTL |= 0x00000001;

    // Enable the digital functionality for the PA1 and PA0 pins by setting Bits 1 to 0 in the
    // DEN register.
	GPIOA->DEN |= 0x03;

}


char UART0_Read_Char(void)
{	
	while((UART0->FR & UART0_RECEIVE_FIFO_EMPTY_BIT_MASK) != 0);

	return (char)(UART0->DR & 0xFF);
}

char UART0_ReadKeyBind() 
{
    char c = UART0_Read_Char();
    if (c == 0x1B) {            // ESC character
        c = UART0_Read_Char();   // Read next character (should be '[')
        if (c == 0x5B) {
            c = UART0_Read_Char(); // Read the final character
            if (c == 0x44) return 'L'; // Left Arrow
            if (c == 0x43) return 'R'; // Right Arrow
            if (c == 0x41) return 'U'; // Up Arrow
            if (c == 0x42) return 'D'; // Down Arrow
        }
    }
    return c; // Return other characters normally
}

void UART0_CharOutput(char data)
{
	while((UART0->FR & UART0_TRANSMIT_FIFO_FULL_BIT_MASK) != 0);

	UART0->DR = data;
}

// this takes creates a pointer to which the character that is place in 
// the brackets and finally running the function to output a string on screen.
void UART0_StringOutput(char *pt)
{
	while(*pt)
	{
		UART0_CharOutput(*pt);
		pt++;
	}
}


void UART0_Output_Unsigned_Decimal(uint32_t n)
{
    // Use recursion to convert decimal number
    // of unspecified lenghth as an ASCII string
	if(n >= 10)
	{
		UART0_Output_Unsigned_Decimal(n/ 10);
		n = n % 10;
	}

    // n is between 0 and 9
	UART0_CharOutput(n + '0');
}

// This function is equivalent to shift + enter in a doc
void UART0_NewLine(void)
{
	UART0_CharOutput(UART0_CR);
	UART0_CharOutput(UART0_LF);
}


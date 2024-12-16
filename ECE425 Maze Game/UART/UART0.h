/**
 * @file UART0.h
 *
 * @brief Header file for the UART0 driver.
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

#include "TM4C123GH6PM.h"

#define UART0_RECEIVE_FIFO_EMPTY_BIT_MASK 0x10
#define UART0_TRANSMIT_FIFO_FULL_BIT_MASK 0x20

/**
 * @brief Carriage return character
 */
#define UART0_CR   0x0D
/**
 * @brief Line feed character
 */
#define UART0_LF   0x0A
/**
 * @brief Back space character
 */
#define UART0_BS   0x08
/**
 * @brief escape character
 */
#define UART0_ESC  0x1B
/**
 * @brief space character
 */
#define UART0_SP   0x20
/**
 * @brief delete character
 */
#define UART0_DEL  0x7F

/**
 * @brief The UART0_Init function initializes the UART0 module.
 *
 * This function configures the UART0 module with the following configuration:
 *
 * - Parity: Disabled
 * - Bit Order: Least Significant Bit (LSB) first
 * - Character Length: 8 data bits
 * - Stop Bits: 1
 * - UART Clock Source: System Clock (50 MHz) Divided By 16
 * - Baud Rate: 115200
 *
 * @note The PA1 (TX) and PA0 (RX) pins are used for UART communication via USB.
 *
 * @return None
 */
void UART0_Init(void);

/**
 * @brief The char UART0_Read_Char function reads a character from the UART data register.
 *
 * This function waits until a character is available in the UART receive buffer
 * from the serial terminal input and returns the received character as a char type.
 *
 * @param None
 *
 * @return The received character from the serial terminal as a char type.
 */
char UART0_Read_Char(void);

/**
 * @brief The char UART0_ReadKeyBind function reads a character from the UART data register.
 *
 * This function waits until a character is available in the UART receive buffer
 * from the serial terminal input and returns the received character as a char type.
 *
 * @param None
 *
 * @return The received character from the serial terminal as a char type.
 */
char UART0_ReadKeyBind();

/**
 * @brief The UART0_CharOutput function transmits a character via UART to the serial terminal.
 *
 * This function waits until the UART transmit buffer is ready to accept
 * a new character and then writes the specified character in the transmit buffer to the serial terminal.
 *
 * @param data The character to be transmitted to the serial terminal.
 *
 * @return None
 */
void UART0_CharOutput(char data);

/**
 * @brief The UART0_StringOutput function transmits a null-terminated string via UART to the serial terminal.
 *
 * This function transmits characters from the provided string (pt) via UART to the serial terminal
 * until a null character is encountered.
 *
 * @param pt Pointer to the null-terminated string to be transmitted.
 *
 * @return None
 */
void UART0_StringOutput(char *pt);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void UART0_Output_Unsigned_Decimal(uint32_t n);

/**
 * @brief The UART0_NewLine function transmits the carriage return (CR) and line feed (LF) to go to a new line.
 *
 * @param None
 *
 * @return None
 */
void UART0_NewLine(void);

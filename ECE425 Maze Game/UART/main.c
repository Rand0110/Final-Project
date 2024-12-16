/*
 * @file main.c
 *
 * @brief Main source code for the UART program.
 *
 * This file contains the main entry point and function definitions for the UART program.
 *
 * @note For more information regarding the UART module, refer to the
 * Universal Asynchronous Receivers / Transmitters (UARTs) section
 * of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @author Randy Ortiz
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "UART0.h"
#include "MazeGame.h"

int main(void) {
  UART0_Init(); // Initialize UART
	SysTick_Delay_Init();
	UART0_StringOutput("\033[H\033[J");
  PlayGame();   // Start the game loop
  return 0;
}
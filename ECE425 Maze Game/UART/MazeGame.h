#ifndef MAZEGAME_H
#define MAZEGAME_H

// Maze dimensions (Maximum)
#define MAX_ROWS 23
#define MAX_COLS 23

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void MenuDisplay(void);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void EndMenuDisplay(void);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void DisplayInstructions(void);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void PlayGame(void);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void printMaze(int maze[][MAX_COLS], int rows, int cols);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void findStart(int maze[][MAX_COLS], int *x, int *y, int rows, int cols);

/**
 * @brief The UART0_Output_Unsigned_Decimal function transmits an unsigned decimal number via UART to the serial terminal.
 *
 * This function transmits the provided unsigned decimal number (n) via UART to the serial terminal.
 *
 * @param n The unsigned decimal number to be transmitted to the serial terminal.
 *
 * @return None
 */
void processInput(char input, int maze[][MAX_COLS], int rows, int cols);


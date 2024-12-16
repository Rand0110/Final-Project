#include "MazeGame.h"
#include "UART0.h"
#include "SysTick_Delay.h"



int maze3[23][23] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 'S', 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 'E', 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Player and game state
int playerX = -1, playerY = -1;
int mazeChoice = 1;

// Function to find the start position 'S'
void findStart(int maze[][MAX_COLS], int *x, int *y, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                *x = j;
                *y = i;
                return;
            }
        }
    }
}

void printMaze(int maze[][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == playerY && j == playerX) {
                UART0_StringOutput("P "); // Player's position
            } else if (maze[i][j] == 1) {
                UART0_StringOutput("# "); // Wall
            } else if (maze[i][j] == 0) {
                UART0_StringOutput(". "); // Open space
            } else if (maze[i][j] == 'S') {
                UART0_StringOutput("S "); // Start
            } else if (maze[i][j] == 'E') {
                UART0_StringOutput("E "); // End
            } else {
                UART0_StringOutput("? "); // For debugging unexpected values
            }
        }
        UART0_NewLine();
    }
}

// Handle WASD input for movement
void processInput(char input, int maze[][MAX_COLS], int rows, int cols) {
    int newX = playerX, newY = playerY;

    // Determine the player's new position based on input
    switch (input) {
        case 'W': case 'w': newY--; break; // Move up
        case 'A': case 'a': newX--; break; // Move left
        case 'S': case 's': newY++; break; // Move down
        case 'D': case 'd': newX++; break; // Move right
        default:
            UART0_StringOutput("Invalid input! Use W, A, S, D to move.\r\n");
            return;
    }

    // Check if the new position is within bounds and not a wall
    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && maze[newY][newX] != 1) {
        playerX = newX;
        playerY = newY;

        // Check if the player has reached the end point ('E')
        if (maze[playerY][playerX] == 'E') {
            // Temporarily update the maze to reflect the player's position
            maze[playerY][playerX] = 'P';

            // Print the updated maze one last time
            UART0_StringOutput("\033[H\033[J"); // Clear screen
            printMaze(maze, rows, cols);

            // Restore the end point to 'E' for consistency
            maze[playerY][playerX] = 'E';

            // Print the victory message
            UART0_StringOutput("Congratulations! You've reached the end!\r\n");
            EndMenuDisplay();
            SysTick_Delay1ms(4000);
            return; // Exit the function
        }
    } else {
        UART0_StringOutput("Cannot move there! Wall or out of bounds.\r\n");
        SysTick_Delay1ms(1000);
    }
}

// Display the menu
void MenuDisplay(void) {
    UART0_StringOutput("--- Welcome to the Maze Game ---\r\n");
    UART0_StringOutput("1. Hard Mode (23x23 Maze)\r\n");
    UART0_StringOutput("Select 1 maze by entering 1.\r\n");
}

void EndMenuDisplay(void) {
    UART0_StringOutput("--- Thanks for PLaying ---\r\n");
    UART0_StringOutput("'Q for quit Game'\r\n");
}

// Display instructions
void DisplayInstructions(void) {
    UART0_StringOutput("Instructions:\r\n");
    UART0_StringOutput("1. Use W, A, S, D to move through the maze.\r\n");
    UART0_StringOutput("2. Your goal is to reach the end marked as 'E'.\r\n");
    UART0_StringOutput("3. Press 'Q' to quit.\r\n");
}

// Main game loop
void PlayGame(void) {
    char choice;
    while (1) {
        MenuDisplay();
        choice = UART0_Read_Char();
        // UART0_CharOutput(choice); // selection works
        // SysTick_Delay1ms(2000);
				UART0_CharOutput(choice);
        if (choice == '1') {
            mazeChoice = 1;
            findStart(maze3, &playerX, &playerY, 23, 23);
        }
        /*
        else if (choice == '2') {
            mazeChoice = 2;
            findStart(maze2, &playerX, &playerY, 13, 13);
        } 
        else if (choice == '3') {
            mazeChoice = 3;
            findStart(maze3, &playerX, &playerY, 23, 23);
        }*/ 
        else {
            
        }
				
        while (1) {
            UART0_StringOutput("\033[H\033[J"); // Clear screen
            if (mazeChoice == 1) {
              printMaze(maze3, 23, 23);
              DisplayInstructions();
            } 
            

            char input = UART0_Read_Char();
            if (input == 'Q' || input == 'q') {
                UART0_StringOutput("Exiting the game...\r\n");
                UART0_NewLine();
                UART0_StringOutput("Would you like to replay? Yes(Y), No(N)\r\n");
                input = UART0_Read_Char();
                if(input == 'Y' || input == 'y')
                {
                  PlayGame();
                }
                else if(input == 'N' || input == 'n'){
									UART0_StringOutput("Thanks For Playing");
									SysTick_Delay1ms(1000);
                  return;
                }
                else{
                  UART0_StringOutput("Invalid choice! Try again.\r\n");
									SysTick_Delay1ms(500);
                  continue;
                }
            }
            processInput(input,maze3, 23, 23);
        }
    }
}

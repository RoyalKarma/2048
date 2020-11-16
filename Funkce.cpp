#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>
#include "Header.h"
int GameBoardMatrix[4][4];

void printBoardMatrix() // Print Board - y Up, Down,  x - Left, Right
{
    system("cls");
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
            if (GameBoardMatrix[x][y] == 0) // if 0 print dot 
            {
                printf(" . ");
            }
            else
            {
                printf(" %d ", GameBoardMatrix[x][y]); // Print numbers in matrix 
            }
        printf("\n"); // New line if line in matrix has numbers or dots
    }
}

void random2()
{
    srand(time(NULL));
    Sleep(1);
    int x = rand() % 4;
    int y = rand() % 4;

    if (GameBoardMatrix[x][y] == 0)
    {
        GameBoardMatrix[x][y] = 2;
        
        printBoardMatrix();
    }
    else
        random2();


}

int mainmenu() // Main menu
{
    system("cls");
    printf("2048\nNew game: n\nContinue game: c\nLeaderboard: l\nQuit : q\n");

    //char input; // User Input in Main Menu - Old Code
    int input; 
    //scanf_s(" %c", &input, 1); - Old Code
    input = controls();
    bool inprogress;
    if (input == 110) // Play new Game
    {
        inprogress = true;
       // printBoardMatrix();
        while (inprogress == true)
        {
           
            game();
            inprogress = false;
        }
        mainmenu();
    }
    else if (input == 99 ) // Continue Game
    {
        inprogress = true;
        printBoardMatrix();
        while (inprogress == true)
        {
            //ContinueGame;
            controls();
            Sleep(5000);
            inprogress = false;
        }
        mainmenu();
    }
    else if (input == 108) // Leaderboard 
    {
        system("cls");
        printf("Lmao leaderboarda here");
        Sleep(5000);
        mainmenu();
    }
    else if (input == 27) // Quit game
    {
        return 0;
    }
   
}


void game() // Main Game Script - put all things in here, Do not bloat code with copying this to ContinueGame, load state and call game
{
    random2();
   
    while (1)
    {
    gamecontrols();
    
    }
}

void up() // Move numbers in Array up - ignore merging
{
  

    for (int x = 0; x < 4; x++)       // Traverse from Top to bottom of a column
        for (int y = 0; y < 4; y++)
        {
            if (!GameBoardMatrix[x][y])    // If tile is empty
            {
                for (int k = y + 1; k < 4; k++)  // Traverse below to find a non-zero element
                    if (GameBoardMatrix[x][k])
                    {
                        GameBoardMatrix[x][y] = GameBoardMatrix[x][k]; // Move the non-zero element to the empty tile
                        GameBoardMatrix[x][k] = 0;          // Assign the non-zero element with zero
                        y++;
                    }
            }
        }
    
}

void down() //Move Numbers in Array down - Ignore Merging
{

    for (int x = 3; x >= 0; x--)       // Traverse from bottom to top of a column
        for (int y = 3; y >= 0; y--)
        {
            if (!GameBoardMatrix[x][y])    // If tile is empty
            {
                for (int k = y - 1; k >= 0; k--)  // Traverse below to find a non-zero element
                    if (GameBoardMatrix[x][k])
                    {
                        GameBoardMatrix[x][y] = GameBoardMatrix[x][k]; // Move the non-zero element to the empty tile
                        GameBoardMatrix[x][k] = 0;  // Assign the non-zero element with zero
                        y--;
                    }
            }
        }
}

void left() // Move numbers in Array to the left - Ignore Merging
{
    for (int y = 0; y < 4; y++)       // Scan Matrix  c - column l - line, scan from left to right
        for (int x = 0; x < 4; x++)
        {
            if (!GameBoardMatrix[x][y])    // If tile is empty
            {
                for (int k = x + 1; k < 4; k++)  // 
                    if (GameBoardMatrix[k][y])
                    {
                        GameBoardMatrix[x][y] = GameBoardMatrix[k][y]; // Move the non-zero element to the empty tile
                        GameBoardMatrix[k][y] = 0;          // Assign the non-zero element with zero
                        x++;
                    }
            }
        }
}

void right() // Move numbers in Array to the right - Ignore Merging
{
    for (int y = 3; y >= 0; y--)       // Scan Matrix  c - column l - line, scan from right to left
        for (int x = 3; x >= 0; x--)
        {
            if (!GameBoardMatrix[x][y])    // If tile is empty
            {
                for (int k = x - 1; k >= 0; k--)  // 
                    if (GameBoardMatrix[k][y])
                    {
                        GameBoardMatrix[x][y] = GameBoardMatrix[k][y]; // Move the non-zero element to the empty tile
                        GameBoardMatrix[k][y] = 0;          // Assign the non-zero element with zero
                        x--;
                    }
            }
        }
}


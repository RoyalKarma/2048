#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>
#include "Header.h"
int GameBoardMatrix[4][4];
char Username[256];
void clearmatrix()
{
   for (int y = 0; y < 4; ++y)
    {
       for (int x = 0; x < 4; ++x)
       {
           GameBoardMatrix[x][y] = 0;
       }
    }
}
/*bool gameOver()           Pokud je pole plné, ukonèí hru. Pokud nepøijdem na nic lepší tak to asi mužem použit jako gameover
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (GameBoardMatrix[x][y] == 0)
            {
                return false;     
            }
        }
    }
    return true;   
}*/

int adj()
{
    int i = 0;
    int help = 0;
    unsigned int counter = 0;
    for (int y = 0; y < 4 && !help; y++)
    {
        for (i = 0; i < 4 - 1 && !help; i++) 
        {
            if (GameBoardMatrix[i][y] == GameBoardMatrix[i + 1][y])
            {

                help = 1;
                counter++;
                break;
            }
        }
    }

   
    if (help == 0)
    {
        
        for (int x = 0; x < 4 && !help; x++) 
        {
            for (i = 0; i < 4 - 1 && !help; i++) 
            {
                if (GameBoardMatrix[x][i] == GameBoardMatrix[x][i + 1])
                {
                    counter++;
                    break;
                }

                    
            }
        }
    }
    return counter;
}
void printBoardMatrix() // Print Board - y Up, Down,  x - Left, Right
{
    system("cls");
    char emptyspace[] = ".";
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
            if (GameBoardMatrix[x][y] == 0) // if 0 print dot 
            {
                printf("%6.1s" , emptyspace);
            }
            else
            {
                printf("%6.1d", GameBoardMatrix[x][y]); // Print numbers in matrix 
            }
        printf("\n\n"); // New line if line in matrix has numbers or dots
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
    printf("2048\nNew game: n\nContinue game: c\nLeaderboard: l\nQuit : ESC\n");

    int input;
    input = controls();
    bool inprogress;

    switch (input)
    {
    case 110: //New Game
        inprogress = true;
        while (inprogress == true)
        {
            system("cls");
            printf("Please enter your username: ");
            scanf_s(" %s", Username, sizeof(Username));
            clearmatrix();
            game();
            inprogress = false;
        }
        mainmenu();
        break;
    case 99:  //Continue game
        inprogress = true;
        while (inprogress == true)
        {
            controls();
            loadstate();
            game();
            
            inprogress = false;
        }
        mainmenu();
        break;
    case 108: //Leaderboard
        system("cls");
        printf("Lmao leaderboarda here");
        Sleep(5000); 
        mainmenu();
        break;
    case 27: //ESC
        return 0;
        break;
    default: mainmenu();
    }

}

int score() // Is highscore the highest achieved number or sum of all numbers in the matrix ?
{
    int max = GameBoardMatrix[0][0];
    int sum = 0;
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            sum = sum + GameBoardMatrix[x][y];
   
    return sum;
}

int loadstate()
{
    system("cls");
    printf("Choose save slot 1, 2 or 3: ");
    // please add magic code that makes it ignore other inputs ._.
    int input = controls();
    int i = 0;
    double loadscore = 0;
    if (input == 49) //load slot1
    {
        FILE* load1;
        errno_t errorCode1 = fopen_s(&load1, "save_1.dat", "r");
        if (load1 == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        system("cls");
        //it works and I will not question it
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (!fscanf_s(load1, "%d", &GameBoardMatrix[x][y]))
                    break;



            }

        }
       /* 
     Tahle funkce je schopná pøeèíst  username, ale ani za pièu nevím jak ho uložit do Username aniž bych dojebal všechno ostatní
     K ètení score se radši ani nebudu vyjadøovat*/



        int loop;
        char name[256];
        int line = 4;
        int end;
        for(end = loop = 0;loop<line;++loop)
        {
            if(0==fgets(name, sizeof(name), load1))
            {
                end = 1;
                break;
            }
        }
        
        printf("\n %s\n", name); //test for correct reading
        Sleep(5000);

       ;
    }

    if (input == 50) //load slot2
    {
        FILE* load2;
        errno_t errorCode2 = fopen_s(&load2, "save_2.dat", "r");
        if (load2 == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        system("cls");
        
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (!fscanf_s(load2, "%d", &GameBoardMatrix[x][y]))
                    break;



            }

        }

    }
    if (input == 51) //load slot3
    {
        FILE* load3;
        errno_t errorCode3 = fopen_s(&load3, "save_3.dat", "r");
        if (load3 == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        system("cls");
       
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (!fscanf_s(load3, "%d", &GameBoardMatrix[x][y]))
                    break;



            }

        }
    }
}

void game() // Main Game Script - put all things in here, Do not bloat code with copying this to ContinueGame, load state and call game
{
    random2(); //this needs to be ignored afer we load a game
    bool inprogress = true;
    while (inprogress == true)
    {
        int input = gamecontrols();
        printf(" score: %d", score());
        if (input == 0)
        inprogress = false;
        if (WinCon() == 1)
            inprogress = false;
        if (adj() != 0)
            inprogress = false;
        /*if (gameOver() == 1)
            inprogress = false;*/
    }
    endgame();
}

int save()
{
    bool inprogress = true;
    printf("Choose save slot 1, 2 or 3: ");// please add magic code that makes it ignore other inputs
    int input = controls();
    system("cls");
   
    if (input == 49) //Save to slot1
    {
        FILE* save1;
        errno_t errorCode1 = fopen_s(&save1, "save_1.dat", "w");
        if (save1 == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                fprintf(save1, "%d ", GameBoardMatrix[x][y]);
            }
            fprintf(save1, "\n");
        }
        

        fprintf(save1, "\nUsername: %s", Username);
        fclose(save1);
        printf("Save complete");
        Sleep(1000);
        
    }
    if (input == 50) //Save to slot2
    {
        FILE* save2;
        errno_t errorCode2 = fopen_s(&save2, "save_2.dat", "w");
        if (save2 == NULL)
        {
            perror("Error opening file");
            return(-1);
        }
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                fprintf(save2, "%d ", GameBoardMatrix[x][y]);
            }
            fprintf(save2, "\n");
        }
        

        fprintf(save2, "\n%s", Username);
        fclose(save2);
        printf("Save complete");
        Sleep(1000);
        
    }
    if (input == 51) // Save to slot3
    {
        FILE* save3;
        errno_t errorCode3 = fopen_s(&save3, "save_3.dat", "w");
        if (save3 == NULL)
        {
            perror("Error opening file");
            return -1;
        }
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                fprintf(save3, "%d ", GameBoardMatrix[x][y]);
            }
            fprintf(save3, "\n");
        }
       

        fprintf(save3, "\nUsername: %s", Username);
        fclose(save3);
        printf("Save complete");
        Sleep(1000);
        
    }
    if (input == 48)
    {
 
        return 0;
    }
    
}

int WinCon() // Check for 2048, if its present, end the game.
{
    int max = GameBoardMatrix[0][0];
    int static sum = 0;
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            if (GameBoardMatrix[x][y] > max)
                max = GameBoardMatrix[x][y];
    sum += max;
    if (max == 2048) // change to 16 for testing
    {
        endgame();
        return 1;
    }
    return 0;
}

void endgame()
{
    system("cls");
    printf("Nice");
    Sleep(5000);
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
                        y++; // Move "zero scanner" to not write other numbers to this
                    }
            }
        }
    for (int x = 0; x < 4; x++)       // Traverse from Top to bottom of a column
        for (int y = 0; y < 4; y++)
        {
            if (GameBoardMatrix[x][y] && GameBoardMatrix[x][y] == GameBoardMatrix[x][y + 1]) // Check Tile is non zero and
            {                                        // adjacent tile is equal
                GameBoardMatrix[x][y] += GameBoardMatrix[x][y + 1];             // add to first element or double
                GameBoardMatrix[x][y + 1] = 0;                       // assign second element with zero
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
                        y--; // Move "zero scanner" to not write other numbers to this
                    }
            }
        }
    for (int x = 3; x >= 0; x--)       // Traverse from bottom to top of a column
        for (int y = 3; y >= 0; y--)
        {
            if (GameBoardMatrix[x][y] && GameBoardMatrix[x][y] == GameBoardMatrix[x][y - 1]) // Check Tile is non zero and adjacent tile is equal
            {
                GameBoardMatrix[x][y] += GameBoardMatrix[x][y - 1];             // add to first element or double
                GameBoardMatrix[x][y - 1] = 0;                       // assign second element with zero
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
                        x++; // Move "zero scanner" to not write other numbers to this
                    }
            }
        }
    for (int y = 0; y < 4; y++)       // Scan Matrix  c - column l - line, scan from left to right
        for (int x = 0; x < 4; x++)
        {
            if (GameBoardMatrix[x][y] && GameBoardMatrix[x][y] == GameBoardMatrix[x + 1][y])//Check if adjecent tiles are equaland non zero
            {
                GameBoardMatrix[x][y] += GameBoardMatrix[x + 1][y];
                GameBoardMatrix[x + 1][y] = 0;
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
                for (int k = x - 1; k >= 0; k--)  // Look for Empty tile
                    if (GameBoardMatrix[k][y])
                    {
                        GameBoardMatrix[x][y] = GameBoardMatrix[k][y]; // Move the non-zero element to the empty tile
                        GameBoardMatrix[k][y] = 0;          // Assign the non-zero element with zero
                        x--; // Move "zero scanner" to not write other numbers to this
                    }
            }

        }

    for (int y = 3; y >= 0; y--)       // Scan Matrix  c - column l - line, scan from right to left
        for (int x = 3; x >= 0; x--)
        {
            if (GameBoardMatrix[x][y] && GameBoardMatrix[x][y] == GameBoardMatrix[x - 1][y]) // Check if adjecent tiles are equal and non zero
            {
                GameBoardMatrix[x][y] += GameBoardMatrix[x - 1][y]; // add
                GameBoardMatrix[x - 1][y] = 0;// Assign 0 to second element
            }
        }
}
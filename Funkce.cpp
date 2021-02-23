#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>
#include "Header.h"
int GameBoardMatrix[4][4];
char Username[SIZE];
struct Leaderboard* first = NULL;

 //basic game functions
int score() // take sum of all numbers in matrix
{
    int max = GameBoardMatrix[0][0];
    int sum = 0;
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            sum = sum + GameBoardMatrix[x][y];

    return sum; // score
}
int mainmenu() // Main menu
{
    int input;
    do
    {
        system("cls");
        printf("   ___   ____  __ __  ____ \n");
        printf("  |__   / __  / // / ( __ )\n");
        printf("  __/ // / / / // /_/ __  |\n");
        printf(" / __// /_/ /__  __/ /_/ / \n");
        printf("/____/ ____/  /_/   ____/  \n");
        printf("|________________|\n");
        printf("|New game: n     |\n|________________|\n");
        printf("|Continue game: c|\n|________________|\n");
        printf("|Leaderboard: l  |\n|________________|\n");
        printf("|Quit : ESC      |\n|________________|\n");


        bool inprogress;
        input = controls();
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
                random2();
                game();
                inprogress = false;

            }
            break;
        case 99:  //Continue game
            inprogress = true;
            while (inprogress == true)
            {
                loadstate();
                game();
                inprogress = false;
            }
            break;
        case 108: //Leaderboard
            system("cls");
            printLead();
            printf("\n Press f to continue");
            while (controls() != 'f');
            break;
        case 27: //ESC
            return 0;
            break;
        }
    } while (input != 27);
    return 0;
}
void game() // Main Game Script - put all things in here, Do not bloat code with copying this to ContinueGame, load state and call game
{
    bool inprogress = true;
    while (inprogress == true)
    {
        int input = gamecontrols();
        printf(" score: %d", score());
        if (input == 0)
            inprogress = false;
        else if (WinCon() == 1)
            inprogress = false;
        else if (adj() == 0) {
            inprogress = false;
            endgameLose();
        }
    }
}


//matrix functions

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
void clearmatrix() // Fill matrix with zeroes
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            GameBoardMatrix[x][y] = 0;
        }
    }
}
int random2() // Generate 2 in a random position
{
    int x = rand() % 4;
    int y = rand() % 4;

    if (GameBoardMatrix[x][y] == 0)
    {
        GameBoardMatrix[x][y] = 2;
        printBoardMatrix();
    }
    else if (adj() == 0)
    {
        return -1;
    }
    else
    random2();
}



//loading and saving functions
int loadstate() // Load State from X slot
{
    system("cls");
    printf("Choose save slot 1, 2 or 3: ");
    
    int input = controls();
    int i = 0;
    double loadscore = 0;
    int loop;
    int line = 4;
    int end;
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
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (!fscanf_s(load1, "%d", &GameBoardMatrix[x][y]))
                    break;
            }
        }


        for(end = loop = 0;loop<line;++loop)
        {
            if(0==fgets(Username, sizeof(Username), load1))
            {
                end = 1;
                break;
            }
        }
        printf("\n %s\n", Username); //testing if loading is correct
        Sleep(1000);
        printBoardMatrix();
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

        

        for (end = loop = 0; loop < line; ++loop)
        {
            if (0 == fgets(Username, sizeof(Username), load2))
            {
                end = 1;
                break;
            }
        }
        printf("\n %s\n", Username); //show username, mostly testing purposes
        Sleep(1000);
        printBoardMatrix();
    }
    if (input == 51) //load slot3
    {
        FILE* load3;
        errno_t errorCode1 = fopen_s(&load3, "save_3.dat", "r");
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

        

        for (end = loop = 0; loop < line; ++loop)
        {
            if (0 == fgets(Username, sizeof(Username), load3))
            {
                end = 1;
                break;
            }
        }
        printf("\n %s\n", Username); //show username, mostly testing purposes
        printBoardMatrix();
    }
}

int save() // Save State to X slot
{
    bool inprogress = true;
    printf("Choose save slot 1, 2 or 3: ");
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
        fprintf(save1, "\n%s", Username);
        fclose(save1);
        printf("Progress Saved");
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
        printf("Progress Saved");
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
        fprintf(save3, "\n%s", Username);
        fclose(save3);
        printf("Progress Saved");
        Sleep(1000);    
    }
    if (input == 48)
    {
        return 0;
    }
}

int savetofile()//save state of leaderboard to file
{
    FILE* Leader;
    errno_t errorCode1 = fopen_s(&Leader, "Leaderboard.dat", "w");
    if (Leader == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    struct Leaderboard* OLeaderboard = first;

    while (OLeaderboard)
    {
        fprintf(Leader, " %s %d\n" , OLeaderboard->Username, OLeaderboard->Score);
        OLeaderboard = OLeaderboard->next;
    }
    fclose(Leader);
}

int loadleader() //load the state of leaderboard from a file, suicidal function
{
    FILE* Leader;
    errno_t errorCode1 = fopen_s(&Leader, "Leaderboard.dat", "r");
    if (Leader == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    char name[SIZE];
    char help[SIZE];
    int num = 0;

    while (!feof(Leader))
    {
        if (fscanf_s(Leader, "%s", name, SIZE) > 0)
        {
            if (fscanf_s(Leader, "%s",  help, SIZE) > 0)
            {
                num = atoi(help);
            }
            saveLead(name, num, &first);
        }

    }
    fclose(Leader);
}

//Win/loose funcitons
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
int adj() // Checker for possible movements if Matrix is reaching low available spaces
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

    if (help == 0)// only check rows if there are no moves in collums
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

void printLead() // Main menu only Leaderboard printer
{
    printf("    __    _________    ____  __________  ____  ____  ___    ____  ____ \n");
    printf("   / /   / ____/   |  / __  / ____/ __  / __ )/ __  /   |  / __  / __ | \n");
    printf("  / /   / __/ / /| | / / / / __/ / /_/ / __  / / / / /| | / /_/ / / / /\n");
    printf(" / /___/ /___/ ___ |/ /_/ / /___/ _, _/ /_/ / /_/ / ___ |/ _, _/ /_/ / \n");
    printf("/_____/_____/_/  |_/_____/_____/_/ |_/_____/ ____/_/  |_/_/ |_/_____/  \n\n");

    struct Leaderboard* OLeaderboard = first;
    while (OLeaderboard)
    {
        printf(" %s %d\n", OLeaderboard->Username, OLeaderboard->Score);
        OLeaderboard = OLeaderboard->next;
    }
}

void endgame() // Winning end
{
    system("cls");
    printf(" _       _______   __\n");
    printf("| |     / /  _/ | / /\n");
    printf("| | /| / // //  |/ / \n");
    printf("| |/ |/ // // /|  /  \n");
    printf("|__/|__/___/_/ |_/   \n\n\n");
    printf("Leaderboard\n");
    saveLead(Username, score(), &first);
    struct Leaderboard* OLeaderboard = first;
    while (OLeaderboard)
    {
        printf(" %s %d\n", OLeaderboard->Username, OLeaderboard->Score);
        OLeaderboard = OLeaderboard->next;
    }
    savetofile();
    printf("\n Press f to continue");
    while (controls() != 'f');
}

void endgameLose() // ends game if you lose
{
    system("cls");
    printf("    ____  _____________________  ______\n");
    printf("   / __  / ____/ ____/ ____/   |/_  __/\n");
    printf("  / / / / __/ / /_  / __/ / /| | / /   \n");
    printf(" / /_/ / /___/ __/ / /___/ ___ |/ /    \n");
    printf("/_____/_____/_/   /_____/_/  |_/_/     \n");
    printf("Leaderboard\n");
    saveLead(Username, score(), &first);
    struct Leaderboard* OLeaderboard = first;
    while (OLeaderboard)
    {
        printf(" %s %d\n", OLeaderboard->Username, OLeaderboard->Score);
        OLeaderboard = OLeaderboard->next;
    }
    savetofile();
    printf("\n Press f to continue");
    while (controls() != 'f');
}

//move functions
void up() // Move numbers in Array up
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

void down() //Move Numbers in Array down 
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

void left() // Move numbers in Array to the left 
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

void right() // Move numbers in Array to the right 
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
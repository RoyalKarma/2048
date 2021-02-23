#include <iostream>
#include <conio.h>
#include "Header.h"
#define getch() _getch()

int controls() // Keyboard control
{
    unsigned int key;
    key = getch();
    if (key == 0 || key == 0xE0) {
        key = getch();
    }
    return key;
}

int gamecontrols()
{
    //Controls for the game itself
    int input = controls();

    switch (input)
    {
    case 27:
        return 0;
        break;
    case 72:
        up();
        random2();
        break;
    case 80:
        down();
        random2();
        break;
    case 75:
        left();
        random2();
        break;
    case 77:
        right();
        random2();
        break;
    case 115:
        system("cls");
        save();
        break;
    default:
        gamecontrols();
    }
}

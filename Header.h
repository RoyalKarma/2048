#pragma once
void game();
int mainmenu();
void clearmatrix();
void printBoardMatrix();
void random2();
int gamecontrols();
//Controls
int controls();
void up();
void down();
void left();
void right();
int save();
int WinCon();
void endgame();
int adj();
int loadstate();
struct LeaderBoard
{
	char Username[256];
	int Score;
};


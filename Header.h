#pragma once
#define SIZE 22

// Game functions
int mainmenu();
void game();
void clearmatrix();
void printBoardMatrix();
int random2();
int gamecontrols();
//Controls
int controls();
void up();
void down();
void left();
void right();
//Save Load
int save();
int loadstate();
//GameState
int WinCon();
void endgame();
void endgameLose();
int adj();
//Leaderboard Struct
void printLead();
int savetofile();
int loadleader();
struct Leaderboard
{
	char Username[SIZE];
	int Score;
	struct Leaderboard* next;
};
void saveLead(char* Username, int Score,struct Leaderboard** sh_first);


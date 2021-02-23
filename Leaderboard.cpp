#include <iostream>
#include "Header.h"

void saveLead(char* Username, int Score, struct Leaderboard** sh_first) // Save Leaderboard to memory struct -> NOT TO A FILE 
{
	struct Leaderboard* NLeaderboard; // New Leaderboard
	struct Leaderboard* OLeaderboard; // Old Leaderboard
	NLeaderboard = (struct Leaderboard*)malloc(sizeof(struct Leaderboard));

	strcpy_s(NLeaderboard->Username, SIZE, Username);
	NLeaderboard->Score = Score;
	NLeaderboard->next = NULL;

	if (*sh_first == NULL)
	{
		*sh_first = NLeaderboard;
		return;
	}
	else if (NLeaderboard->Score > (*sh_first)->Score)
	{
		NLeaderboard->next = *sh_first;
		*sh_first = NLeaderboard;
		return;
	}

	OLeaderboard = *sh_first;
	while (OLeaderboard)
	{
		{
			if (OLeaderboard->next == NULL)
			{
				OLeaderboard->next = NLeaderboard;
				return;
			}
			else if (NLeaderboard->Score > OLeaderboard->next->Score)
			{
				NLeaderboard->next = OLeaderboard->next;
				OLeaderboard->next = NLeaderboard;
				return;
			}
			OLeaderboard = OLeaderboard->next;
		}
	}
}


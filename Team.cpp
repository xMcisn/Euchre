#include "Team.h"

Team::Team()
{
	score = 0;
	totalTricks = 0;
	playerNum1 = -1;
	playerNum2 = -1;
}

Team::Team(int p1, int p2)
{
	score = 0;
	totalTricks = 0;
	playerNum1 = p1;
	playerNum2 = p2;
}

int Team::getPlayerNum1()
{
	return playerNum1;
}

void Team::setPlayerNum1(int pNum)
{
	playerNum1 = pNum;
}

int Team::getPlayerNum2()
{
	return playerNum2;
}

void Team::setPlayerNum2(int pNum)
{
	playerNum2 = pNum;
}

int Team::getScore()
{
	return score;
}

void Team::increaseScore(int amountToIncreaseScore)
{
	score += amountToIncreaseScore;
}

int Team::getNumOfTricks()
{
	return totalTricks;
}
void Team::increaseTrickCountByOne()
{
	totalTricks++;
}

void Team::resetTrickCountToZero()
{
	totalTricks = 0;
}
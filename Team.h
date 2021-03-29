#pragma once
#ifndef TEAM_H
#define TEAM_H

class Team
{
private:
	int score;
	int playerNum1;
	int playerNum2;
public:
	Team();
	Team(int player1, int player2);

	int getPlayerNum1();
	void setPlayerNum1(int pNum);

	int getPlayerNum2();
	void setPlayerNum2(int pNum);

	int getScore();
	void increaseScore(int amountToIncreaseBy);
};

#endif
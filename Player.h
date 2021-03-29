#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"

class Player
{
private:
	int numCardsInHand;
	Deck playerDeck;
	bool dealerStatus;
	std::string playerType;
	int handsWon;
public:
	Player();

	void viewDeck();
	Deck* getDeck();

	int getNumOfCardsInHand();
	void increaseNumOfCardsInHand();

	void setDealerStatus(bool status);
	bool getDealerStatus();

	void setPlayerType(std::string newType);
	std::string getPlayerType();

	void increaseHandsWon();
	int getHandsWon();
};
#endif // !PLAYER_H

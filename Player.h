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
};
#endif // !PLAYER_H

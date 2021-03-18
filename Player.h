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
public:
	Player();

	void viewDeck();
	Deck* getDeck();

	int getNumOfCardsInHand();
	void increaseNumOfCardsInHand();

	void setDealerStatus(bool status);
	bool getDealerStatus();
};
#endif // !PLAYER_H

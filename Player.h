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
};
#endif // !PLAYER_H

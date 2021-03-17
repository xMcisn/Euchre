#pragma once
#ifndef IPC_H
#define IPC_H

#include "Player.h"

class IPC
{
private:
	int currentPlayer;
	int dealer;
	char trumpSuit;
public:
	IPC();
	void passCardsToPlayers(Player p[4], Deck* mainDeck);
	void displayTopCardInMainDeck(Deck* mainDeck);
	bool pickUpOrPass(Player p[4], Deck* mainDeck);
	char pickASuit(Deck* mainDeck);
	void playersPlaceCardOnPile(Player p[4], Deck* pileDeck);


	char getTrump();
};

#endif
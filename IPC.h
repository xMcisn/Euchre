#pragma once
#ifndef IPC_H
#define IPC_H

#include "Player.h"

class IPC
{
private:
	int currentPlayer;
public:
	IPC();
	void passCardsToPlayers(Player p[4], Deck* mainDeck);

	void playersPlaceCardOnPile(Player p[4], Deck* pileDeck);
};

#endif
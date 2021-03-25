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
	int trickWinner;
public:
	IPC();
	IPC(int dlr);

	void passCardsToPlayers(Player p[4], Deck* mainDeck);
	void displayTopCardInMainDeck(Deck* mainDeck);
	bool pickUpOrPass(Player p[4], Deck* mainDeck);
	void cardToDiscard(Player p[4], Deck* mainDeck);
	char pickASuit(Deck* mainDeck);
	void playersPlaceCardOnPile(Player p[4], Deck* pileDeck);


	char getTrump();

	void setCurrentPlayer(int curPlyr);
	int getCurrentPlayer();

	void setDealer(Player p[4]);
	int getCurrentDealer();
	
	void setNextDealerAndUpdatePrevious(Player p[4]);
};

#endif
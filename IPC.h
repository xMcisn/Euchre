#pragma once
#ifndef IPC_H
#define IPC_H

#include "Player.h"
#include "Team.h"

class IPC
{
private:
	int currentPlayer;
	int dealer;
	char trumpSuit;
	int trickWinner;
	int trumpCaller;
	Team t1 = Team(0, 2);
	Team t2 = Team(1,3);
public:
	IPC();
	IPC(int dlr);

	void passCardsToPlayers(Player p[4], Deck* mainDeck);
	void displayTopCardInMainDeck(Deck* mainDeck);
	bool pickUpOrPass(Player p[4], Deck* mainDeck);
	void cardToDiscard(Player p[4], Deck* mainDeck);
	char pickASuit(Deck* mainDeck);
	void playersPlaceCardOnPile(Player p[4], Deck* pileDeck);
	void placeCardsBackInMainDeck(Deck* pileDeck, Deck* mainDeck);
	void determineWhichTeamWonRoundAndIncreaseScore();
	void displayTeamScores();

	char getTrump();

	void setCurrentPlayer(int curPlyr);
	int getCurrentPlayer();

	void setDealer(Player p[4]);
	int getCurrentDealer();
	
	void setNextDealerAndUpdatePrevious(Player p[4]);
};

#endif
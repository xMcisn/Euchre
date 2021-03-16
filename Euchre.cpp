// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Deck.h"
#include "Player.h"
#include "IPC.h"

void displayAllPlayersCards(Player p[4]);

int main()
{
	Deck myEuchreDeck;
	Deck pileDeck;
	Player players[4];
	IPC communicator;
	
	myEuchreDeck.buildMainDeck();

	myEuchreDeck.printDeck();

	for (int i = 0; i < 5; i++)
	{
		myEuchreDeck.shuffle();
		std::cout << "---------------------------------------Post " << i+1 << " shuffle---------------------------------------\n";
		myEuchreDeck.printDeck();
	}

	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();

	communicator.passCardsToPlayers(players, &myEuchreDeck);

	for (int i = 0; i < 4; i++)
	{
		displayAllPlayersCards(players);
		communicator.playersPlaceCardOnPile(players, &pileDeck);
	}

	std::cout << "----------Pile Deck----------\n";
	pileDeck.printDeck();

	return 0;
}

void displayAllPlayersCards(Player p[4])
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << "----------Player " << i + 1 << " Deck----------\n";
		p[i].viewDeck();
	}
}
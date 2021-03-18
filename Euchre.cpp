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
	IPC communicator(1);

	myEuchreDeck.buildMainDeck();

	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();
	std::cout << "-----------------------------\n";

	for (int i = 0; i < 5; i++)
	{
		myEuchreDeck.shuffle();
	}

	communicator.setDealer(players);

	communicator.passCardsToPlayers(players, &myEuchreDeck);
	std::cout << "----------Top Card----------\n";
	communicator.displayTopCardInMainDeck(&myEuchreDeck);
	std::cout << "----------------------------\n";
	displayAllPlayersCards(players);
	bool result = communicator.pickUpOrPass(players, &myEuchreDeck);
	
	std::cout << result << std::endl;
	displayAllPlayersCards(players);

	if (result == 0)
		communicator.pickASuit(&myEuchreDeck);
	else
		communicator.cardToDiscard(players, &myEuchreDeck);

	std::cout << "Trump Suit: " << communicator.getTrump() << std::endl;

	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();
	std::cout << "-----------------------------\n";

	displayAllPlayersCards(players);

	return 0;
}

void displayAllPlayersCards(Player p[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (p[i].getDealerStatus() == true)
		{
			std::cout << "----------Player " << i << " Deck----------*Dealer*\n";
		}
		else
		{
			std::cout << "----------Player " << i << " Deck----------\n";
		}
		p[i].viewDeck();
		std::cout << "---------------------------------\n";
	}
}
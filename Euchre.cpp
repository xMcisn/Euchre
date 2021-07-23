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
	char trumpSt = '-';

	myEuchreDeck.buildMainDeck();

	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();

	for (int i = 0; i < 5; i++)
	{
		myEuchreDeck.shuffle();
		std::cout << "------Shuffle " << i+1 << " ------\n";
		myEuchreDeck.printDeck();
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
		trumpSt = communicator.pickASuit(&myEuchreDeck);
	else
		communicator.cardToDiscard(players, &myEuchreDeck);

	if(trumpSt == 'X')
	{
		std::cout << "No suit was picked. Ending program.\n";
		return 0;
	}

	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();

	displayAllPlayersCards(players);
	std::cout << "Trump Suit: " << communicator.getTrump() << std::endl;
	communicator.setCurrentPlayer(communicator.getCurrentDealer() + 1);

	std::cout << "Current Player: " << communicator.getCurrentPlayer() << std::endl;
	for(int i = 0; i < 5; i++)
	{
		communicator.playersPlaceCardOnPile(players, &pileDeck);
	    std::cout << "------Pile Deck after round " << i+1 << " ------\n";
		pileDeck.printDeck();
		std::cout << "Trump Suit: " << communicator.getTrump() << std::endl;
		displayAllPlayersCards(players);
		communicator.placeCardsBackInMainDeck(&pileDeck, &myEuchreDeck);
	}
	communicator.determineWhichTeamWonRoundAndIncreaseScore();
	communicator.setNextDealerAndUpdatePrevious(players);
	std::cout << "----------Main Deck----------\n";
	myEuchreDeck.printDeck();
	communicator.displayTeamScores();

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
	}
}
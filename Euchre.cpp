// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Deck.h"

int main()
{
	Deck myEuchreDeck;

	myEuchreDeck.printDeck();

	myEuchreDeck.shuffle();

	std::cout << "----------------------------------------------NEW DECK----------------------------------------------\n";

	myEuchreDeck.printDeck();


	myEuchreDeck.shuffle();

	std::cout << "----------------------------------------------NEW DECK----------------------------------------------\n";

	myEuchreDeck.printDeck();
	return 0;
}
// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Deck.h"

int main()
{
	Deck* myEuchreDeck = new Deck();

	myEuchreDeck->printDeck();

	return 0;
}
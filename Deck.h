#pragma once
#ifndef EUCHRE_H
#define EUCHRE_H

#include <string>

class Deck
{
	struct Card
	{
		char suit;
		std::string name;
		Card * next;
	};

	Card* head;
	Card* tail;

	int deckSize;
public:
	Deck();
	void shuffle();

	void setSuit(char st);
	char getSuit();

	void setName(std::string nme);
	std::string getName();

	void printDeck();
};

#endif // !"EUCHRE.H"
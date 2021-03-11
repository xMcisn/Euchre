#pragma once
#ifndef EUCHRE_H
#define EUCHRE_H

#include <string.h>
using namespace std;

class Deck
{
	struct Card
	{
		char suit;
		string name;
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

	void setName(string nme);
	string getName();

	void printDeck();
};

#endif // !"EUCHRE.H"
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
	std::string myCardNames[6] = { "9", "10", "J", "Q", "K", "A" };

public:
	Deck();
	void shuffle();
	void printDeck();
	void buildMainDeck(); // should only be used in main when creating the main deck
	int getDeckSize();

	Card* pop() // function currently for main deck only
	{
		Card* tempHead = head;

		if (head == NULL)
		{
			return NULL;
		}
		else
		{
			head = head->next;
			tempHead->next = NULL;
			deckSize--;
			return tempHead;
		}
	}
	void push(Card* c) // function currently for player only
	{
		if (head == NULL)
		{
			head = c;
			tail = c;
		}
		else
		{
			c->next = head;
			head = c;
		}
		deckSize++;
	}
};

#endif // !"EUCHRE.H"
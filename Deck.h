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
		int cardOwner;
		int cardValue;
		Card * next;
	};

	Card* head;
	Card* tail;

	int deckSize;
	const std::string myCardNames[6] = { "9", "10", "J", "Q", "K", "A" };

public:
	Deck();
	void shuffle();
	void printDeck();
	void buildMainDeck(); // should only be used in main when creating the main deck
	int getDeckSize();
	int searchAndDiscard(char st, std::string nme, Deck* mainDeck);
	int searchAndPlay(char st, std::string nme, Deck* pileDeck);
    int searchForFirstPlayedSuit(char firstPlayedSt, char trumpSt);
	int determineHighestValueCard(char trumpSuit, char firstPlayedSuit);
	int countNumberOfFirstPlayedSuit(char firstPlayedSuit);
	bool doesPlayerHaveJackOfOtherColor(char trumpSuit);

	Card* topOfMainDeck()
	{
		Card* temp = head;
		return temp;
	}

	Card* pop() // function currently for main deck only, not anymore it is actually works for any deck now
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

	void push(Card* c, int owner) // function currently for player only
	{
		if (head == NULL)
		{
			c->cardOwner = owner;
			head = c;
			tail = c;
		}
		else
		{
			c->next = head;
			c->cardOwner = owner;
			head = c;
		}
		deckSize++;
	}

	Card* getHead()
	{
		return head;
	}
};

#endif // !"EUCHRE.H"
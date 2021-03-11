#include "Deck.h"
#include <iostream>
#include <cstddef>

Deck::Deck()
{
	head = NULL;
	tail = NULL;
	Card* current = head;
	string myCardNames[6] = { "9", "10", "J", "Q", "K", "A" };
	deckSize = 0;

	for (int i = 0; i < 24; i++)
	{
		Card* newCard = new Card;
		if (i < 4)
		{
			newCard->name = myCardNames[0];
		}
		else if (i < 8)
		{
			newCard->name = myCardNames[1];
		}
		else if (i < 12)
		{
			newCard->name = myCardNames[2];
		}
		else if (i < 16)
		{
			newCard->name = myCardNames[3];
		}
		else if (i < 20)
		{
			newCard->name = myCardNames[4];
		}
		else if (i < 24)
		{
			newCard->name = myCardNames[5];
		}

		if (i % 4 == 0)
		{
			newCard->suit = 'H';
		}
		else if (i % 4 == 1)
		{
			newCard->suit = 'D';
		}
		else if (i % 4 == 2)
		{
			newCard->suit = 'C';
		}
		else if (i % 4 == 3)
		{
			newCard->suit = 'S';
		}

		if (head == NULL)
		{
			head = newCard;
		}
		else if (deckSize == 1)
		{
			head->next = newCard;
			newCard->next = NULL;
		}
		else
		{
			tail->next = newCard;
			newCard->next = NULL;
			tail = newCard;
		}

		deckSize++;
		tail = newCard;
	}
}

void Deck::printDeck()
{
	Card* cardIter = head;

	if (head == NULL)
	{
		return;
	}

	for (int i = 0; cardIter <= tail; i++)
	{
		cout << cardIter->suit << " " << cardIter->name << endl;
	}
}

void Deck::shuffle()
{
	//
}

void Deck::setSuit(char st)
{
	//
}
char Deck::getSuit()
{
	//
}


void Deck::setName(string nme)
{
	//
}
string Deck::getName()
{
	//
}
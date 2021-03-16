#include "Deck.h"
#include <iostream>
#include <cstddef>
#include <ctime>

Deck::Deck()
{
	head = NULL;
	tail = NULL;
	deckSize = 0;
}

void Deck::printDeck()
{
	Card* cardIter = head;

	if (head == NULL)
	{
		return;
	}

	for (int i = 0; i < deckSize; i++)
	{
		std::cout << i+1 << ": " << cardIter->name << " " << cardIter->suit << std::endl;
		cardIter = cardIter->next;
	}

	cardIter = NULL;
	delete cardIter;
}

void Deck::buildMainDeck()
{
	Card* current = head;

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

void Deck::shuffle()
{
	Card* cardToMove = head;
	Card* cardBefore = head;
	Card* tempHead = head;
	Card* tempTail = head;
	int tempDeckSize = deckSize;
	int nodesToMove = 0;
	int iterator = 1;
	int newDeckSize = 0;

	srand(unsigned int(time(0)));

	if (head == NULL)
	{
		return;
	}

	while (tempDeckSize > 0)
	{
		nodesToMove = rand() % tempDeckSize + 1;

		if (tempDeckSize == 1)
		{
			cardToMove = head;
			tempTail->next = cardToMove;
			cardToMove->next = NULL;
			tempTail = cardToMove;
			head = tempHead;
			tail = tempTail;

			tempHead = NULL;
			tempTail = NULL;
			cardToMove = NULL;
			cardBefore = NULL;
			delete tempHead;
			delete tempTail;
			delete cardToMove;
			delete cardBefore;
			return;
		}
		else if(nodesToMove == 1)
		{
			cardToMove = head;
			head = head->next;
			cardToMove->next = NULL;
			if (tempDeckSize == deckSize)
			{
				tempHead = cardToMove;
				tempTail = cardToMove;
			}
			else
			{
				tempTail->next = cardToMove;
				tempTail = cardToMove;
			}
		}
		else if (nodesToMove == tempDeckSize)
		{
			while (iterator < tempDeckSize)
			{
				if (iterator == tempDeckSize - 1)
				{
					cardBefore = cardToMove;
				}
				cardToMove = cardToMove->next;
				iterator++;
			}

			cardBefore->next = cardToMove->next;
			cardToMove->next = NULL;
			tail = cardBefore;

			if (tempDeckSize == deckSize)
			{
				tempHead = cardToMove;
				tempTail = cardToMove;
			}
			else
			{
				tempTail->next = cardToMove;
				tempTail = cardToMove;
			}
		}
		else
		{
			while (iterator < nodesToMove)
			{
				if (iterator == nodesToMove - 1)
				{
					cardBefore = cardToMove;
				}
				cardToMove = cardToMove->next;
				iterator++;
			}

			cardBefore->next = cardToMove->next;
			cardToMove->next = NULL;

			if (tempDeckSize == deckSize)
			{
				tempHead = cardToMove;
				tempTail = cardToMove;
			}
			else
			{
				tempTail->next = cardToMove;
				tempTail = cardToMove;
			}
		}

		tempDeckSize--;
		newDeckSize++;
		cardToMove = head;
		iterator = 1;
	}
}

int Deck::getDeckSize()
{
	return deckSize;
}
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
		std::cout << "Empty Deck...\n";
		return;
	}

	for (int i = 0; i < deckSize; i++)
	{
		std::cout << i+1 << ": " << cardIter->name << " " << cardIter->suit << " " << cardIter->cardOwner << " " << cardIter->cardValue << std::endl;
		cardIter = cardIter->next;
	}
	std::cout << "Deck Size is " << getDeckSize() << std::endl;
	std::cout << "---------------------------------\n";
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
			newCard->cardValue = 0;
		}
		else if (i < 8)
		{
			newCard->name = myCardNames[1];
			newCard->cardValue = 1;
		}
		else if (i < 12)
		{
			newCard->name = myCardNames[2];
			newCard->cardValue = 2;
		}
		else if (i < 16)
		{
			newCard->name = myCardNames[3];
			newCard->cardValue = 3;
		}
		else if (i < 20)
		{
			newCard->name = myCardNames[4];
			newCard->cardValue = 4;
		}
		else if (i < 24)
		{
			newCard->name = myCardNames[5];
			newCard->cardValue = 5;
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

		newCard->cardOwner = -1;

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

	srand(unsigned(time(0)));

	if (head == NULL)
	{
		std::cerr << "Head is NULL, exiting program...\n";
		exit(0);
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

int Deck::searchAndDiscard(char st, std::string nme, Deck* mainDeck)
{
	Card* cardBefore = head;
	Card* toRemove = head;

	if (head == NULL)
	{
		std::cerr << "Head is NULL, exiting program...\n";
		exit(0);
	}
	else if (head->suit == st && head->name == nme)
	{
		head = head->next;
		toRemove->next = NULL;
		mainDeck->push(toRemove);
		deckSize--;
		return 1;
	}
	else
	{
		while (toRemove != NULL)
		{
			if (toRemove->suit == st && toRemove->name == nme)
			{
				cardBefore->next = toRemove->next;
				toRemove->next = NULL;
				mainDeck->push(toRemove);
				deckSize--;
				return 1;
			}
			else
			{
				if (toRemove->next != NULL)
				{
					if (toRemove->next->suit == st && toRemove->next->name == nme)
					{
						cardBefore = toRemove;
					}
				}
			}
			toRemove = toRemove->next;
		}
		std::cout << "Card not found try again...\n";
		return -1;
	}
}


//Need to search through deck and check if the player has a card that matches the previously played suit, if they don't then
// they should probably look for a Trump card otherwise just throw out a low card off suit <--- honestly this part isn't really necessary for the test unless it is 100% automated
// which it might have to be otherwise it will take me forever to finish
int Deck::searchAndPlay(char st, std::string nme, Deck* pileDeck)
{
	Card* cardBefore = head;
	Card* toRemove = head;

	if (head == NULL)
	{
		std::cerr << "Head is NULL, exiting program...\n";
		exit(0);
	}
	else if (head->suit == st && head->name == nme)
	{
		head = head->next;
		toRemove->next = NULL;
		pileDeck->push(toRemove);
		deckSize--;
		return 1;
	}
	else
	{
		while (toRemove != NULL)
		{
			if (toRemove->suit == st && toRemove->name == nme)
			{
				cardBefore->next = toRemove->next;
				toRemove->next = NULL;
				pileDeck->push(toRemove);
				deckSize--;
				return 1;
			}
			else
			{
				if (toRemove->next != NULL)
				{
					if (toRemove->next->suit == st && toRemove->next->name == nme)
					{
						cardBefore = toRemove;
					}
				}
			}
			toRemove = toRemove->next;
		}
		std::cout << "Card not found try again...\n";
		return -1;
	}
}

// This function needs to check if a player has a Jack of other "Trump" suit For example, Hearts is trump so they needs to check if they have a Jack of diamonds if a heart gets played
// Like say that a 10 of hearts gets played and the user only has a Jack of diamonds and no other heart, then they must play that card... that should finish the project right there.
int Deck::searchForFirstPlayedSuit(char firstSt, char trumpSt) 
{
	Card* searchForFirstSt = head;

	if (head == NULL)
	{
		std::cerr << "Head is NULL, exiting program...\n";
		exit(0);
	}

	while (searchForFirstSt != NULL)
	{
		if (searchForFirstSt->suit == firstSt)
		{
			return 1;
		}
		else if(trumpSt == 'H')
		{
			if(searchForFirstSt->name == "J" && searchForFirstSt->suit == 'D')
			{
				return 2;
			}
		}
		else if(trumpSt == 'D')
		{
			if(searchForFirstSt->name == "J" && searchForFirstSt->suit == 'H')
			{
				return 3;
			}
		}
		else if(trumpSt == 'C')
		{
			if(searchForFirstSt->name == "J" && searchForFirstSt->suit == 'S')
			{
				return 4;
			}
		}
		else if(trumpSt == 'S')
		{
			if(searchForFirstSt->name == "J" && searchForFirstSt->suit == 'C')
			{
				return 5;
			}
		}

		searchForFirstSt = searchForFirstSt->next;
	}
	return -1;
}

int Deck::determineHighestValueCard(char trumpSt, char firstPlayedSt)
{
	Card* highestValueCardFinder = head;
	Card* highestValueTrumpFinder = head;

	int playerWithHighestTrump = -1;
	int playerWithHighestCard = -1;

	int maxTrumpValue = -1;
	int maxValue = -1;

	if (head == NULL)
	{
		std::cerr << "Head is NULL. Exiting program...\n";
		exit(1);
	}
	else
	{
		while (highestValueCardFinder != NULL && highestValueTrumpFinder != NULL)
		{
			if (trumpSt == 'H')
			{
				if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == trumpSt)
				{
					return highestValueTrumpFinder->cardOwner;
				}
				else if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == 'D')
				{
					playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					maxTrumpValue = 6;
				}
				else
				{
					if(highestValueTrumpFinder->cardValue > maxTrumpValue && highestValueTrumpFinder->suit == trumpSt)
					{
						maxTrumpValue = highestValueTrumpFinder->cardValue;
						playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					}
				}
			}
			else if (trumpSt == 'D')
			{
				if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == trumpSt)
				{
					return highestValueTrumpFinder->cardOwner;
				}
				else if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == 'H')
				{
					playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					maxTrumpValue = 6;
				}
				else
				{
					if(highestValueTrumpFinder->cardValue > maxTrumpValue && highestValueTrumpFinder->suit == trumpSt)
					{
						maxTrumpValue = highestValueTrumpFinder->cardValue;
						playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					}
				}
			}
			else if (trumpSt == 'C')
			{
				if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == trumpSt)
				{
					return highestValueTrumpFinder->cardOwner;
				}
				else if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == 'S')
				{
					playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					maxTrumpValue = 6;
				}
				else
				{
					if(highestValueTrumpFinder->cardValue > maxTrumpValue && highestValueTrumpFinder->suit == trumpSt)
					{
						maxTrumpValue = highestValueTrumpFinder->cardValue;
						playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					}
				}
			}
			else if (trumpSt == 'S')
			{
				if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == trumpSt)
				{
					return highestValueTrumpFinder->cardOwner;
				}
				else if (highestValueTrumpFinder->name == "J" && highestValueTrumpFinder->suit == 'C')
				{
					playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					maxTrumpValue = 6;
				}
				else
				{
					if(highestValueTrumpFinder->cardValue > maxTrumpValue && highestValueTrumpFinder->suit == trumpSt)
					{
						maxTrumpValue = highestValueTrumpFinder->cardValue;
						playerWithHighestTrump = highestValueTrumpFinder->cardOwner;
					}
				}
			}

			if (highestValueCardFinder->cardValue > maxValue)
			{
				maxValue = highestValueCardFinder->cardValue;
				playerWithHighestCard = highestValueCardFinder->cardOwner;
			}

			highestValueCardFinder = highestValueCardFinder->next;
			highestValueTrumpFinder = highestValueTrumpFinder->next;
		}
	}
	if(maxTrumpValue > -1)
	{
		return playerWithHighestTrump;
	}
	else
	{
		return playerWithHighestCard;
	}
}
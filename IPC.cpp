#include "IPC.h"
#include <iostream>

IPC::IPC()
{
	currentPlayer = 0;
	dealer = 0;
	trumpSuit = 'X';
}

IPC::IPC(int dlr)
{
	if (dlr < 0)
	{
		dealer = 0;
		currentPlayer = 1;
	}
	else if (dlr >= 3)
	{
		dealer = 3;
		currentPlayer = 0;
	}
	else
	{
		dealer = dlr;
		currentPlayer = dlr + 1;
	}
	trumpSuit = 'X';
}

void IPC::passCardsToPlayers(Player p[4], Deck* mainDeck)
{
	for (int i = 0; i < 20; i++)
	{
		if (p[i%4].getNumOfCardsInHand() < 5)
		{
			p[i%4].getDeck()->push(mainDeck->pop());
			p[i%4].increaseNumOfCardsInHand();
		}
	}
}

void IPC::displayTopCardInMainDeck(Deck* mainDeck)
{
	std::cout << mainDeck->topOfMainDeck()->name << " " << mainDeck->topOfMainDeck()->suit << std::endl;
}

bool IPC::pickUpOrPass(Player p[4], Deck* mainDeck)
{
	/*Setting current player here is eventually going to fail, need to create a 
	setter and change current player at the correct time, this is not the correct time*/
	//currentPlayer = dealer + 1; 
	char playerResponse;

	if (currentPlayer >= 3)
		currentPlayer = 0;

	while (currentPlayer != dealer)
	{
		std::cout << "Player " << currentPlayer << ", should the dealer pick up the card? (y/n)";
		std::cin >> playerResponse;
		while (playerResponse != 'n' && playerResponse != 'y')
		{
			std::cout << "Invalid input, try again";
			std::cin >> playerResponse;
		}
		if (playerResponse == 'n')
		{
			if (currentPlayer >= 3)
				currentPlayer = 0;
			else
				currentPlayer++;
		}
		else if (playerResponse == 'y')
		{
			trumpSuit = mainDeck->topOfMainDeck()->suit;
			p[dealer].getDeck()->push(mainDeck->pop());
			return true;
		}
	}
	std::cout << "Dealer, would you like to pick up the card? (y/n)";
	std::cin >> playerResponse;
	while (playerResponse != 'n' && playerResponse != 'y')
	{
		std::cout << "Invalid input, try again";
		std::cin >> playerResponse;
	}
	if (playerResponse == 'n')
	{
		return false;
	}
	else if (playerResponse == 'y')
	{
		trumpSuit = mainDeck->topOfMainDeck()->suit;
		p[dealer].getDeck()->push(mainDeck->pop());
		return true;
	}
	std::cerr << "SOMETHING WENT WRONG, CLOSING PROGRAM\n";
	exit(0);
}

void IPC::cardToDiscard(Player p[4], Deck* mainDeck)
{
	char suit;
	std::string name;
	int result = -1;

	while (result == -1)
	{
		std::cout << "Which card would you like to discard? (suit, name)";
		std::cin >> suit >> name;
		result = p[dealer].getDeck()->searchAndDiscard(suit, name, mainDeck); //Error in search and discard function.
	}
	
}

char IPC::pickASuit(Deck* mainDeck)
{
	currentPlayer = dealer + 1;
	char playerResponse;
	char topCardSuit = mainDeck->topOfMainDeck()->suit;

	if (currentPlayer > 3)
		currentPlayer = 0;
	else
	{
		while (currentPlayer != dealer)
		{
			std::cout << "Player " << currentPlayer << ", would you like to name trump? (H/D/C/S/X)";
			std::cin >> playerResponse;
			while (playerResponse != 'H' && playerResponse != 'D' && playerResponse != 'C' && playerResponse != 'S' && playerResponse != 'X'
				|| playerResponse == topCardSuit)
			{
				if (playerResponse == topCardSuit)
				{
					std::cout << "Suit cannot be the same as the turned over top card(" << topCardSuit << "): ";
					std::cin >> playerResponse;
				}
				else
				{
					std::cout << "Invalid input, try again: \n";
					std::cin >> playerResponse;
				}
			}
			switch (playerResponse)
			{
			case 'H':
				trumpSuit = 'H';
				return trumpSuit;
				break;
			case 'D':
				trumpSuit = 'D';
				return trumpSuit;
				break;
			case 'C':
				trumpSuit = 'C';
				return trumpSuit;
				break;
			case 'S':
				trumpSuit = 'S';
				return trumpSuit;
				break;
			default:
				trumpSuit = 'X';
				break;
			}
			currentPlayer++;
			if (currentPlayer > 3)
				currentPlayer = 0;
		}
		std::cout << "Dealer, would you like to name trump? (H/D/C/S/X)";
		std::cin >> playerResponse;
		while (playerResponse != 'H' && playerResponse != 'D' && playerResponse != 'C' && playerResponse != 'S' && playerResponse != 'X')
		{
			std::cout << "Invalid input, try again";
			std::cin >> playerResponse;
		}
		switch (playerResponse)
		{
		case 'H':
			trumpSuit = 'H';
			return trumpSuit;
			break;
		case 'D':
			trumpSuit = 'D';
			return trumpSuit;
			break;
		case 'C':
			trumpSuit = 'C';
			return trumpSuit;
			break;
		case 'S':
			trumpSuit = 'S';
			return trumpSuit;
			break;
		default:
			trumpSuit = 'X';
			break;
		}
	}
	return trumpSuit;
}

/*This is going to need a lot of logic, may be best to utilize other functions
it's going to have to take some sort of input, but for now it can be automated 
but it's going to need to be able to get a cards suit and match that suit 
if it has that suit in hand, if it doesn't then they need to play a lower
card*/
void IPC::playersPlaceCardOnPile(Player p[4], Deck* pileDeck)
{
	for (int i = 0; i < 4; i++)
	{
		if(currentPlayer > 3)
			currentPlayer = 0;

		pileDeck->push(p[currentPlayer].getDeck()->pop());
		currentPlayer++;
	}
	currentPlayer = dealer + 1; // current player should be set to the trick winner instead of the player next to the dealer
}

char IPC::getTrump()
{
	return trumpSuit;
}

int IPC::getCurrentPlayer()
{
	return currentPlayer;
}

int IPC::getCurrentDealer()
{
	return dealer;
}

void IPC::setDealer(Player p[4])
{
	p[dealer].setDealerStatus(true);
}

void IPC::setNextDealerAndUpdatePrevious(Player p[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (p[i].getDealerStatus() == true)
		{
			if (i >= 3)
			{
				p[i].setDealerStatus(false);
				p[0].setDealerStatus(true);
				dealer = 0;
				return;
			}
			else
			{
				p[i].setDealerStatus(false);
				p[i+1].setDealerStatus(true);
				dealer = i + 1;
				return;
			}
		}
	}
}
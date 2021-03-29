#include "IPC.h"
#include <iostream>

IPC::IPC()
{
	dealer = 0;
	currentPlayer = 1;
	trumpSuit = 'X';
	trumpCaller = -1;
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
	trickWinner = currentPlayer;
	trumpCaller = -1;
}

void IPC::passCardsToPlayers(Player p[4], Deck* mainDeck)
{
	for (int i = 0; i < 20; i++)
	{
		if (p[i%4].getNumOfCardsInHand() < 5)
		{
			p[i%4].getDeck()->push(mainDeck->pop(), i%4);
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
			trumpCaller = currentPlayer;
			trumpSuit = mainDeck->topOfMainDeck()->suit;
			p[dealer].getDeck()->push(mainDeck->pop(), dealer);
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
		trumpCaller = dealer;
		trumpSuit = mainDeck->topOfMainDeck()->suit;
		p[dealer].getDeck()->push(mainDeck->pop(), dealer);
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
		std::cout << "Which card would you like to discard? (name, suit)";
		std::cin >> name >> suit;
		result = p[dealer].getDeck()->searchAndDiscard(suit, name, mainDeck); //Fixed error
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
				trumpCaller = currentPlayer;
				trumpSuit = 'H';
				return trumpSuit;
				break;
			case 'D':
				trumpCaller = currentPlayer;
				trumpSuit = 'D';
				return trumpSuit;
				break;
			case 'C':
				trumpCaller = currentPlayer;
				trumpSuit = 'C';
				return trumpSuit;
				break;
			case 'S':
				trumpCaller = currentPlayer;
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
			trumpCaller = dealer;
			trumpSuit = 'H';
			return trumpSuit;
			break;
		case 'D':
			trumpCaller = dealer;
			trumpSuit = 'D';
			return trumpSuit;
			break;
		case 'C':
			trumpCaller = dealer;
			trumpSuit = 'C';
			return trumpSuit;
			break;
		case 'S':
			trumpCaller = dealer;
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
	static char firstPlayedSuit = 'X';
	char suit;
	std::string name;
	int result = -1;
	int playerHasCardOnSuit = -1;
	int howManyFirstPlayed = -1;
	bool jackOfOtherColorTrump = false;

	for (int i = 0; i < 4; i++)
	{
		if (currentPlayer > 3)
			currentPlayer = 0;

		if (i == 0)
		{
			while (result == -1)
			{
				std::cout << "Player " << currentPlayer << ", which card would you like to play? (name, suit)";
				std::cin >> name >> suit;
				result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);

				if (result == 1)
				{
					if (trumpSuit == 'H' && name == "J" && suit == 'D')
					{
						firstPlayedSuit = 'H';
					}
					else if (trumpSuit == 'D' && name == "J" && suit == 'H')
					{
						firstPlayedSuit = 'D';
					}
					else if (trumpSuit == 'C' && name == "J" && suit == 'S')
					{
						firstPlayedSuit = 'C';
					}
					else if (trumpSuit == 'S' && name == "J" && suit == 'C')
					{
						firstPlayedSuit = 'S';
					}
					else
					{
						firstPlayedSuit = suit;
					}
				}
			}
			std::cout << "==========Pile Deck==========\n";
			pileDeck->printDeck();
		}
		else
		{
			result = -1;
			howManyFirstPlayed = p[currentPlayer].getDeck()->countNumberOfFirstPlayedSuit(firstPlayedSuit);
			jackOfOtherColorTrump = p[currentPlayer].getDeck()->doesPlayerHaveJackOfOtherColor(trumpSuit);
			playerHasCardOnSuit = p[currentPlayer].getDeck()->searchForFirstPlayedSuit(firstPlayedSuit, trumpSuit);
			while (result == -1)
			{
				// There is one more piece of logic missing here, for example, Hearts is trump, player 1 throws out
				// a 10 of Diamonds, player 2 has a: J of D, A of H, K of C, K of H, and Q of S. They should not be 
				// forced to play the J of D, because it is actually treated as a Heart instead so they should be 
				// able to play any card from their hand
				std::cout << "Player " << currentPlayer << ", which card would you like to play? (name, suit)";
				std::cin >> name >> suit;
				if (name == "J" && suit == 'H' && firstPlayedSuit == 'D')
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
				else if (name == "J" && suit == 'D' && firstPlayedSuit == 'H')
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
				else if (name == "J" && suit == 'C' && firstPlayedSuit == 'S')
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
				else if (name == "J" && suit == 'S' && firstPlayedSuit == 'C')
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
				else if (howManyFirstPlayed == 1 && jackOfOtherColorTrump == true)
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
				else if (playerHasCardOnSuit == 1 && suit != firstPlayedSuit)
				{
					std::cout << "You must play a card that follows suit (" << firstPlayedSuit << ")\n";
					result = -1;
				}
				else if (jackOfOtherColorTrump == true && howManyFirstPlayed == 0)
				{
					std::cout << "You must play the jack that follows color (" << firstPlayedSuit << ")\n";
					result = -1;
				}
				else
				{
					result = p[currentPlayer].getDeck()->searchAndPlay(suit, name, pileDeck);
				}
			}
			std::cout << "==========Pile Deck==========\n";
			pileDeck->printDeck();
		}
		// player needs to choose a matching suit if they have one otherwise throw down a lower level card off suit
		//pileDeck->push(p[currentPlayer].getDeck()->pop()); // instead of pop it needs to be 
		// determine who the current trick winner is by checking card up against the others
		// 
		currentPlayer++;
	}
	trickWinner = pileDeck->determineHighestValueCard(trumpSuit, firstPlayedSuit);
	p[trickWinner].increaseHandsWon();
	currentPlayer = trickWinner; // current player should be set to the trick winner instead of the player next to the dealer
	std::cout << "Trick winner is: " << trickWinner << std::endl;

	/* This code needs to happen when all tricks have been played not when a single
	* trick has happened, this should also not check trump caller yet we need to have a new
	* function that counts the number of hands won by each team then determine how many
	* points they should receive based on that count
	if ((trumpCaller == t1.getPlayerNum1() || trumpCaller == t1.getPlayerNum2()))
	{
		if (trickWinner != t1.getPlayerNum1() || trickWinner != t1.getPlayerNum2())
		{
			t2.increaseScore(2);
		}
	}
	else if ((trumpCaller == t2.getPlayerNum1() || trumpCaller == t2.getPlayerNum2()))
	{
		if (trickWinner != t2.getPlayerNum1() || trickWinner != t2.getPlayerNum2())
		{
			t1.increaseScore(2);
		}
	}*/
}

char IPC::getTrump()
{
	return trumpSuit;
}


void IPC::setCurrentPlayer(int curPlyer)
{
	currentPlayer = curPlyer;
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

void IPC::placeCardsBackInMainDeck(Deck* pileDeck, Deck* mainDeck)
{
	while(pileDeck->getHead() != NULL)
	{
		mainDeck->push(pileDeck->pop());
	}
}
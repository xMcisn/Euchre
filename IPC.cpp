#include "IPC.h"

IPC::IPC()
{
	currentPlayer = 0;
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

/*This is going to need a lot of logic, may be best to utilize other functions
it's going to have to take some sort of input, but for now it can be automated 
but it's going to need to be able to get a cards suit and match that suit 
if it has that suit in hand, if it doesn't then they need to play a lower
card*/
void IPC::playersPlaceCardOnPile(Player p[4], Deck* pileDeck)
{
	for (int i = 0; i < 4; i++)
	{
		pileDeck->push(p[currentPlayer].getDeck()->pop());
		currentPlayer++;
	}
	currentPlayer = 0;
}
#include "Player.h"


Player::Player()
{
	numCardsInHand = 0;
	dealerStatus = false;
}

void Player::viewDeck()
{
	playerDeck.printDeck();
}

Deck* Player::getDeck()
{
	return &playerDeck;
}

int Player::getNumOfCardsInHand()
{
	return numCardsInHand;
}

void Player::increaseNumOfCardsInHand()
{
	numCardsInHand++;
}
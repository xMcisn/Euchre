#include "Player.h"


Player::Player()
{
	numCardsInHand = 0;
	dealerStatus = false;
	playerType = "AI";
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

void Player::setDealerStatus(bool status)
{
	dealerStatus = status;
}

bool Player::getDealerStatus()
{
	return dealerStatus;
}

void Player::setPlayerType(std::string newType)
{
	playerType = newType;
}

std::string Player::getPlayerType()
{
	return playerType;
}
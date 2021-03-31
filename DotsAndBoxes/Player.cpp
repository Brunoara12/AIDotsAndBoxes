#include "Player.h"

void Player::initVariables()
{
	score = 0;
}

void Player::playerScore()
{
	score++;
}

int Player::getScore()
{
	return score;
}

std::string Player::getName()
{
	return name;
}

Player::Player(std::string name, sf::Color color)
{
	this->name = name;
	this->color = color;

	initVariables();
}

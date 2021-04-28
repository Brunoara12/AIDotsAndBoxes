#pragma once

#include "Dot.h"
#include "Line.h"

class Player
{
private:
	std::string name;
	int score;
	void initVariables();

public:
	sf::Color color;
	bool isAI;
	bool thinking;

	void playerScore();
	int getScore();
	std::string getName();

	Player(std::string name, sf::Color color, bool isAi);
};


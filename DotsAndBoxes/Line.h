#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Dot.h"

class Line
{
private:

	sf::RectangleShape* line;
	std::pair<int, int> lineCoord;


	

	// Radius
	float dotR;
	int dotOffset;
	int marginOffset;
	int topOffset;
public:
	// Line that has been confirmed of being connected between two dots
	bool completed;

	Line(int dotOff, int marginOff, int topOff, float dotR, int x, int y);

	sf::RectangleShape* getLine();
	void connectPair(std::pair<Dot*, Dot*> connP);
	void connectLine();
};

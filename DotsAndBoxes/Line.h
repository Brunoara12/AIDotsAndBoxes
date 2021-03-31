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

	// Radius
	float dotR;
	int dotOffset;
	int marginOffset;
	int topOffset;
public:
	Line(int dotOff, int marginOff, int topOff, float dotR);

	sf::RectangleShape* getLine();
	void connectPair(std::pair<Dot*, Dot*> connP);
};

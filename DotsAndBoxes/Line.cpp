
#include "Line.h"


Line::Line(int dotOff, int marginOff, int topOff, float dotR)
{
	this->dotR = dotR;
	dotOffset = dotOff;
	marginOffset = marginOff;
	topOffset = topOff;

	line = new sf::RectangleShape(sf::Vector2f(dotOff, dotR));
	line->setFillColor(sf::Color::Yellow);
	line->setOrigin(0, dotR/2);
}

sf::RectangleShape* Line::getLine()
{
	return line;
}

void Line::connectPair(std::pair<Dot*, Dot*> connP)
{
	int xDif = connP.second->getCoord().first - connP.first->getCoord().first;
	int yDif = connP.second->getCoord().second - connP.first->getCoord().second;
	
	sf::Vector2f startPos = sf::Vector2f(connP.first->getDot()->getPosition().x, connP.first->getDot()->getPosition().y);


	if (xDif == 1) // Right
	{

	}
	else if (xDif == -1) // Left
	{
		line->rotate(180.f);
	}
	else if (yDif == 1) // Down
	{
		line->rotate(90.f);
	}
	else // UP
	{
		line->rotate(-90.f);
	}

	line->setPosition(startPos);
}


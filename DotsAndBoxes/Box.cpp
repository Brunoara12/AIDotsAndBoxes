#include "Box.h"


void Box::initBoxes()
{
	box->setPosition((float)boxCoord.first * dotOffset + marginOffset, (float)boxCoord.second * dotOffset + marginOffset + topOffset);
	bOnce = false;
}

Box::Box(int dotOff, int marginOff, int topOff, int x, int y, std::vector<Dot*> dots)
{
	marginOffset = marginOff;
	dotOffset = dotOff;
	topOffset = topOff;
	boxCoord = std::make_pair(x, y);
	box = new sf::RectangleShape(sf::Vector2f((float)dotOff, (float)dotOff));
	box->setFillColor(sf::Color::Red);
	box->setOrigin((float)dotOff / 2, (float)dotOff / 2);
	for (Dot* d : dots)
		dotsInBox.push_back(d);
	initBoxes();
}

sf::RectangleShape* Box::getBox()
{
	return box;
}

std::pair<int, int> Box::getCoord()
{
	return boxCoord;
}

void Box::setColor(sf::Color c)
{
	box->setFillColor(c);
}

bool Box::checkBoxComplete()
{
	bool rtn = true;
	for (Dot* d : dotsInBox)
	{
		if (!d->checkCompleted())
			rtn = false;
	}
	bool rtn2 = true;
	rtn2 = dotsInBox[0]->checkConnection(dotsInBox[2]);
	rtn2 = dotsInBox[2]->checkConnection(dotsInBox[3]) && rtn2;
	rtn2 = dotsInBox[3]->checkConnection(dotsInBox[1]) && rtn2;
	rtn2 = dotsInBox[1]->checkConnection(dotsInBox[0]) && rtn2;

	confirmed = rtn && rtn2;
	return confirmed;
}

void Box::playerCompleted(Player* p)
{
	setColor(p->color);
	p->playerScore();
}

void Box::update()
{
	if (checkBoxComplete() && !bOnce)
	{
		
		bOnce = true;
	}
}

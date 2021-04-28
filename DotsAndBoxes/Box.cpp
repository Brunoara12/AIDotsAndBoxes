#include "Box.h"



void Box::initBoxes()
{
	box->setPosition((float)boxCoord.first * dotOffset + marginOffset, (float)boxCoord.second * dotOffset + marginOffset + topOffset);
	debugBox->setPosition((float)boxCoord.first * dotOffset + marginOffset, (float)boxCoord.second * dotOffset + marginOffset + topOffset);
	debugBox->setScale(.65f,.65f);
	jointBox->setPosition((float)boxCoord.first * dotOffset + marginOffset, (float)boxCoord.second * dotOffset + marginOffset + topOffset);
	jointBox->setScale(.45f, .45f);
	bOnce = false;
	valence = 4;
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("Roboto-Regular.ttf"))
		std::cout << "LOAD PROBLEM" << std::endl;
	T_Valence = new sf::Text(std::to_string(valence), *font, 20);
	T_Valence->setPosition((float)boxCoord.first * dotOffset + marginOffset, (float)boxCoord.second * dotOffset + marginOffset + topOffset);
	T_Valence->setFillColor(sf::Color::Black);
	T_Valence->setStyle(sf::Text::Bold);

	visited = false;
	chainLen = 0;
	
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
	debugBox = new sf::RectangleShape(sf::Vector2f((float)dotOff, (float)dotOff));
	debugBox->setFillColor(sf::Color::Red);
	debugBox->setOrigin((float)dotOff / 2, (float)dotOff / 2);
	jointBox = new sf::RectangleShape(sf::Vector2f((float)dotOff, (float)dotOff));
	jointBox->setFillColor(sf::Color::Red);
	jointBox->setOrigin((float)dotOff / 2, (float)dotOff / 2);
	this->prev = nullptr;
	this->next = nullptr;
	for (Dot* d : dots)
		dotsInBox.push_back(d);
	initBoxes();
}

sf::RectangleShape* Box::getBox()
{
	return box;
}

sf::RectangleShape* Box::D_getBox()
{
	return debugBox;
}

sf::RectangleShape* Box::J_getBox()
{
	return jointBox;
}

sf::Text* Box::getText()
{
	return T_Valence;
}

void Box::printBoxChain(Box* b)
{
	
	Box* currB = b;
	
	if (chainLen >= 3)
	{
		while (currB->prev != nullptr && currB != nullptr)
		{
			currB = currB->prev;
		}
		do{
			std::cout << currB->boxCoord.first << "," << currB->boxCoord.second << " -- ";
			currB = currB->next;
		} while (currB != nullptr);
		
		std::cout << std::endl;
	}
}
bool operator==(const Box& lhs, const Box& rhs)
{
	/* do actual comparison */
	if (lhs.boxCoord.first == rhs.boxCoord.first && lhs.boxCoord.second == rhs.boxCoord.second)
		return true;
	else
		return false;
}

int Box::numBoxForward(Box* b)
{
	Box* currB = b;
	int num = 0;
	while (currB != nullptr && currB->next != nullptr )
	{
		num++;
		currB = currB->next;
	}
	if (currB == nullptr)
		num = -1;
	return num;
}

int Box::numBoxBackwards(Box* b)
{
	Box* currB = b;
	int num = 0;
	while (currB != nullptr && currB->prev != nullptr)
	{
		num++;
		currB = currB->prev;
	}
	if (currB == nullptr)
		num = -1;
	return num;
}

std::pair<int, int> Box::getCoord()
{
	return boxCoord;
}

void Box::setColor(sf::Color c)
{
	box->setFillColor(c);
}

void Box::D_setColor(sf::Color c)
{
	debugBox->setFillColor(c);
}

void Box::J_setColor(sf::Color c)
{
	jointBox->setFillColor(c);
}



bool Box::checkBoxComplete()
{
	/*bool rtn = true;
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

	confirmed = rtn && rtn2;*/
	confirmed = valence == 0;
	return confirmed;
}

void Box::playerCompleted(Player* p)
{
	setColor(p->color);
	D_setColor(p->color);
	J_setColor(p->color);
	p->playerScore();
}

void Box::update()
{
	T_Valence->setString(std::to_string(valence));

	if (checkBoxComplete() && !bOnce)
	{
		
		bOnce = true;
	}
}



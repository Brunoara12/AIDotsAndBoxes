#include "Dot.h"

void Dot::initVariables()
{
	maxScale = 1.1f;
	minScale = .9f;
	currScale = 1.f;
	deltaScale = 0.005f;
	selected = false;
}

Dot::Dot(float r, int x, int y)
{
	dot = new sf::CircleShape(r);
	dot->setFillColor(sf::Color::White);
	dot->setOrigin(r, r);
	coord = std::make_pair(x, y);

	initVariables();

}

bool Dot::checkPair(Dot* pair)
{

	int xAbs = std::abs(this->coord.first - pair->coord.first);
	int yAbs = std::abs(this->coord.second - pair->coord.second);
	// Xor to see if Pair
	if ((xAbs == 1 ^ yAbs == 1) && !(xAbs > 1 || yAbs > 1))
	{
		return true;
	}
	else // Not a Pair
	{
		return false;
	}
}

bool Dot::checkSame(Dot* d)
{
	if (this->coord.first == d->coord.first && this->coord.second == d->coord.second)
	{
		return true;
	}
	return false;
}

bool Dot::checkCompleted()
{
	return completed;
}

bool Dot::checkConnection(Dot* d)
{
	for (auto p : completedP)
	{
		if (p == d->getCoord())
			return true;
	}
	return false;
}

void Dot::addPair(Dot* d)
{
	setCompleted();
	completedP.push_back(d->getCoord());
}

void Dot::setSelected(bool s)
{
	if (!s)
	{
		dot->setScale(1, 1);
	}
	selected = s;
}

void Dot::setCompleted()
{
	completed = true;
}

void Dot::setColor(sf::Color c)
{
	dot->setFillColor(c);
}

void Dot::update()
{
	if (selected)
	{
		//std::cout << currScale << "\n";
		currScale += deltaScale;
		if (currScale >= maxScale)
		{
			deltaScale *= -1;
		}
		else if (currScale <= minScale)
		{
			deltaScale *= -1;

		}
		dot->setScale(currScale, currScale);
	}

}

sf::CircleShape* Dot::getDot()
{
	return dot;
}

std::pair<int, int> Dot::getCoord()
{
	return coord;
}

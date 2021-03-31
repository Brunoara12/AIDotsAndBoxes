#pragma once


#include "Dot.h"
#include "Player.h"
class Box
{
private:

	sf::RectangleShape* box;
	int dotOffset;
	int marginOffset;
	int topOffset;
	std::pair<int,int> boxCoord;
	bool bOnce;
	void initBoxes();

	

public:
	// Box that has been confirmed to be completed
	bool confirmed;

	std::vector<Dot*> dotsInBox;

	Box(int dotOff,int marginOff, int topOff, int x, int y, std::vector<Dot*> dots);

	sf::RectangleShape* getBox();
	std::pair<int, int> getCoord();
	void setColor(sf::Color c);
	
	bool checkBoxComplete();
	// Sets player variables once Box is completed;
	void playerCompleted(Player* p);

	void update();
};


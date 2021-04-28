#pragma once


#include "Dot.h"
#include "Player.h"
class Box
{
private:

	sf::RectangleShape* box;
	sf::RectangleShape* debugBox;
	sf::RectangleShape* jointBox;

	int dotOffset;
	int marginOffset;
	int topOffset;
	bool bOnce;
	void initBoxes();

	sf::Text* T_Valence;
	

public:
	Box* prev;
	Box* next;
	int chainLen;
	// Box that has been confirmed to be completed
	bool confirmed;
	bool joint;
	int valence;
	bool visited;
	std::vector<Dot*> dotsInBox;
	std::pair<int, int> boxCoord;

	Box(int dotOff,int marginOff, int topOff, int x, int y, std::vector<Dot*> dots);
	
	sf::RectangleShape* getBox();
	sf::RectangleShape* D_getBox();
	sf::RectangleShape* J_getBox();
	sf::Text* getText();

	void printBoxChain(Box* b);
	int numBoxForward(Box* b);
	int numBoxBackwards(Box* b);

	std::pair<int, int> getCoord();
	void setColor(sf::Color c);
	void D_setColor(sf::Color c);
	void J_setColor(sf::Color c);
	
	bool checkBoxComplete();
	// Sets player variables once Box is completed;
	void playerCompleted(Player* p);

	void update();
};


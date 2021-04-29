#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <math.h>

#include "Dot.h"
#include "Line.h"
#include "Box.h"
#include "Player.h"
/*
	Class for Game Engine

*/
enum Turn { Player1, Player2, Start };
enum Control { p1, p2};

struct Play
{
	char d;
	int x;
	int y;
};

class DotsAndBoxes
{

private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoM;

	// DEBUG
	bool valenceT;
	bool longChainV;
	bool ChainV2;
	bool ChainV1;
	bool jointBoxV;
	bool debugUpdateBoard;
	std::vector<sf::Color> arrRandColor;

	void debugBoxColor();
	void jointBoxColor();
	void testScreen1();
	void testScreen2();

	// Game LOGIC Var
	int maxPoints;
	Player* p1;
	Player* p2;
	Turn eState;
	Play LastTurn;
	sf::Text* p1Score;
	sf::Text* p2Score;
	sf::Text* WinText;
	sf::RectangleShape WinBox;
	sf::RectangleShape ScoreTurnBox;
	sf::RectangleShape TurnColorBox;

	// Objects
	std::vector<std::vector<Dot*>> dotBoard;
	std::vector<std::vector<Line*>> H_linesBoard;
	std::vector<std::vector<Line*>> V_linesBoard;
	std::vector<std::vector<Box*>> board;

	std::vector<std::vector<Box*>> ListOfChains;
	std::vector<std::vector<Box*>> ListOfChains2;
	std::vector<std::vector<Box*>> ListOfChains1;
	std::vector<Box*> ListofJoints;

	// Pair to connect
	std::pair<Dot *, Dot *> connectP;


	// Variables
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// Radius
	float dotR;
	// Number of dots on board;
	int dotsX;
	int dotsY;
	// Window Size based on dots
	int screenW;
	int screenH;
	int dotOffset;
	int marginOffset;
	int topOffset;
	
	

	void initVariables(int xDots, int yDots);
	void initGameVar();
	void initUI();
	void initWindow();
	void initDots();
	void initLines();
	void initBoxes();

	
	// AI Algorithms
	int resultValenceFromLine(Play p);
	bool placeRandLineDown();
	bool checkIfVFull();
	bool checkIfHFull();
	bool checkBoxesComplete();
	bool checkIfJoint(Box* b);
	Control checkWhoHasControl();
	bool doubleDealChain(Play p);
	void closeBox(Box* b);
	void doubleCrossHelp(Box* b, bool forward);
	void clearChain();
	void checkBoardForChains();
	void checkBoardForChain2();
	void checkBoardForChain1();
	int chainHelper(int x, int y, std::vector<Box*> &chain);
	int checkBoxForValence(int x);
	bool checkEndgame();
	bool checkForFree();
	void halfHeartedHandout();
	void hardHeartedHandout();
	void openUp();
	bool openChain(Play LastTurn);

public:
	DotsAndBoxes(int xDots, int yDots);
	virtual ~DotsAndBoxes();

	const bool running() const;

	void setPlayerTurn(Turn t);
	Player* getPlayerTurn();

	void updateMousePositions();
	void printMousePos();

	bool updateVLine(int x, int y);
	bool updateHLine(int x, int y);

	void pollEvents();

	void updateUI();
	void updateBoxes();
	void updateLines();
	void updateDots();
	void update();

	void renderUI();
	void renderBoxes();
	void renderLines();
	void renderDots();
	void render();
};


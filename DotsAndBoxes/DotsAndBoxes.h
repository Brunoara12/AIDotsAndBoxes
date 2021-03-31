#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Dot.h"
#include "Line.h"
#include "Box.h"
#include "Player.h"
/*
	Class for Game Engine

*/
enum Turn { Player1, Player2, Start };


class DotsAndBoxes
{

private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoM;


	// Game LOGIC Var
	int maxPoints;
	Player* p1;
	Player* p2;
	Turn eState;
	sf::Text* p1Score;
	sf::Text* p2Score;
	sf::Text* WinText;
	sf::RectangleShape WinBox;
	sf::RectangleShape ScoreTurnBox;
	sf::RectangleShape TurnColorBox;

	// Objects
	std::vector<std::vector<Dot*>> dotBoard;
	std::vector<Line*> linesBoard;
	std::vector<std::vector<Box*>> board;

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
	

	void initVariables();
	void initGameVar();
	void initUI();
	void initWindow();
	void initDots();
	void initBoxes();

	

public:
	DotsAndBoxes();
	virtual ~DotsAndBoxes();

	const bool running() const;

	void setPlayerTurn(Turn t);
	Player* getPlayerTurn();

	void updateMousePositions();
	void printMousePos();

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


#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class Dot
{
	private:
		sf::CircleShape* dot;
		std::pair<int, int> coord;
		std::vector<std::pair<int, int>> completedP;
		// Dot that is currently being Selected for visual purposes
		bool selected;
		// Dot that has been confirmed of connecting to a line
		bool completed;

		void initVariables();

public:
	
	Dot(float r, int x, int y);

	// Check to see if Pair is adjacent to each other
	bool checkPair(Dot* pair);
	// Check to see if same Dot
	bool checkSame(Dot* d);

	//Check to see if Dot is Completed
	bool checkCompleted();

	bool checkConnection(Dot* d);
	void addPair(Dot* d);

	// LOGIC Var
	float maxScale;
	float minScale;
	float currScale;
	float deltaScale;

	// True if First selected
	void setSelected(bool s);
	void setCompleted();
	void setColor(sf::Color c);

	void update();

	sf::CircleShape* getDot();
	std::pair<int, int> getCoord();
};


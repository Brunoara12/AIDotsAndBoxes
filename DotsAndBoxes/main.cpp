#include "DotsAndBoxes.h"

int main()
{
	

	

	int xDots = 0;
	int yDots = 0;
	while (xDots < 2 || xDots > 25)
	{
		std::cout << "Please enter a number between 2 - 25 for number of Dots Wide: \n";
		std::cin >> xDots;
	}
	while (yDots < 2 || yDots > 13)
	{
		std::cout << "Please enter a number between 2 - 13 for number of Dots High: \n";
		std::cin >> yDots;
	}
	// Init Dots and Boxes
	DotsAndBoxes game(xDots, yDots);
	srand(static_cast<unsigned>(time(0)));

	// Game Loop
	while (game.running())
	{
		
		// Update
		game.update();

		// Render
		game.render();
		
	}

	return 0;
}
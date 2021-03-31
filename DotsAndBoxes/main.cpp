#include "DotsAndBoxes.h"

int main()
{
	

	// Init Dots and Boxes
	DotsAndBoxes game;

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
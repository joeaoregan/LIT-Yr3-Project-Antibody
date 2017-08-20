#include "Game.h"

//#define GAME_LOOPS 20		// Number of times to loop the game

//int main()
int main(int argc, char *argv[])
{
	Game game;				// Create a game object

	//game.init();			// ERROR -- Window won't close

	game.update();

	game.close();			// Free resources and close SDL
	/*
	//srand(static_cast<unsigned int>(time(0)));	// Seed random number

	//int loopNum = 0;
	//int finished = 2;

	//game.init();			// Call the Game Class init function

							// game loop
							//while (loopNum < GAME_LOOPS) // loop until 20
	while (finished >= 2 && finished < 5) // CA2 - Loop until game over condition has been triggered
	{
		loopNum++;			// Start loop at 1

		game.draw();		// Call draw() for each object
		game.update();		// Move Game Objects
							/*	2016-11-30:
							If the player occupies the coordinates of a static game object
							He can interact with it. This is similar to the battle() function
							but instead of trying to kill a Game Object, the player decides
							whether to add it to his inventory
							*/
	/*
		game.interact();
		game.battle();		// If 2 objects occups same coords - fight
							//game.addToInventory();
		game.info();		// Call info() for each object
		game.clean();		// Remove Game Objects from list with 0 health
		finished = game.GameOver();
		if (finished < 2 || finished > 5) break;	// Exit loop if game is won or lost
	}

	game.info();			// Print Game Object details one more time
	*/

	system("pause");

	return 0;
}

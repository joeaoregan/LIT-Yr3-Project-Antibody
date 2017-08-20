#include "Game.h"

//#define GAME_LOOPS 20		// Number of times to loop the game

int main()
{
	Game game;				// Create a game object

	//game.init();			// ERROR -- Window won't close

	game.update();

	game.close();			// Free resources and close SDL
	
	return 0;
}
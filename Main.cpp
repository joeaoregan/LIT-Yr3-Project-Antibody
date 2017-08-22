#include "Game.h"
//#include "MainMenu.h"

//#define GAME_LOOPS 20		// Number of times to loop the game

int main() {
	srand(static_cast<unsigned int>(time(0)));	// Seed the random number

	//MainMenu menu;	//create menu object

	//menu.update();

	Game game;				// Create a game object

	game.update();

	game.close();			// Free resources and close SDL

	system("pause");

	return 0;
}
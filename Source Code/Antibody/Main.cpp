/*
	MAIN:

	This is the main entry point for the game
*/

#include "Game.h"
//#include "MainMenu.h"

//#define GAME_LOOPS 20		// Number of times to loop the game

int main() {
	srand(static_cast<unsigned int>(time(0)));	// Seed the random number


	//Game::Instance()->init();
	//MainMenu menu;	//create menu object

	//menu.update();

	//Game game;				// Create a game object

	//game.update();
	//game.close();			// Free resources and close SDL

	Game::Instance()->update();	// 2017-02-27 Game singleton
	Game::Instance()->close();

	system("pause");

	return 0;
}
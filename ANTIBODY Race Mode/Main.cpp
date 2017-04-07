/*
	MAIN:

	Main entry point for the game
*/

#include "Game.h"

//#define GAME_LOOPS 20		// Number of times to loop the game

Game game1;

int main() {
	//srand(static_cast<unsigned int>(time(0)));	// Seed the random number
	
	game1.update();	// 2017-02-27 Game singleton
	game1.close();

	system("pause");

	return 0;
}
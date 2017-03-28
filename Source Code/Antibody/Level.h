/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Level.cpp
	- Description:			Class for levels of the game
	- Information:			The level class was to be used to separate the Level functionality from the Game class

	- Log:

		2017/03/21			Divide the game into levels
		2017/03/22			Moved over all game functionality from Game class, but other classes are relying on it
							for spawning objects etc. so did not make the final version
----------------------------------------------------------------------------------------------------------------------*/

#ifndef LEVEL_H
#define LEVEL_H

#include "Game.h"

class Level {
public:
	// Constructor - Initializes the variables
	Level(int level = LEVEL_1);

	// Destructor
	~Level() {};

	void loadMedia();
	void update();
	void render();
	void clearMedia();
};

#endif
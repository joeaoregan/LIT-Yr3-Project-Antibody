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
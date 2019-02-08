#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>

class Game {
public:

	bool init();					// Starts up SDL and creates window

	bool loadMedia();				// Loads media

	void render();					// Draw media to screen
	
	void update();					// Update the game

	void close();					// Frees media and shuts down SDL

	void scrollBackground();		// Handle background image scrolling

private:

};

#endif
#ifndef SHIP_H
#define SHIP_H
#include "LTexture.h"

// The ship that will move around on the screen

/* 
2017-01-04:
Fixed dimensions of ship
*/

class Ship {
public:
	// The dimensions of the ship (dimensions of sprite image)
	static const int SHIP_WIDTH = 100;
	static const int SHIP_HEIGHT = 47;
			
	static const int SHIP_VEL = 5;	// Maximum axis velocity of the ship
	
	Ship();							// Initializes the variables
	
	void handleEvent(SDL_Event& e);	// Takes key presses and adjusts the ship's velocity	
	void move();					// Moves the ship	
	void render();					// Shows the ship on the screen

private:	
	int mPosX, mPosY;				// The X and Y offsets of the ship	
	int mVelX, mVelY;				// The velocity of the ship
};

#endif
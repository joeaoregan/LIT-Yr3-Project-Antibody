#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"

// The Player ship that will move around on the screen

/*
2017-01-04:
Fixed dimensions of ship
*/
/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/

class Ship : public GameObject {
public:
	Ship();							// Initializes the variables

	void handleEvent(SDL_Event& e);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();		// Moves the ship
	void movement(SDL_Rect& square, Circle& circle);	// Movement with collisions
	void render();					// Shows the ship on the screen
};

#endif

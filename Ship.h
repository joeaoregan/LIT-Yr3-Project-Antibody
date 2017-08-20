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
			
	static const int SHIP_VEL = 10;	// Maximum axis velocity of the ship
	
	Ship();							// Initializes the variables
	
	void handleEvent(SDL_Event& e);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();		// Moves the ship	
	void render();					// Shows the ship on the screen

protected:
	// The dimensions of the ship (dimensions of sprite image)
	static const int SHIP_WIDTH = 100;
	static const int SHIP_HEIGHT = 47;
};

#endif
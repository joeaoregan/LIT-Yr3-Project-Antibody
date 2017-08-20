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

	SDL_Rect mCollider;				// Players Hit Box

	//void handleEvent(SDL_Event& e);
	void handleEvent(SDL_Event& e, int player);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();		// Moves the ship	
	void render();					// Shows the ship on the screen
	void gameControllerDPad(SDL_Event& e);
	void gameControllerButton(SDL_Event& e);
	void resetPreviousDirection();

	// Speed boost
	bool getSpeedBoost();
	unsigned int getBoostStartTime();
	void setSpeedBoost(bool boost);

	// Movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int moveDiagonal();

	SDL_Rect getCollider();
	void setShipColX(int x);					// get the ships X position
	void setShipColY(int y);					// get the ships Y position

private:
	bool mSpeedBoost;
	unsigned int mBoostStartTime;
};

#endif

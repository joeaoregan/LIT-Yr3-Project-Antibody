/*
*-------------------------------------------------
*		Laser.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/

/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/
#ifndef LASER_H
#define LASER_H
#include "Weapon.h"

class Laser : public Weapon {
public:
	Laser();							// Initializes the variables
	~Laser();							// Destructor
		
	virtual void movement();			// Moves the laser	
	void render();						// Shows the laser on the screen
	virtual void spawn(int x, int y);	// Spawn the object at the dimensions provided
	virtual void spawn(int x, int y, SDL_Rect collider);
	SDL_Rect getLaserCollider();

private:
	SDL_Rect mLaserCollider;
};

#endif
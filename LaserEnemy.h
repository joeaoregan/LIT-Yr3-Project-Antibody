
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class LaserEnemy : public Weapon {
public:
	LaserEnemy();						// Initializes the variables
	~LaserEnemy();						// Destructor

	virtual void movement();			// Moves the laser	
	void render();						// Shows the laser on the screen
	virtual void spawn(int x, int y, SDL_Rect collider);	// Spawn the object at the dimensions provided
	SDL_Rect getELaserCollider();

private:
	SDL_Rect mELaserCollider;
};

#endif#pragma once

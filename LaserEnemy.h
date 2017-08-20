
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class LaserEnemy : public Weapon {
public:
	LaserEnemy();						// Initializes the variables
	~LaserEnemy();

	// The dimensions of the laser (dimensions of sprite image)
	static const int LASER_E_WIDTH = 50;
	static const int LASER_E_HEIGHT = 5;

	static const int LASER_E_VEL = 15;	// Maximum axis velocity of the laser

	virtual void movement();			// Moves the laser	
	void render();						// Shows the laser on the screen
	virtual void spawn(int x, int y);
};

#endif#pragma once

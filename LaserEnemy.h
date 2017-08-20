
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
	virtual void spawn(int x, int y);	// Spawn the laser at the coords provided
};

#endif

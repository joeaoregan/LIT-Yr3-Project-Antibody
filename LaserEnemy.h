
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class LaserEnemy : public Weapon {
public:
	LaserEnemy(int type = 0);						// Initializes the variables
	~LaserEnemy();									// Destructor

	virtual void movement();						// Moves the laser
};

#endif

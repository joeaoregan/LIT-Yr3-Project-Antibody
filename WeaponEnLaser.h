
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class WeaponEnLaser : public Weapon {
public:
	WeaponEnLaser(int type = 0);						// Initializes the variables
	~WeaponEnLaser();									// Destructor

	virtual void movement();						// Moves the laser
};

#endif

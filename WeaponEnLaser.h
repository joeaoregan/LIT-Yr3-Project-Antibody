
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

//enum EnemyLaserTypes { ENEMY_SHIP_LASER, VIRUS_FIREBALL, BLUE_VIRUS_BULLET };

class WeaponEnLaser : public Weapon {
public:
	WeaponEnLaser(int type = ENEMY_SHIP_LASER, int rotateCenter = 0);	// Initializes the variables
	~WeaponEnLaser();			// Destructor

	virtual void move();		// Moves the laser

	int centerX, centerY;		// center for rotation
};

#endif

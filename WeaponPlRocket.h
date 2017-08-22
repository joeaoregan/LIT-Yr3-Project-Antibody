#ifndef ROCKET_H
#define ROCKET_H

#include "Weapon.h"

class WeaponPlRocket : public Weapon {
public:
	WeaponPlRocket();												// Initializes the variables
	~WeaponPlRocket();												// Destructor

	virtual void movement();								// Moves the laser

	virtual void spawn(int x, int y, SDL_Rect* collider, int player = 1, int type = 9);	// Spawn the object at the dimensions provided
};

#endif

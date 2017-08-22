#ifndef ROCKET_H
#define ROCKET_H

#include "Weapon.h"

class WeaponPlRocket : public Weapon {
public:
	WeaponPlRocket();						// Initializes the variables
	~WeaponPlRocket();						// Destructor

	virtual void movement();				// Moves the Rocket	
};

#endif
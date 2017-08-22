/*
2017-01-17:
Add Circular Saw weapon class
*/
#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class WeaponPlSaw : public Weapon {
public:
	WeaponPlSaw(int player);									// Initializes the variables
	~WeaponPlSaw();									// Deconstructor

	virtual void movement(int x, int y);	// Moves the Saw
};

#endif
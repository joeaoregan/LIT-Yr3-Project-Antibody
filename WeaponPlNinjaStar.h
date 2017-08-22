/*
2017-01-09:
Add Ninja Star weapon class
*/
#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class WeaponPlNinjaStar : public Weapon {
public:
	WeaponPlNinjaStar(int player);							// Initializes the variables
	~WeaponPlNinjaStar();
};

#endif
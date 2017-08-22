/*
	2017/02/21 Added check so only Ninja Stars and Saws split viruses
	2017/01/30 Added rotation angle to constructors for Textures that rotate
	2017/01/17 Added player decision to spawnNinjaStar() function - determines player to spawn for and their coords
	2017/01/09 Add Ninja Star weapon class
*/
#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class WeaponPlNinjaStar : public Weapon {
public:
	WeaponPlNinjaStar(int player);							// Initializes the variables
	~WeaponPlNinjaStar();

	virtual void move();
};

#endif
/*
2017-01-09:
Add Ninja Star weapon class
*/
#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class NinjaStar : public Weapon {
public:
	NinjaStar();					// Initializes the variables
	~NinjaStar();					// Deconstructor
};

#endif
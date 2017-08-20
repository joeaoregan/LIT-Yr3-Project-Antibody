/*
2017-01-09:
Add Ninja Star weapon class
*/
#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class NinjaStar : public Weapon {
public:
	NinjaStar();							// Initializes the variables
	~NinjaStar();

	virtual void movement();				// Moves the Ninja Star	
	void render();							// Shows the Ninja Star on the screen
	virtual void spawn(int x, int y);		// Spawn the Ninja Star at the coords provided
};

#endif
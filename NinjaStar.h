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
	void render(int player);				// Shows the Ninja Star on the screen - 2017/01/17 Add player decision
	virtual void spawn(int x, int y);
};

#endif
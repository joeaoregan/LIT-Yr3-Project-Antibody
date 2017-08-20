/*
2017-01-17:
Add Circular Saw weapon class
*/
#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class Saw : public Weapon {
public:
	Saw();							// Initializes the variables
	~Saw();

	virtual void movement(int x, int y);				// Moves the Saw	

	void render();
	virtual void spawn(int x, int y);
};

#endif
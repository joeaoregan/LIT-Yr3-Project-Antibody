/*
2017-01-17:
Add Circular Saw weapon class
*/
#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class Saw : public Weapon {
public:
	Saw(int player);									// Initializes the variables
	~Saw();									// Deconstructor

	virtual void movement(int x, int y);	// Moves the Saw	

	//virtual void spawn(int x, int y);		// Spawn the saw
};

#endif
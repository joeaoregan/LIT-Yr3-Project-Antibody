#ifndef ROCKET_H
#define ROCKET_H
#include "Weapon.h"

class Rocket : public Weapon {
public:
	Rocket();												// Initializes the variables
	~Rocket();												// Destructor

	virtual void movement();								// Moves the laser	

	virtual void spawn(int x, int y, SDL_Rect collider, int player = 1, int type = 9);	// Spawn the object at the dimensions provided
};

#endif
#ifndef ROCKET_H
#define ROCKET_H
#include "Weapon.h"

class Rocket : public Weapon {
public:
	Rocket();												// Initializes the variables
	~Rocket();												// Destructor

	virtual void movement();								// Moves the laser	
															//void render(int player);								// Shows the laser on the screen - 2017/01/17 Add player decision
	virtual void spawn(int x, int y, SDL_Rect collider, int player = 1, int type = 9);	// Spawn the object at the dimensions provided
};

#endif
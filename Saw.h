/*
2017-01-17:
Add Circular Saw weapon class
*/
#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class Saw : public Weapon {
public:
	Saw();									// Initializes the variables
	~Saw();									// Deconstructor

	virtual void movement(int x, int y);	// Moves the Saw	

	//void render(LTexture &texture, SDL_Renderer *rend, int degrees);							// Render the saw //2017/01/22 added texture and renderer
	//void render();
	virtual void spawn(int x, int y);		// Spawn the saw
};

#endif
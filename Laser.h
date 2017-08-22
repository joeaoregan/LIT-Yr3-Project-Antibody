/*
*-------------------------------------------------
*		Laser.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/

/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/
#ifndef LASER_H
#define LASER_H
#include "Weapon.h"

class Laser : public Weapon {
public:
	Laser();												// Initializes the variables
	Laser(int type);										// Initializes the variables
	~Laser();												// Destructor
	
	//void spawn(int x, int y, int velocity, int player);
	virtual void movement();								// Moves the laser	
	//void render(int player);								// Shows the laser on the screen - 2017/01/17 Add player decision
	void render(int player, LTexture &orange, LTexture &green, SDL_Renderer *rend);	// 2017/01/22 added textures to renderer
	virtual void spawn(int x, int y, SDL_Rect collider);	// Spawn the object at the dimensions provided
	void spawn(int x, int y, int velocity, int player, int type = 0);
};

#endif
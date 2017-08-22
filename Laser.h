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
	Laser(int angle = 0, int grade = 0);
	~Laser();												// Destructor
	
	virtual void movement();								// Moves the laser	

	void render(int player, LTexture &orange, LTexture &green, SDL_Renderer *rend);	// 2017/01/22 added textures to renderer

	void spawn(int x, int y, int velocity, int player, int type = 0);
};

#endif
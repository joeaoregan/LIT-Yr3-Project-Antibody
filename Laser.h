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
	Laser();							// Initializes the variables
	~Laser();

	// The dimensions of the laser (dimensions of sprite image)
	static const int LASER_WIDTH = 50;
	static const int LASER_HEIGHT = 5;

	static const int LASER_VEL = 15;	// Maximum axis velocity of the laser
		
	virtual void movement();			// Moves the laser	
	void render();						// Shows the laser on the screen
	virtual void spawn(int x, int y);
};

#endif
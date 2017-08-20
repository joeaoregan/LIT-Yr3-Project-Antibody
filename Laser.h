/*
*-------------------------------------------------
*		Laser.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/
#pragma once
#ifndef LASER_H
#define LASER_H
#include "LTexture.h"
#include <iostream>

class Laser {
public:
	// The dimensions of the laser (dimensions of sprite image)
	static const int LASER_WIDTH = 70;
	static const int LASER_HEIGHT = 5;

	static const int LASER_VEL = 20;	// Maximum axis velocity of the laser

	Laser();							// Initializes the variables
	
	void spawn(int x, int y, int velocity);
	void move();					// Moves the laser	
	void render();					// Shows the laser on the screen
	
	~Laser();
private:
	int mPosX, mPosY;				// The X and Y offsets of the laser	
	int mVelX, mVelY;				// The velocity of the laser
	int mAlive;

};

#endif
/*
	2017/03/04 Moved smaller class files functionality into their headers
	2017/02/19 Added separate explosions for blood cells to look more like a blood splatter
	2017/02/18 Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen
	2017/02/15 Added Explosions to list of game objects
	2017/02/09 Made Explosion animations independent, so they don't all render same frame at the same time
	2017/01/25 Added spawnExplosion() function for creating explosions when lasers collide with Enemy Ships and Virus
				Added explosion handling class Explosion.h
	2017/01/20 Added spawnExplosion() functions for creating explosions when objects collide
*/
/*
	EXPLOSION:

	This class handles explosions for collisons between objects
	Different explosions are rendered for blood cells, the different types of objects, and player and enemy ship collisions
	Explosions are independently animated, so they don't show the same frame for every explosion appearing on screen.
*/
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"

class Explosion : public GameObject {
public:
	// Constructor - Initializes the variables
	Explosion(int x, int y, int subType = 0) {
		setWidth(96);
		setHeight(96);

		setDamage(5);

		setX(x);
		setY(y);

		setSubType(subType);

		setAlive(true);
	};							

	// Destructor
	~Explosion() {};

	// Inherited Movement function (Enemy ships only move right to left)
	virtual void move() {};
};

#endif
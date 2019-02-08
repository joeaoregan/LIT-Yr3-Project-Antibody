/*
	2017/03/04 Moved smaller class files functionality into their headers
	2017/01/10 Added spawn functions to spawn enemies and obstacles at random coords & distances apart
					Create parent class for Enemies
*/
/*
	ENEMY:

	Base class for enemy objects, inherits from Game Object class
*/

#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
public:
	// Constructor
	Enemy() {};

	// Destructor
	~Enemy() {};
};

#endif
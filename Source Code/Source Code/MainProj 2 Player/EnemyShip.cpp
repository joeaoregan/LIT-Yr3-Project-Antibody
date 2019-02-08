/*
	2017/02/09 Made Enemy Ship animations independent, so they don't all render same frame at the same time
	2017/01/20 Added more random shooting from enemy ships
				Fixed problem where not all ships are firing
	2017/01/10 Added ability to spawn lasers in Game.cpp
				Added spawn functions to spawn enemies and obstacles at random coords & distances apart
	2017/01/09 Added spawnEnemyShip() function to create enemy ships at random times and random y coord
	2017/01/06 Enemy movement from right to left towards player adapted from laser spawning
*/
/* 
	ENEMY SHIP:

	The enemy ship moves right to left across the screen firing intermittently
*/

#include "EnemyShip.h"

EnemyShip::EnemyShip() {					// Constructor
	setSubType(ENEMY_SHIP);
	setScore(25);							// Value for killing object
	setDamage(15);

	// Initialise Dimensions
	setWidth(100);
	setHeight(47);

	// Initialize the offsets
	setX(0);
	setY(0);

	// Initialise the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(20);

	// Initialise Collider
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setFrames(0);

	setType(ENEMY_OBJECT);

	setName("Enemy Ship");
}

EnemyShip::~EnemyShip() {					// Destructor
	std::cout << "Enemy Ship destroyed" << std::endl;
}
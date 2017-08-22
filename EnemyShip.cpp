#include "Game.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip() {					// Constructor
	setScore(25);							// Value for killing object

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
}

EnemyShip::~EnemyShip() {					// Destructor
	std::cout << "Enemy Ship destroyed" << std::endl;
}
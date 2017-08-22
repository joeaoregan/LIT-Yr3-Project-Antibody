
/*
* LaserEnemy.cpp is where all the implementations of the function definitions in LaserEnemy.h reside.
*/
/*
2017-01-10:
Added enemy laser projectile, velocity is a minus value as it is travelling right to left
*/
#include "LaserEnemy.h"
#include "EnemyShip.h"

// LaserEnemy Constructor
LaserEnemy::LaserEnemy(int type) {
	//std::cout << "Enemy Laser constuctor called.\n";
	setWidth(50);
	setHeight(5);
	setVelocity(-15);
	setVelX(-15);
	//setVelY(0);
	setType(type);
	setAlive(true);
	setName("Enemy Laser");

	if (getType() == 0) {
		setColliderWidth(getWidth());
		setColliderHeight(getHeight());
	}
	else{								// Type 1 = orange fireball
		setColliderWidth(25);
		setColliderHeight(25);
	}
	setScore(5);						// 2017/01/20 Points to deduct from player after collision with this object
}

// LaserEnemy Destructor
LaserEnemy::~LaserEnemy() {
	std::cout << "Enemy Laser destructor called.\n";
}

void LaserEnemy::movement() {
	GameObject::movement();
	setY(getY() + getVelY());

	// destroy laser beam once it is offscreen
	if (getY() < 40) setAlive(false);			// Once it reaches the pink border
	else if (getY() > (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	else setAlive(true);
}
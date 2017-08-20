
/*
* LaserEnemy.cpp is where all the implementations of the function definitions in LaserEnemy.h reside.
*/
/*
2017-01-10:
Added enemy laser projectile
*/
#include "LaserEnemy.h"
#include "EnemyShip.h"

// LaserEnemy Constructor
LaserEnemy::LaserEnemy()
{
	//std::cout << "Enemy Laser constuctor called.\n";
}

// LaserEnemy Destructor
LaserEnemy::~LaserEnemy()
{
	std::cout << "Enemy Laser destructor called.\n";
}

void LaserEnemy::movement() {
	GameObject::movement();

	// destroy laser beam once it is offscreen
	if (getX() < -LASER_E_WIDTH) setAlive(false);
	else setAlive(true);
}

void LaserEnemy::spawn(int x, int y) {
	setX(x);
	setY(y+30);
	setVelX(-LASER_E_VEL);
	setVelY(0);
}
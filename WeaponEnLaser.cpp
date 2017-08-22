
/*
* LaserEnemy.cpp is where all the implementations of the function definitions in LaserEnemy.h reside.
*/
/*
2017-01-10:
Added enemy laser projectile, velocity is a minus value as it is travelling right to left
*/
#include "WeaponEnLaser.h"
#include "EnemyShip.h"
#include <math.h>

// LaserEnemy Constructor
WeaponEnLaser::WeaponEnLaser(int type, int rotateCenter) {
	//std::cout << "Enemy Laser constuctor called.\n";
	setWidth(50);
	setHeight(5);
	setVelocity(-15);
	setVelX(-15);
	//setVelY(0);
	setType(type);
	setAlive(true);

	// Set the name
	if (type == ENEMY_SHIP_LASER)
		setName("Enemy Laser");
	else if (type == VIRUS_FIREBALL)
		setName("Virus Fireball");
	else if (type == BLUE_VIRUS_BULLET)
		setName("Blue Virus Bullet");

	if (getType() == 0) {
		setColliderWidth(getWidth());
		setColliderHeight(getHeight());
	}
	else{								// Type 1 = orange fireball
		setColliderWidth(25);
		setColliderHeight(25);
	}
	setScore(5);						// 2017/01/20 Points to deduct from player after collision with this object

	rotateCounter = 0;
	satelliteObjectAlive = false;
}

// LaserEnemy Destructor
WeaponEnLaser::~WeaponEnLaser() {
	std::cout << "Enemy Laser destructor called.\n";
}

void WeaponEnLaser::movement() {
	/*
	if (getType() == BLUE_VIRUS_BULLET) {
		//centerX = getX();
		//centerY = getY();

		rotateCounter %= 360;

		setX(100 * cos(rotateCounter * 3.1415926f / 180.0f) + centerX);
		setY(100 * sin(rotateCounter * 3.1415926f / 180.0f) + centerY);

		rotateCounter += 5;
	}
	else {
	*/
		GameObject::movement();
		setY(getY() + getVelY());
	//}
	// destroy laser beam once it is offscreen
	//if (getY() < 40) setAlive(false);			// Once it reaches the pink border
	//else if (getY() > (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	//else setAlive(true);
}
/*
void WeaponEnLaser::movement(int centerX, int centerY, float timer) {	
	if (centerX < SCREEN_WIDTH) {
		rotateCounter %= 360;
		if (timer != 0.5) {
			setX(70 * cos(rotateCounter * 3.1415926f / 180.0f) + centerX);		// rotate the bullet object
			setY(70 * sin(rotateCounter * 3.1415926f / 180.0f) + centerY);

			rotateCounter += 3;
		}
		else
			GameObject::movement();					// Fire the satellite bullet object
	}
}
*/

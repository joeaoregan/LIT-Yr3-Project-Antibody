/*
	2017/02/18 Added enemy laser to game objects list
				Set types and sub-types for objects on game objects list
	2017-01-10 Added enemy laser projectile, velocity is a minus value as it is travelling right to left
*/
/*
	ENEMY LASER: 

	This class handles enemy weapon objects, first starting with Enemy Ship lasers, then adding Orange Virus projectiles,
	and then adding the satellite projectile for the Blue Virus.

	WeaponEnLaser (LaserEnemy.cpp) is where all the implementations of the function definitions in LaserEnemy.h reside.
*/

#include "WeaponEnLaser.h"
#include <math.h>

// LaserEnemy Constructor
WeaponEnLaser::WeaponEnLaser(int subType, int rotateCenter) {
	//std::cout << "Enemy Laser constuctor called.\n";
	setVelocity(-15);
	setVelX(-15);
	//setVelY(0);
	setAlive(true);

	setType(ENEMY_WEAPON);	// Type of object (enemy weapon)
	setSubType(subType);	// Subtype of weapon

	// Set the name
	if (subType == ENEMY_SHIP_LASER) {
		setName("Enemy Laser");
		setDamage(5);						// 2017/02/21 Player health is decreased by 5 health points
		setWidth(50);
		setHeight(5);
	}
	else if (subType == VIRUS_FIREBALL) {
		setName("Virus Fireball");
		setDamage(10);						// 2017/02/21 Player health is decreased by 5 health points
		setWidth(25);
		setHeight(25);
	}
	else if (subType == BLUE_VIRUS_BULLET) {
		setProjectileActive(false);
		setName("Blue Virus Bullet");
		setDamage(15);						// 2017/02/21 Player health is decreased by 5 health points
		setWidth(25);
		setHeight(25);
		std::cout << "BLUE VIRUS BULLET CONSTRUCTOR" << std::endl;
	}

	if (getSubType() == ENEMY_SHIP_LASER) {
		setColliderWidth(getWidth());
		setColliderHeight(getHeight());
	}
	else{								// Type 1 = orange fireball
		setColliderWidth(25);
		setColliderHeight(25);
	}
	setScore(0);						// 2017/01/20 Points to deduct from player after collision with this object

	rotateCounter = 0;
	satelliteObjectOrbiting = false;
}

// LaserEnemy Destructor
WeaponEnLaser::~WeaponEnLaser() {
	std::cout << "Enemy Laser destructor called.\n";
}

void WeaponEnLaser::move() {
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
		GameObject::move();
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

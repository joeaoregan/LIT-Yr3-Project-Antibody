/* 2017-01-09:
Ninja Star Weapon
*/
#include "WeaponPlNinjaStar.h"
#include "Player.h"

// Ninja Star Constructor
WeaponPlNinjaStar::WeaponPlNinjaStar() {
	//std::cout << "NinjaStar constuctor called.\n";
	setWidth(25);
	setHeight(25);
	setVelocity(10);
	setVelX(10);						// Set velocity on X axis as 10

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	//setAlive(true);
}

// Laser Destructor
WeaponPlNinjaStar::~WeaponPlNinjaStar() {
	std::cout << "NinjaStar destructor called.\n";
}
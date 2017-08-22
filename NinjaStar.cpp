/* 2017-01-09:
Ninja Star Weapon
*/
#include "NinjaStar.h"
#include "Player.h"

// Ninja Star Constructor
NinjaStar::NinjaStar() {
	//std::cout << "NinjaStar constuctor called.\n";
	setWidth(25);
	setHeight(25);
	setVelX(10);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAlive(true);
}

// Ninja Star Destructor
NinjaStar::~NinjaStar() {
	std::cout << "NinjaStar destructor called.\n";
}
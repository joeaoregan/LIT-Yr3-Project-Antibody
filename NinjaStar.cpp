/* 2017-01-09:
Ninja Star Weapon
*/
#include "NinjaStar.h"
#include "Ship.h"

// Ninja Star Constructor
NinjaStar::NinjaStar() {
	std::cout << "NinjaStar constuctor called.\n";
	setWidth(25);
	setHeight(25);
	setVelocity(10);
}

// Laser Destructor
NinjaStar::~NinjaStar() {
	std::cout << "NinjaStar destructor called.\n";
}

void NinjaStar::movement() {
	GameObject::movement();											// Move the NinjaStar

	// destroy NinjaStar once it is offscreen
	if (getX() > SCREEN_WIDTH) setAlive(false);
	else  setAlive(true);
}

void NinjaStar::spawn(int x, int y) {
	setX(x + 65);
	setY(y + 25);
	setVelX(getVelocity());
	setVelY(0);
}

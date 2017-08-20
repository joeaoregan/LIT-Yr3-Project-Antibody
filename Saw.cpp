/* 2017-01-09:
Saw Weapon
*/
#include "Saw.h"
#include "Ship.h"

// Ninja Star Constructor
Saw::Saw() {
	std::cout << "Saw constuctor called.\n";
	setWidth(40);
	setHeight(40);
	setVelocity(0);
}

// Laser Destructor
Saw::~Saw() {
	std::cout << "Saw destructor called.\n";
}

void Saw::movement(int x, int y) {
	//GameObject::movement();											// Move the Saw

	//if (getX() > SCREEN_WIDTH) setAlive(false);
	//else  setAlive(true);
	setX(x + 65);
	setY(y + 25);
}

void Saw::spawn(int x, int y) {
	setX(x + 25);
	setY(y + 70);
	//setVelX(getVelocity());
	//setVelY(0);
}

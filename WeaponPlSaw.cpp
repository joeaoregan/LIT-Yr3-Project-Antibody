/* 2017-01-09:
Saw Weapon
*/
#include "WeaponPlSaw.h"
#include "Player.h"

// Saw Constructor
WeaponPlSaw::WeaponPlSaw(int player) {
	setPlayer(player);
	std::cout << "Saw constuctor called.\n";
	setWidth(40);
	setHeight(40);
	setVelocity(0);
	setAlive(true);
}

// Saw Destructor
WeaponPlSaw::~WeaponPlSaw() {
	std::cout << "Saw destructor called.\n";
}

void WeaponPlSaw::movement(int x, int y) {
	setX(x + 65);
	setY(y + 25);
}
/* 2017-01-09:
Saw Weapon
*/
#include "Saw.h"
#include "Player.h"

// Saw Constructor
Saw::Saw(int player) {
	setPlayer(player);
	std::cout << "Saw constuctor called.\n";
	setWidth(40);
	setHeight(40);
	setVelocity(0);
	setAlive(true);
}

// Saw Destructor
Saw::~Saw() {
	std::cout << "Saw destructor called.\n";
}

void Saw::movement(int x, int y) {
	setX(x + 65);
	setY(y + 25);
}
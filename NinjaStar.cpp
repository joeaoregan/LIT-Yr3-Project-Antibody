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
	setVelocity(10);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAlive(true);
}

// Laser Destructor
NinjaStar::~NinjaStar() {
	//std::cout << "NinjaStar destructor called.\n";
}

void NinjaStar::spawn(int x, int y, SDL_Rect collider) {
	setX(x + 65);
	setY(y + 25);
	setVelX(getVelocity());
	setVelY(0);
	setCollider(collider);
}
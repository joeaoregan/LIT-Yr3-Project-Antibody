#include "WeaponPlRocket.h"
#include "Player.h"

// Laser Constructor
WeaponPlRocket::WeaponPlRocket() {
	//std::cout << "Rocket constuctor called.\n";

	setWidth(75);
	setHeight(20);
	setVelocity(12);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	//setAngle(0);	// Fire straight
	//setGrade(0);	// Basic Rocket = 0

	setAlive(true);	// Make sure Rocket is alive from the beginning
}

// Laser Destructor
WeaponPlRocket::~WeaponPlRocket() {
	std::cout << "Rocket destructor called.\n";
}

void WeaponPlRocket::movement() {
	GameObject::movement();
	setY(getY() + getVelY());							// Up direction

	if (getY() > SCREEN_HEIGHT_GAME - 40) setAlive(false);
	else if (getY() < 40) setAlive(false);
}

void WeaponPlRocket::spawn(int x, int y, SDL_Rect* collider, int player, int type) {
	setX(x + 57);
	setY(y + 13);
	setVelX(getVelocity());
	setVelY(0);
	setCollider((*collider));
	setPlayer(player);
	setType(type);
}

#include "WeaponPlRocket.h"
#include "Player.h"

// Laser Constructor
WeaponPlRocket::WeaponPlRocket() {
	//std::cout << "Rocket constuctor called.\n";

	setWidth(75);
	setHeight(20);
	setVelocity(20);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	//setAngle(0);	// Fire straight
	//setGrade(0);	// Basic Rocket = 0

	setAlive(true);	// Make sure Rocket is alive from the beginning
	setSubType(PLAYER_WEAPON);
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

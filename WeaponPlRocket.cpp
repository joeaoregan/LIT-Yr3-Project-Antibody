#include "WeaponPlRocket.h"
#include "Player.h"

// Laser Constructor
WeaponPlRocket::WeaponPlRocket(int player) {
	//std::cout << "Rocket constuctor called.\n";
	setType(PLAYER_WEAPON);
	setPlayer(player);

	if (player == PLAYER1) setSubType(ROCKET_P1);
	else if (player == PLAYER2) setSubType(ROCKET_P2);

	setWidth(75);
	setHeight(20);
	setVelocity(20);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAngle(0);	// Fire straight
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

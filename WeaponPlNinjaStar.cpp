/* 2017-01-09:
Ninja Star Weapon
*/
#include "WeaponPlNinjaStar.h"
#include "Player.h"

// Ninja Star Constructor
WeaponPlNinjaStar::WeaponPlNinjaStar(int player) {
	//std::cout << "NinjaStar constuctor called.\n";
	setType(PLAYER_WEAPON);

	if (player == PLAYER1) setSubType(NINJA_STAR_P1);
	else if (player == PLAYER2) setSubType(NINJA_STAR_P2);

	setPlayer(player);					// 2017/01/17 Set the player the laser belongs too

	setWidth(25);
	setHeight(25);
	//setVelocity(10);
	setVelX(10);						// Set velocity on X axis as 10 --- NOT WORKING HERE???

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAlive(true);
}

// Laser Destructor
WeaponPlNinjaStar::~WeaponPlNinjaStar() {
	std::cout << "NinjaStar destructor called.\n";
}
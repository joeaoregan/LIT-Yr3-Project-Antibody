/* 2017-01-09:
Saw Weapon
*/
#include "WeaponPlSaw.h"
#include "Player.h"

// Saw Constructor
WeaponPlSaw::WeaponPlSaw(int type) {
	setType(PLAYER_WEAPON);		// 2017/02/19 Can't be set as PLAYER_WEAPON, as this causes an explosion (fixed with if statement in call to explosion)
	//setPlayer(player);
	setSubType(type);
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
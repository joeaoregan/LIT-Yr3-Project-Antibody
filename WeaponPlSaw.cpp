/* 
	2017/01/23 Fixed saw spawning, now appearing/disappearing
	2017/01/20 Added spawnSaw() function to Game class to create Saw Weapon for player
	2017/01/17 Added separate class for saw weapon Saw.h (renamed WeaponPlSaw.h)
	2017/01/09 Saw Weapon
*/
/*
	SAW:

	The players saw weapon can be used to cut Enemy Virus enemies in half. The smaller virus
	objects are then more managable for White Blood Cells to destroy. Saws are close range 
	weapons, the player can not be damaged while using the saw, as other objects are deflected
	with it. It is limited to close range which makes it less usefull than Ninja Stars for 
	destroying Orange Virus enemies, that explode on impact.
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

void WeaponPlSaw::move() {
}
void WeaponPlSaw::move(int x, int y) {
	setX(x + 65);
	setY(y + 25);
}
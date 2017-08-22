/*
	2017/02/21 Added check so only Ninja Stars and Saws split viruses
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

#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class WeaponPlSaw : public Weapon {
public:
	// Constructor - Initializes the variables
	WeaponPlSaw(int subType) {
		setType(PLAYER_WEAPON);		// 2017/02/19 Can't be set as PLAYER_WEAPON, as this causes an explosion (fixed with if statement in call to explosion)
		//setPlayer(player);
		setSubType(subType);
		std::cout << "Saw constuctor called.\n";
		setWidth(40);
		setHeight(40);
		setVelocity(0);
		setAlive(true);
	};

	// Deconstructor
	~WeaponPlSaw() {
		std::cout << "Saw destructor called." << std::endl;
	};

	// Inherited movement function
	virtual void move() {};

	// Moves the Saw - stalker movement, follows players every move
	virtual void move(int x, int y) {
		setX(x + 65);
		setY(y + 25);
	};

	virtual void destroy() {};
};

#endif
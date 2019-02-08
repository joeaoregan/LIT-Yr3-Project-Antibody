/*
	2017/03/04 Moved smaller class files functionality into their headers
	2017/02/10 Fixed velocity for ninja star after spawning, ninja stars are no longer static
	2017/01/30 Added rotation angle to constructors for Textures that rotate
	2017/01/25 Fixed Ninja Star scoring for Player 2
	2017/01/20 Fixed problem for ninja stars only scoring for Player 1
	2017/01/17 Added collision detection for Ninja Stars
	2017/01/09 Ninja Star Weapon
				Added spawnNinjaStar() function to create ninja star weapon
*/
/*
	NINJA STAR (Renamed WeaponPlNinjaStar.h)

	*** This class contains the functions for spawning, rendering, and moving ninja stars. *** NEED TO MOVE THIS FUNCTIONALITY BACK, my bad, Joe
	Ninja stars are rotating objects, and they have a slower speed than Lasers but a higher
	points value. Like lasers the player automatically has unlimited ninja stars. Ninja stars
	can be used to cut Enemy Virus in two. Each player has a differnt colour ninja star, and
	sound effect.
*/
/*
	2017/02/21 Added check so only Ninja Stars and Saws split viruses
	2017/01/30 Added rotation angle to constructors for Textures that rotate
	2017/01/17 Added player decision to spawnNinjaStar() function - determines player to spawn for and their coords
	2017/01/09 Add Ninja Star weapon class
*/

#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class WeaponPlNinjaStar : public Weapon {
public:
	// Ninja Star Constructor
	WeaponPlNinjaStar(int player) {
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
	}; 							// Initializes the variables

	// Ninja Star Destructor
	~WeaponPlNinjaStar() {
		std::cout << "NinjaStar destructor called." << std::endl;
	};

	// Inherited movement function
	virtual void move() {
		GameObject::move();
	};
};

#endif
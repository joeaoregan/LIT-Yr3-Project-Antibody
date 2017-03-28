/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponPlSaw.h
	- Description:			Header file for the Weapon Player Saw class.
	- Information:			The players saw weapon can be used to cut Enemy Virus enemies in half. The smaller virus
							objects are then more managable for White Blood Cells to destroy. Saws are close range
							weapons, the player can not be damaged while using the saw, as other objects are deflected
							with it. It is limited to close range which makes it less usefull than Ninja Stars for
							destroying Orange Virus enemies, that explode on impact.

	- Log:
		2017/02/21		Added check so only Ninja Stars and Saws split viruses
		2017/01/23		Fixed saw spawning, now appearing/disappearing
		2017/01/20		Added spawnSaw() function to Game class to create Saw Weapon for player
		2017/01/17		Added separate class for saw weapon Saw.h (renamed WeaponPlSaw.h)
		2017/01/09		Saw Weapon
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef CIRCULAR_SAW_H
#define CIRCULAR_SAW_H

#include "Weapon.h"

class WeaponPlSaw : public Weapon {
public:
	/* 
		Saw Constructor 
		
		Initializes the variables
		The Saw type, name, textureID, angle of rotation, dimensions, velocity are set
		And the saw is set alive or active on screen
	*/
	WeaponPlSaw(int subType) {
		setType(PLAYER_WEAPON);		// 2017/02/19 Can't be set as PLAYER_WEAPON, as this causes an explosion (fixed with if statement in call to explosion)
		setSubType(subType);

		if (subType == SAW1) {
			setName("Saw P1");
			setPlayer(PLAYER1);
		}
		else if (subType == SAW2) {
			setName("Saw P2");
			setPlayer(PLAYER2);
		}

		setTextureID("sawID");		// 2017/03/18 Added saw texture to texture map
		setAngle(5);				// 2017/03/18 Angle of rotation for Ninja Stars, rotates clockwise 5 degrees each frame	

		std::cout << "Saw constuctor called.\n";
		setWidth(40);
		setHeight(40);
		setVelocity(0);
		setAlive(true);

		//setPlayer(player);
	};

	// Deconstructor
	~WeaponPlSaw() {
		std::cout << "Saw destructor called." << std::endl;
	};

	/*
		Saws have basic movement, inherited move function from Game Object base class
		Stalker movement, follows players every move
		The Saw rotation is updated as it moves across the screen, similar to Blood Cells and Ninja Stars
	*/
	virtual void move(int x, int y) {
		setX(x + 65);					// Move the saw towards the front of the ship
		setY(y + 25);					// Move the saw down towards bottom of the ship
		GameObject::move(x, y);			// Inherited Stalker Movement function from GameObject base class

		setAngle(getAngle() + 5);		// 2017/03/18 The angle of rotation is set, similar to Blood Cell and Ninja Star, functionality moved from Game class
	};									

	/*
		Saws are destroyed when they move off screen
		This functionality is inherited from the Game Object base class
	*/
	virtual void destroy() {								// Destroy the object when it moves off screen
		GameObject::destroy();
	};

	/*
		2017/03/18 Render Player Saw

		The Saw texture is loaded from the texture map using the stored ID
		Saws rotate identical to Ninja Stars in only one direction
	*/
	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

		// 2018/03/17 Identical to Ninja Star Rotation 
		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
	}
};

#endif


/*
// 2017/03/18 Older movment function

// Moves the Saw - stalker movement, follows players every move
virtual void move(int x, int y) {
	setX(x + 65);
	setY(y + 25);
};
*/
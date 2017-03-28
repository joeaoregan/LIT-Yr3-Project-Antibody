/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponPlNinjaStar.h
	- Description:			Header file for the Weapon Player Ninja Star class.
	- Information:			Ninja stars are rotating objects, and they have a slower speed than Lasers but a higher
							points value. Like lasers the player automatically has unlimited ninja stars. Ninja stars
							can be used to cut Enemy Virus in two. Each player has a differnt colour ninja star, and
							sound effect.

	- Log:
		2017/03/18		Added the Ninja Stars texture to the texture map in Texture class
						Ninja star rotations are updated in the move() function instead of setRotatingAngle() in Game class
						A texture ID has been added for both Player 1 and Player 2 types of ninja star
						And the angle of rotation is now assigned to the Ninja Star class instead of the Texture class
						Destroy function is inherited from Game Object base class
		2017/03/04		Moved smaller class files functionality into their headers
		2017/02/10		Fixed velocity for ninja star after spawning, ninja stars are no longer static
		2017/01/30		Added rotation angle to constructors for Textures that rotate
		2017/01/25		Fixed Ninja Star scoring for Player 2
		2017/01/20		Fixed problem for ninja stars only scoring for Player 1
		2017/01/17		Added collision detection for Ninja Stars
		2017/01/09		Ninja Star Weapon
						Added spawnNinjaStar() function to create ninja star weapon
		2017/02/21		Added check so only Ninja Stars and Saws split viruses
		2017/01/30		Added rotation angle to constructors for Textures that rotate
		2017/01/17		Added player decision to spawnNinjaStar() function - determines player to spawn for and their coords
		2017/01/09		Add Ninja Star weapon class
		2017/03/18		Rendering functionality has been moved back to class
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef NINJA_STAR_H
#define NINJA_STAR_H

#include "Weapon.h"

class WeaponPlNinjaStar : public Weapon {
public:
	/* 
		Ninja Star Constructor
		
		Initializes the variables
		The ninja star name, texture ID, sub-type, type, angle of rotation, and assigned player are set
		Along with dimensions, velocity on X axis, collider width and height, and the object is set alive.
	*/
	WeaponPlNinjaStar(int player) {
		if (player == PLAYER1) {
			setName("Ninja Star P1");		// 2017/03/18 Name of Ninja Star for info / error messages
			setTextureID("nsP1ID");			// 2017/03/18 Texture ID for Player 1 Ninja Star
			setSubType(NINJA_STAR_P1);		// The sub-type of weapon
		}
		else if (player == PLAYER2) {
			setName("Ninja Star P2");		// 2017/03/18 Name of Ninja Star for info / error messages
			setTextureID("nsP2ID");			// 2017/03/18 Texture ID for Player 2 Ninja Star
			setSubType(NINJA_STAR_P2);		// The sub-type of weapon
		}

		setType(PLAYER_WEAPON);				// The type of game object is Player Weapon
		setAngle(5);						// 2017/03/18 Angle of rotation for Ninja Stars, rotates clockwise 5 degrees each frame		
		setPlayer(player);					// 2017/01/17 Set the player the laser belongs too

		setWidth(25);						// Set width for texture and collider
		setHeight(25);						// Set Height for texture and collider
		setVelX(10);						// Set velocity on X axis as 10 --- NOT WORKING HERE???

		setColliderWidth(getWidth());
		setColliderHeight(getHeight());

		setAlive(true);
		/*
		// Older variables set elsewhere e.g. velocity set in spawn function in Game class

		std::cout << "NinjaStar constuctor called.\n";
		if (player == PLAYER1) setSubType(NINJA_STAR_P1);
		else if (player == PLAYER2) setSubType(NINJA_STAR_P2);
		setVelocity(10);					// The speed the object moves at
		*/
	}; 

	// Ninja Star Destructor
	~WeaponPlNinjaStar() {
		std::cout << "NinjaStar destructor called." << std::endl;
	};

	/*
		Ninja stars have basic movement, inherited move function from Game Object base class
		The ninja star rotation is updated as it moves across the screen, similar to Blood Cells
	*/
	virtual void move(int x = 0, int y = 0) {
		GameObject::move();						// Movement is inherited from Game Object base class

		setAngle(getAngle() + 5);				// 2017/03/18 The angle of rotation is set, similar to Blood Cell, functionality moved from Game class
	};

	/*
		Ninja Stars are destroyed when they move off screen
		This functionality is inherited from the Game Object base class
	*/
	virtual void destroy() {
		GameObject::destroy();					// 2017/03/18 destroy method inherited from Game Object base class
	};

	/*
		2017/03/18 Render Ninja Stars

		The Ninja Stars texture is loaded from the texture map using the stored ID
		Ninja Stars rotate similar to Blood Cells but in only one direction
	*/
	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

		// Similar to Blood Cell rotation but rotating in only one direction
		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
	}
};

#endif
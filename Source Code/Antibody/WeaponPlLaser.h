/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponPlLaser.h
	- Description:			Header file for the Weapon Player Laser class.
	- Information:			Contains all function definitions and variables for the Player Weapon Laser class.
							This class contains the functions for spawning, rendering, and moving player laser objects.
							The player has two grades of laser, a single beam laser, and upon collecting a laser power
							up, a three beam laser. The three beam laser fires 3 laser beams at a time, at 3 different
							angles. The player can fire an unlimited amount of laser beams.

							Laser.cpp is where all the implementations of the function definitions in Laser.h reside.
	- Log:
		2017/03/04		Moved smaller class files functionality into their headers
						Set a game object texture ID variable, Player and Enemy lasers now render based on their unique texture ID
		2017/01/23		Added power up to change laser grade
		2017/01/22		Added separate textures to renderer, each player has a different colour laser
		2017/01/19		Added 3 beam laser
		2017/01/16		Spawn laser function added to game class to create laser with coords and velocity
		2017/01/09		Moved functionality common to game objects to GameObjects class reducing the code
		2017/01/06		Added player lasers
----------------------------------------------------------------------------------------------------------------------*/

#ifndef LASER_H
#define LASER_H

#include "Weapon.h"
#include "Texture.h"

class WeaponPlLaser : public Weapon {
public:
	// Player Laser Constructor
	WeaponPlLaser(int player, int angle = 0, int grade = 0) {
		//std::cout << "Laser constuctor called.\n";
		setType(PLAYER_WEAPON);
		setPlayer(player);

		if (player == PLAYER1) { 
			setSubType(LASER_P1);
			setTextureID("orangeLaserID");
		}
		else if (player == PLAYER2) { 
			setSubType(LASER_P2);
			setTextureID("greenLaserID");
		}

		setAngle(angle);	// Fire straight
		setGrade(grade);	// Basic Laser = 0, Triple Laser = 1

		//setVelocity(15);

		setWidth(50);
		setHeight(5);

		setColliderWidth(getWidth());
		setColliderHeight(getHeight());

		setAlive(true);
	};		

	// Player Laser Destructor
	~WeaponPlLaser() {
		std::cout << "Laser destructor called.\n";
	};
	
	// Moves the laser	
	virtual void move(int x, int y) {
		setY(getY() + getVelY());		// Up direction
		//if (getGrade() == 1) {

		// Double lasers move at angles to each other and not straight
		if (getAngle() == LASER2_TOP) setY(getY() - 1);
		else if (getAngle() == LASER2_BOTTOM) setY(getY() + 1);

		// Triple lasers have one straight, and two moving at angles
		else if (getAngle() == LASER3_TOP) setY(getY() - 3);
		else if (getAngle() == LASER3_BOTTOM) setY(getY() + 3);

		GameObject::move();				// Inherited movement
	};

	virtual void destroy() {
		GameObject::destroy();			// 2017/03/18 destroy method inherited from Game Object base class
	};

	/*
		2017/03/18 Render function
	*/
	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
	};

	/*
	// 2017/01/22 Added separate textures to renderer, each player has a different colour laser 
	void render(int player, Texture &orange, Texture &green) {
		if (getPlayer() == PLAYER1)
			orange.render(getX(), getY());
	else if (getPlayer() == PLAYER2)
			green.render(getX(), getY());
	};

	//virtual void spawn(int x, int y, int velocity, int player, int type = 0);
	*/
};

#endif
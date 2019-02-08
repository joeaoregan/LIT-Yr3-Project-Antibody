/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Blockage.h
	- Description:			Class for Blockage enemy type
	- Information:
		How it works:		Creates an enemy blockage object
							Object is a rectangle so four of them can fit together and look like one big object.
							The spawn function in the Game class will spawn four of them, they will be algined vertically.
							Once all 4 have spawned they will appear as one big wall or blockage.
							They objects will move across the screen from right to left.
							Player can only destroy them by activiating the saw.
	- Log:

	2017/02/04				Implemented Blockage object to the game.
								- Aim is to spawn 4 blockages which act as one wall moving across the screen.
								- Player must cut through the wall with their saw or be pushed of screen to their death.
								- Added texture to the blockage
----------------------------------------------------------------------------------------------------------------------*/

#ifndef BLOCKAGE_H
#define BLOCKAGE_H

#include "Enemy.h"

class Blockage : public Enemy {
public:
	// Name: Blockage()
	// Role: Constructor to initialize vavriables conscering the blockage object
	Blockage() {
		setType(ENEMY_OBJECT);						// Its an enemy.
		setSubType(BLOCKAGE);						// Specifically a Blockage.
		setScore(15);								// Score player will receive for destroying a blockage.

		setTextureID("blockageID");

		// Dimensions of a blockage object in pixels.
		setWidth(56);
		setHeight(130);
		
		// Adjust size of the bounding volume to exactly that of the blockage object
		setColliderWidth(getWidth());
		setColliderHeight(getHeight());

		// Set velocity to move with the background from right to left
		setVelocity(-BACKGROUND_SCROLL_SPEED);

		// Upon creation, it will be alive
		setAlive(true);
};	

	// Name: ~Blockage()
	// Role: To destroy the blockage object upon being set to dead
	~Blockage() {
		std::cout << "Destroying blockage" << std::endl;
	};

	// Name: move()
	// Role: Sets the (X, Y) coordinates based on velocity
	//		 Inherits from GameObject base class
	virtual void move() {
		GameObject::move();

		setColliderX(getX());
		setColliderY(getY());

		//// destroy blockage once it is offscreen
		//if (getX() < -getWidth()) setAlive(false);
		//else setAlive(true);
	};

	virtual void destroy() {};
};
#endif
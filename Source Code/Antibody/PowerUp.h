/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					PowerUp.h
	- Description:			header file for the PowerUp class.
	- Information:			Contains all function definitions and variables for PowerUp class.
							The players can collect power ups in the game for health, laser weapon, 
							increasing the number of rockets in their inventory,
							time checkpoint power ups to add time to the clock, and increasing number of lives
	- Log:
		2017/03/18		Added render function to class to render from texture map using texture ID
		2017/03/04		Moved smaller class files functionality into their headers
						Set a game object texture ID variable for Power Ups, now render based on their unique texture ID
		2017/02/21		POWER UPS: Added gold coloured lives power up to increase the number of player lives
		2017/02/18		CHECKPOINT: Added checkpoint power up to game objects list
						Set types and sub-types for objects on game objects list
		2017/02/15		Added Power Ups to list of game objects
		2017/01/10		Added class for handling powerups PowerUp.h
----------------------------------------------------------------------------------------------------------------------*/

#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

//enum powerUpTypes { POWER_UP_HEALTH = 1, POWER_UP_LASER, POWER_UP_ROCKET };

class PowerUp : public GameObject {
public:
	// Power Up Constructor
	PowerUp(int subType = 0, int score = 0) {
		setType(POWER_UP);
		setSubType(subType);
		setScore(score);

		setDamage(50);							// 2017/02/21 Increase health by 50 for health power up

		// Change dimensions, name, and Texture ID for different types of power ups
		if (subType == POWER_UP_HEALTH) {			
			setHeight(60);
			setWidth(60);
			setName("Health Power Up");
			setTextureID("healthPowerUpID");
		}
		else if (subType == POWER_UP_LASER) {
			setHeight(48);
			setWidth(60);
			setName("Laser Power Up");
			setTextureID("laserPowerUpID");
		}
		else if (subType == POWER_UP_ROCKET) {
			setHeight(60);
			setWidth(30);
			setName("Rocket Power Up");
			setTextureID("rocketPowerUpID");
		}
		else if (subType == POWER_UP_CHECKPOINT) {
			setHeight(60);
			setWidth(60);
			setName("Checkpoint Power Up");
			setTextureID("checkpointPowerUpID");
		}
		else if (subType == POWER_UP_LIVES) {
			setHeight(29);
			setWidth(60);
			setName("New Life Power Up");
			setTextureID("lifePowerUpID");
		}

		setVelocity(1);

		setColliderWidth(getWidth());
		setColliderHeight(getHeight());
	};

	// Power Up Deconstructor
	~PowerUp() {};

	// Inherited Movement function
	virtual void move() {
		GameObject::move();
	};

	virtual void destroy() {};

	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
	};
};

#endif
/*
	2017/02/21 POWER UPS: Added gold coloured lives power up to increase the number of player lives
	2017/02/18 CHECKPOINT: Added checkpoint power up to game objects list
				Set types and sub-types for objects on game objects list
	2017/02/15 Added Power Ups to list of game objects
	2017/01/10 Added class for handling powerups PowerUp.h
*/
/*
	POWER UP:

	The players can collect power ups in the game for health, laser weapon, increasing the number of rockets in their inventory,
	time checkpoint power ups to add time to the clock, and increasing number of lives
*/

#include "PowerUp.h"

PowerUp::PowerUp(int type, int score) {
	setType(POWER_UP);
	setSubType(type);
	setScore(score);

	setDamage(50);							// 2017/02/21 Increase health by 50 for health power up
	
	if (type == POWER_UP_HEALTH) {			// Change dimensions for different types of power ups
		setHeight(60);
		setWidth(60);
		setName("Health Power Up");
	}
	else if (type == POWER_UP_LASER) {
		setHeight(48);
		setWidth(60);
		setName("Laser Power Up");
	}
	else if (type == POWER_UP_ROCKET) {
		setHeight(60);
		setWidth(30);
		setName("Rocket Power Up");
	}
	else if (type == POWER_UP_CHECKPOINT) {
		setHeight(60);
		setWidth(60);
		setName("Checkpoint Power Up");
	}
	else if (type == POWER_UP_LIVES) {
		setHeight(29);
		setWidth(60);
		setName("New Life Power Up");
	}

	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

PowerUp::~PowerUp() {

}
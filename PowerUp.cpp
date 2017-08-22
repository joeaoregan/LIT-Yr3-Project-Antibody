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
#include "PowerUp.h"

PowerUp::PowerUp(int type, int score) {
	setSubType(type);
	setScore(score);
	
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
	if (type == POWER_UP_ROCKET) {
		setHeight(60);
		setWidth(30);
		setName("Rocket Power Up");
	}
	if (type == POWER_UP_CHECKPOINT) {
		setHeight(60);
		setWidth(60);
		setName("Checkpoint Power Up");
	}

	setType(POWER_UP);

	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

PowerUp::~PowerUp() {

}
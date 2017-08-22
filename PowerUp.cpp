#include "PowerUp.h"

PowerUp::PowerUp(int type, int score) {
	setType(type);
	setScore(score);
	
	setWidth(60);

	if (type == 1) {			// Change dimensions for different types of power ups
		setHeight(60);
		setName("Health Power Up");
	}
	else if (type == 2) {
		setHeight(48);
		setName("Laser Power Up");
	}

	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

PowerUp::~PowerUp() {

}
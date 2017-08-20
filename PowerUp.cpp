#include "PowerUp.h"

PowerUp::PowerUp() {
	//setScore(50);

	setWidth(60);
	setHeight(60);
	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

PowerUp::~PowerUp() {

}

void PowerUp::movement() {
	GameObject::movement();

	setColliderX(getX());
	setColliderY(getY());

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}

#include "WhiteBloodCell.h"

WhiteBloodCell::WhiteBloodCell() {
	setWidth(70);
	setHeight(70);
	setVelocity(1);
}

WhiteBloodCell::~WhiteBloodCell() {

}

#define MOVEMENT 250
int WBCUp = 0, WBCDown = MOVEMENT;

void WhiteBloodCell::movement() {
	GameObject::movement();

	if (WBCUp < MOVEMENT) {
		setY(getY() - getVelocity());
		WBCUp += 1;
		if (WBCUp >= MOVEMENT) WBCDown = 0;
	}
	if (WBCDown < MOVEMENT) {
		setY(getY() + getVelocity());
		WBCDown += 1;
		if (WBCDown >= MOVEMENT) WBCUp = 0;
	}

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
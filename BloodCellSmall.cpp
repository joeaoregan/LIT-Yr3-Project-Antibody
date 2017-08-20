#include "BloodCellSmall.h"
#define SBC_MOVEMENT 200
int sbcUp = 0, sbcDown = SBC_MOVEMENT;

BloodCellSmall::BloodCellSmall() {
	setWidth(59);
	setHeight(66);
	setVelocity(1);
	setScore(5);
}

BloodCellSmall::~BloodCellSmall() {

}

void BloodCellSmall::movement() {
	GameObject::movement();

	if (sbcUp < SBC_MOVEMENT) {
		setY(getY() - getVelocity());
		sbcUp += 1;
		if (sbcUp >= SBC_MOVEMENT) sbcDown = 0;
	}
	if (sbcDown < SBC_MOVEMENT) {
		setY(getY() + getVelocity());
		sbcDown += 1;
		if (sbcDown >= SBC_MOVEMENT) sbcUp = 0;
	}

	// destroy blood cell once it is offscreen
	if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}
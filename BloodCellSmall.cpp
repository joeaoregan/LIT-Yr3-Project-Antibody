#include "BloodCellSmall.h"
#define SBC_MOVEMENT 200
int sbcUp = 0, sbcDown = SBC_MOVEMENT;

BloodCellSmall::BloodCellSmall() {
	setWidth(59);
	setHeight(66);
	setVelocity(1);
}

BloodCellSmall::~BloodCellSmall() {

}

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
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
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
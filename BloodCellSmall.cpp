#include "BloodCellSmall.h"

BloodCellSmall::BloodCellSmall() {

}

BloodCellSmall::~BloodCellSmall() {

}

#define SBC_MOVEMENT 200
int sbcUp = 0, sbcDown = SBC_MOVEMENT;

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void BloodCellSmall::movement() {
	GameObject::movement();

	if (sbcUp < SBC_MOVEMENT) {
		setY(getY() - BLOODS_VEL);
		sbcUp += 1;
		if (sbcUp >= SBC_MOVEMENT) sbcDown = 0;
	}
	if (sbcDown < SBC_MOVEMENT) {
		setY(getY() + BLOODS_VEL);
		sbcDown += 1;
		if (sbcDown >= SBC_MOVEMENT) sbcUp = 0;
	}

	//std::cout << "test blood cell floating movement" << std::endl;

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
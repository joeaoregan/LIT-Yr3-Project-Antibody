#include "BloodCell.h"
int up = 0, down = 250;

BloodCell::BloodCell(int type) {
	//setColliderR(getWidth() / 2);		// Set circular collider
	//setScore(5);
	//shiftColliders();
	int randomRotationDirection = rand() % 3 + 1;

	setSubType(type);
	setVelocity(1);
	setMovement(200);
	setDistanceBetween(100);

	if (getSubType() == BLOOD_CELL) {					// Set dimensions for different types of blood cells
		setWidth(100);
		setHeight(55);
	}
	else if (getSubType() == SMALL_BLOOD_CELL) {
		setWidth(59);
		setHeight(66);
	}
	else if (getSubType() == WHITE_BLOOD_CELL) {
		setMovement(250);
		setDistanceBetween(150);
		setWidth(70);
		setHeight(70);
	}
	// Set 1 out of 3 (ish) Blood Cells rotating backwards
	if (randomRotationDirection == 1)
		setRotationDirection(-1);
	else
		setRotationDirection(1);
}

BloodCell::~BloodCell() {
	std::cout << "Blood Cell Destroyed" << std::endl;
}

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void BloodCell::movement() {
	GameObject::movement();

	if (up < getMovement()) {
		setY(getY() - getVelocity());
		up += 1;
		if (up >= getMovement()) down = 0;
	}
	if (down < getMovement()) {
		setY(getY() + getVelocity());
		down += 1;
		if (down >= getMovement()) up = 0;
	}
}
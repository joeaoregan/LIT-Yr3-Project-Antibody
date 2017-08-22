#include "BloodCell.h"
int up = 0, down = 250;

BloodCell::BloodCell(int subType) {
	//setColliderR(getWidth() / 2);		// Set circular collider
	//setScore(5);
	//shiftColliders();
	int randomRotationDirection = rand() % 3 + 1;
	setType(BLOOD_CELL);
	setSubType(subType);
	setVelocity(1);
	setMovement(200);
	setDistanceBetween(100);

	setWidth(70);
	setHeight(55);

	/*
	// NOT WORKING
	if (subType == LARGE_BLOOD_CELL) {					// Set dimensions for different types of blood cells
		setWidth(100);
		setHeight(55);
		setColliderWidth(getWidth() + 5);
		setColliderHeight(getHeight() + 5);
	}
	else if (subType == SMALL_BLOOD_CELL) {
		setWidth(59);
		setHeight(66);
		setColliderWidth(59);
		setColliderHeight(66);
	}
	else if (subType == WHITE_BLOOD_CELL) {
		setMovement(250);
		setDistanceBetween(150);
		setWidth(70);
		setHeight(70);
		setColliderWidth(getWidth() + 5);
		setColliderHeight(getHeight() + 5);
	}
	*/

	// Set 1 out of 3 (ish) Blood Cells rotating backwards
	if (randomRotationDirection == 1)
		setRotationDirection(-1);
	else
		setRotationDirection(1);

	setColliderWidth(getWidth() + 5);
	setColliderHeight(getHeight() + 5);
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

void BloodCell::movement(int targetX, int targetY) {
	if (getSubType() == WHITE_BLOOD_CELL) {
		if (getX() < SCREEN_WIDTH - getWidth()) {				// If the object is on the screen
			int randomVelocity = rand() % 4 + 2;

			if (getX() - targetX >= 0) {		// If the small virus is behind the white blood cell
				if (getX() - targetX >= randomVelocity)
					setX(getX() - randomVelocity);			// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getX() - targetX < 0) {	// if the small virus is in front of the white blood cell
				setX(getX() + randomVelocity);				// Move towards X coord
			}

			if (getY() - targetY >= 0) {		// if the small virus is below the white blood cell
				if (getY() - targetY >= randomVelocity)
					setY(getY() - randomVelocity);			// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getY() - targetY < 0) {	// if the small virus is above the white blood cell
				setY(getY() + randomVelocity);				// Move towards Y coord
			}

			setColliderX(getX());
			setColliderY(getY());
		}
	}
	else
		GameObject::movement();
}

#include "BloodCell.h"
#define MOVEMENT 250
int up = 0, down = MOVEMENT;

BloodCell::BloodCell() {
	//setColliderR(getWidth() / 2);		// Set circular collider

	setScore(5);

	//shiftColliders();
	setWidth(100);
	setHeight(55);
	setVelocity(1);
}

BloodCell::~BloodCell() {

}

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void BloodCell::movement() {
	GameObject::movement();

	if (up < MOVEMENT) {
		setY(getY() - getVelocity());
		up += 1;
		if (up >= MOVEMENT) down = 0;
	}
	if (down < MOVEMENT) {
		setY(getY() + getVelocity());
		down += 1;
		if (down >= MOVEMENT) up = 0;
	}

	// destroy blood cell once it is offscreen
	if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}
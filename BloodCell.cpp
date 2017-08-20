#include "BloodCell.h"

BloodCell::BloodCell() {

}

BloodCell::~BloodCell() {

}

#define MOVEMENT 250
int up = 0, down = MOVEMENT;

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void BloodCell::movement() {
	GameObject::movement();

	if (up < MOVEMENT) {
		setY(getY() - BLOOD_VEL);
		up+=1;
		if (up >= MOVEMENT) down = 0;
	}	
	if (down < MOVEMENT) {
		setY(getY() + BLOOD_VEL);
		down+=1;
		if (down >= MOVEMENT) up = 0;
	}

	//std::cout << "test blood cell floating movement" << std::endl;

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
#include "WhiteBloodCell.h"

WhiteBloodCell::WhiteBloodCell() {

}

WhiteBloodCell::~WhiteBloodCell() {

}

#define MOVEMENT 250
int WBCUp = 0, WBCDown = MOVEMENT;

//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void WhiteBloodCell::movement() {
	GameObject::movement();

	if (WBCUp < MOVEMENT) {
		setY(getY() - WBLOOD_VEL);
		WBCUp += 1;
		if (WBCUp >= MOVEMENT) WBCDown = 0;
	}
	if (WBCDown < MOVEMENT) {
		setY(getY() + WBLOOD_VEL);
		WBCDown += 1;
		if (WBCDown >= MOVEMENT) WBCUp = 0;
	}

	//std::cout << "test white blood cell floating movement" << std::endl;

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
/* 2017-01-09:
Weapons will inherit from weapon
*/

#include "Weapon.h"

// Constructor
Weapon::Weapon() {

}

// Deconstructors
Weapon::~Weapon() {

}

int Weapon::getPlayer() {
	return mPlayer;
}

void Weapon::setPlayer(int p) {
	mPlayer = p;
}
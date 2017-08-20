#include "EnemyVirus.h"

EnemyVirus::EnemyVirus() {

}

EnemyVirus::~EnemyVirus() {

}


//void EnemyVirus::movement(Ship ship) {	// No need for full ship object, just ship y coord will do
void EnemyVirus::movement(int shipX, int shipY) {
	GameObject::movement();
	
	if (getX() > shipX) {
		if (getY() - shipY >= 0) {
			if (getY() - shipY >= VIRUS_VEL)
				setY(getY() - VIRUS_VEL);			// No need to make smaller movements, as velocity is v.low anyway
		}
		else if (getY() - shipY < 0) {
			setY(getY() + VIRUS_VEL);
		}
	}
	//else if (getY() - ship.getY() > 0 && getY() - ship.getY() < VIRUS_VEL)
	//	setY(getY() - ship.getY());

	// destroy enemy ship once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
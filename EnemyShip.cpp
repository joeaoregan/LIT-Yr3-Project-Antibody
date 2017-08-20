#include "Game.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip() {
	// Initialize the offsets
	//mEnPosX = 0;
	//mEnPosY = 0;
	setX(0);
	setY(0);

	// Initialize the velocity
	//mEnVelX = 0;
	//mEnVelY = 0;
	setVelX(0);
	setVelY(0);
}

//void EnemyShip::spawn()/ {
	//mEnPosX = SCREEN_WIDTH;
	//mEnPosY = SCREEN_HEIGHT / 2 - ENEMY_HEIGHT / 2;	// JOE 09/01: Spawn Enemy in the middle of the screen
	//mEnVelX = 5;
//	setX(SCREEN_WIDTH);
//	setY(SCREEN_HEIGHT / 2 - ENEMY_HEIGHT / 2);
//	setVelX(5);
//}

//void EnemyShip::moveEnemy() {
//	//mEnPosX -= mEnVelX;
//	//setX(getX() - mEnVelX);
//	setX(getX() - getVelX());
//}
void EnemyShip::movement() {
	GameObject::movement();

	// destroy enemy ship once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}
/*
// get x and y function for Enemy
int EnemyShip::getEnemyX()
{
	return mEnPosX;
}

int EnemyShip::getEnemyY()
{
	return mEnPosY;
}

int EnemyShip::getEnemyVelX()
{
	return mEnVelX;
}
*/
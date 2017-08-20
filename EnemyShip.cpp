
#include "Game.h"
#include "EnemyShip.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

EnemyShip::EnemyShip() {
	std::cout << "Enemy constuctor called.\n";
	// Initialize the offsets
	mEnPosX = 0;
	mEnPosY = 0;

	// Initialize the velocity
	mEnVelX = 0;
	mEnVelY = 0;

	// Set Collision Box Dimension
	mCollider.w = ENEMY_WIDTH;
	mCollider.h = ENEMY_HEIGHT;
}

void EnemyShip::spawn() {
	//setX(640);
	//setY(240);
	//setVelx(-10);
	mEnPosX = 500;
	mEnPosY = 240;
	mEnVelX = 0;
}

void EnemyShip::moveEnemy() {

	//setEnemyX(getEnemyX() + getEnemyVelX());


	mEnPosX -= mEnVelX;
	mCollider.x = mEnPosX;

	//mPosX += mVelX;												// Move the Enemy left or right

	// If the ship went too far to the left or right
	if ((mEnPosX < 0) || (mEnPosX + ENEMY_WIDTH > SCREEN_WIDTH)) {
		mEnPosX += mEnVelX;											// Move back
		mCollider.x = mEnPosX;
	}

	mEnPosY += mEnVelY;												// Move the ship up or down
	mCollider.y = mEnPosY;

	// If the ship went too far up or down
	if ((mEnPosY < 0) || (mEnPosY + ENEMY_HEIGHT > SCREEN_HEIGHT)) {
		mEnPosY -= mEnVelY;											// Move back
		mCollider.y = mEnPosY;
	}

}

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

SDL_Rect* EnemyShip::getCollider()
{
	return &mCollider;
}

/*
void setEnemyX(int x) {
	mEnPosX = x;
}

void setEnemyY(int y) {
	mEnPosY = y;
}

void setEnemyVelX(int x) {
	mEnVelX = x;
}
*/

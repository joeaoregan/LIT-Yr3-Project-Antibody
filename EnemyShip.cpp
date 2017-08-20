#include "Game.h"
#include "EnemyShip.h"

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
	mEnPosX = 500;
	mEnPosY = 240;
	mEnVelX = 0;
}

void EnemyShip::moveEnemy() {
	mEnPosX -= mEnVelX;
	mCollider.x = mEnPosX;

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
int EnemyShip::getEnemyX(){
	return mEnPosX;
}

int EnemyShip::getEnemyY(){
	return mEnPosY;
}

int EnemyShip::getEnemyVelX(){
	return mEnVelX;
}

SDL_Rect* EnemyShip::getCollider(){
	return &mCollider;
}

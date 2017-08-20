#include <SDL.h>
#include <SDL_image.h>
#include "Ship.h"
#include "Game.h"
#include "EnemyShip.h"
#include "LTexture.h"

/*
2017-01-04:
Added asdw keyboard movement
*/
Game game1;
Ship::Ship() {
	// Initialize the offsets
	mPosX = 0;
	mPosY = 200;

	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	// Set Collision Box Dimension
	mCollider.w = SHIP_WIDTH;
	mCollider.h = SHIP_HEIGHT;
}

void Ship::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// MOVEMENT
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: mVelY -= SHIP_VEL; break;
		case SDLK_DOWN:
		case SDLK_s: mVelY += SHIP_VEL; break;
		case SDLK_LEFT:
		case SDLK_a: mVelX -= SHIP_VEL; break;
		case SDLK_RIGHT:
		case SDLK_d: mVelX += SHIP_VEL; break;

		// FIRE WEAPON
		case SDLK_SPACE:
			game1.spawnLaser();
			break; // SEAN: Press space bar to spawn a new laser
		}
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: mVelY += SHIP_VEL; break;
		case SDLK_DOWN:
		case SDLK_s: mVelY -= SHIP_VEL; break;
		case SDLK_LEFT:
		case SDLK_a: mVelX += SHIP_VEL; break;
		case SDLK_RIGHT:
		case SDLK_d: mVelX -= SHIP_VEL; break;
		}
	}
}

void Ship::move() {
	mPosX += mVelX;												// Move the ship left or right
	mCollider.x = mPosX;

	// If the ship went too far to the left or right
	if ((mPosX < 0) || (mPosX + SHIP_WIDTH > SCREEN_WIDTH)) {
		mPosX -= mVelX;											// Move back
		mCollider.x = mPosX;
	}

	mPosY += mVelY;												// Move the ship up or down
	mCollider.y = mPosY;

	// If the ship went too far up or down
	if ((mPosY < 0) || (mPosY + SHIP_HEIGHT > SCREEN_HEIGHT)) {
		mPosY -= mVelY;
		mCollider.y = mPosY;// Move back
	}
}

// SEAN: Added get x and y function for ship to allow laser to spawn at ships location
int Ship::getShipX() {
	return mPosX;
}// end getX

int Ship::getShipY() {
	return mPosY;
}// end getX

int Ship::getShipVelX() {
	return mVelX;
}// end getX

int Ship::getShipVelY() {
	return mVelY;
}// end getX

//SDL_Rect Ship::getCollider() {
//	return mCollider;
//}
SDL_Rect* Ship::getCollider() {
	return &mCollider;
}

void Ship::setShipX(int x) {
	mPosX = x;
}// end setX

 // set Y
void Ship::setShipY(int y) {
	mPosY = y;
}// end setY

void Ship::setShipColX(int x) {
	mCollider.x = x;
}// end setX

 // set Y
void Ship::setShipColY(int y) {
	mCollider.y = y;
}// end setY

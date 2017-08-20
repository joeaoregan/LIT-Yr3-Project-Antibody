#include <SDL.h>
#include <SDL_image.h>
#include "Ship.h"
#include "LTexture.h"

/*
2017-01-04:
Added asdw keyboard movement
*/

Ship::Ship() {
	// Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Ship::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
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

	// If the ship went too far to the left or right
	if ((mPosX < 0) || (mPosX + SHIP_WIDTH > SCREEN_WIDTH)) {
		mPosX -= mVelX;											// Move back
	}
		
	mPosY += mVelY;												// Move the ship up or down

	// If the ship went too far up or down
	if ((mPosY < 0) || (mPosY + SHIP_HEIGHT > SCREEN_HEIGHT)) {		
		mPosY -= mVelY;											// Move back
	}
}

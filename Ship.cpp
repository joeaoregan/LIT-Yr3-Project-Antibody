#include <SDL.h>
#include <SDL_image.h>
#include "Ship.h"
#include "LTexture.h"
#include <iostream>

/*
2017-01-04:
Added asdw keyboard movement
*/

int speed = 1;


Ship::Ship() {
	// Initialize the offsets
	mPosX = SCREEN_WIDTH / 2 - (SHIP_WIDTH / 2);
	mPosY = SCREEN_HEIGHT / 2 - (SHIP_HEIGHT / 2);					// Start at centre of screen

	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	std::cout << speed << std::endl;								// Test display speed
}




void Ship::handleEvent(SDL_Event& e) {
	// Increase speed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_PERIOD:
			if (speed < 5) speed += 1;
			std::cout << speed << std::endl;
			break;
		case SDLK_COMMA:
			if (speed > 1) speed -= 1;
			std::cout << speed << std::endl;
			break;
		}
	}


	// Key pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: mVelY -= (SHIP_VEL * speed); break;
		case SDLK_DOWN:
		case SDLK_s: mVelY += (SHIP_VEL * speed); break;
		case SDLK_LEFT:
		case SDLK_a: mVelX -= (SHIP_VEL * speed); break;
		case SDLK_RIGHT:
		case SDLK_d: mVelX += (SHIP_VEL * speed); break;
		}
	}
	// Key released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: mVelY += (SHIP_VEL * speed); break;
		case SDLK_DOWN:
		case SDLK_s: mVelY -= (SHIP_VEL * speed); break;
		case SDLK_LEFT:
		case SDLK_a: mVelX += (SHIP_VEL * speed); break;
		case SDLK_RIGHT:
		case SDLK_d: mVelX -= (SHIP_VEL * speed); break;
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

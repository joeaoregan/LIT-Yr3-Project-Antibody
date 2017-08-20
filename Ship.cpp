#include "Ship.h"
#include "Game.h"

/*
2017-01-04:
Added asdw keyboard movement
*/
Game weapon;
Ship::Ship() {
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
}

void Ship::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// MOVEMENT
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: setVelY(getVelY() - SHIP_VEL); break;
		case SDLK_DOWN:
		case SDLK_s: setVelY(getVelY() + SHIP_VEL); break;
		case SDLK_LEFT:
		case SDLK_a: setVelX(getVelX() - SHIP_VEL); break;
		case SDLK_RIGHT:
		case SDLK_d: setVelX(getVelX() + SHIP_VEL); break;


		// SELECT WEAPON
		//case SDLK
		// FIRE WEAPON
		case SDLK_SPACE:
			weapon.spawnLaser();		// 2017/01/09 JOE: Added sound effect
			break; // SEAN: Press space bar to spawn a new laser
		case SDLK_n:
			weapon.spawnNinjaStar();	// 2017/01/09 JOE: Added sound effect
			break; // JOE: Press 'n' to spawn a new Ninja Star
		}
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: setVelY(getVelY() + SHIP_VEL); break;
		case SDLK_DOWN:
		case SDLK_s: setVelY(getVelY() - SHIP_VEL); break;
		case SDLK_LEFT:
		case SDLK_a: setVelX(getVelX() + SHIP_VEL); break;
		case SDLK_RIGHT:
		case SDLK_d: setVelX(getVelX() - SHIP_VEL); break;
		}
	}
}

void Ship::movement() {
	GameObject::movement();
	//setX(getX() + getVelX());											// Move the ship left or right	

	// If the ship went too far to the left or right
	if ((getX() < 0) || ((getX() + SHIP_WIDTH) > SCREEN_WIDTH)) {
		setX(getX() - getVelX());										// Move back
	}

	setY(getY() + getVelY());											// Move the ship up or down

	// If the ship went too far up or down
	if ((getY() < 40) || ((getY() + SHIP_HEIGHT) > SCREEN_HEIGHT - 40)) {
		setY(getY() - getVelY());										// Move back
	}
}
/*
2017-01-04:
Added asdw keyboard movement
*/
#include "Ship.h"
#include "Game.h"
#include <math.h>   // 2017-08-11

#define DIAGONAL_VEL SHIP_VEL / (sqrt(2))

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;	// Create a deadzone where input from the controller is ignored

int previous = 0;
int previousStick = 0;

Game game1;
Ship::Ship() {
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(10);
}

void Ship::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_w: setVelY(getVelY() - getVelocity()); break;
			case SDLK_s: setVelY(getVelY() + getVelocity()); break;
			case SDLK_a: setVelX(getVelX() - getVelocity()); break;
			case SDLK_d: setVelX(getVelX() + getVelocity()); break;

			// FIRE WEAPON
			//case SDLK_SPACE: game1.spawnLaser(); break; // SEAN: Press space bar to spawn a new laser
			case SDLK_SPACE: game1.spawnLaser(getX(), getY(), 1); break;
			case SDLK_n: game1.spawnNinjaStar(getX(), getY(), 1); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: setVelY(getVelY() + getVelocity()); break;
			case SDLK_s: setVelY(getVelY() - getVelocity()); break;
			case SDLK_a: setVelX(getVelX() + getVelocity()); break;
			case SDLK_d: setVelX(getVelX() - getVelocity()); break;
			}
		}
	}
	else if (player == 2) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: setVelY(getVelY() - getVelocity()); break;
			case SDLK_DOWN: setVelY(getVelY() + getVelocity()); break;
			case SDLK_LEFT: setVelX(getVelX() - getVelocity()); break;
			case SDLK_RIGHT: setVelX(getVelX() + getVelocity()); break;

				// FIRE WEAPON SDLK_RCTRL
				//case SDLK_e: game1.spawnLaser(getX(), getY()); break; // SEAN: Press space bar to spawn a new laser
			case SDLK_RCTRL: game1.spawnLaser(getX(), getY(), 2); break;
			case SDLK_RSHIFT: game1.spawnNinjaStar(getX(), getY(), 2); break;
			}
		}
		// If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: setVelY(getVelY() + getVelocity()); break;
			case SDLK_DOWN: setVelY(getVelY() - getVelocity()); break;
			case SDLK_LEFT: setVelX(getVelX() + getVelocity()); break;
			case SDLK_RIGHT: setVelX(getVelX() - getVelocity()); break;
			}
		}
		if (SDL_NumJoysticks() > 0) {				// Joystick present
			if (e.type == SDL_JOYBUTTONDOWN) {		// Number of buttons
				gameControllerButton(e);
			}
			else if (e.type == SDL_JOYHATMOTION) {	// Set movement for D-Pad
				gameControllerDPad(e);
			}
		} // joystick present
	}

	/*

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// MOVEMENT
		switch (e.key.keysym.sym) {			// Adjust the velocity with keyboard
		case SDLK_UP:
		case SDLK_w: setVelY(getVelY() - getVelocity()); break;
		case SDLK_DOWN:
		case SDLK_s: setVelY(getVelY() + getVelocity()); break;
		case SDLK_LEFT:
		case SDLK_a: setVelX(getVelX() - getVelocity()); break;
		case SDLK_RIGHT:
		case SDLK_d: setVelX(getVelX() + getVelocity()); break;

		// FIRE WEAPON
		case SDLK_SPACE:					// SEAN: Press space bar to spawn a new laser
			game1.spawnLaser();
			break;
		case SDLK_e:						// JOE: Press 'n' to spawn a new Ninja Star
			game1.spawnNinjaStar();
			break;
		}
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: setVelY(getVelY() + getVelocity()); break;
		case SDLK_DOWN:
		case SDLK_s: setVelY(getVelY() - getVelocity()); break;
		case SDLK_LEFT:
		case SDLK_a: setVelX(getVelX() + getVelocity()); break;
		case SDLK_RIGHT:
		case SDLK_d: setVelX(getVelX() - getVelocity()); break;
		}
	}
	if (SDL_NumJoysticks() > 0) {				// Joystick present
		if (e.type == SDL_JOYBUTTONDOWN) {		// Number of buttons
			gameControllerButton(e);
		}
		else if (e.type == SDL_JOYHATMOTION) {	// Set movement for D-Pad
			gameControllerDPad(e);
		}
	} // joystick present
	*/
}

void Ship::movement() {
	GameObject::movement();												// Move the ship left or right - setX(getX() + getVelX());

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

void Ship::gameControllerDPad(SDL_Event& e) {
	if (e.jhat.value == SDL_HAT_UP) {
		resetPreviousDirection();
		setVelY(getVelY() - getVelocity());
		previous = SDL_HAT_UP;
	}
	else if (e.jhat.value == SDL_HAT_DOWN) {
		resetPreviousDirection();
		setVelY(getVelY() + getVelocity());
		previous = SDL_HAT_DOWN;
	}
	else if (e.jhat.value == SDL_HAT_LEFT) {
		resetPreviousDirection();
		setVelX(getVelX() - getVelocity());
		previous = SDL_HAT_LEFT;
	}
	else if (e.jhat.value == SDL_HAT_RIGHT) {
		resetPreviousDirection();
		setVelX(getVelX() + getVelocity());
		previous = SDL_HAT_RIGHT;
	}
	else if (e.jhat.value == SDL_HAT_RIGHTUP) {
		resetPreviousDirection();
		setVelX(getVelX() + DIAGONAL_VEL);
		setVelY(getVelY() - DIAGONAL_VEL);
		previous = SDL_HAT_RIGHTUP;
	}
	else if (e.jhat.value == SDL_HAT_RIGHTDOWN) {
		resetPreviousDirection();
		setVelX(getVelX() + DIAGONAL_VEL);
		setVelY(getVelY() + DIAGONAL_VEL);
		previous = SDL_HAT_RIGHTDOWN;
	}
	else if (e.jhat.value == SDL_HAT_LEFTUP) {
		resetPreviousDirection();
		setVelX(getVelX() - DIAGONAL_VEL);
		setVelY(getVelY() - DIAGONAL_VEL);
		previous = SDL_HAT_LEFTUP;
	}
	else if (e.jhat.value == SDL_HAT_LEFTDOWN) {
		resetPreviousDirection();
		setVelX(getVelX() - DIAGONAL_VEL);
		setVelY(getVelY() + DIAGONAL_VEL);
		previous = SDL_HAT_LEFTDOWN;
	}

	if (e.jhat.value == SDL_HAT_CENTERED) {
		resetPreviousDirection();
		previous = SDL_HAT_CENTERED;
	}
}

void Ship::gameControllerButton(SDL_Event& e) {
		if (e.jbutton.button == 0) {
			game1.spawnLaser(getX(), getY(), 2);
			std::cout << (int)e.jbutton.button << std::endl;	// shows which button has been pressed
		}
		if (e.jbutton.button == 1) {
			game1.spawnNinjaStar(getX(), getY(), 2);
			std::cout << (int)e.jbutton.button << std::endl;	// shows which button has been pressed
		}
}

void Ship::resetPreviousDirection() {
	if (previous == SDL_HAT_UP) {
		setVelY(getVelY() + getVelocity());
	}
	else if (previous == SDL_HAT_DOWN) {
		setVelY(getVelY() - getVelocity());
	}
	else if (previous == SDL_HAT_LEFT) {
		setVelX(getVelX() + getVelocity());
	}
	else if (previous == SDL_HAT_RIGHT) {
		setVelX(getVelX() - getVelocity());
	}

	else if (previous == SDL_HAT_RIGHTUP) {
		setVelX(getVelX() - DIAGONAL_VEL);
		setVelY(getVelY() + DIAGONAL_VEL);
	}
	else if (previous == SDL_HAT_RIGHTDOWN) {
		setVelX(getVelX() - DIAGONAL_VEL);
		setVelY(getVelY() - DIAGONAL_VEL);
	}
	else if (previous == SDL_HAT_LEFTDOWN) {
		setVelX(getVelX() + DIAGONAL_VEL);
		setVelY(getVelY() - DIAGONAL_VEL);
	}
	else if (previous == SDL_HAT_LEFTUP) {
		setVelX(getVelX() + DIAGONAL_VEL);
		setVelY(getVelY() + DIAGONAL_VEL);
		//	std::cout << " previous " << previous << std::endl;
	}
}

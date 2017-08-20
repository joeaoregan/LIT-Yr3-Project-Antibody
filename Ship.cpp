/*
2017-01-04:
Added asdw keyboard movement
*/
#include "Ship.h"
#include "Game.h"
#include <math.h>

#define VELOCITY 10
#define BOOST 2

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;	// Create a deadzone where input from the controller is ignored

int previous = 0;
int previousStick = 0;

unsigned int curTime;
int VEL;

Game game1;
Ship::Ship() {
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	setWidth(100);
	setHeight(47);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(VELOCITY);
	mCollider.w = getWidth();
	mCollider.h = getHeight();
}

void Ship::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_w: moveUp(); break;
			case SDLK_s: moveDown(); break;
			case SDLK_a: moveLeft(); break;
			case SDLK_d: moveRight(); break;

				// FIRE WEAPON
			case SDLK_SPACE: game1.spawnLaser(getX(), getY(), 1); break;
			case SDLK_n: game1.spawnNinjaStar(getX(), getY(), 1); break;
			case SDLK_e: game1.spawnSaw(getX(), getY(), 1); break;			// 2017/01/17 Saw Weapon added, check saw is active with if statement in spawn Saw, and activate/deactivate the weapon
			case SDLK_f: setSpeedBoost(true); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: moveDown(); break;		// undo up movement
			case SDLK_s: moveUp(); break;		// undo down movement
			case SDLK_a: moveRight(); break;	// undo left movement
			case SDLK_d: moveLeft(); break;		// undo right movement
			}
		}
	}
	else if (player == 2) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: moveUp(); break;
			case SDLK_DOWN: moveDown(); break;
			case SDLK_LEFT: moveLeft(); break;
			case SDLK_RIGHT: moveRight(); break;

				// FIRE WEAPON SDLK_RCTRL
				//case SDLK_e: game1.spawnLaser(getX(), getY()); break; // SEAN: Press space bar to spawn a new laser
			case SDLK_RCTRL: game1.spawnLaser(getX(), getY(), 2); break;
			case SDLK_RSHIFT: game1.spawnNinjaStar(getX(), getY(), 2); break;
			case SDLK_r: game1.spawnSaw(getX(), getY(), 2); break;			// 2017/01/17 Separate saw for player 2
			case SDLK_g: setSpeedBoost(true); break;
			}
		}
		// If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: moveDown(); break;
			case SDLK_DOWN: moveUp(); break;
			case SDLK_LEFT: moveRight(); break;
			case SDLK_RIGHT: moveLeft(); break;
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
void Ship::moveUp() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelY(getVelY() - (getVelocity() + BOOST));
	else
		setVelY(getVelY() - getVelocity());
}
void Ship::moveDown() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelY(getVelY() + (getVelocity() + BOOST));
	else
		setVelY(getVelY() + getVelocity());
}
void Ship::moveLeft() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelX(getVelX() - (getVelocity() + BOOST));
	else
		setVelX(getVelX() - getVelocity());
}
void Ship::moveRight() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelX(getVelX() + (getVelocity() + BOOST));
	else
		setVelX(getVelX() + getVelocity());
}
int Ship::moveDiagonal() {
	if (getSpeedBoost() && getVelocity() != 0)
		return getVelocity() + BOOST / sqrt(2);

	return getVelocity() / sqrt(2);
}

void Ship::movement() {
	curTime = SDL_GetTicks();

	if (getSpeedBoost() && (curTime > getBoostStartTime() + 2000)) {
		setSpeedBoost(false);
		std::cout << "SPEED BOOST ENDED";
	}

	setX(getX() + getVelX());											// Velocity is 0 if not moving

																		// If the ship went too far to the left or right
	if ((getX() < 0) || ((getX() + getWidth()) > SCREEN_WIDTH)) {
		setX(getX() - getVelX());										// Move back
	}

	setY(getY() + getVelY());											// Move the ship up or down

																		// If the ship went too far up or down
	if ((getY() < 40) || ((getY() + getHeight()) > SCREEN_HEIGHT - 40)) {
		setY(getY() - getVelY());										// Move back
	}

	mCollider.x = getX();												// Only needed once if you check after movement
	mCollider.y = getY();
}

void Ship::gameControllerDPad(SDL_Event& e) {
	if (e.jhat.value == SDL_HAT_UP) {
		resetPreviousDirection();
		moveUp();
		previous = SDL_HAT_UP;
	}
	else if (e.jhat.value == SDL_HAT_DOWN) {
		resetPreviousDirection();
		moveDown();
		previous = SDL_HAT_DOWN;
	}
	else if (e.jhat.value == SDL_HAT_LEFT) {
		resetPreviousDirection();
		moveLeft();
		previous = SDL_HAT_LEFT;
	}
	else if (e.jhat.value == SDL_HAT_RIGHT) {
		resetPreviousDirection();
		moveRight();
		previous = SDL_HAT_RIGHT;
	}
	else if (e.jhat.value == SDL_HAT_RIGHTUP) {
		resetPreviousDirection();
		setVelX(getVelX() + moveDiagonal());
		setVelY(getVelY() - moveDiagonal());
		previous = SDL_HAT_RIGHTUP;
	}
	else if (e.jhat.value == SDL_HAT_RIGHTDOWN) {
		resetPreviousDirection();
		setVelX(getVelX() + moveDiagonal());
		setVelY(getVelY() + moveDiagonal());
		previous = SDL_HAT_RIGHTDOWN;
	}
	else if (e.jhat.value == SDL_HAT_LEFTUP) {
		resetPreviousDirection();
		setVelX(getVelX() - moveDiagonal());
		setVelY(getVelY() - moveDiagonal());
		previous = SDL_HAT_LEFTUP;
	}
	else if (e.jhat.value == SDL_HAT_LEFTDOWN) {
		resetPreviousDirection();
		setVelX(getVelX() - moveDiagonal());
		setVelY(getVelY() + moveDiagonal());
		previous = SDL_HAT_LEFTDOWN;
	}

	if (e.jhat.value == SDL_HAT_CENTERED) {
		resetPreviousDirection();
		previous = SDL_HAT_CENTERED;
	}
}

void Ship::gameControllerButton(SDL_Event& e) {
	if (e.jbutton.button == 0) {
		game1.spawnLaser(getX(), getY(), 2);										// Fire Laser
		std::cout << "Laser Button: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
	}
	if (e.jbutton.button == 1) {
		game1.spawnNinjaStar(getX(), getY(), 2);									// Fire Ninja Star
		std::cout << "Ninja Star Button: " << (int)e.jbutton.button << std::endl;	// shows which button has been pressed
	}
	if (e.jbutton.button == 2) {
		game1.spawnSaw(getX(), getY(), 2);											// Saw Weapon
		std::cout << "Saw Button: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 3) {
		setSpeedBoost(true);														// Speed Boost
		std::cout << "Speed Boost: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 4) {
		game1.musicBack();															// Pick previous track on the list
		std::cout << "Music Back: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 5) {
		game1.musicForward();														// Pick next track on the list
		std::cout << "Music Forward: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
	}
}

void Ship::resetPreviousDirection() {
	if (previous == SDL_HAT_UP) {
		moveDown();
	}
	else if (previous == SDL_HAT_DOWN) {
		moveUp();
	}
	else if (previous == SDL_HAT_LEFT) {
		moveRight();
	}
	else if (previous == SDL_HAT_RIGHT) {
		moveLeft();
	}

	else if (previous == SDL_HAT_RIGHTUP) {
		setVelX(getVelX() - moveDiagonal());
		setVelY(getVelY() + moveDiagonal());
	}
	else if (previous == SDL_HAT_RIGHTDOWN) {
		setVelX(getVelX() - moveDiagonal());
		setVelY(getVelY() - moveDiagonal());
	}
	else if (previous == SDL_HAT_LEFTDOWN) {
		setVelX(getVelX() + moveDiagonal());
		setVelY(getVelY() - moveDiagonal());
	}
	else if (previous == SDL_HAT_LEFTUP) {
		setVelX(getVelX() + moveDiagonal());
		setVelY(getVelY() + moveDiagonal());
	}
}

// Collisiona
SDL_Rect Ship::getCollider() {
	return mCollider;
}
void Ship::setShipColX(int x) {
	mCollider.x = x;
}// end setX
void Ship::setShipColY(int y)
{
	mCollider.y = y;
}// end setY

 // Speed Boost
bool Ship::getSpeedBoost() {
	return mSpeedBoost;
}
unsigned int Ship::getBoostStartTime() {
	return mBoostStartTime;
}
void Ship::setSpeedBoost(bool boost) {
	mSpeedBoost = boost;
	if (boost) {
		mBoostStartTime = SDL_GetTicks();
		std::cout << "SPEED BOOST START" << std::endl;
	}
}

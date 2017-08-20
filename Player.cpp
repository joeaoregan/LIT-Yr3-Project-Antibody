/*
2017-01-04:
Added asdw keyboard movement
*/
#include "Player.h"
#include "Game.h"
#include <math.h>

#define VELOCITY 10
#define BOOST 2
#define MAX_HEALTH 100

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;	// Create a deadzone where input from the controller is ignored

int previous = 0;
int previousStick = 0;

unsigned int curTime;
int VEL;

Game game1;
Player::Player() {
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	setWidth(100);
	setHeight(47);
	setHealth(MAX_HEALTH);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(VELOCITY);
	mCollider.w = getWidth();
	mCollider.h = getHeight();

	setSawActive(false);
	setScore(0);
	setAlive(false);
	setNumLives(3);							// works, game is over when both players lives are <= 0
}

Player::Player(LTexture &dark, LTexture &medium, LTexture &light) {
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	setWidth(100);
	setHeight(47);
	setHealth(MAX_HEALTH);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(VELOCITY);
	mCollider.w = getWidth();
	mCollider.h = getHeight();

	setSawActive(false);
	setScore(0);
	setAlive(false);
	setNumLives(3);							// works, game is over when both players lives are <=

											//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i] = new Particle(getX(), getY(), dark, medium, light);
	}

	drawParticle = true;
}

// 2017/01/22 Separated player render() from game.cpp
void Player::render(LTexture &player, LTexture &dark, LTexture &medium, LTexture &light, LTexture &shimmer, LTexture &lives, SDL_Renderer *rend) {
	if (getAlive()) {																			// 2017/01/22 If the player is alive render the player, with particles
		renderParticles(dark, medium, light, shimmer, rend);
		player.render(getX(), getY(), rend);
	}

	if (getNumLives() > 0)
		lives.render(10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);							// Display the players lives
	if (getNumLives() > 1)
		lives.render(10 + lives.getWidth(), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
	if (getNumLives() > 2)
		lives.render(10 + (lives.getWidth() * 2), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
}
/*

void Player::render(LTexture &texture, LTexture &one, LTexture &two, LTexture &three, LTexture &four, SDL_Renderer *rend) {

	renderParticles(one, two, three, four, rend);					// Show particles on top of dot

	texture.render(getX(), getY(), rend);								// Show the dot 2017-01-20 Moved after, so ship is on top of particles
}
*/


void Player::renderParticles(LTexture &one, LTexture &two, LTexture &three, LTexture &four, SDL_Renderer *rend) {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//Delete and replace dead particles
		if (particles[i]->isDead(getDrawParticle())) {
			delete particles[i];
			particles[i] = new Particle(getX() + 9, getY() + 30, one, two, three);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render(four, rend);
	}
}

bool Player::getDrawParticle() {
	return drawParticle;
}
void Player::setDrawParticle(bool p) {
	drawParticle = p;
}



void Player::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_w: moveUp(); break;
			case SDLK_s: moveDown(); break;
			case SDLK_a: moveLeft(); break;
			case SDLK_d: moveRight(); break;

			// FIRE WEAPON
			case SDLK_SPACE: game1.spawnLaser(getX(), getY(), 1, 20, 1); break;	// TEST NEW WEAPON
			case SDLK_n: game1.spawnNinjaStar(getX(), getY(), 1); break;
			//case SDLK_e: game1.spawnSaw(getX(), getY(), 1, getSawActive()); break;			// 2017/01/17 Saw Weapon added, check saw is active with if statement in spawn Saw, and activate/deactivate the weapon
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
			//case SDLK_r: game1.spawnSaw(getX(), getY(), 2, getSawActive()); break;			// 2017/01/17 Separate saw for player 2
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
void Player::moveUp() {
	if (getSpeedBoost() && getVelocity() != 0)			// If speedboost is active, and the player is moving
		setVelY(getVelY() - (getVelocity() + BOOST));
	else
		setVelY(getVelY() - getVelocity());
}
void Player::moveDown() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelY(getVelY() + (getVelocity() + BOOST));
	else
		setVelY(getVelY() + getVelocity());
}
void Player::moveLeft() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelX(getVelX() - (getVelocity() + BOOST));
	else
		setVelX(getVelX() - getVelocity());
}
void Player::moveRight() {
	if (getSpeedBoost() && getVelocity() != 0)
		setVelX(getVelX() + (getVelocity() + BOOST));
	else
		setVelX(getVelX() + getVelocity());
}
int Player::moveDiagonal() {
	//if (getSpeedBoost() && getVelocity() != 0)
	//	return getVelocity() + BOOST / sqrt(2);

	return getVelocity() / sqrt(2);
}

void Player::movement() {
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

void Player::gameControllerDPad(SDL_Event& e) {
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

void Player::gameControllerButton(SDL_Event& e) {
	if (e.jbutton.button == 0) {
		game1.spawnLaser(getX(), getY(), 2);										// Fire Laser
		std::cout << "Laser Button: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
	}
	if (e.jbutton.button == 1) {
		game1.spawnNinjaStar(getX(), getY(), 2);									// Fire Ninja Star
		std::cout << "Ninja Star Button: " << (int)e.jbutton.button << std::endl;	// shows which button has been pressed
	}
	if (e.jbutton.button == 2) {
		//game1.spawnSaw(getX(), getY(), 2, getSawActive());							// Saw Weapon
		game1.spawnSaw(getX(), getY(), 2);							// Saw Weapon
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

void Player::resetPreviousDirection() {
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
SDL_Rect Player::getCollider() {
	return mCollider;
}
void Player::setShipColX(int x) {
	mCollider.x = x;
}// end setX
void Player::setShipColY(int y)
{
	mCollider.y = y;
}// end setY

// Speed Boost
bool Player::getSpeedBoost() {
	return mSpeedBoost;
}
unsigned int Player::getBoostStartTime() {
	return mBoostStartTime;
}
void Player::setSpeedBoost(bool boost) {
	mSpeedBoost = boost;
	if (boost) {
		mBoostStartTime = SDL_GetTicks();
		std::cout << "SPEED BOOST START" << std::endl;
	}
}




bool Player::getSawActive() {
	return sawActive;
}
void Player::setSawActive(bool active) {
	sawActive = active;
}

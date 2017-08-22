﻿/*
2017-01-04:
Added asdw keyboard movement
*/
#include "Player.h"
#include "Game.h"
#include "WeaponPlSaw.h"
#include "WeaponPlRocket.h"
#include "Particle.h"
#include <math.h>

//Particle partPlayer;

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
WeaponPlRocket rocket;

Player::Player() {
	// Initialize the offsets
	setType(PLAYER);

	setX(0);
	setY(SCREEN_HEIGHT / 2);

	setWidth(100);
	setHeight(47);
	setHealth(MAX_HEALTH);

	// Initialize the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(VELOCITY);
	//setCollider(mCollider);
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setSawActive(false);
	setScore(0);
	setAlive(false);
	setNumLives(3);								// works, game is over when both players lives are <= 0

	createParticle(getX(), getY());	// Initialise particles
	setDrawParticle(true);

	setRocketActive(false);						// Player can spawn a rocket straight away
	setNumRockets(3);							// The number of rockets a player has

	setTimer(ROCKET_TIMER);
	setTimerTracker(0.0);
}

void Player::renderPlayer(Texture &player, SDL_Renderer *rend) {
	std::cout << "PARTICLES renderPlayer 1" << std::endl;

	if (getAlive()) {														// 2017/01/22 If the player is alive render the player, with particles
		renderPlayerParticles(getX(), getY(), true, rend);					// Render the particles 1st

		std::cout << "PARTICLES renderPlayer 2" << std::endl;


		player.render(getX(), getY(), rend);								// Render the player on top of the particles

		//std::cout << "PARTICLES" << std::endl;

		//partPlayer.createParticle(getX(), getY());
		//createParticle(getX(), getY());
	}
}

/*
// 2017/01/22 Separated player render() from game.cpp
void Player::render(Texture &player, SDL_Renderer *rend) {
	//Set texture transparency
	//gDarkBlueParticleTexture.modifyAlpha(100);	// Alpha of 192 gives particles a semi transparent look
	//gMediumBlueParticlTexture.modifyAlpha(100);
	//gLightBlueParticleTexture.modifyAlpha(100);
	//gShimmerTexture.modifyAlpha(150);

	if (getAlive()) {																			// 2017/01/22 If the player is alive render the player, with particles
		//partPlayer.renderParticles(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, rend);
		partPlayer.renderPlayerParticles(getX(), getY(), getDrawParticle(), rend);
		player.render(getX(), getY(), rend);
	}
}

// 2017/01/22 Separated player render() from game.cpp
void Player::render(Texture &player, Texture &dark, Texture &medium, Texture &light, Texture &shimmer, SDL_Renderer *rend) {
	//Set texture transparency
	dark.modifyAlpha(100);	// Alpha of 192 gives particles a semi transparent look
	medium.modifyAlpha(100);
	light.modifyAlpha(100);
	shimmer.modifyAlpha(150);

	if (getAlive()) {																			// 2017/01/22 If the player is alive render the player, with particles
		partPlayer.renderParticles(dark, medium, light, shimmer, rend, getDrawParticle(), getX(), getY());
		player.render(getX(), getY(), rend);
	}
}
*/

void Player::spawnPlayerSaw(int x, int y, int type) {
	game1.spawnSaw(x, y, type);
}

void Player::handleEvent(SDL_Event& e, int player) {
	if (player == PLAYER_1 && getAlive()) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_w: moveUp(); break;
			case SDLK_s: moveDown(); break;
			case SDLK_a: moveLeft(); break;
			case SDLK_d: moveRight(); break;

			// FIRE WEAPON
			case SDLK_SPACE: game1.spawnLaser(getX(), getY(), 1); break;				// TEST NEW WEAPON
			case SDLK_n: game1.spawnNinjaStar(getX(), getY(), 1); break;
			case SDLK_e: game1.spawnSaw(getX(), getY(), SAW1); break;					// 2017/01/17 Saw Weapon added, check saw is active with if statement in spawn Saw, and activate/deactivate the weapon
			case SDLK_f: setSpeedBoost(true);
				game1.infoMessage("Player 1 speed boost activated", PLAYER_1); break;
			case SDLK_c: game1.spawnRocket(getX(), getY(), PLAYER_1, ROCKET_P1, false); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: moveDown(); break;		// undo move up
			case SDLK_s: moveUp(); break;		// undo move down
			case SDLK_a: moveRight(); break;	// undo move left
			case SDLK_d: moveLeft(); break;		// undo move right

			case SDLK_c: game1.spawnRocket(getX(), getY(), PLAYER_1, ROCKET_P1, true); break;
			}
		}
	}
	else if (player == PLAYER_2 && getAlive()) {
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
			case SDLK_r: spawnPlayerSaw(getX(), getY(), SAW2); break;
			case SDLK_g: setSpeedBoost(true);
				game1.infoMessage("Player 2 speed boost activated", PLAYER_2); break;
			case SDLK_v: game1.spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, false); break;
			}
		}
		// If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				if (getVelY() < 0) moveDown(); break;	// only
			case SDLK_DOWN:
				if (getVelY() > 0) moveUp(); break;
			case SDLK_LEFT:
				if (getVelX() < 0) moveRight(); break;
			case SDLK_RIGHT:
				if (getVelX() > 0) moveLeft(); break;
			case SDLK_v: game1.spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, true); break;
			}
		}
		if (SDL_NumJoysticks() > 0) {				// Joystick present
			if (e.type == SDL_JOYBUTTONDOWN) {		// Number of buttons
				gameControllerButton(e);
			}
			else if (e.type == SDL_JOYHATMOTION) {	// Set movement for D-Pad
				gameControllerDPad(e);
			}

			// Fire rocket when button 9 released

			else if (e.type == SDL_JOYBUTTONUP) {		// Number of buttons
				if (e.jbutton.button == 9) {															// Pick next track on the list
					std::cout << "Launch Rocket - Button: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
					game1.spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, true);
				}
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
	//if (getVelY() > 0) setVelY(0);						// If moving down, cancel downward movement
	//setVelY(0);

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

	GameObject::movement();

	// If the ship went too far to the left or right
	if ((getX() < 0) || ((getX() + getWidth()) > SCREEN_WIDTH)) {
		setX(getX() - getVelX());										// Move back
	}

	setY(getY() + getVelY());											// Move the ship up or down

	// If the ship went too far up or down
	if ((getY() < 40) || ((getY() + getHeight()) > SCREEN_HEIGHT_GAME - 40)) {
		setY(getY() - getVelY());										// Move back
	}
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
	else if (e.jhat.value == SDL_HAT_CENTERED) {
		resetPreviousDirection();
		setVelX(0);
		setVelY(0);
		previous = SDL_HAT_CENTERED;
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
		game1.spawnSaw(getX(), getY(), SAW2);										// Saw Weapon
																					// spawnPlayerSaw(getX(), getY(), SAW2);
		std::cout << "Saw Button: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 3) {
		setSpeedBoost(true);														// Speed Boost
		std::cout << "Speed Boost: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
		game1.infoMessage("Player 2 speed boost activated", PLAYER_2);
	}
	if (e.jbutton.button == 4) {
		game1.musicTrackBackward();													// Pick previous track on the list
		std::cout << "Music Back: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 5) {
		game1.musicTrackForward();													// Pick next track on the list
		std::cout << "Music Forward: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
	}
	if (e.jbutton.button == 9) {															// Pick next track on the list
		std::cout << "Enable Rocket - Button: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
		game1.spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, false);
	}
}

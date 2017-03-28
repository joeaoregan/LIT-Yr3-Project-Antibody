/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Player.cpp
	- Description:			cpp file for the Player class.
	- Information:			The Player class handles all the Player ships functionality, including movement, rendering the player ship, 
							and the player lives, player input from keyboard and gamepad, rendering particles for the ship engine, 
							and handling the players weapons. The Player weapons include Laser, Ninja Star, Saw, and Rocket.
	- Log:
		2017/02/27		User game singleton to access renderer
						Fixed player lives not rendering for 1 Player mode in Game class
		2017/02/23		Added option to play as 1 or 2 players
		2017/02/22		Added check to make sure player is alive to dislay speed boost indicator on heads up display
		2017/02/21		Separated heads up display object initialisation to the class for loading textures for player lives
		2017/02/19		Added check to player movement for speed boost
		2017/02/16		Added infoMessage() function to display player messages for player events in Game class
		2017/02/15		Added independent information messages for player 1 and 2 in Game class
						Fixed saw not spawning ...again!
		2017/02/10		Added functionality so the scores displayed on screen move to player who scored them (Changed from moving to players score)
		2017/02/09		Fixed player spawning, player now flashes after spawning, and can't be damaged straight away
		2017/01/30		Moved flashGameObject() functionality into Texture class
						Added particle texture alpha modify functionality
						Combined player weapons to one list instead of lists for each type
		2017/01/25		Fixed error for Player Message Text
						Fixed Ninja Star scoring for Player 2
		2017/01/23		Added laser power up, player can increase the laser weapons grade to fire 3 beams instead of just 1
						Fixed saw spawning, now appearing/disappearing
		2017/01/20		Spawn Player 1 at random Y coord added to spawnPlayer() function
						Added player lives indicators for players
		2017/01/18		Added speed boost
						Added flashing for 2nd player
						Added health bars for players
		2017/01/17		Separated Player 1 and 2 scores
		2017/01/16		Added second player to the game
		2017/01/11		Added flash on collision for player
		2017/01/09		Added playerInput() function to handle input from player
		2017/01/04		Added asdw keyboard movement for player 1
----------------------------------------------------------------------------------------------------------------------*/
#include "Player.h"
#include "Game.h"
#include "WeaponPlSaw.h"
#include "WeaponPlRocket.h"
#include "Audio.h"

#define VELOCITY 10
#define BOOST 5
#define MAX_HEALTH 100

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;	// Create a deadzone where input from the controller is ignored

int previous = 0;
int previousStick = 0;

unsigned int curTime;
int VEL;

//Game game1;
WeaponPlRocket rocket;

//Player::Player() {
Player::Player(int subType) {				// 2017/03/22
	// Initialize the offsets
	setX(0);
	setY(SCREEN_HEIGHT / 2);

	setType(PLAYER);
	setSubType(subType);
	
	if (subType == PLAYER1) {
		setName("Player 1");
	}
	else if (subType == PLAYER2) {
		setName("Player 2");
	}

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

	setShieldActive(true);
	setSawActive(false);
	setScore(0);
	setAlive(false);
	setNumLives(3);							// works, game is over when both players lives are <= 0
	
	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//particles[i] = new Particle(getX(), getY(), gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
		particles[i] = new Particle(getX(), getY());
	}

	setDrawParticle(true);

	setProjectileActive(false);				// Player can spawn a rocket straight away
	setNumRockets(3);						// The number of rockets a player has

	setTimer(ROCKET_TIMER);
	setTimerTracker(0.0);

	setLaserGrade(LASER_SINGLE);
}

// 2017/01/22 Separated player render() from game.cpp
void Player::render(Texture &player) {
	if (getAlive()) {																			// 2017/01/22 If the player is alive render the player, with particles
		renderParticles();
		player.render(getX(), getY());
	}
}

void Player::renderParticles() {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//Delete and replace dead particles
		if (particles[i]->isDead(getDrawParticle())) {
			delete particles[i];
			particles[i] = new Particle(getX() + 9, getY() + 30);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render();
	}
}

void Player::rendPlayerLives(Texture &lives, int player) {
//void Player::rendPlayerLives(Texture &lives, int player, SDL_Renderer *rend) {
	if (player == 1) {
		if (getNumLives() > 0)
			//lives.render(10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(10, 120 - lives.getHeight() - 10);
		if (getNumLives() > 1)
			//lives.render(10 + lives.getWidth(), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(20 + lives.getWidth(), 120 - lives.getHeight() - 10);
		if (getNumLives() > 2)
			//lives.render(10 + (lives.getWidth() * 2), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(30 + (lives.getWidth() * 2), 120 - lives.getHeight() - 10);
	}

	if (player == 2) {
		if (getNumLives() > 0)
			//lives.render(SCREEN_WIDTH - lives.getWidth() - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(SCREEN_WIDTH - lives.getWidth() - 10, 120 - lives.getHeight() - 10);
		if (getNumLives() > 1)
			//lives.render(SCREEN_WIDTH - (lives.getWidth() * 2) - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(SCREEN_WIDTH - (lives.getWidth() * 2) - 20, 120 - lives.getHeight() - 10);
		if (getNumLives() > 2)
			//lives.render(SCREEN_WIDTH - (lives.getWidth() * 3) - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			lives.render(SCREEN_WIDTH - (lives.getWidth() * 3) - 30, 120 - lives.getHeight() - 10);
	}
}

void Player::spawnPlayerSaw(int x, int y, int type) {
	Game::Instance()->spawnSaw(x, y, type);
}

void Player::handleEvent(SDL_Event& e, int player) {
	if (player == PLAYER1 && getAlive()) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_w: moveUp(); break;
			case SDLK_s: moveDown(); break;
			case SDLK_a: moveLeft(); break;
			case SDLK_d: moveRight(); break;

			// FIRE WEAPON
			case SDLK_SPACE: Game::Instance()->spawnLaser(getX(), getY(), PLAYER1, getLaserGrade()); break;				// TEST NEW WEAPON
			case SDLK_n: Game::Instance()->spawnNinjaStar(getX(), getY(), PLAYER1); break;
			case SDLK_e: Game::Instance()->spawnSaw(getX(), getY(), SAW1); break;					// 2017/01/17 Saw Weapon added, check saw is active with if statement in spawn Saw, and activate/deactivate the weapon
			case SDLK_f: setSpeedBoost(true);
				Game::Instance()->infoMessage("Player 1 speed boost activated", PLAYER_1); break;
			case SDLK_c: Game::Instance()->spawnRocket(getX(), getY(), PLAYER_1, ROCKET_P1, false); break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: moveDown(); break;		// undo move up 
			case SDLK_s: moveUp(); break;		// undo move down 
			case SDLK_a: moveRight(); break;	// undo move left 
			case SDLK_d: moveLeft(); break;		// undo move right 

			case SDLK_c: Game::Instance()->spawnRocket(getX(), getY(), PLAYER_1, ROCKET_P1, true); break;
			}
		}
	}
	else if (player == PLAYER2 && getAlive()) {		
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: moveUp(); break;
			case SDLK_DOWN: moveDown(); break;
			case SDLK_LEFT: moveLeft(); break;
			case SDLK_RIGHT: moveRight(); break;

			// FIRE WEAPON SDLK_RCTRL
			//case SDLK_e: game1.spawnLaser(getX(), getY()); break; // SEAN: Press space bar to spawn a new laser
			case SDLK_RCTRL: Game::Instance()->spawnLaser(getX(), getY(), PLAYER2, getLaserGrade()); break;
			case SDLK_RSHIFT: Game::Instance()->spawnNinjaStar(getX(), getY(), PLAYER2); break;
			case SDLK_r: spawnPlayerSaw(getX(), getY(), SAW2); break;
			case SDLK_g: setSpeedBoost(true);
				Game::Instance()->infoMessage("Player 2 speed boost activated", PLAYER_2); break;
			case SDLK_v: Game::Instance()->spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, false); break;
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
			case SDLK_v: Game::Instance()->spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, true); break;
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
					Game::Instance()->spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, true);
				}
			}
		} // joystick present
	}
	else if (player == 3) {

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
	if (getVelY() > 0 && getVelY() < getVelocity()) setVelY(0);
	if (getVelY() < 0 && getVelY() > -getVelocity()) setVelY(0);

	if (getSpeedBoost() && getVelocity() != 0)				// If speedboost is active, and the player is moving
		setVelY(getVelY() - (getVelocity() + BOOST));
	else
		setVelY(getVelY() - getVelocity());
}

void Player::moveDown() {
	if (getVelY() > 0 && getVelY() < getVelocity()) setVelY(0);
	if (getVelY() < 0 && getVelY() > -getVelocity()) setVelY(0);

	if (getSpeedBoost() && getVelocity() != 0)
		setVelY(getVelY() + (getVelocity() + BOOST));
	else
		setVelY(getVelY() + getVelocity());
}
void Player::moveLeft(bool blocked) {
	if (!blocked) {
		if (getVelX() > 0 && getVelX() < getVelocity()) setVelX(0);
		if (getVelX() < 0 && getVelX() > -getVelocity()) setVelX(0);

		if (getSpeedBoost() && getVelocity() != 0)
			setVelX(getVelX() - (getVelocity() + BOOST));
		else
			setVelX(getVelX() - getVelocity());
	}
	else
		setX(getX() + getVelX());
}
void Player::moveRight(bool blocked) {
	if (!blocked) {
		if (getVelX() > 0 && getVelX() < getVelocity()) setVelX(0);
		if (getVelX() < 0 && getVelX() > -getVelocity()) setVelX(0);

		if (getSpeedBoost() && getVelocity() != 0)
			setVelX(getVelX() + (getVelocity() + BOOST));
		else
			setVelX(getVelX() + getVelocity());
	}
}
int Player::moveDiagonal() {
	//if (getSpeedBoost() && getVelocity() != 0)
	//	return getVelocity() + BOOST / sqrt(2);
	
	return getVelocity() / sqrt(2);
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
		Game::Instance()->spawnLaser(getX(), getY(), PLAYER2, getLaserGrade());			// Fire Laser
		std::cout << "Laser Button: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 1) {
		Game::Instance()->spawnNinjaStar(getX(), getY(), 2);							// Fire Ninja Star
		std::cout << "Ninja Star Button: " << (int)e.jbutton.button << std::endl;		// shows which button has been pressed
	}
	if (e.jbutton.button == 2) {
		Game::Instance()->spawnSaw(getX(), getY(), SAW2);								// Saw Weapon
																						// spawnPlayerSaw(getX(), getY(), SAW2);
		std::cout << "Saw Button: " << (int)e.jbutton.button << std::endl;				// shows which button has been pressed
	}
	if (e.jbutton.button == 3) {
		setSpeedBoost(true);															// Speed Boost
		std::cout << "Speed Boost: " << (int)e.jbutton.button << std::endl;				// shows which button has been pressed
		Game::Instance()->infoMessage("Player 2 speed boost activated", PLAYER_2);
	}
	if (e.jbutton.button == 4) {
		Audio::Instance()->musicBackSongName();											// Pick previous track on the list
		std::cout << "Music Back: " << (int)e.jbutton.button << std::endl;				// shows which button has been pressed
	}
	if (e.jbutton.button == 5) {
		Audio::Instance()->musicForwardSongName();										// Pick next track on the list
		std::cout << "Music Forward: " << (int)e.jbutton.button << std::endl;			// shows which button has been pressed
	}
	if (e.jbutton.button == 9) {														// Pick next track on the list
		std::cout << "Enable Rocket - Button: " << (int)e.jbutton.button << std::endl;	// shows which button has been pressed
		Game::Instance()->spawnRocket(getX(), getY(), PLAYER_2, ROCKET_P2, false);
	}
}


//void Player::initialiseRocket(bool active, bool barActive, int timer, int numRockets) {
bool Player::initialiseRocket() {
	setProjectileActive(true);					// Set the rocket active, ready to render to screen
	setRocketBarActive(false);				// Set the rocket power bar inactive
	setTimer(ROCKET_TIMER);					// Reset the rocket timer
	setNumRockets(getNumRockets() - 1);		// decrement the number of rockets

	return true;							// Ready to create a rocket
}

void Player::resetRocket() {
	setProjectileActive(false);
	setRocketBarActive(false);

	setKillRocket(true);
}

void::Player::rocketScore() {
	if (SDL_GetTicks() >= getTimerTracker() + 200) {
		setTimerTracker(SDL_GetTicks());						// start the timer
		setTimer(getTimer() - 0.2);								// Take away 10% of the timer
	}

	setBonusScore(50 - (50.0 * (getTimer() / ROCKET_TIMER)));	// Score increments by 5 (10% of 50)

	setKillRocket(false);										// The rocket can be erased
}

float Player::boostTimer() {
	float boost = getBoostPercent();

	if (getSpeedBoost()) {
		if (SDL_GetTicks() > getLastTime() + 100) {								// Decrement countdown timer
			setLastTime(SDL_GetTicks());

			setBoostPercent(boost - 0.1);
		}
	}
	return boost;
}

void Player::move() {
	curTime = SDL_GetTicks();

	if (getVelY() > 0 && getVelY() < getVelocity()) setVelY(0);
	if (getVelY() < 0 && getVelY() > -getVelocity()) setVelY(0);
	if (getVelX() > 0 && getVelX() < getVelocity()) setVelX(0);
	if (getVelX() < 0 && getVelX() > -getVelocity()) setVelX(0);

	if (getSpeedBoost() && (curTime > getBoostStartTime() + ROCKET_TIMER * 1000)) {
		setSpeedBoost(false);
		setBoostPercent(ROCKET_TIMER);
		std::cout << "SPEED BOOST ENDED";
	}

	GameObject::move();

	// If the ship went too far to the left or right
	if ((getX() < 0) || ((getX() + getWidth()) > SCREEN_WIDTH)) {
		setX(getX() - getVelX());										// Move back
	}

	//setY(getY() + getVelY());											// Move the ship up or down

																		// If the ship went too far up or down
	if ((getY() < 40) || ((getY() + getHeight()) > SCREEN_HEIGHT_GAME - 40)) {
		setY(getY() - getVelY());										// Move back
	}
}
/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Player.h
	- Description:			header file for the Player class.
	- Information:			Contains all function definitions and variables for Player class.
							The Player ship that will move around on the screen
	- Log:
		2017/02/27			User game singleton to access renderer
		2017/01/25			Changed player max y value to 600 - 40
		2017/01/04			Fixed dimensions of ship
		2017/01/09			Moved functionality common to game objects to GameObjects class reducing the code
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Texture.h"
#include "Particle.h"

// The Player ship that will move around on the screen

/* 
	2017/02/27:	User game singleton to access renderer
	2017/01/25 Changed player max y value to 600 - 40 (
	2017/01/04: Fixed dimensions of ship
	2017/01/09: Moved functionality common to game objects to GameObjects class reducing the code
*/

const int TOTAL_PARTICLES = 20;	// Particle count

class Player : public GameObject {
public:
	//Player();								// Initializes the variables
	Player(int subType = PLAYER1);			// Initializes the variables // 2017/03/22 Added subtype

	Particle* particles[TOTAL_PARTICLES];	// The particles
	bool getDrawParticle() { return drawParticle; }
	void setDrawParticle(bool p) { drawParticle = p; }

	void rendPlayerLives(Texture &lives, int player);
	void render(Texture &player);
	void renderParticles();

	void spawnPlayerSaw(int x, int y, int type);
	
	//void handleEvent(SDL_Event& e);
	void handleEvent(SDL_Event& e, int player);	// Takes key presses and adjusts the ship's velocity
	virtual void move();					// Moves the ship	
	void gameControllerDPad(SDL_Event& e);
	void gameControllerButton(SDL_Event& e);
	void resetPreviousDirection();

	float boostTimer();

	// Movement
	void moveUp();
	void moveDown();
	void moveLeft(bool blocked = false);
	void moveRight(bool blocked = false);
	int moveDiagonal();

	virtual void destroy() {};

	bool initialiseRocket();	// 2017/02/19 Move rocket reset parameters here
	void resetRocket();			// 2017/02/19 Reset the player rocket and rocket power bar
	void rocketScore();			// 2017/02/19 set the timer and score for the rocket

private:
	bool drawParticle;
};

#endif

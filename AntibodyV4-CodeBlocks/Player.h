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
	//Player();											// Initializes the variables
	Player(int subType = PLAYER1);						// Initializes the variables // 2017/03/22 Added subtype

	Particle* particles[TOTAL_PARTICLES];				// Array of particles to render for Player Ship engine

	/* METHODS */

	virtual void move();								// Moves the ship	
	virtual void destroy() {							// Destroy / re-spawn the Player Ship
	// If an obstacle knocks a player off screen or out of bounds, respawn
		if (getX() < 0) {
			Game::Instance()->spawnPlayer(getSubType());				// If the player is off screen even one pixel, respawn and subtract from health 2017/03/26 Moved from Game class
			Game::Instance()->managePlayerHealth(getSubType(), 25);		// Subtract 25 from the players health 2017/03/26 Moved from Game class
		}
	};
	void render(Texture &player);						// Render the Player


	bool getDrawParticle() { return drawParticle; }		// Draw Particles or not
	void setDrawParticle(bool p) { drawParticle = p; }	// Set OK to draw particles or not

	void rendPlayerLives(Texture &lives, int player);	// Render lives for the Player
	void renderParticles();								// Render the Player's ship's particles

	void spawnPlayerSaw(int x, int y, int type);		// Spawn / hide the Player ship's Saw weapon
	
	//void handleEvent(SDL_Event& e);
	void handleEvent(SDL_Event& e, int player);			// Takes key presses and adjusts the ship's velocity
	void gameControllerDPad(SDL_Event& e);				// Contoller direction pad events
	void gameControllerButton(SDL_Event& e);			// Controller button events
	void resetPreviousDirection();						// Reset the previous the direction the player moved in

	float boostTimer();									// The Player ship speed boost timer

	// Movement
	void moveUp();										// Move the Player Ship up
	void moveDown();									// Move the Player Ship down
	void moveLeft(bool blocked = false);				// Move the Player Ship left
	void moveRight(bool blocked = false);				// Move the Player Ship right
	int moveDiagonal();									// Move the Player Ship diagonally (different amount)


	bool initialiseRocket();	// Setup a rocket, ready to fire 2017/02/19 Move rocket reset parameters here
	void resetRocket();			// 2017/02/19 Reset the player rocket and rocket power bar
	void rocketScore();			// 2017/02/19 Set the timer and score for the rocket

private:
	bool drawParticle;			// Decide to draw the particles or not
};

#endif

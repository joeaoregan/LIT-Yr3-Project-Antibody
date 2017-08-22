#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Texture.h"
#include "Particle.h"

// The Player ship that will move around on the screen

/* 
	2017/02/27:	User game singleton to access renderer
	2017-01-04: Fixed dimensions of ship
	2017/01/09: JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/

const int TOTAL_PARTICLES = 20;	// Particle count


class Player : public GameObject {
public:				
	Player();								// Initializes the variables
	//Player(Texture &dark, Texture &medium, Texture &light);				// 2017/01/20 Particles

	// Particles
	Texture gDarkBlueParticleTexture;		// Dark blue engine particle
	Texture gMediumBlueParticlTexture;		// Medium blue engine particle
	Texture gLightBlueParticleTexture;		// Light blue engine particle
	Texture gShimmerTexture;				// Shimmer engine particle

	Particle* particles[TOTAL_PARTICLES];	// The particles

	/*
	void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend);
	void render(Texture &player, SDL_Renderer *rend);
	void render();							// Shows the ship on the screen
	void render(Texture &player, Texture &dark, Texture &medium, Texture &light, Texture &shimmer, SDL_Renderer *rend);	// Shows the ship with particles on the screen
	void rendPlayerLives(Texture &lives, int player, SDL_Renderer *rend);
	*/
	void rendPlayerLives(Texture &lives, int player);
	void render(Texture &player);
	void render(Texture &player, Texture &dark, Texture &medium, Texture &light, Texture &shimmer);	// Shows the ship with particles on the screen
	void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four);

	void spawnPlayerSaw(int x, int y, int type);

	//bool loadMediaPlayer(SDL_Renderer *rend);
	bool loadMediaPlayer();
	void closePlayer();

	//void handleEvent(SDL_Event& e);
	void handleEvent(SDL_Event& e, int player);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();					// Moves the ship	
	void gameControllerDPad(SDL_Event& e);
	void gameControllerButton(SDL_Event& e);
	void resetPreviousDirection();

	float boostTimer();

	// Movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int moveDiagonal();

	//void initialiseRocket(bool active, bool barActive, int timer, int numRockets);	// 2017/02/19 Move rocket reset parameters here
	bool initialiseRocket();	// 2017/02/19 Move rocket reset parameters here
	void resetRocket();			// 2017/02/19 Reset the player rocket and rocket power bar
	void rocketScore();			// 2017/02/19 set the timer and score for the rocket
};

#endif

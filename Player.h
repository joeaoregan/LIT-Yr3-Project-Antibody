#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Texture.h"
//#include "Particle.h"

// The Player ship that will move around on the screen

/* 
2017-01-04:
Fixed dimensions of ship
*/
/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/

class Player : public GameObject {
public:				
	Player();							// Initializes the variables
	//Player(Texture &dark, Texture &medium, Texture &light);				// 2017/01/20 Particles
	
	void spawnPlayerSaw(int x, int y, int type);

	//bool loadMediaPlayer(SDL_Renderer *rend);
	//void closePlayer();
	virtual void renderPlayer(Texture &player, SDL_Renderer *rend);

	//void handleEvent(SDL_Event& e);
	virtual void handleEvent(SDL_Event& e, int player);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();			// Moves the ship	
	void gameControllerDPad(SDL_Event& e);
	void gameControllerButton(SDL_Event& e);
	void resetPreviousDirection();


	// Movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int moveDiagonal();
	
	//void render(Texture &player, Texture &dark, Texture &medium, Texture &light, Texture &shimmer, SDL_Renderer *rend);	// Shows the ship with particles on the screen

private:
	//bool mSpeedBoost;
	//unsigned int mBoostStartTime;

	//Particle* particles[TOTAL_PARTICLES];	// The particles

	//void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend);

};

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Particle.h"

// The Player ship that will move around on the screen

/* 
2017-01-04:
Fixed dimensions of ship
*/
/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/

const int TOTAL_PARTICLES = 20;	// Particle count


class Player : public GameObject {
public:				
	Player();							// Initializes the variables
	Player(LTexture &dark, LTexture &medium, LTexture &light);				// 2017/01/20 Particles

	SDL_Rect mCollider;				// Players Hit Box

	//void handleEvent(SDL_Event& e);
	void handleEvent(SDL_Event& e, int player);	// Takes key presses and adjusts the ship's velocity
	virtual void movement();		// Moves the ship	
	//void render();					// Shows the ship on the screen
	void gameControllerDPad(SDL_Event& e);
	void gameControllerButton(SDL_Event& e);
	void resetPreviousDirection();

	// Speed boost
	bool getSpeedBoost();
	unsigned int getBoostStartTime();
	void setSpeedBoost(bool boost);

	// Movement
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int moveDiagonal();

	SDL_Rect getCollider();
	void setShipColX(int x);					// get the ships X position
	void setShipColY(int y);					// get the ships Y position
	
	// Saw
	bool getSawActive();
	void setSawActive(bool active);
	bool sawActive;

	// Laser
	int getLaserGrade();
	void setLaserGrade(int grade);

	void render(LTexture &player, LTexture &dark, LTexture &medium, LTexture &light, LTexture &shimmer, SDL_Renderer *rend);
	void rendPlayerLives(LTexture &lives, int player, SDL_Renderer *rend);
	//void render(LTexture &texture, LTexture &one, LTexture &two, LTexture &three, LTexture &four, SDL_Renderer *rend);	// Shows the ship with particles on the screen
	bool getDrawParticle();
	void setDrawParticle(bool p);

private:
	bool mSpeedBoost;
	unsigned int mBoostStartTime;

	Particle* particles[TOTAL_PARTICLES];	// The particles

	void renderParticles(LTexture &one, LTexture &two, LTexture &three, LTexture &four, SDL_Renderer *rend);

	bool drawParticle;

	int mLaserGrade;
};

#endif

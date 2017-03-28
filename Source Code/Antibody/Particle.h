/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Particle.h
	- Description:			header file for the particle class.
	- Information:			Contains all function definitions and variables for particle class.
							Class for handling particles for the ship engine
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef PARTICLE_H
#define PARTICLE_H
#include "Texture.h"

class Particle {
public:
	Texture gShimmer, one, two, three, four, five, six;						// Type of particle

	Particle() {};
	Particle(int x, int y, int type = 0);
	Particle(int x, int y, Texture &one, Texture &two, Texture &three);		// Constructor: Initialize position and animation
	
	void render();															// Shows the particle

	bool isDead(bool drawParticle);											// Checks if particle is dead, 2017/01/20 Doesn't draw a trail if moving left
	
	void initPlayerEngine(int x, int y);
	void initRocketTrail(int x, int y);
	//void renderParticles(int x, int y, bool drawParticle);
	bool initParticle();
	void closeParticle();

private:
	int mPosX, mPosY;														// Offsets

	int mFrame;																// Current frame of animation

	Texture *mTexture;														// Type of particle
};

#endif
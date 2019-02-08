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

	Particle(int x = 0, int y = 0, int type = 0);							// Constructor
	Particle(int x, int y, Texture &one, Texture &two, Texture &three);		// Constructor: Initialize position and animation
	
	void render();															// Render the particle textures to screen

	bool isDead(bool drawParticle);											// Checks if particle is dead, 2017/01/20 Doesn't draw a trail if moving left
	
	void initPlayerEngine(int x, int y);									// Set up particles for the Players ship engine
	void initRocketTrail(int x, int y);										// Set up particles for the Players rocket weapon

	bool initParticle();													// Load media for Particles
	void closeParticle();													// Free media for Particles from memory

	//void renderParticles(int x, int y, bool drawParticle);

private:
	int mPosX, mPosY;														// Offsets

	int mFrame;																// Current frame of animation

	Texture *mTexture;														// Particle Texture
};

#endif
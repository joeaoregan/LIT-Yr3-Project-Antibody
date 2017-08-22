#ifndef PARTICLE_H
#define PARTICLE_H
#include "Texture.h"

class Particle {
public:
	Particle(int x, int y, Texture &one, Texture &two, Texture &three);		// Constructor: Initialize position and animation

	void render(Texture &texture);						// Shows the particle

	bool isDead(bool drawParticle);											// Checks if particle is dead, 2017/01/20 Doesn't draw a trail if moving left

private:
	int mPosX, mPosY;			// Offsets

	int mFrame;					// Current frame of animation

	Texture *mTexture;			// Type of particle
};

#endif
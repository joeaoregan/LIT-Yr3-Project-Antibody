#ifndef PARTICLE_H
#define PARTICLE_H
#include "LTexture.h"

class Particle {
public:
	Particle(int x, int y, LTexture &one, LTexture &two, LTexture &three);		// Constructor: Initialize position and animation

	void render(LTexture &texture, SDL_Renderer *rend);				// Shows the particle

	bool isDead(bool drawParticle);				// Checks if particle is dead, 2017/01/20 Doesn't draw a trail if moving left

private:
	int mPosX, mPosY;			// Offsets

	int mFrame;					// Current frame of animation

	LTexture *mTexture;			// Type of particle
};

#endif
#ifndef PARTICLE_H
#define PARTICLE_H
#include "Texture.h"

const int TOTAL_PARTICLES = 20;	// Particle count

class Particle {
public:
	//Particle(int x = 0, int y = 0);
	Particle(int x, int y, Texture &one, Texture &two, Texture &three);		// Constructor: Initialize position and animation

	~Particle() {};
	/*
	// Particles
	Texture gDarkBlueParticleTexture;	// Dark blue engine particle
	Texture gMediumBlueParticlTexture;	// Medium blue engine particle
	Texture gLightBlueParticleTexture;	// Light blue engine particle
	Texture gShimmerTexture;			// Shimmer engine particle

	// 2017/02/18 Moved from player class (via gameobject)
	bool loadMediaParticles(SDL_Renderer *rend);

	void closeParticle();
	*/
	//void createParticle(int x, int y);

	//void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y);

	//void renderParticles(Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y);

	//void renderPlayerParticles(int x, int y, bool drawParticle, SDL_Renderer *rend);	// 2017/02/18

	void render(Texture &texture, SDL_Renderer *rend);						// Shows the particle

	bool isDead(bool drawParticle);											// Checks if particle is dead, 2017/01/20 Doesn't draw a trail if moving left

private:
	int mPosX, mPosY;						// Offsets

	int mFrame;								// Current frame of animation

	Texture *mTexture;						// Type of particle



	//Particle* particles[TOTAL_PARTICLES];	// The particles array
};

#endif
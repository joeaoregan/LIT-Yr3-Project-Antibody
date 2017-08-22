#include "Particle.h"
#include "Texture.h"
#include <iostream>
/*
Particle::Particle(int x, int y) {
	//Set offsets
	mPosX = x - 5 + (rand() % 10);		// CHANGE TO SET SIZE BIGGER / SMALLER
	mPosY = y - 5 + (rand() % 7);

	mFrame = rand() % 5;				// Initialize animation

	// Set type
	switch (rand() % 3) {
	case 0: mTexture = &gDarkBlueParticleTexture; break;
	case 1: mTexture = &gMediumBlueParticlTexture; break;
	case 2: mTexture = &gLightBlueParticleTexture; break;
	}
}
*/

Particle::Particle(int x, int y, Texture &one, Texture &two, Texture &three) {
	//Set offsets
	mPosX = x - 5 + (rand() % 10);		// CHANGE TO SET SIZE BIGGER / SMALLER
	mPosY = y - 5 + (rand() % 7);

	mFrame = rand() % 5;				// Initialize animation

	// Set type
	switch (rand() % 3) {
	case 0: mTexture = &one; break;
	case 1: mTexture = &two; break;
	case 2: mTexture = &three; break;
	}
}

/*
void Particle::createParticle(int x, int y) {
	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//particles[i] = new Particle(x, y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
		particles[i] = new Particle(x, y);
	}
}
*/

/* render our texture selected in the constructor
and then every other frame we render a semitransparent shimmer texture over it
to make it look like the particle is shining. We then update the frame of
animation.
*/
void Particle::render(Texture &texture, SDL_Renderer *rend) {	
	mTexture->render(mPosX, mPosY, rend);				//Show image

	//Show shimmer
	if (mFrame % 3 == 0) {
		texture.render(mPosX, mPosY, rend);
	}

	mFrame++;	// Animate
}

bool Particle::isDead(bool drawParticle) {
	if (drawParticle)
		return mFrame > 2;		// Mark as dead after 3 frames			CHANGE TO MAKE SHORTER TRAIL
	else
		return mFrame > 0;
}

/*
bool Particle::loadMediaParticles(SDL_Renderer *rend) {
	bool success = true;
	// Particles	
	if (!gDarkBlueParticleTexture.loadFromFile("Art/particleDarkBlue.bmp", rend)) {	// Load Dark Particle texture
		printf("Failed to load red texture!\n");
		success = false;
	}
	if (!gMediumBlueParticlTexture.loadFromFile("Art/particleMediumBlue.bmp", rend)) {	// Load Medium Particle texture
		printf("Failed to load green texture!\n");
		success = false;
	}
	if (!gLightBlueParticleTexture.loadFromFile("Art/particleLightBlue.bmp", rend)) {	// Load Light Particle texture
		printf("Failed to load blue texture!\n");
		success = false;
	}
	if (!gShimmerTexture.loadFromFile("Art/shimmer.bmp", rend)) {						// Load shimmer texture
		printf("Failed to load shimmer texture!\n");
		success = false;
	}

	gDarkBlueParticleTexture.modifyAlpha(100);	// Alpha of 192 gives particles a semi transparent look
	gMediumBlueParticlTexture.modifyAlpha(100);
	gLightBlueParticleTexture.modifyAlpha(100);
	gShimmerTexture.modifyAlpha(150);

	return success;
}

void Particle::closeParticle() {
	// Particles
	gDarkBlueParticleTexture.free();
	gMediumBlueParticlTexture.free();
	gLightBlueParticleTexture.free();
	gShimmerTexture.free();
}


void Particle::renderPlayerParticles(int x, int y, bool drawParticle, SDL_Renderer *rend) {

	//std::cout << "PARTICLES 1" << std::endl;

	//gDarkBlueParticleTexture.render(100, 100, rend);
	//gDarkBlueParticleTexture.render(110, 100, rend);
	//gDarkBlueParticleTexture.render(120, 100, rend);
	//gDarkBlueParticleTexture.render(130, 100, rend);

	gDarkBlueParticleTexture.modifyAlpha(100);	// Alpha of 192 gives particles a semi transparent look
	gMediumBlueParticlTexture.modifyAlpha(100);
	gLightBlueParticleTexture.modifyAlpha(100);
	gShimmerTexture.modifyAlpha(150);

	//std::cout << "PARTICLES 2" << std::endl;

	createParticle(x, y);

	//std::cout << "PARTICLES 3" << std::endl;

	//renderParticles(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, rend, drawParticle, x + 9, y + 30);
	renderParticles(gShimmerTexture, rend, drawParticle, x, y);
	//std::cout << "PARTICLES 4" << std::endl;
}

//void Particle::renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y) {
void Particle::renderParticles(Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y) {

	//four.render(100, 100, rend);

	//std::cout << "PARTICLES 5" << std::endl;
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		if (particles[i]->isDead(drawParticle)) {
			delete particles[i];										// Delete dead particles
			//particles[i] = new Particle(x, y, one, two, three);			// Then replace them
			particles[i] = new Particle(x, y);			// Then replace them
		}
	}
	//std::cout << "PARTICLES 6" << std::endl;

	// Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render(four, rend);
	}
	//std::cout << "PARTICLES 7" << std::endl;
}
*/

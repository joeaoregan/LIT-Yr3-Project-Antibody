#include "Particle.h"
#include "Texture.h"

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

void Particle::renderPlayerParticles(int x, int y, SDL_Renderer *rend, bool draw) {
	gDarkBlueParticleTexture.modifyAlpha(100);	// Alpha of 192 gives particles a semi transparent look
	gMediumBlueParticlTexture.modifyAlpha(100);
	gLightBlueParticleTexture.modifyAlpha(100);
	gShimmerTexture.modifyAlpha(150);

	renderParticles(x, y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, rend, draw);
}

void Particle::renderParticles(int x, int y, Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend, bool draw) {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//Delete and replace dead particles
		if (particles[i]->isDead(draw)) {
			delete particles[i];
			particles[i] = new Particle(x + 9, y + 30, one, two, three);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render(four, rend);
	}
}

void Particle::initParticle(int x, int y) {
	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i] = new Particle(x, y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
	}
}

bool Particle::loadMediaPlayer(SDL_Renderer *rend) {
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

	return success;
}

void Particle::closePlayer() {
	// Particles
	gDarkBlueParticleTexture.free();
	gMediumBlueParticlTexture.free();
	gLightBlueParticleTexture.free();
	gShimmerTexture.free();
}

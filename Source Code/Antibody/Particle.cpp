/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Particle.cpp
	- Description:			cpp file for the particle class.
	- Information:			The particle class handles the functionality for displaying the engine particles
							for the players ships. A random number of aparticles is drawn to the screen each
							frame. A random number pool is used to create the effect of the particles.
	- Log:
		2017/01/30		Added particle texture alpha modify functionality
		2017/01/20		Class for handling particles for the ship engine
	----------------------------------------------------------------------------------------------------------------------*/
#include "Particle.h"
#include "Texture.h"

Particle::Particle(int x, int y, Texture &one, Texture &two, Texture &three) {
	//Set offsets
	mPosX = x - 5 + (rand() % 10);								// CHANGE TO SET SIZE BIGGER / SMALLER
	mPosY = y - 5 + (rand() % 7);

	mFrame = rand() % 5;										// Initialize animation

																// Set type
	switch (rand() % 3) {
	case 0: mTexture = &one; break;
	case 1: mTexture = &two; break;
	case 2: mTexture = &three; break;
	}
}

bool Particle::initParticle() {
	bool success = true; 
	
	if (!one.loadFromFile("Art/particleDarkBlue.bmp")) {		// Load Dark Particle texture
		printf("Failed to load darkblue texture!\n");
		success = false;
	}
	//if (!Texture::Instance()->load("Art/particleMediumBlue.bmp", "mediumBlueParticleID")) {
	if (!two.loadFromFile("Art/particleMediumBlue.bmp")) {		// Load Medium Particle texture
		printf("Failed to load medium blue texture!\n");
		success = false;
	}
	if (!three.loadFromFile("Art/particleLightBlue.bmp")) {		// Load Medium Particle texture
		printf("Failed to load light blue texture!\n");
		success = false;
	}
	if (!four.loadFromFile("Art/particleRed.bmp")) {			// Load Dark Particle texture
		printf("Failed to load red texture!\n");
		success = false;
	}
	//if (!Texture::Instance()->load("Art/particleMediumBlue.bmp", "mediumBlueParticleID")) {
	if (!five.loadFromFile("Art/particleOrange.bmp")) {			// Load Medium Particle texture
		printf("Failed to load orange texture!\n");
		success = false;
	}
	if (!six.loadFromFile("Art/particleGrey.bmp")) {			// Load Medium Particle texture
		printf("Failed to load grey texture!\n");
		success = false;
	}

	return success;
}

void Particle::closeParticle() {
	one.free();
	two.free();
	three.free();
	four.free();
	five.free();
	six.free();
}

void Particle::initPlayerEngine(int x, int y) {
	//Set offsets
	mPosX = x - 5 + (rand() % 10);								// CHANGE TO SET SIZE BIGGER / SMALLER
	mPosY = y - 5 + (rand() % 7);
}

void Particle::initRocketTrail(int x, int y) {

	//Set offsets
	mPosX = x - 5 + (rand() % 15);								// CHANGE TO SET SIZE BIGGER / SMALLER
	mPosY = y - 5 + (rand() % 8);
}

Particle::Particle(int x, int y, int type) {
	mFrame = rand() % 5;										// Initialize animation

	if (type == 0) {
		//Set offsets
		mPosX = x - 5 + (rand() % 10);							// CHANGE TO SET SIZE BIGGER / SMALLER
		mPosY = y - 5 + (rand() % 7);

		// Set type
		switch (rand() % 3) {
		case 0: mTexture = &one; break;
		case 1: mTexture = &two; break;
		case 2: mTexture = &three; break;
		}
	}
	else {
		//Set offsets
		mPosX = x - 5 + (rand() % 15);							// CHANGE TO SET SIZE BIGGER / SMALLER
		mPosY = y - 5 + (rand() % 8);

		// Set type
		switch (rand() % 3) {
		case 0: mTexture = &four; break;
		case 1: mTexture = &five; break;
		case 2: mTexture = &six; break;
		}
	}
}

/*
 Name: render()
 Role: render our texture selected in the constructor
 and then every other frame we render a semitransparent shimmer texture over it
 to make it look like the particle is shining. We then update the frame of
 animation.
*/
void Particle::render() {

	if (!gShimmer.loadFromFile("Art/shimmer.bmp")) {						// Load shimmer texture
		printf("Failed to load shimmer texture!\n");
		//success = false;
	}

	mTexture->render(mPosX, mPosY);											//Show image

																			//Show shimmer
	if (mFrame % 3 == 0) {
		gShimmer.render(mPosX, mPosY);
	}

	mFrame++;	// Animate
}

bool Particle::isDead(bool drawParticle) {
	if (drawParticle)
		return mFrame > 2;													// Mark as dead after 3 frames
	else
		return mFrame > 0;
}
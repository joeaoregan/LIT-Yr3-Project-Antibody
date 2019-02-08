#include "Particle.h"
#include "Texture.h"

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

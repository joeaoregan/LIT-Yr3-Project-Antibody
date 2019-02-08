#include "Player.h"

Player::Player(Texture &dark, Texture &medium, Texture &light) {
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	player = 1;

	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i] = new Particle(mPosX, mPosY, dark, medium, light);
	}

	drawParticle = true;
}

Player::~Player() {
	//Delete particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		delete particles[i];
	}
}

void Player::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_UP: mVelY -= PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_DOWN: mVelY += PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_LEFT: mVelX -= PLAYER_VELOCITY; setDrawParticle(false); break;
			case SDLK_RIGHT: mVelX += PLAYER_VELOCITY; setDrawParticle(true); break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_UP: mVelY += PLAYER_VELOCITY; break;
			case SDLK_DOWN: mVelY -= PLAYER_VELOCITY; break;
			case SDLK_LEFT: mVelX += PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_RIGHT: mVelX -= PLAYER_VELOCITY; break;
			}
		}
	}
	else {
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: mVelY -= PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_s: mVelY += PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_a: mVelX -= PLAYER_VELOCITY; setDrawParticle(false); break;
			case SDLK_d: mVelX += PLAYER_VELOCITY; setDrawParticle(true); break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_w: mVelY += PLAYER_VELOCITY; break;
			case SDLK_s: mVelY -= PLAYER_VELOCITY; break;
			case SDLK_a: mVelX += PLAYER_VELOCITY; setDrawParticle(true); break;
			case SDLK_d: mVelX -= PLAYER_VELOCITY; break;
			}
		}
	}
}

void Player::move() {
	mPosX += mVelX;	//Move the Player left or right

	//If the Player went too far to the left or right
	//if ((mPosX < 0) || (mPosX  > SCREEN_WIDTH - Player_WIDTH - 150)) {
	if ((mPosX < 0) || (mPosX  > 640)) {					// match up to background width, to factor in distance players have travelled on map
															//Move back
		mPosX -= mVelX;
	}

	mPosY += mVelY;	//Move the Player up or down

	//If the Player went too far up or down
	if (getPlayer() == 1) {
		if ((mPosY < 0) || (mPosY + PLAYER_HEIGHT >(SCREEN_HEIGHT_GAME / 2))) {
			//Move back
			mPosY -= mVelY;
		}
	}
	else {
		if ((mPosY < (SCREEN_HEIGHT_GAME / 2)) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT_GAME)) {
			//Move back
			mPosY -= mVelY;
		}
	}
}

void Player::render(Texture &texture, Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend) {

	renderParticles(one, two, three, four, rend);					// Show particles on top of Player

	texture.render(mPosX, mPosY, rend);								// Show the Player 2017-01-20 Moved after, so ship is on top of particles
}

void Player::renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend) {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//Delete and replace dead particles
		if (particles[i]->isDead(getDrawParticle())) {
			delete particles[i];
			particles[i] = new Particle(mPosX + 9, mPosY + 30, one, two, three);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render(four, rend);
	}
}

bool Player::getDrawParticle() {
	return drawParticle;
}
void Player::setDrawParticle(bool p) {
	drawParticle = p;
}
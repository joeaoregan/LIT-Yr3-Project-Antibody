#include "GameObject.h"
#include <math.h>

// Constructor
//GameObject::GameObject(int damage) :	// Constructor has default value for damage of 3
//	m_Damage(damage)
//{}
GameObject::GameObject() {
	m_x = 0;
	m_y = 0;
	m_xVel = 0;
	m_yVel = 0;

	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//particles[i] = new Particle(m_x, m_y);
		particles[i] = new Particle(m_x, m_y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
	}
}
// Deconstructors
GameObject::~GameObject() {
	//std::cout << "GameObject deconstructor" << std::endl;
	//Delete particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		delete particles[i];
	}
}

// Render the Game Objects to the screen
void GameObject::render(Texture &texture, SDL_Renderer *rend, int degrees) {
	texture.render(getX(), getY(), rend, NULL, degrees, NULL, SDL_FLIP_NONE);
}

void GameObject::render(Texture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &currentframe, int frames) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend, currentClip);

	++currentframe;						// Go to next frame

	if (currentframe >= frames * 10) {	// Cycle animation
		currentframe = 0;
	}
}

void GameObject::spawn(int x, int y, int vx, int vy) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
	setAlive(true);
}

void GameObject::spawn(int x, int y, int vx, SDL_Rect* collider) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vx;	// 2017-01-10 JOE: use same velocity for x and y
//	m_Collider = collider;
	setCollider((*collider));
}

void GameObject::spawn(int x, int y, int vx, int vy, SDL_Rect* collider, int type) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
//	m_Collider = collider;
	setCollider((*collider));
	m_SubType = type;
	setAlive(true);
}


void GameObject::movement() {
	m_x += m_xVel;
	//m_y += m_yVel;

	setColliderX(getX());
	setColliderY(getY());

	// Destroy Game Object moving off screen on Y axis
	if (getY() <= 40) setAlive(false);								// Once it reaches the pink border
	else if (getY() >= (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	else setAlive(true);

	// Destroy Game Object moving off screen on X axis
	if ((getX() > SCREEN_WIDTH && getVelX() > 0)) setAlive(false);	// 2017/02/08 Need to check if velocity is negative, or power ups & blood cells don't appear on screen
	else if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}

void GameObject::movement(int centerX, int centerY, float timer) {
	if (centerX < SCREEN_WIDTH) {
		rotateCounter %= 360;
		if (timer != 0.5) {
			setX(70 * cos(rotateCounter * 3.1415926f / 180.0f) + centerX);		// rotate the bullet object
			setY(70 * sin(rotateCounter * 3.1415926f / 180.0f) + centerY);

			rotateCounter += 3;
		}
		else
			movement();					// Fire the satellite bullet object
	}
}

void GameObject::setHealth(int h) {
	if (h < 0) {
		m_Health = 0;				// If health is less than 0 set 0
		setAlive(false);			// set the Game object as not alive
	}
	else if (h > 100)
		m_Health = 100;
	else
		m_Health = h;
}


void GameObject::spawn(int x, int y, SDL_Rect* collider, int player, int type) {
	setX(x + 57);
	setY(y + 13);
	setVelX(getVelocity());
	setVelY(0);
//	setCollider(collider);
	setCollider((*collider));
	setPlayer(player);
	setSubType(type);
}

// 2017/02/18 Moved from player
void GameObject::setSpeedBoost(bool boost) {
	mSpeedBoost = boost;
	if (boost) {
		mBoostStartTime = SDL_GetTicks();
		std::cout << "SPEED BOOST START" << std::endl;
	}
}


// 2017/02/18 Moved to particle class
bool GameObject::loadMediaPlayer(SDL_Renderer *rend) {
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

void GameObject::closePlayer() {
	// Particles
	gDarkBlueParticleTexture.free();
	gMediumBlueParticlTexture.free();
	gLightBlueParticleTexture.free();
	gShimmerTexture.free();
}

/*
void GameObject::rendPlayerLives(int lives, Texture &texture, int player, SDL_Renderer *rend) {
	if (player == 1) {
		if (lives > 0)
			//lives.render(10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(10, 120 - texture.getHeight() - 10, rend);
		if (lives > 1)
			//lives.render(10 + lives.getWidth(), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(20 + texture.getWidth(), 120 - texture.getHeight() - 10, rend);
		if (lives > 2)
			//lives.render(10 + (lives.getWidth() * 2), SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(30 + (texture.getWidth() * 2), 120 - texture.getHeight() - 10, rend);
	}
	// Texture Has Different Coordinates Depending on the player
	if (player == 2) {
		if (lives > 0)
			//lives.render(SCREEN_WIDTH - lives.getWidth() - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(SCREEN_WIDTH - texture.getWidth() - 10, 120 - texture.getHeight() - 10, rend);
		if (lives > 1)
			//lives.render(SCREEN_WIDTH - (lives.getWidth() * 2) - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(SCREEN_WIDTH - (texture.getWidth() * 2) - 20, 120 - texture.getHeight() - 10, rend);
		if (lives > 2)
			//lives.render(SCREEN_WIDTH - (lives.getWidth() * 3) - 10, SCREEN_HEIGHT - lives.getHeight() - 10, rend);
			texture.render(SCREEN_WIDTH - (texture.getWidth() * 3) - 30, 120 - texture.getHeight() - 10, rend);
	}
}
*/

void GameObject::createParticle(int x, int y) {
	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		//particles[i] = new Particle(x, y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
		//particles[i] = new Particle(x, y);
		particles[i] = new Particle(m_x, m_y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
	}
}

void GameObject::renderPlayerParticles(int x, int y, bool drawParticle, SDL_Renderer *rend) {

	//std::cout << "PARTICLES 1" << std::endl;

	//gDarkBlueParticleTexture.render(100, 100, rend);
	//gDarkBlueParticleTexture.render(110, 100, rend);
	//gDarkBlueParticleTexture.render(120, 100, rend);
	//gDarkBlueParticleTexture.render(130, 100, rend);


	//std::cout << "PARTICLES 2" << std::endl;

	createParticle(x, y);

	//std::cout << "PARTICLES 3" << std::endl;

	//renderParticles(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, rend, drawParticle, x + 9, y + 30);
	renderParticles(gShimmerTexture, rend, drawParticle, x, y);
	//std::cout << "PARTICLES 4" << std::endl;
}

//void Particle::renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y) {
void GameObject::renderParticles(Texture &four, SDL_Renderer *rend, bool drawParticle, int x, int y) {

	//four.render(100, 100, rend);

	//std::cout << "PARTICLES 5" << std::endl;
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		if (particles[i]->isDead(drawParticle)) {
			delete particles[i];										// Delete dead particles
																		//particles[i] = new Particle(x, y, one, two, three);			// Then replace them
			//particles[i] = new Particle(x, y);						// Then replace them

			particles[i] = new Particle(m_x, m_y, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
		}
	}
	//std::cout << "PARTICLES 6" << std::endl;

	// Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i) {
		particles[i]->render(four, rend);
	}
	//std::cout << "PARTICLES 7" << std::endl;
}

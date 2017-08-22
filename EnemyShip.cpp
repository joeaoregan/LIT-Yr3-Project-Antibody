#include "Game.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip() {					// Constructor
	setScore(25);							// Value for killing object

	// Initialise Dimensions
	setWidth(100);
	setHeight(47);

	// Initialize the offsets
	setX(0);
	setY(0);

	// Initialise the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(20);

	// Initialise Collider
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

EnemyShip::~EnemyShip() {					// Destructor

}

void EnemyShip::movement() {
	GameObject::movement();

	setColliderX(getX());
	setColliderY(getY());

	// destroy enemy ship once it is offscreen
	if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}

// Enemies render function with sprite animation
void EnemyShip::render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &enemyframe) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend, currentClip);

	++enemyframe;								// Go to next frame

	if (enemyframe >= ANIMATION_FRAMES * 10) {	// Cycle animation
		enemyframe = 0;
	}
}
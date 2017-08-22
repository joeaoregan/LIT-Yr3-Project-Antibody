
/*
* LaserEnemy.cpp is where all the implementations of the function definitions in LaserEnemy.h reside.
*/
/*
2017-01-10:
Added enemy laser projectile, velocity is a minus value as it is travelling right to left
*/
#include "LaserEnemy.h"
#include "EnemyShip.h"

// LaserEnemy Constructor
LaserEnemy::LaserEnemy() {
	//std::cout << "Enemy Laser constuctor called.\n";
	setWidth(50);
	setHeight(5);
	setVelocity(15);
	if (getType() == 0) {
		setColliderWidth(getWidth());
		setColliderHeight(getHeight());
	}
	else{								// Type 1 = orange fireball
		setColliderWidth(25);
		setColliderHeight(25);
	}
	setScore(5);						// 2017/01/20 Points to deduct from player after collision with this object
}

// LaserEnemy Destructor
LaserEnemy::~LaserEnemy() {
	std::cout << "Enemy Laser destructor called.\n";
}

void LaserEnemy::movement() {
	GameObject::movement();
	setY(getY() + getVelY());

	setColliderX(getX());
	setColliderY(getY());

	// destroy laser beam once it is offscreen
	if (getY() < 40) setAlive(false);			// Once it reaches the pink border
	else if (getY() > (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	else setAlive(true);

	if (getX() < -getWidth()) setAlive(false);	// The width of the object off the screen
	else if (getX() > SCREEN_WIDTH) setAlive(false);	// offscreen to the right
	else setAlive(true);
}

void LaserEnemy::spawn(int x, int y, SDL_Rect collider) {
	setX(x - 20);
	setY(y + 30);
	setVelX(-getVelocity());	// Minus value as travelling right to left
	setVelY(0);
	setCollider(collider);
}

void LaserEnemy::render(LTexture &texture, SDL_Renderer *rend) { // 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend);
}
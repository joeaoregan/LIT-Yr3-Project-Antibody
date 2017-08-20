
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
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
	setScore(5);						// 2017/01/20 Points to deduct from player after collision with this object
}

// LaserEnemy Destructor
LaserEnemy::~LaserEnemy() {
	std::cout << "Enemy Laser destructor called.\n";
}

void LaserEnemy::movement() {
	GameObject::movement();

	setColliderX(getX());
	setColliderY(getY());;

	// destroy laser beam once it is offscreen
	if (getX() < - getWidth()) setAlive(false);
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

//SDL_Rect LaserEnemy::getELaserCollider(){
//	return mELaserCollider;
//}

/*
*-------------------------------------------------
*		Laser.cpp
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:46pm
*-------------------------------------------------
*/
/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/

/*
* Laser.cpp is where all the implementations of the function definitions in Laser.h reside.
*/

#include "Laser.h"
#include "Ship.h"

// Laser Constructor
Laser::Laser() {
	std::cout << "Laser constuctor called.\n";

	setWidth(50);
	setHeight(5);
	setVelocity(15);

	mLaserCollider.w = getWidth();
	mLaserCollider.h = getHeight();
}


// Laser Destructor
Laser::~Laser()
{
	std::cout << "Laser destructor called.\n";
}

void Laser::movement() {
	GameObject::movement();

	mLaserCollider.x = getX();
	mLaserCollider.y = getY();
	// destroy laser beam once it is offscreen
	if (getX() > SCREEN_WIDTH) setAlive(false);
	else setAlive(true);
}

void Laser::spawn(int x, int y, SDL_Rect collider) {
	setX(x + 65);
	setY(y + 30);
	setVelX(getVelocity());
	setVelY(0);
	mLaserCollider = collider;
}

SDL_Rect Laser::getLaserCollider()
{
	return mLaserCollider;
}
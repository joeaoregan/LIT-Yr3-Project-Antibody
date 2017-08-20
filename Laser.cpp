/*
*-------------------------------------------------
*		Laser.cpp
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:46pm
*-------------------------------------------------
*/

/*
* Laser.cpp is where all the implementations of the function definitions in Laser.h reside.
*/

#include "Laser.h"
#include "Ship.h"

// Laser Constructor
Laser::Laser()
{
	std::cout << "Laser constuctor called.\n";
	mLaserCollider.w = LASER_WIDTH;
	mLaserCollider.h = LASER_HEIGHT;
}// end Laser constructor

void Laser::spawn(int x, int y, int velocity) {
	mPosX = x;
	mPosY = y;
	mVelX = velocity;
}

void Laser::move() {
	mPosX += mVelX; 											// Move the ship left or right
	mLaserCollider.x = mPosX;

	// destroy laser beam once it is offscreen
	if (getLaserX() > 645) mAlive = false;
	else mAlive = true;

}

 // Laser Destructor
Laser::~Laser()
{
	std::cout << "Laser destructor called.\n";
}// end ~Laser

/* Get the X coord of the laser beam. This tracks the laser beam so it can be destroyed once it moves off the screen */
int Laser::getLaserX() {
	return mPosX;
}

bool Laser::getLaserAlive() {
	return mAlive;
}

SDL_Rect Laser::getLaserCollider()
{
	return mLaserCollider;
}
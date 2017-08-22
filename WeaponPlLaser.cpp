/* 
	2017/01/23 Added power up to change laser grade
	2017/01/19 Added 3 beam laser
	2017/01/16 Spawn laser function added to game class to create laser with coords and velocity
	2017/01/09 Moved functionality common to game objects to GameObjects class reducing the code
	2017/01/06 Added player lasers
*/
/*
*-------------------------------------------------
*		Laser.cpp
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:46pm
*-------------------------------------------------
*/
/*
	LASER (Renamed WeaponPLLaser):

	This class contains the functions for spawning, rendering, and moving player laser objects.
	The player has two grades of laser, a single beam laser, and upon collecting a laser power
	up, a three beam laser. The three beam laser fires 3 laser beams at a time, at 3 different 
	angles. The player can fire an unlimited amount of laser beams.

	Laser.cpp is where all the implementations of the function definitions in Laser.h reside.
*/

#include "WeaponPlLaser.h"
#include "Player.h"

WeaponPlLaser::WeaponPlLaser(int player, int angle, int grade) {
	//std::cout << "Laser constuctor called.\n";
	setType(PLAYER_WEAPON);

	setPlayer(player);

	if (player == PLAYER1) setSubType(LASER_P1);
	else if (player == PLAYER2) setSubType(LASER_P2);

	setAngle(angle);	// Fire straight
	setGrade(grade);	// Basic Laser = 0, Triple Laser = 1

	//setVelocity(15);

	setWidth(50);
	setHeight(5);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAlive(true);
}

// Laser Destructor
WeaponPlLaser::~WeaponPlLaser(){
	std::cout << "Laser destructor called.\n";
}

void WeaponPlLaser::movement() {
	GameObject::movement();
	setY(getY() + getVelY());		// Up direction
	//if (getGrade() == 1) {
		if (getAngle() == 1) {
			setY(getY() + 3);
		}
		else if (getAngle() == 2) {
			setY(getY() - 3);
		}
	//}
}

void WeaponPlLaser::spawn(int x, int y, int velocity, int player, int type) {
	setX(x);
	setY(y);
	//setVelocity(velocity);
	setVelX(velocity);
	setPlayer(player);
	setSubType(type);
}

// Render the laser objects to the screen // 2017/01/22 Moved from game.cpp
void WeaponPlLaser::render(int player, Texture &orange, Texture &green) {
	if (player == 1)
		orange.render(getX(), getY());
	else if (player == 2)
		green.render(getX(), getY());
}
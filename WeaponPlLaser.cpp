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

#include "WeaponPlLaser.h"
#include "Player.h"

WeaponPlLaser::WeaponPlLaser(int angle, int grade) {
	//std::cout << "Laser constuctor called.\n";

	setWidth(50);
	setHeight(5);
	setVelocity(15);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAngle(angle);	// Fire straight
	setGrade(grade);	// Basic Laser = 0, Triple Laser = 1

	setAlive(true);

	setSubType(PLAYER_WEAPON);
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
	setType(type);
}

// Render the laser objects to the screen // 2017/01/22 Moved from game.cpp
void WeaponPlLaser::render(int player, Texture &orange, Texture &green, SDL_Renderer *rend) {
	if (player == 1)
		orange.render(getX(), getY(), rend);
	else if (player == 2)
		green.render(getX(), getY(), rend);
}
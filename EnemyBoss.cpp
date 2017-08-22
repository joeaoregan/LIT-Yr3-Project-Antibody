/*
	2017/03/02 Added Enemy Boss class 
*/
/*
	ENEMY BOSS:

	The enemy ship moves right to left across the screen firing intermittently
*/

#include "EnemyBoss.h"

EnemyBoss::EnemyBoss() {					// Constructor
	setType(ENEMY_OBJECT);
	setSubType(ENEMY_BOSS);
	setName("Enemy Boss");

	setScore(50);							// Value for killing object
	setDamage(20);

	// Initialise Dimensions
	//setWidth(100);
	//setHeight(47);

	// Initialize the offsets
	setX(0);
	setY(0);

	// Initialise the velocity
	setVelX(0);
	setVelY(0);
	setVelocity(-10);

	// Initialise Collider
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setFrames(0);
}

EnemyBoss::~EnemyBoss() {					// Destructor
	std::cout << "Enemy Boss destroyed" << std::endl;
}

bool moveRight = true;

void EnemyBoss::movement() {

	if (getX() > SCREEN_WIDTH - 330 && getX() < SCREEN_WIDTH + 200 && moveRight) {
		GameObject::movement();
		if (getX() >= SCREEN_WIDTH - 330 && getX() <= SCREEN_WIDTH - 320) moveRight = false;
	}
	
	//m_x += m_xVel;

	else if (getX() <= SCREEN_WIDTH - 330 && !moveRight) {
		setX(getX() - getVelX() + 5);
		if (getX() <= 0) moveRight = true;
	}
}
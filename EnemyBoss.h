/*
	2017/03/02 Added Enemy Boss class
*/
/*
	ENEMY BOSS:

	The enemy ship moves right to left across the screen firing intermittently
*/

#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include "Enemy.h"

class EnemyBoss : public Enemy {
public:
	bool moveRight = true;

	// Constructor
	EnemyBoss() {					
		setType(ENEMY_OBJECT);					// Set type
		setSubType(ENEMY_BOSS);					// Set sub-type
		setName("Enemy Boss");					// Identify object

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

	// Destructor
	~EnemyBoss() {					
		std::cout << "Enemy Boss destroyed" << std::endl;
	}

	virtual void move() {
		if (getX() > SCREEN_WIDTH - 330 && getX() < SCREEN_WIDTH + 200 && moveRight) {
			GameObject::move();
			if (getX() >= SCREEN_WIDTH - 330 && getX() <= SCREEN_WIDTH - 320) moveRight = false;
		}

		//m_x += m_xVel;

		else if (getX() <= SCREEN_WIDTH - 330 && !moveRight) {
			setX(getX() - getVelX() + 5);
			if (getX() <= 0) moveRight = true;
		}
	}

	virtual void destroy() {		// Destory the enemy boss when it moves out of bounds
		GameObject::destroy();		// Destroy function from Game Object base class
	};
};

#endif
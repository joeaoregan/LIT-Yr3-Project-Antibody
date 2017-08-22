/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnemyShip.h
	- Description:			Header file for the EnemyShip object which is a sub-type of Enemy
	- Information:			Contains constructor and destructor for enemy ship object and move function.
							The enemy ship moves right to left across the screen firing intermittently.

	- Log:
		2017/07/03		Moved enemy laser spawning from Game class to Enemy Ship move function
		2017/02/09		Made Enemy Ship animations independent, so they don't all render same frame at the same time
		2017/01/20		Added more random shooting from enemy ships
						Fixed problem where not all ships are firing
		2017/01/10		Added ability to spawn lasers in Game.cpp
						Added spawn functions to spawn enemies and obstacles at random coords & distances apart
		2017/01/09		Added spawnEnemyShip() function to create enemy ships at random times and random y coord
		2017/01/06		Enemy movement from right to left towards player adapted from laser spawning
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Enemy.h"
#include "Game.h"

class EnemyShip : public Enemy {
public:
	// Name: EnemyShip()
	// Role: Constructor, Initialize the variables
	EnemyShip()	{
		setType(ENEMY_OBJECT);			// Set type
		setSubType(ENEMY_SHIP);			// Set sub-type

		setScore(25);					// Value for killing object
		setDamage(15);

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

		setFrames(0);					// Frames needed for animation

		setName("Enemy Ship");
	}

	// Name: ~EnemyShip()
	// Role: Destructor for enemy ship object
	~EnemyShip() {								
		std::cout << "Enemy Ship destroyed" << std::endl;
	}

	/* 
		Name: move()
		Role: Move the enemy ship across the screen while firing lasers.
		The Enemy Ship / Nano-bot movement function inherits the game objects move() function
		Moved call to Nano-bot fire laser function to move() from Game class
		The enemy ship fires lasers based on its X coordinate position
	*/
	virtual void move(int x = 0, int y = 0) {									// Needs to have X and Y values to override base class function
		Game::Instance()->spawnEnemyLaser(getX(), getY(), ENEMY_SHIP_LASER);	// 2017/03/17 Moved from Game class
		GameObject::move();
	};
	virtual void destroy() {};
};

#endif
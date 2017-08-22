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
#include "Game.h"

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
		setWidth(300);
		setHeight(460);

		// Initialize the offsets
		setX(0);
		setY(0);

		setHealth(100);

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
	bool moveUp = false, moveDown = false, moveForward = true, moveBackwards = false, moveAttack = false, spawnVirus = false;
	int countMoves = 0;
	virtual void move(int x, int y) {
		// Set collider movement as its not inheriting movment
		setColliderX(getX());
		setColliderY(getY());
		//if (getX() == 

		//if (getX() > SCREEN_WIDTH - 330 && getX() < SCREEN_WIDTH - 200 && moveRight) { // 1st
		if (moveForward && !moveDown && !moveUp && !moveBackwards) {
			GameObject::move();
			//if (getX() >= SCREEN_WIDTH - 330 && getX() <= SCREEN_WIDTH - 320) moveRight = false;

			if (getX() <= SCREEN_WIDTH - 330) {
				moveForward = false;
				moveDown = true;
			}
		}

		if (moveDown) {
			setY(getY() + 3);
			
			if (getY() > 200) {
				moveUp = true;
				moveDown = false;
				countBossMoves();
				//Game::Instance()->spawnEnemyLaser(getX() + 70, getY() + 225, BLUE_VIRUS_BULLET);
				//Game::Instance()->spawnEnemyLaser(getX() + 180, getY() + 225, BLUE_VIRUS_BULLET);
			}
			
		}
		if (moveUp) {
			setY(getY() - 3);

			if (getY() < 35) {
				moveDown = true;
				moveUp = false;
				countBossMoves();
				//Game::Instance()->spawnEnemyLaser(getX() + 70, getY() + 225, BLUE_VIRUS_BULLET);
				//Game::Instance()->spawnEnemyLaser(getX() + 180, getY() + 225, BLUE_VIRUS_BULLET);
				//Game::Instance()->spawnEnemyLaser(getX() + 57, getY() + 210, BLUE_VIRUS_BULLET);
				//Game::Instance()->spawnEnemyLaser(getX() + 167, getY() + 214, BLUE_VIRUS_BULLET);
			}
		}

		if (moveAttack) {
			setX(getX() - 7);
			//if (getX() == SCREEN_WIDTH) {
			//	moveForward = true;
			if (getX() < 200) {
				moveBackwards = true;
				moveAttack = false;
			}
		}
		
		if (moveBackwards) {
			setX(getX() + 5);
			if (getX() >= SCREEN_WIDTH - getWidth() - 250 && getX() <= SCREEN_WIDTH - getWidth() - 245) {
				spawnVirus = true;
			}
			if (spawnVirus) {
				Game::Instance()->spawnEnemyVirus(VIRUS_ORANGE, getX() + 70, getY() + 320);
				//Game::Instance()->spawnEnemyVirus(VIRUS_ORANGE, getX() + 70, getY() + 320);
				spawnVirus = false;
			}

			if (getX() == SCREEN_WIDTH) {
				moveUp = false;
				moveDown = false;
				moveForward = true;
				moveBackwards = false;
			}
		}

		//m_x += m_xVel;

		//else if (getX() <= SCREEN_WIDTH - 330 && !moveRight) {
		//	setX(getX() - getVelX() + 5);
		//	if (getX() <= 0) moveRight = true;
		//}
	}

	void countBossMoves() {
		countMoves++;
		if (countMoves == 6) {
			moveAttack = true;	// Move the boss backwards
			countMoves = 0;			// reset move counter
		}
	}

	virtual void destroy() {		// Destory the enemy boss when it moves out of bounds
		GameObject::destroy();		// Destroy function from Game Object base class
	};
};

#endif
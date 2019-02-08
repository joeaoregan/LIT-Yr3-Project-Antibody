/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnemyBoss.h
	- Description:			Header file for the EnemyBoss object which is a sub-type of Enemy but with more functionality
	- Information:			Contains constructor and destructor for enemy boss object and all functionality.
							The Boss is a sub-type of Enemy but with more functionality than basic nano-bots and viruses.
							It has more varied movement than other enemy objects, but stops short of the start of the 
							game screen, giving the player a position from which to attack.
							It also fires lasers from its eyes and viruses from its mouth in level 1.
							

	- Log:	
		2017/03/22		Made the Enemy Boss collider slightly smaller and closer to the face, 
						so explosions are happening closer to the target.
		2017/03/18		Updated animation swapping Lorcan for Daniel (an improvement!!!)
						Added more complicated movement, with the player performing different
						movement sequences at different points on the screen.
						Added laser spawning from the eyes, along with laser generation animation
						Added Virus spawning from the opening mouth at certain positions on screen
		2017/03/02		Added Enemy Boss class.
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include "Enemy.h"
#include "Game.h"

class EnemyBoss : public Enemy {
public:
	//bool moveRight = true;					// 2017/03/21 original movement boolean

	/* 
		Name: EnemyBoss()
		Role: Constructor for enemty boss
		The Boss is a sub-type of Enemy
		It has more varied movement than other enemy objects
		It also fires lasers from its eyes and viruses from its mouth in level 1
	*/
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
		setColliderWidth(getWidth() - 50);
		setColliderHeight(getHeight() - 70);

		setFrames(0);
	}

	// Destructor
	~EnemyBoss() {					
		std::cout << "Enemy Boss destroyed" << std::endl;
	}

	/*
		2017/03/18 Updated enemy boss movement to randomly move around the screen 
		after first moving to the left, stopping, and moving up and down
		Some of the movement was accidental, but it looks good, so no need to change
		Moved projectile and virus spawning to Game class, to be triggered by animation end-point
	*/
	bool moveUp = false, moveDown = false, moveForward = true, moveBackwards = false, moveAttack = false, spawnVirus = false;
	int countMoves = 0;

	// Name: move()
	// Role: Move the Enemy Boss Object around the screen in a pattern
	virtual void move(int x, int y) {
		// Set collider movement as its not inheriting movment
		setColliderX(getX() + 30);					// 2017/03/22 Set the enemy collider closer to its face
		setColliderY(getY() + 10);
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

	/*
		Name: CountBossMoves()
		Role: This function counts the number of times the boss moves up and down
		before it progresses to random diagonal movement back and forth from Player
	*/
	void countBossMoves() {
		countMoves++;
		if (countMoves == 6) {
			moveAttack = true;	// Move the boss backwards
			countMoves = 0;			// reset move counter
		}
	}

	/*
		Name: destroy();
		Role: destroy the enemy boss objects and set it to be removed from memory
		The destroy function inherits from GameObject
	*/
	virtual void destroy() {		// Destory the enemy boss when it moves out of bounds
		GameObject::destroy();		// Destroy function from Game Object base class
	};
};

#endif
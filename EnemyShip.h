#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Enemy.h"

class EnemyShip : public Enemy {
public:
	EnemyShip();							// Initializes the variables
	//~EnemyShip();
	
	// The dimensions of the Enemy (dimensions of sprite image)
	static const int ENEMY_WIDTH = 100;
	static const int ENEMY_HEIGHT = 47;

	static const int ENEMY_VEL = 20;		// Maximum axis velocity of the Enemy


	//void spawn(int x, int y, int velocity);
	//void spawn(int y, int velocity);
	//virtual void spawn();
	//void moveEnemy();						// Moves the Enemy	
	virtual void movement();
	void render();							// Shows the Enemy on the screen
	int getESwidth();						// get the width of an enemy ship
	
	//int getEnemyX();
	//int getEnemyY();
	//int getEnemyVelX();

	//int setEnemyX(int x);
	//int setEnemyY(int y);
	//int setEnemyVelX(int x);

private:
	//int mEnPosX, mEnPosY;					// The X and Y offsets of the Enemy	
	int mEnVelX, mEnVelY;					// The velocity of the Enemy
	int mEnAlive;

};

#endif
#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Ship.h"

class EnemyVirus : public Enemy {
public:
	EnemyVirus();							// Initializes the variables
	~EnemyVirus();

	// The dimensions of the Enemy (dimensions of sprite image)
	//static const int ENEMY_WIDTH = 100;
	//static const int ENEMY_HEIGHT = 47;

	static const int VIRUS_VEL = 3;		// 2017/01/10 JOE: Maximum axis velocity of the Enemy Virus (Slower than a ship)

	virtual void movement(int playerX, int playerY);
	void render();							// Shows the Enemy on the screen
};

#endif
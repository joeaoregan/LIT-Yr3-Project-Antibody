#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Ship.h"

class EnemyVirus : public Enemy {
public:
	EnemyVirus();							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);
	//virtual void movement(int shipX, int shipY, SDL_Rect& square, Circle& circle); // 2017-01-10e collisions
	void render();							// Shows the Enemy on the screen
};

#endif
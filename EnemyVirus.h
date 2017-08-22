#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"

class EnemyVirus : public Enemy {
public:
	float bombTimer;

	EnemyVirus(int type = 0, float time = 3.0);							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);

	float getTimer() { return bombTimer; }
	void setTimer(int t) { bombTimer = t; }
};

#endif
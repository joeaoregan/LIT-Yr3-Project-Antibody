#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"
#include "WeaponEnLaser.h"

//enum virusType { VIRUS_GREEN, VIRUS_ORANGE, VIRUS_BLUE };

class EnemyVirus : public Enemy {
public:
	float bombTimer;

	EnemyVirus(int type = VIRUS_GREEN, float time = 0);							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);

	WeaponEnLaser* laser;
};

#endif
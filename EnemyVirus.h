#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"
#include "WeaponEnLaser.h"

enum virusType { GREEN, ORANGE, BLUE };

class EnemyVirus : public Enemy {
public:
	float bombTimer;

	EnemyVirus(int type = 0, float time = 0);							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);

	WeaponEnLaser* laser;
};

#endif
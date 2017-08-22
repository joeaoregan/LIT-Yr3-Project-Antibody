#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include "Enemy.h"

class EnemyBoss : public Enemy {
public:
	EnemyBoss();							// Initializes the variables
	~EnemyBoss();

	void movement();
};

#endif
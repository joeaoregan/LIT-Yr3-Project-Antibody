#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Enemy.h"

class EnemyShip : public Enemy {
public:
	EnemyShip();							// Initializes the variables
	~EnemyShip();

	virtual void move() {};
};

#endif
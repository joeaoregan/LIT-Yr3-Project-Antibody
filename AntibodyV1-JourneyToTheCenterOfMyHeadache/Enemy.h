/* 2017/01/10:
JOE: Create parent class for Enemies
*/
#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	~Enemy();
};

#endif
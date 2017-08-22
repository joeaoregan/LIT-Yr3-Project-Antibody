#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"

class Explosion : public GameObject {
public:
	Explosion(int x, int y, int subType = 0);							// Initializes the variables
	~Explosion();

	virtual void move();
};

#endif
#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

//enum powerUpTypes { POWER_UP_HEALTH = 1, POWER_UP_LASER, POWER_UP_ROCKET };

class PowerUp : public GameObject {
public:
	PowerUp(int type = 0, int score = 0);
	~PowerUp();

	virtual void move();
};

#endif
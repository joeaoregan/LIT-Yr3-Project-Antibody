#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp(int type = 0, int score = 0);
	~PowerUp();
};

#endif
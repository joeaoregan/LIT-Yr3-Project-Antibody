#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp();
	~PowerUp();

	virtual void movement();
	void render();							// Shows the Power Up on the screen
};

#endif
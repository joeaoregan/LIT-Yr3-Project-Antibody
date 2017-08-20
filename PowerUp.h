#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp();
	~PowerUp();

	virtual void movement();
	void render(LTexture &texture, SDL_Renderer *rend);							// Shows the Power Up on the screen
};

#endif
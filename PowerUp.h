#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp();
	PowerUp(int type, int score);
	~PowerUp();

	virtual void movement();
	//void render();							// Shows the Power Up on the screen
	void render(LTexture &texture, SDL_Renderer *rend);							// Shows the Power Up on the screen
	//int powerUpType;
};

#endif
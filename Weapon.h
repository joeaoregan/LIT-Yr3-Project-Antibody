#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include <list>

class Weapon : public GameObject {
public:
	Weapon();
	~Weapon();

	int getPlayer();
	void setPlayer(int p = 0);

	int getAngle();
	void setAngle(int a);

	int getGrade();
	void setGrade(int g);

	void render(LTexture &texture, SDL_Renderer *rend, int degrees = 0);				// Shows the Ninja Star on the screen - 2017/01/17 Add player decision
	void handleEvent(SDL_Event& e, int player);

private:
	int mPlayer;
	int mAngle;
	int mGrade;
};

#endif
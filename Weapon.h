#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include <list>

class Weapon : public GameObject {
public:
	Weapon();
	~Weapon();

	int getPlayer() { return mPlayer; }
	void setPlayer(int p = 0) { mPlayer = p; }
	
	int getGrade() { return mGrade; }
	void setGrade(int g) { mGrade = g; }

	void handleEvent(SDL_Event& e, int player);

private:
	int mPlayer;
	int mAngle;
	int mGrade;
};

#endif
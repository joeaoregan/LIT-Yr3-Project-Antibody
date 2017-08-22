#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include <list>

class Weapon : public GameObject {
public:
	Weapon();
	~Weapon();

	
	int getGrade() { return mGrade; }
	void setGrade(int g) { mGrade = g; }

	virtual void handleEvent(SDL_Event& e, int player);

private:
	int mAngle;
	int mGrade;
};

#endif
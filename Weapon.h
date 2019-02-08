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

private:
	int mPlayer;
	int mAngle;
	int mGrade;
};

#endif
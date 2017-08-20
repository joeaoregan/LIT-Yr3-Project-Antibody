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

private:
	int mPlayer;
};

#endif
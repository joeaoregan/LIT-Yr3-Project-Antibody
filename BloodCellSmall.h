#ifndef BLOOD_CELL_SMALL_H
#define BLOOD_CELL_SMALL_H

#include "Enemy.h"

class BloodCellSmall : public Enemy {
public:
	BloodCellSmall();							// Initializes the variables
	~BloodCellSmall();

	// The dimensions of the Enemy (dimensions of sprite image)
	//static const int ENEMY_WIDTH = 100;
	//static const int ENEMY_HEIGHT = 47;

	static const int BLOODS_VEL = 1;			// 2017/01/10 JOE: Maximum axis velocity of the Blood Cell obstacle

	virtual void movement();
	void render();							// Shows the Blood Cell on the screen
};

#endif
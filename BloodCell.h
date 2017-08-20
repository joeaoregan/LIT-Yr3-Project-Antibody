#ifndef BLOOD_CELL_H
#define BLOOD_CELL_H

#include "Enemy.h"

class BloodCell : public Enemy {
public:
	BloodCell();				// Initializes the variables
	~BloodCell();				// Destructor
	
	virtual void movement();	// Move the Blood Cell
	void render();				// Shows the Blood Cell on the screen
};

#endif
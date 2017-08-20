#ifndef WHITE_BLOOD_CELL_H
#define WHITE_BLOOD_CELL_H

#include "Enemy.h"

class WhiteBloodCell : public Enemy {
public:
	WhiteBloodCell();							// Initializes variables
	~WhiteBloodCell();							// Deconstructor  
	
	virtual void movement();					// Move the White Blood Cells
	void render();								// Shows the White Blood Cell on the screen
};

#endif
#ifndef BLOOD_CELL_H
#define BLOOD_CELL_H

#include "Enemy.h"

class BloodCell : public Enemy {
public:
	BloodCell();							// Initializes the variables
	~BloodCell();
	
	virtual void movement();
	//void render(LTexture &texture, SDL_Renderer *rend, int degrees);							// Shows the Blood Cell on the screen
};

#endif
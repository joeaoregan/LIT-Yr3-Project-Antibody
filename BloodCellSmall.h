#ifndef BLOOD_CELL_SMALL_H
#define BLOOD_CELL_SMALL_H

#include "Enemy.h"

class BloodCellSmall : public Enemy {
public:
	BloodCellSmall();				// Initializes the variables
	~BloodCellSmall();				// Destructor

	virtual void movement();		// Move the small blood cell
	//void render();					// Shows the Blood Cell on the screen
	void render(LTexture &texture, SDL_Renderer *rend, int degrees);					// Shows the Blood Cell on the screen
};

#endif
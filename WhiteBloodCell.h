#pragma once
#ifndef WHITE_BLOOD_CELL_H
#define WHITE_BLOOD_CELL_H

#include "Enemy.h"

class WhiteBloodCell : public Enemy {
public:
	WhiteBloodCell();							// Initializes the variables
	~WhiteBloodCell();
	
	virtual void movement();
	//void render(LTexture &texture, SDL_Renderer *rend, int degrees);							// Shows the Blood Cell on the screen
};

#endif
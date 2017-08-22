/* 2017/01/30
	Added random rotation direction for blood cells, so Blood Cells can rotate both forwards and backwards
*/

#ifndef BLOOD_CELL_H
#define BLOOD_CELL_H

#include "Enemy.h"

enum bloodCellTypes { BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL };

class BloodCell : public Enemy {
public:
	BloodCell(int type = 0);					// Initializes the variables
	~BloodCell();
	
	virtual void movement();
	//void render();							// Shows the Blood Cell on the screen
	void render(LTexture &texture, SDL_Renderer *rend, int degrees);
	int getMovement();
	void setMovement(int movement);
	int getDistanceBetween();
	void setDistanceBetween(int d);

	// 2017/01/30 Added rotation direction, so Blood Cells can rotate both forwards and backwards
	int getRotationDirection();
	void setRotationDirection(int d);

private:
	int mMovement;
	int mDistanceBetween;						// Distance between Blood Cells spawning
	int mRotationDirection;						// Direction to rotate Blood Cell (-1 = anticlockwise, 1 = clockwise)
};

#endif
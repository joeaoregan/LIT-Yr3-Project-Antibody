/* 
	2017/02/19 Added separate explosions for blood cells to look more like a blood splatter
	2017/01/30 Added random rotation direction for blood cells, so Blood Cells can rotate both forwards and backwards
*/

#ifndef BLOOD_CELL_H
#define BLOOD_CELL_H

#include "Enemy.h"

//enum bloodCellTypes { BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL };

class BloodCell : public Enemy {
public:
	BloodCell(int type = 0);					// Initializes the variables
	~BloodCell();
	
	virtual void movement();

	int getMovement() { return mMovement; }
	void setMovement(int movement) { mMovement = movement; }

	virtual void movement(int targetx, int targetY);

private:
	int mMovement;
};

#endif
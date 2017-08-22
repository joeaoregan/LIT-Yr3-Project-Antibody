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

	int getMovement() { return mMovement; }
	void setMovement(int movement) { mMovement = movement; }
	int getDistanceBetween() { return mDistanceBetween; }
	void setDistanceBetween(int d) { mDistanceBetween = d; }

	// 2017/01/30 Added rotation direction, so Blood Cells can rotate both forwards and backwards
	int getRotationDirection() { return mRotationDirection; }
	void setRotationDirection(int d) { mRotationDirection = d; }

private:
	int mMovement;
	int mDistanceBetween;						// Distance between Blood Cells spawning
	int mRotationDirection;						// Direction to rotate Blood Cell (-1 = anticlockwise, 1 = clockwise)
};

#endif
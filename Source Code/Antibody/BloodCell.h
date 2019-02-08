/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					BloodCell.h
	- Description:			Header file for BloodCell object
	- Information:			Class to declare functions and variables for creating and updating the BloodCell Object

	- Log:

		2017/03/17		Created a unique render function for Blood Cells that uses the stored texture ID to load the texture image
						it also rotates the blood cells in a random direction
		2017/02/19		Added separate explosions for blood cells to look more like a blood splatter
		2017/02/18		Moved Blood Cells to game object list
		2017/01/30		Combined the three separate blood cell classes for Large, small, and white blood cells into a common blood cell class
						Added random rotation direction for blood cells, so Blood Cells can rotate both forwards and backwards
						Added rotation angle to constructors for Textures that rotate, including blood cells
						Moved degrees variable to object so all rotating objects rotate at different times
		2017/01/22		Added forwards/backwards rotation for blood cells
		2017/01/10		Added Large Blood Cell object
						Added class for handling blood cells including Small Blood Cell, and White Blood Cells, BloodCell.h
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef BLOOD_CELL_H
#define BLOOD_CELL_H

#include "Enemy.h"

//enum bloodCellTypes { BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL };

class BloodCell : public Enemy {
public:
	BloodCell(int type = 0);									// Initializes the variables
	~BloodCell();												// Destructor
	
	virtual void move(int x, int y);							// Movement funtion
	virtual void moveStalker(int targetx, int targetY);			// Stalker movement, allows White Blood Cells to track small virus enemies
	virtual void render();										// 2017/03/17 Unique render function using stored texture ID, with random rotation direction

	virtual void destroy() {									// Destroy the blood cells
		GameObject::destroy();									// 2017/03/17 Test - inheriting destroy function from game object base class
	};

	int getMovement() const { return mMovement; }				// Get the blood cells movement
	void setMovement(int movement) { mMovement = movement; }	// Set the blood cells moevment

private:
	int mMovement;
};

#endif
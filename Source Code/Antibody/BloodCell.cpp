/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					BloodCell.cpp
	- Description:			cpp file for BloodCell object
	- Information:			Contains all functions used in creating and updating the BloodCell object

		Other Info:			There are three types of blood cell in the game small, large, and white blood cells. Small blood cells move in the background
							and do not affect the player in any way. Large blood cells can be split by player weapons causing a explosion of blood
							splattered on the screen. The white blood cell does not interfere with the player in any way, but when a player splits an 
							enemy virus in two, the white blood cell can then swoop in to clear up the virus, as they are a more manageable size for the
							white blood cells to break down.
							Blood cells have random rotational movement, and random speed is assigned when they are spawned.

	- Log:
		2017/03/17		Created a unique render function for Blood Cells that uses the stored texture ID to load the texture image
						it also rotates the blood cells in a random direction.
						Render Blood Cells.
		2017/02/19		Added separate explosions for blood cells to look more like a blood splatter.
		2017/02/18		Moved Blood Cells to game object list.
		2017/01/30		Combined the three separate blood cell classes for Large, small, and white blood cells into a common blood cell class.
						Added random rotation direction for blood cells, so Blood Cells can rotate both forwards and backwards.
						Added rotation angle to constructors for Textures that rotate, including blood cells.
						Moved degrees variable to object so all rotating objects rotate at different times.
		2017/01/22		Added forwards/backwards rotation for blood cells.
		2017/01/10		Added Large Blood Cell object.
						Added class for handling blood cells including Small Blood Cell, and White Blood Cells, BloodCell.h
	----------------------------------------------------------------------------------------------------------------------*/
#include "BloodCell.h"

int up = 0, down = 250;

/* 
	Name: BloodCell()
	Role: Constructor for Blood Cell objects
	The Blood Cell Constructor can create 3 different sub types of Blood Cell
	Large, Small, and White blood cells
	Each type of blood cell has its own name, texture ID, angle of rotation, and dimensions
*/
BloodCell::BloodCell(int subType) {
	if (subType == LARGE_BLOOD_CELL) {
		setName("Large Blood Cell");		// Name of blood cell for info / error messages
		setTextureID("bcID");				// Texture ID for blood cell
		setAngle(1);						// Angle of rotation for blood cell
		setWidth(100);						// Width of blood cell
		setHeight(55);						// Height of blood cell
	}
	else if (subType == SMALL_BLOOD_CELL) {
		setName("Small Blood Cell");
		setTextureID("bcsID");
		setAngle(2);
		setWidth(59);
		setHeight(66);
	}
	else if (subType == WHITE_BLOOD_CELL) {
		setName("White Blood Cell");
		setTextureID("bcwID");
		setAngle(2);
		setWidth(70);
		setHeight(70);
	}

	int randomRotationDirection = rand() % 3 + 1;
	setType(BLOOD_CELL);
	setSubType(subType);
	setVelocity(1);
	setMovement(200);
	setDistanceBetween(100);
	
	// Set approx. 1 out of 3 (ish) Blood Cells rotating backwards
	if (randomRotationDirection == 1)
		setRotationDirection(-1);
	else
		setRotationDirection(1);

	setColliderWidth(getWidth() + 5);
	setColliderHeight(getHeight() + 5);

	/*
	//setColliderR(getWidth() / 2);		// Set circular collider
	//setScore(5);
	//shiftColliders();
	//setWidth(70);
	//setHeight(55);

	// NOT WORKING
	if (subType == LARGE_BLOOD_CELL) {					// Set dimensions for different types of blood cells
	setWidth(100);
	setHeight(55);
	}
	else if (subType == SMALL_BLOOD_CELL) {
	setWidth(59);
	setHeight(66);
	}
	else if (subType == WHITE_BLOOD_CELL) {
	setMovement(250);
	setDistanceBetween(150);
	setWidth(70);
	setHeight(70);
	}
	*/
}

// Name: ~BloodCell()
// Role: Remove BloodCell from memory when destroyed
BloodCell::~BloodCell() {
	std::cout << "Blood Cell Destroyed" << std::endl;
}

/*
	Name: move
	Role: Move slightly up and down, as they move across the screen
	Red blood cells use standard gameobject movement
*/
void BloodCell::move(int x, int y) {					// Move() must have x and y to inherit from base class
	GameObject::move();

	if (up < getMovement()) {
		setY(getY() - getVelocity());
		up += 1;
		if (up >= getMovement()) down = 0;
	}
	if (down < getMovement()) {
		setY(getY() + getVelocity());
		down += 1;
		if (down >= getMovement()) up = 0;
	}

	// 2017/03/17 Rotate the blood cells
	if (getSubType() == LARGE_BLOOD_CELL)
		setAngle(getAngle() + 1);
	else
		setAngle(getAngle() + 2);
}

/* 
	Name: moveStalker
	Role: Tracker movement for White Blood Cells 
	The White Blood Cells can clean up smaller viruses
	When the player splits a virus in two the White Blood Cell
	swoops in to tidy up
*/
void BloodCell::moveStalker(int targetX, int targetY) {
	if (getSubType() == WHITE_BLOOD_CELL) {
		if (getX() < SCREEN_WIDTH - getWidth()) {		// If the object is on the screen
			int randomVelocity = rand() % 4 + 2;

			if (getX() - targetX >= 0) {				// If the small virus is behind the white blood cell
				if (getX() - targetX >= randomVelocity)
					setX(getX() - randomVelocity);		// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getX() - targetX < 0) {			// if the small virus is in front of the white blood cell
				setX(getX() + randomVelocity);			// Move towards X coord
			}

			if (getY() - targetY >= 0) {				// if the small virus is below the white blood cell
				if (getY() - targetY >= randomVelocity)
					setY(getY() - randomVelocity);		// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getY() - targetY < 0) {			// if the small virus is above the white blood cell
				setY(getY() + randomVelocity);			// Move towards Y coord
			}

			setColliderX(getX());
			setColliderY(getY());
		}
	}
	else
		GameObject::move();								// If there are no small virus enemies use standard movement

	setAngle(getAngle() + 2);							// Update the angle of rotation for White Blood Cell
}

/*
	Name: render()
	Role: render the blood cell object to the screen.
	The blood cells texture is loaded from the texture map using the stored ID
	The mRotationDirection variable is used to set some of the bloodcells spinning in the opposite direction
*/
void BloodCell::render() {
	SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle() * mRotationDirection, NULL, SDL_FLIP_NONE);	// Render to screen
}
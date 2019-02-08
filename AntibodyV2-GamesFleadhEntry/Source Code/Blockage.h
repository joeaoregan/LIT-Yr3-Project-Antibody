#ifndef BLOCKAGE_H
#define BLOCKAGE_H

#include "Enemy.h"

class Blockage : public Enemy {
public:
	// Blockage Constructor - Initializes the variables
	Blockage() {
		setType(ENEMY_OBJECT);
		setSubType(BLOCKAGE);
		setScore(15);						// Value for killing object

		setTextureID("blockageID");

		setWidth(56);
		setHeight(130);

		setColliderWidth(getWidth());
		setColliderHeight(getHeight());

		setVelocity(-BACKGROUND_SCROLL_SPEED);

		setAlive(true);
};	

	// Blockage Destructor
	~Blockage() {
		std::cout << "Destroying blockage" << std::endl;
	};

	// Movement function inherits from GameObject base class
	virtual void move() {
		GameObject::move();

		setColliderX(getX());
		setColliderY(getY());

		//// destroy blockage once it is offscreen
		//if (getX() < -getWidth()) setAlive(false);
		//else setAlive(true);
	};
};
#endif
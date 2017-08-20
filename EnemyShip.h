#ifndef ENEMY_H
#define ENEMY_H
//#include "LTexture.h"
//#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

class EnemyShip {
public:
	EnemyShip();							// Initializes the variables
	//~EnemyShip();


	// The dimensions of the Enemy (dimensions of sprite image)
	static const int ENEMY_WIDTH = 70;
	static const int ENEMY_HEIGHT = 5;

	static const int ENEMY_VEL = 20;	// Maximum axis velocity of the Enemy


	//void spawn(int x, int y, int velocity);
	//void spawn(int y, int velocity);
	void spawn();
	void moveEnemy();						// Moves the Enemy	
	void render();						// Shows the Enemy on the screen
	
	int getEnemyX();
	int getEnemyY();
	int getEnemyVelX();

	//int setEnemyX(int x);
	//int setEnemyY(int y);
	//int setEnemyVelX(int x);

private:
	int mEnPosX, mEnPosY;					// The X and Y offsets of the Enemy	
	int mEnVelX, mEnVelY;					// The velocity of the Enemy
	int mEnAlive;

};

#endif
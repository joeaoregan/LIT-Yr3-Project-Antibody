/*
*-------------------------------------------------
*		Game.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/

#ifndef GAME_H
#define GAME_H

//#include <SDL.h>
//#include <SDL_image.h>
#include <cstdlib>		// For Random Numbers
#include <ctime>		// For Random Numbers
#include <list>
#include <vector>

class Game {
public:
	int counter = 0;
	bool gameOver = false;

	// Render Healthbars
	//enum healthBarOrientation { VERTICAL, HORIZONTAL };
	//void renderHealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation);	// 2017/01/20 Added orientation


	//bool init();								// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();								// Frees media and shuts down SDL

	void displayGameLogos();					// Display Logos at start of game

	void spawnEnemies();
	void spawnEnemyShip();						// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus();						// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell();						// 2017/01/10 JOE: add function to create blood cells
	void spawnSmallBloodCell();
	void spawnWhiteBloodCell();
	void spawnLaser(int x, int y, int player, int v = 20, int grade = 0);	// 2017/01/16 spawn a laser at coords, with velocitys 2017/01/20 added Weapons grade
	void spawnEnemyLaser(int x, int y);						// 2017/01/10
	void spawnNinjaStar(int x, int y, int player);			// 2017/01/09 JOE: added function to create ninja star weapons - 2017/01/17 added player decision - player to spawn for and their coords
	void spawnSaw(int x, int y, int player, bool active = false);				// 2017/01/20: Saw Weapon for player
	//void spawnSaw(int x, int y, int player);				// 2017/01/17: Saw Weapon for player
	void spawnPowerUp();

	void gamepadInfo();							// 2017/01/17: Separate gamepad information
	void displayText();							// 2017/01/17: Display game text
	void pressButtonToContinue();				// 2017/01/18

	void collisionCheck();

	bool playerInput(bool quit);				// 2017/01/09 JOE: Handle input from player
	void renderGameObjects();					// 2017-01-09 JOE: Render the game objects to the screen
	void moveGameObjects();						// 2017-01-09 JOE: Move the game objects on the screen
	void destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen
	void flashGameObject(int &alpha, bool &flash, int rate = 10, int times = 0);
	
	// Music
	void musicForward();
	void musicBack();

	void spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier, int speed = 1);
};

#endif
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

#include <cstdlib>		// For Random Numbers
#include <ctime>		// For Random Numbers
#include <list>

class Game {
public:
	//bool init();					// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();					// Frees media and shuts down SDL

	void spawnEnemies();
	void spawnEnemyShip();			// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus();			// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell();			// 2017/01/10 JOE: add function to create blood cells
	void spawnSmallBloodCell();
	void spawnLaser();
	void spawnNinjaStar();			// 2017/01/09 JOE: added function to create ninja star weapons

	bool playerInput(bool quit);	// 2017/01/09 JOE: Handle input from player
	void renderGameObjects();		// 2017-01-09 JOE: Render the game objects to the screen
	void moveGameObjects();			// 2017-01-09 JOE: Move the game objects on the screen
	void destroyGameObjects();		// 2017-01-09 JOE: Destroy the game objects when finished on the screen
	void playerFlashOnCollide();	// 2017-01-09 JOE: The player texture flashes on collision with other Game Objects
	void audio();					// 2017-01-10 JOE: Handle the audio for game objects
	void engineFX();				// 2017-01-09 JOE: Engine Sound FX for ship
};

#endif
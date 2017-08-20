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

#include <stdio.h>
#include <string>
#include <sstream>		// For timer

#include <SDL_mixer.h>	// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <cstdlib>		// For Random Numbers
#include <ctime>		// For Random Numbers
#include <list>
#include <vector>

class Game {
public:
	//The music that will be played
	Mix_Music *gMusic = NULL;		// Mix_Music: Data type for music
	//The sound effects that will be used (pointers)
	//Mix_Chunk *gNinjaFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	//Mix_Chunk *gLaserFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	//Mix_Chunk *gLaserEFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	//Mix_Chunk *gEngineFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds

	Uint8 a = 0;					// Modulation component

	int alphaUp = 5, alphaDown = 5;
	int counter = 0;
	
	bool init();					// Starts up SDL and creates window
	bool loadMedia();				// Loads media//void close();
	void update();
	void close();					// Frees media and shuts down SDL

	void spawnEnemies();
	void spawnEnemyShip();			// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus();			// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell();			// 2017/01/10 JOE: add function to create blood cells
	void spawnSmallBloodCell();
	void spawnWhiteBloodCell();
	void spawnLaser();
	void spawnEnemyLaser(int x, int y);			// 2017/01/10
	void spawnNinjaStar();			// 2017/01/09 JOE: added function to create ninja star weapons
	void spawnPowerUp();

	bool playerInput(bool quit);	// 2017/01/09 JOE: Handle input from player
	void renderGameObjects();		// 2017-01-09 JOE: Render the game objects to the screen
	void moveGameObjects();			// 2017-01-09 JOE: Move the game objects on the screen
	void destroyGameObjects();		// 2017-01-09 JOE: Destroy the game objects when finished on the screen

	void playerFlashOnCollide();	// 2017-01-09 JOE: The player texture flashes on collision with other Game Objects
	void flashGameObject(int &alpha, bool &flash, int rate = 10, int times = 0);
};

#endif
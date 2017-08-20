/*
*-------------------------------------------------
*		Game.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/
#pragma once
#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <iostream>

class Game {
public:
	int alphaUp = 5, alphaDown = 255;

	bool init();					// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();					// Frees media and shuts down SDL
	void spawnLaser();

	bool playerInput(bool quit);
	void renderGameObjects();
	void moveGameObjects();
	void destroyGameObjects();

	void playerFlashOnCollide();	// 2017-01-09 JOE: The player texture flashes on collision with other Game Objects
};

#endif
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

#include <iostream>

class Game {
public:
	//bool init();					// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();					// Frees media and shuts down SDL
	void spawnLaser();
	void destroyLaser();
};

#endif
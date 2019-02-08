/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Level.cpp
	- Description:			Class for levels of the game
	- Information:			The level class was to be used to separate the Level functionality from the Game class

	- Log:

		2017/03/21			Divide the game into levels
		2017/03/22			Moved over all game functionality from Game class, but other classes are relying on it
							for spawning objects etc. so did not make the final version
----------------------------------------------------------------------------------------------------------------------*/
/*
	2017/03/21 Divide the game into levels

#include "SDL.h"
#include "Level.h"
#include "Texture.h"

Texture gPlayer1Texture;
Texture gPlayer2Texture;
Texture gRocketTexture;
Texture gPowerUpRocketTexture;
Texture gEnemySpriteSheetTexture;

SDL_Rect gEnemySpriteClips[4];


Level::Level(int level) {
	Game::Instance()->setCurrentLevel(level);					// Set the current level

}

void Level::loadMedia() {
	bool success = true;														// Successful loading flag

	// Global Level Media

	// Player ships
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png")) {					// Player 1 Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.png")) {					// Player 2 Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	// Power Ups
	if (!gPowerUpRocketTexture.loadFromFile("Art/PowerUpRocket.png")) {			// Rocket Power Up Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}
	// Enemies
	if (!gEnemySpriteSheetTexture.loadFromFile("Art/EnemySpriteSheet2.png")) {	// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Ship animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (int i = 0; i < 4; ++i) {
			gEnemySpriteClips[i].x = 0;
			gEnemySpriteClips[i].y = i * 50;
			gEnemySpriteClips[i].w = 120;
			gEnemySpriteClips[i].h = 50;
		}
	}
	// Specific Level Media
	if (Game::Instance()->getCurrentLevel() == LEVEL_1) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3) {
	}
}

void Level::update() {
}

void Level::render() {
}

void Level::clearMedia() {
	if (Game::Instance()->getCurrentLevel() == LEVEL_1) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3) {
	}
}
*/
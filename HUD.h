#ifndef HEADS_UP_DISPLAY_H
#define HEADS_UP_DISPLAY_H

#include "Texture.h"

class HUD {
public:
	Texture gLevelTextTexture;			// Current level displayed at top of game screen
	//Texture gTimeTextTexture;			// Countdown time displayed in game screen
	Texture gSpeedBoostTextTexture;		// Text "SPEED BOOST"
	Texture gPowerUpRocketTexture2;		// Texture for Rocket power up
	Texture gNumRocketsTextTexture1;	// Indicate the number of rockets for player 1
	//Texture gNumRocketsTextTexture2;	// Indicate the number of rockets for player 2
	Texture gCreatedByTextTexture;		// Created by message at bottom of screen for demo
	Texture gP1LivesTexture;			// Player 1 Small ship for number of lives
	Texture gP2LivesTexture;			// Player 2 Small Ship for number of lives
	Texture gP1ScoreTextTexture;		// Player 1 current score
	Texture gP2ScoreTextTexture;		// Player 2 current score

	bool loadLevelStuff(SDL_Renderer *rend);
	void resetHUD();
	void closeLevelStuff();

	void rendPlayerLives(int livesP1, int livesP2, SDL_Renderer *rend);
	void createdByText(SDL_Renderer *rend);

	void rocketIndicator(int numRockets, int player, bool alive, SDL_Renderer *rend);
	void speedBoostIndicator(bool boost, SDL_Renderer *rend);
	void playerScore(int scoreP1, int scoreP2, SDL_Renderer *rend);
	//void gameTime(int time, SDL_Renderer *rend);
	void displayLevelNum(int levelNum, SDL_Renderer *rend);
};

#endif
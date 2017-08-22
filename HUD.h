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

	void rendPlayerLives(SDL_Renderer *rend, int livesP1, int livesP2 = 0);
	void createdByText(SDL_Renderer *rend);

	void rocketIndicator(int numRockets, int player, bool alive, SDL_Renderer *rend);
	void speedBoostIndicator(bool boost, SDL_Renderer *rend);
	void playerScore(SDL_Renderer *rend, bool twoPlayer, int scoreP1, int scoreP2 = 0);		// 2017-02-23 Player 2 score initialised to 0 to allow reusing the function for single player game
	//void gameTime(int time, SDL_Renderer *rend);
	void displayLevelNum(int levelNum, SDL_Renderer *rend);
};

#endif
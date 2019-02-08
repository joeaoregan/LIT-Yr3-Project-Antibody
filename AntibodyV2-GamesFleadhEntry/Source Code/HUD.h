#ifndef HEADS_UP_DISPLAY_H
#define HEADS_UP_DISPLAY_H

#include "Texture.h"

class HUD {
public:
	TTF_Font *gHUDFont = NULL;

	Texture gLevelTextTexture;			// Current level displayed at top of game screen
	Texture gSpeedBoostTextTexture;		// Text "SPEED BOOST"
	Texture gPowerUpRocketTexture;		// Texture for Rocket power up
	Texture gNumRocketsTextTexture1;	// Indicate the number of rockets for player 1
	Texture gNumRocketsTextTexture2;	// Indicate the number of rockets for player 2
	Texture gCreatedByTextTexture;		// Created by message at bottom of screen for demo
	Texture gP1LivesTexture;			// Player 1 Small ship for number of lives
	Texture gP2LivesTexture;			// Player 2 Small Ship for number of lives
	Texture gP1ScoreTextTexture;		// Player 1 current score
	Texture gP2ScoreTextTexture;		// Player 2 current score
	//Texture gTimeTextTexture;			// Countdown time displayed in game screen
	//Texture gNumRocketsTextTexture2;	// Indicate the number of rockets for player 2

	bool loadLevelStuff();
	void resetHUD();
	void closeLevelStuff();

	void rendPlayerLives(int livesP1, int livesP2 = 0);
	void createdByText();

	void rocketIndicator(int numRockets, int player, bool alive);
	void speedBoostIndicator(bool boost);
	void playerScore(bool twoPlayer, int scoreP1, int scoreP2 = 0);			// 2017-02-23 Player 2 score initialised to 0 to allow reusing the function for single player game
	//void gameTime(int time, SDL_Renderer *rend);
	void displayLevelNum(int levelNum);

	void percentageNinjaStarKills(bool twoPlayer, int ninja1, int ninja2); // 2017/03/01 Track a kill rate for ninja stars
	void playerScoresCounter(bool twoPlayer, int p1, int p2);
};

#endif
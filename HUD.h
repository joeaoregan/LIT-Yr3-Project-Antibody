/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					HUD.h
	- Description:			Header file for the heads up display class.
	- Information:			Contains all function definitions and variables for the HUD.
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef HEADS_UP_DISPLAY_H
#define HEADS_UP_DISPLAY_H

#include "Texture.h"

class HUD {
public:
	/* VARIABLES */

	// Viewports
	//SDL_Rect gameVP;	// Main game screen view port
	SDL_Rect UIVP;		// Menu below main game screen view port
	SDL_Rect mapVP;		// Map indicating the ships current location in the professors body
	SDL_Rect weaponVP1;	// Indicates the currently selected main weapon
	SDL_Rect weaponVP2;	// Indicates the currently selected main weapon
	SDL_Rect rocketVP1;	// Indicates the current amount of Rockets for Player 1
	SDL_Rect rocketVP2;	// Indicates the current amount of Rockets for Player 2
	SDL_Rect boostVP1;	// Indicates if Player 1 speed boost is active
	SDL_Rect boostVP2;	// Indicates if Player 2 speed boost is active

	// Player variables to display information for
	int scoreP1, scoreP2;		// Score for Player
	bool aliveP1, aliveP2;		// Player is alive or not
	int livesP1, livesP2;		// Number of lives for each player
	int gradeP1, gradeP2;		// The current grade of the laser weapon (single, double, or triple laser beams)
	int rocketsP1, rocketsP2;	// The number of rockets for each player
	bool speedP1, speedP2;		// Is Players speed boost active
	float timerP1, timerP2;		// Timer for speedboost

	int weaponScrolling;				// Scroll the image for current default laser weapon // 2017/03/20 Moved from Game class

	TTF_Font *gHUDFont = NULL;

	Texture gLevelTextTexture;			// Current level displayed at top of game screen
	Texture gSpeedBoostTextTexture;		// Text "SPEED BOOST"
	Texture gPowerUpRocketTexture;		// Texture for Rocket power up
	Texture gNumRocketsTextTexture1;	// Indicate the number of rockets for player 1
	Texture gNumRocketsTextTexture2;	// Indicate the number of rockets for player 2
	Texture gCreatedByTextTexture1;		// Created by message at bottom of screen for demo - ANTIBODY
	Texture gCreatedByTextTexture2;		// Created by message at bottom of screen for demo - A GAME BY
	Texture gCreatedByTextTexture3;		// Created by message at bottom of screen for demo - JOE O'REGAN, SEAN HORGAN, BRIAN RYAN 
	Texture gP1LivesTexture;			// Player 1 Small ship for number of lives
	Texture gP2LivesTexture;			// Player 2 Small Ship for number of lives
	Texture gP1ScoreTextTexture;		// Player 1 current score
	Texture gP2ScoreTextTexture;		// Player 2 current score
	//Texture gTimeTextTexture;			// Countdown time displayed in game screen
	//Texture gNumRocketsTextTexture2;	// Indicate the number of rockets for player 2

	/* FUNCTIONS */

	void getPlayerInfo(bool a1, bool a2, int l1, int l2, int g1, int g2, int r1, int r2, bool sp1, bool sp2, float t1, float t2);	// Import information from Game class

	bool miniMap;															// 2017/03/20 Moved from Game class, decide between full and mini map

	void render();															// 2017/03/20 Combine all Heads Up Display rendering to one main render function
	void shipPositionOnMap();												// 2017/03/20 Positions on mini map

	bool loadHUDMedia();													// HUD media, Set viewports, render text textures
	void resetHUD();														// Reset the Heads Up Display, including map viewport, and scrolling
	void closeLevelStuff();													// Free Heads Up Display media from memory

	void rendPlayerLives(int livesP1, int livesP2 = 0);						// Display the number of lives for each player
	void createdByText();													// Display animated Game Creators text

	void rocketIndicator(int numRockets, int player, bool alive);			// Display the number of rockets in each players inventory
	void speedBoostIndicator(bool boost);									// Indicate Players speed boost is active and show timer
	void playerScore(bool twoPlayer, int scoreP1, int scoreP2 = 0);			// 2017-02-23 Player 2 score initialised to 0 to allow reusing the function for single player game
	//void gameTime(int time, SDL_Renderer *rend);
	void displayLevelNum(int levelNum);										// Display the current level number

	void percentageNinjaStarKills(bool twoPlayer, int ninja1, int ninja2);	// 2017/03/01 Track a kill rate for ninja stars
	void playerScoresCounter(bool twoPlayer, int p1, int p2);				// The 
};

#endif
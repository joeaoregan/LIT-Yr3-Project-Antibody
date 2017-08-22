/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					SplashScreen.h
		- Description:			Handles intro screens, information screens and their random movement
		- Information:			Game intro screens and information screens at start of game are created in this class, 
								and transition screens between level with scores and level objectives.
								Displays final score and game winner at end of game.

								Backgrounds have random scrolling, up / down / left / right to give a
								transition affect between title, logo, and information screens

		- Log:
			2017/03/06			Added function for randomly selecting the scrolling direction for level background logos
								Added function for choosing the level background ID based on the level
								Added array for loading textures
			2017/02/09			 Added separate function for text and logos to Game class
			2017/02/08			Added separate splash screen class SplashScreen.h for displaying splash screens
								Moved press enter to continue for splash screens instead of delay before progressing to level
			2017/02/02			Added storyline at intro to game
			2017/01/20			Added game over message
			2017/01/18			Added splash screens at start of game, Game Title & Game Creators
								Added pressButtonToContinue() function for splash screens at start of game, so player can read writing at own pace
			2017/01/17			Added scrolling text to intro screens
								Added wrapped text to add new line character for level intro splash screens
			2017/01/11			Added flashing game over texture
------------------------------------------------------------------------------------------------------------------------------------------------------- */
#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

//#include <SDL_ttf.h>
#include "Texture.h"
#include <iostream>

class SplashScreen {
public:
	/* VARIABLES */

	TTF_Font *gFont = NULL;							// The font to be used for rendered text

	SDL_Color textColour;							// The text colour for rendered text

	// Splash Screens textures
	Texture gFinalScoreTextTexture;					// Final score displayed at end of level / end of game
	Texture gGameWinnerTextTexture;					// Game winner displayed at end of game
	Texture gGameOverTextTexture;					// End of game, game over texture
	Texture gPressEnterSpriteSheetTexture;			// Press Enter to Continue sprite sheet
	Texture gObjectiveTextTexture;					// Objective for each level
	Texture gStoryA, gStoryB, gStoryC;				// 2017/02/01 Story Text

	std::string levelObjective;						// Objective for each level
	std::string storyPage1, storyPage2, storyPage3;	// The story, can spread over 3 screens

	SDL_Rect gPressButtonToContinueSpriteClips[6];	// Sprite frames for Press Button to Continue animation
		
	/* METHODS */

	// Set up / Close Splash Screens
	bool initSplashScreens();						// Load media for Splash Screens
	void closeSplashScreens();						// Free media for Splash Screens

	// Game Title & Created By SplashScreens
	bool displayGameTitleScreens();					// Display intro screens at start of game before menu		

	// Level 1 Logo & Info Screens
	bool levelIntroScreens(int level);												// Level background with scrolling text for objective
	void infoScreenEnemies(int level, int seconds, int startAt = SCREEN_HEIGHT);	// Scroll text and image up the screen with information about the enemies in each level
	void infoScreenPowerUps(int level, int seconds, int startAt = SCREEN_HEIGHT);	// Render information for each levels Power Ups
	void infoScreenStory(int level, int seconds, int startAt = SCREEN_HEIGHT);		// Display each levels story, up to 3 pages
	void endOfGame(int level, std::string finalScore = "", std::string winner = "");// Display final score, game winner, game over, level complete messages

	// Scroll text up the screen, from a start point to an end point
	void scrollUpText(std::string backgroundID, Texture & text, int seconds = 0, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // 2017/02/26 Edited to take an ID. Change rate to increase speed, higher number = faster
																																				
	void pressButtonToContinue(SDL_Event e);																						// Press Any Key To Continue
	
	// Level Background Functions
	std::string chooseBackground(int level);																						// 2017/03/06 Choose the level background image to display
	void scrollRandomBackground(std::string textureID, int rate = 20, int seconds = 0);												// 2017/03/06 Random direction to scroll the background
	void scrollLogoHorizontal(std::string textureID, int seconds = 0, int rate = 20, int startAt = -SCREEN_WIDTH, int stopAt = 0);	// Scroll message Up or Down. Default is scroll from Left to Right
	void scrollLogoVertical(std::string textureID, int seconds = 1, int rate = 10, int startAt = -SCREEN_HEIGHT, int stopAt = 0);	// Scroll message from left or right. Default is scroll down from top, -600 starts above the screen
};

#endif
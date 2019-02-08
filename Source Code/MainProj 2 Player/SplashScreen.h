#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

//#include <SDL_ttf.h>
#include "Texture.h"
#include <iostream>

class SplashScreen {
public:
	// Set up / Close Splash Screens
	bool initSplashScreens();
	void closeSplashScreens();

	// Game Title & Created By SplashScreens
	bool displayGameTitleScreens();

	// Level 1 Logo & Info Screens
	bool levelIntroScreens(int level);
	void infoScreenEnemies(int level, int seconds, int startAt = SCREEN_HEIGHT);
	void infoScreenPowerUps(int level, int seconds, int startAt = SCREEN_HEIGHT);
	void infoScreenStory(int level, int seconds, int startAt = SCREEN_HEIGHT);
	void endOfGame(int level, std::string finalScore = "", std::string winner = "");

	// Scroll text up the screen, from a start point to an end point
	void scrollUpText(std::string backgroundID, Texture & text, int seconds = 0, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // 2017/02/26 Edited to take an ID. Change rate to increase speed, higher number = faster
																																				// Press Any Key To Continue
	void pressButtonToContinue(SDL_Event e);

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

	TTF_Font *gFont = NULL;							// The font to be used for rendered text

	SDL_Color textColour;							// The text colour for rendered text

													// Level Background Functions
	std::string chooseBackground(int level);																						// 2017/03/06 Choose the level background image to display
	void scrollRandomBackground(std::string textureID, int rate = 20, int seconds = 0);												// 2017/03/06 Random direction to scroll the background
	void scrollLogoHorizontal(std::string textureID, int seconds = 0, int rate = 20, int startAt = -SCREEN_WIDTH, int stopAt = 0);	// Default is scroll from Left to Right
	void scrollLogoVertical(std::string textureID, int seconds = 1, int rate = 10, int startAt = -SCREEN_HEIGHT, int stopAt = 0);	// Default is scroll down from top, -600 starts above the screen
};

#endif
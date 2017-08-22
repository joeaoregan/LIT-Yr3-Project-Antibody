#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

//#include <SDL_ttf.h>
#include "Texture.h"

class SplashScreen {
public:
	// Game Title & Created By SplashScreens
	bool displayGameIntroSplashScreens();
	void scrollCreatedBySplashScreen(int startAt = 0, int seconds = 1);

	// Level 1 Logo & Info Screens
	bool level1IntroScreens();
	void scrollDownL1Logo(int startAt);
	void infoScreenL1Enemies(int seconds, int startAt, Texture &story);
	void infoScreenL1PowerUps(int seconds, int startAt, Texture &story);
	void level1FinalScore();
	
	// Scroll text up the screen, from a start point to an end point
	void scrollUpText(std::string backgroundID, Texture & text, int seconds = 0, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // 2017/02/26 Edited to take an ID. Change rate to increase speed, higher number = faster

	// Press Any Key To Continue
	void pressButtonToContinue(SDL_Event e);

	// Level 2 Logo & Info Screens
	//bool level2IntroScreens(SDL_Renderer *rend);
	void scrollRightL2Logo(int startAt);






	Texture gFinalScoreTextTexture;		// Final score displayed at end of level / end of game
	Texture gGameWinnerTextTexture;		// Game winner displayed at end of game
	Texture gGameOverTextTexture;		// End of game, game over texture

	//Texture gEnemyShipTexture;			// Enemy Ship for info screen
	//Texture gVirusGreenTexture;			// Enemy Virus
	//Texture gVirusOrangeTexture;		// Enemy Virus Orange
	//Texture gVirusBlueTexture;			// Enemy Virus Blue

	Texture gPressEnterSpriteSheetTexture;	// Press Enter to Continue sprite sheet

	Texture gLevelObjectiveTextTexture;// Objective for each level

	// Story Text
	Texture gStoryA;	// 2017/02/01
	Texture gStoryB;	// 2017/02/01
	Texture gStoryC;	// 2017/02/01

						// Splash Screens / Logos
	Texture gLevel1;	// 2017/01/18 Texture for level Splash Screen 1
	Texture gLevel2;	// 2017/01/18 Texture for level Splash Screen 2
	Texture gLevel3;	// 2017/01/18 Texture for level Splash Screen 3

	Texture test;

	// Images for information Splash Screen
	//Texture gEnemyShipTextureA;			// Enemy Ship for info screen	USING SAME IMAGES AS GAME SPRITES
	//Texture gEnemyVirusTextureA;		// Enemy Virus
	//Texture gEnemyVirusOrangeTextureA;	// Enemy Virus Orange


	//Texture gLevelObjectiveTextTextureA;// Objective for each level
	std::string storyPage1;
	std::string storyPage2;
	std::string storyPage3;
	
	bool initSplashScreens();
	void closeSplashScreens();
	void level2FinalScore();
	void level3FinalScore();
	void endOfGame(int level, std::string finalScore = "", std::string winner = "");

	SDL_Rect gPressButtonToContinueSpriteClips[6];			// Sprite frames for Press Button to Continue animation

	//bool level3IntroScreens(SDL_Renderer *rend);



	//void enemyInformationSplashScreen(SDL_Renderer *rend, Texture &background, Texture &orangeVirus, Texture &enemyShip, Texture &health, Texture &laser);
	
	TTF_Font *gFont = NULL;

	//bool displaySplashScreens(SDL_Renderer *rend, Texture *texture1, Texture *texture2);

	//void displayLevelSplashScreen(std::string objective, SDL_Renderer *rend, int level);

	//void scrollUpLogo(SDL_Renderer *rend, Texture &texture, int seconds = 1, int rate = 5); 
	void scrollVerticalLogo(Texture &texture, int seconds = 1, int rate = 10, int startAt = -SCREEN_HEIGHT, int stopAt = 0);	// Default is scroll down from top, -600 starts above the screen

	//void scrollUpText(SDL_Renderer *rend, Texture &background, Texture & text, int seconds, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // Change rate to increase speed, higher number = faster


	SDL_Color textColour;

	//std::string l1Objective = "Destroy enemy virus and ships      \nThe player with the highest score\nIs the winner";
	//std::string l2Objective = "Destroy more enemy virus and ships\nThe player with the highest score\nIs the winner";
	//std::string l3Objective = "Destroy even more enemy virus and ships\nThe player with the highest score\nIs the winner";

	//void displaySplashScreens(SDL_Renderer *rend, Texture *texture1, Texture *texture2, bool *displayIntro);

	//SplashScreen(int x, int y, Texture &one, Texture &two, Texture &three);		// Constructor: Initialize position and animation

	//void render(Texture &texture, SDL_Renderer *rend);						// Shows the particle

//private:
	//int mPosX, mPosY;			// Offsets
};

#endif
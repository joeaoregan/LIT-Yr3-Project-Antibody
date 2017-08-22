#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <SDL_ttf.h>
#include "Texture.h"

class SplashScreen {
public:

	Texture gFinalScoreTextTexture;		// Final score displayed at end of level / end of game
	Texture gGameWinnerTextTexture;		// Game winner displayed at end of game
	Texture gGameOverTextTexture;		// End of game, game over texture

	std::string storyPage1;
	std::string storyPage2;
	std::string storyPage3;
	
	bool initSplashScreens(SDL_Renderer *rend);
	void closeSplashScreens();
	void level1FinalScore(SDL_Renderer *rend);
	void level2FinalScore(SDL_Renderer *rend);
	void level3FinalScore(SDL_Renderer *rend);
	void endOfGame(SDL_Renderer *rend, int level, std::string finalScore = "", std::string winner = "");

	Texture gPressEnterSpriteSheetTexture;					// Press Enter to Continue sprite sheet
	SDL_Rect gPressButtonToContinueSpriteClips[6];			// Sprite frames for Press Button to Continue animation

	bool level1IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip, Texture &Laser, Texture &Health, Texture &rocket);
	bool level2IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip);
	bool level3IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip);

	Texture gLevelObjectiveTextTexture;// Objective for each level

	void pressButtonToContinue(SDL_Renderer *rend, SDL_Event e);

	void enemyInformationSplashScreen(SDL_Renderer *rend, Texture &background, Texture &tx1, Texture &tx2, Texture &tx3, Texture &img4, Texture &img5, Texture &img6);

	// Intro Logos
	Texture gGameLogoTexture;		// 2017/01/18 Texture for game Splash Screen 1
	Texture gGameCreatorsTexture;	// 2017/01/18 Texture for game Splash Screen 2

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


	//TTF_Font *gFontRetro20A = TTF_OpenFont("Fonts/Retro.ttf", 20);
	TTF_Font *gFont = NULL;

	//bool displaySplashScreens(SDL_Renderer *rend, Texture *texture1, Texture *texture2);
	bool displayGameIntroSplashScreens(SDL_Renderer *rend);

	//void displayLevelSplashScreen(std::string objective, SDL_Renderer *rend, int level);

	//void scrollUpLogo(SDL_Renderer *rend, Texture &texture, int seconds = 1, int rate = 5); 
	void scrollVerticalLogo(SDL_Renderer *rend, Texture &texture, int seconds = 1, int rate = 10, int startAt = -SCREEN_HEIGHT, int stopAt = 0);	// Default is scroll down from top, -600 starts above the screen

	void scrollUpText(SDL_Renderer *rend, Texture &background, Texture & text, int seconds, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // Change rate to increase speed, higher number = faster

	void infoScreenL1Enemies(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &tx1, Texture &tx2, Texture &tx3);
	void infoScreenL1PowerUps(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &tx1, Texture &tx2, Texture &tx3);



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
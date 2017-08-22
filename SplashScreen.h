#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <SDL_ttf.h>
#include "Texture.h"

class SplashScreen {
public:
	// Intro Logos
	Texture gLogo1;		// 2017/01/18 Texture for game Splash Screen 1
	Texture gLogo2;		// 2017/01/18 Texture for game Splash Screen 2

	// Story Text
	Texture gStoryA;	// 2017/02/01
	Texture gStoryB;	// 2017/02/01
	Texture gStoryC;	// 2017/02/01

	// Splash Screens / Logos
	Texture gLevel1a;	// 2017/01/18 Texture for level Splash Screen 1
	Texture gLevel2a;	// 2017/01/18 Texture for level Splash Screen 2
	Texture gLevel3a;	// 2017/01/18 Texture for level Splash Screen 3


	//Texture gEnemyShipTextureA;			// Enemy Ship for info screen
	//Texture gEnemyVirusTextureA;			// Enemy Virus
	//Texture gEnemyVirusOrangeTextureA;	// Enemy Virus Orange


	//Texture gLevelObjectiveTextTextureA;// Objective for each level


	//TTF_Font *gFontRetro20A = TTF_OpenFont("Fonts/Retro.ttf", 20);

	//bool displaySplashScreens(SDL_Renderer *rend, Texture *texture1, Texture *texture2);
	bool displayGameIntroSplashScreens(SDL_Renderer *rend);

	//void displayLevelSplashScreen(std::string objective, SDL_Renderer *rend, int level);

	//void scrollUpLogo(SDL_Renderer *rend, Texture &texture, int seconds = 1, int rate = 5); 
	void scrollVerticalLogo(SDL_Renderer *rend, Texture &texture, int seconds = 1, int rate = 10, int startAt = -SCREEN_HEIGHT, int stopAt = 0);	// Default is scroll down from top, -600 starts above the screen

	void scrollUpText(SDL_Renderer *rend, Texture &background, Texture & text, int seconds, int rate = 15, int startAt = SCREEN_HEIGHT, int stopAt = 300); // Change rate to increase speed, higher number = faster

	void scrollTextAndImage(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &tx1, Texture &tx2, Texture &tx3);


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
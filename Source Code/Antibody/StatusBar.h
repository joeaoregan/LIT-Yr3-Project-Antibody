/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					StatusBar.h
	- Description:			Header file for the Status Bar class.
	- Information:			Contains all function definitions and variables for the Status Bar class.
	- Log:
		2017/02/09		Added status bar class StatusBar.h for creating status bars, such as health bar
		2017/01/18		Added health bars for players
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SDL_image.h>

#define MAX_HEALTH 100.0		// The max health for a player
#define VIRUS_TIMER 3.0			// Virus Timer Max time
#define ROCKET_TIMER_SET 3.0	// Rocket Timer Max time
#define START_LEFT 0			// Move status bar left to right
#define START_RIGHT 1			// Move status bar right to left

enum healthBarOrientation { VERTICAL, HORIZONTAL };

class StatusBar {
public:
	StatusBar();
	~StatusBar();

	float startTime = 3.0;
	float endTime = 0.0;

	SDL_Color fgColour = { 0, 255, 0, 255 };						// Set foreground colour as green
	SDL_Color fgColourBlue = { 0, 200, 255, 255 };					// Set foreground colour as Blue
	SDL_Color bgColour = { 255, 0, 0, 255 };						// Set background colour as red
	SDL_Color bgColourOrange = { 255, 150, 0, 255 };				// Set background colour as Orange
	SDL_Color bgColourBlue = { 0, 0, 255, 255 };					// Set background colour as Blue

	void createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation, int startFrom = START_LEFT);
	void playerHealthBar(int x, int y, int w, float Percent);
	void virusTimer(int x, int y, int w, float Percent);
	void virusTimerBlue(int x, int y, int w, float Percent);
	void rocketPowerBar(int x, int y, int w, float time);			// Rocket timer -> build up power for rocket
	void speedBoostBar(float healthd, int startFrom = START_LEFT);	// 2017/02/20 Speed boost bar
	void enemyBossBar(float health);								// 2017/03/18 Added Bar for Enemy Boss
};

#endif
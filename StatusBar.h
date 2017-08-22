#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SDL_image.h>

#define MAX_HEALTH 100.0				// The max health for a player
#define VIRUS_TIMER 3.0
#define ROCKET_TIMER_SET 3.0
#define START_LEFT 0
#define START_RIGHT 1

enum healthBarOrientation { VERTICAL, HORIZONTAL };

class StatusBar {
public:
	StatusBar();
	~StatusBar();

	float startTime = 3.0;
	float endTime = 0.0;

	SDL_Color fgColour = { 0, 255, 0, 255 };								// Set foreground colour as green
	SDL_Color fgColourBlue = { 0, 200, 255, 255 };							// Set foreground colour as Blue
	SDL_Color bgColour = { 255, 0, 0, 255 };								// Set background colour as red
	SDL_Color bgColourOrange = { 255, 150, 0, 255 };						// Set background colour as Orange
	SDL_Color bgColourBlue = { 0, 0, 255, 255 };							// Set background colour as Blue

	void createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer *rend, int orientation, int startFrom = START_LEFT);
	void playerHealthBar(int x, int y, int w, float Percent, SDL_Renderer *rend);
	void virusTimer(int x, int y, int w, float Percent, SDL_Renderer *rend);
	void virusTimerBlue(int x, int y, int w, float Percent, SDL_Renderer *rend);
	void rocketPowerBar(int x, int y, int w, float time, SDL_Renderer *rend);				// Rocket timer -> build up power for rocket
	void speedBoostBar(float health, SDL_Renderer *rend, int startFrom = START_LEFT);		// 2017/02/20 Speed boost bar
};

#endif
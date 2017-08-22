#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SDL_image.h>

#define MAX_HEALTH 100.0				// The max health for a player
#define VIRUS_TIMER 3.0

enum healthBarOrientation { VERTICAL, HORIZONTAL };

class StatusBar {
public:
	StatusBar();
	~StatusBar();

	float startTime = 3.0;
	float endTime = 0.0;

	SDL_Color fgColour = { 0, 255, 0, 255 };								// Set foreground colour as green
	SDL_Color fgColourBlue = { 0, 200, 255, 255 };							// Set foreground colour as green
	SDL_Color bgColour = { 255, 0, 0, 255 };								// Set background colour as red
	SDL_Color bgColourOrange = { 255, 150, 0, 255 };						// Set background colour as red

	void createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer *rend, int orientation);
	void playerHealthBar(int x, int y, int w, float Percent, SDL_Renderer *rend);
	void virusTimer(int x, int y, int w, float Percent, SDL_Renderer *rend);
	
};

#endif
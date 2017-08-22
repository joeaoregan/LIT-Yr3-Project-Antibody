#include "StatusBar.h"
#include "Game.h"

#define MAX_HEALTH 100.0				// The max health for a player

StatusBar::StatusBar() {
}

StatusBar::~StatusBar() {
}

void StatusBar::speedBoostBar(float percent, int startFrom) {
	if (ROCKET_TIMER_SET - percent == 0) createStatusBar(0, 50, 60, 10, percent / ROCKET_TIMER_SET, { 36, 136, 36, 255 }, bgColour, HORIZONTAL, startFrom);	// -10 Places 10 pixels above Player Ship
	else createStatusBar(0, 50, 60, 10, percent / ROCKET_TIMER_SET, { 0, 255, 0, 255 }, bgColour, HORIZONTAL, startFrom);	// -10 Places 10 pixels above Player Ship
}
void StatusBar::playerHealthBar(int x, int y, int w, float health) {
	createStatusBar(x + (w / 4), y - 10, w / 2, 5, health / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);	// -10 Places 10 pixels above Player Ship
}

void StatusBar::rocketPowerBar(int x, int y, int w, float time) {
	createStatusBar(x + (w / 4), y + 57, w / 2, 5, time / ROCKET_TIMER_SET, {125,125,125,255}, bgColour, HORIZONTAL, START_RIGHT);	// +57 Places 10 pixels below Player Ship (height = 47)
}

void StatusBar::virusTimer(int x, int y, int w, float virusTimer) {
	createStatusBar(x + w + 25, y + 10, 5, 60, virusTimer / VIRUS_TIMER, fgColourBlue, bgColourOrange, VERTICAL);	//
																														//bar.createStatusBar(, 5, (listOfEnemyVirus[index]->getHeight() / 3) * 2, virusBar / listOfEnemyVirus[index]->getTimer(), fgColourBlue, bgColourOrange, gRenderer, VERTICAL); // 2/3s the height of the virus
}
void StatusBar::virusTimerBlue(int x, int y, int w, float virusTimer) {
	createStatusBar(x + w + 25, y + 10, 5, 60, virusTimer / VIRUS_TIMER, fgColourBlue, bgColourBlue, VERTICAL);	//
																														//bar.createStatusBar(, 5, (listOfEnemyVirus[index]->getHeight() / 3) * 2, virusBar / listOfEnemyVirus[index]->getTimer(), fgColourBlue, bgColourOrange, gRenderer, VERTICAL); // 2/3s the height of the virus
}

void StatusBar::createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation, int startFrom) {	// Horizontal healthbar 2017/01/20 added if statement to decide orientation of health bar
	SDL_Rect foregroundRect;													// The rectangle to
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(Game::Instance()->getRenderer(), &old.r, &old.g, &old.g, &old.a);
	SDL_Rect backgroundRect = { x, y, w, h };									// Background rectangle with coordinates and dimensions entered
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), BGColor.r, BGColor.g, BGColor.b, BGColor.a);	// Draw a Solid Rectangle with the RGB colour values assigned
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &backgroundRect);
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	// Decide if Healthbar is horizontal or vertical
	if (orientation == HORIZONTAL) {
		int newW = (int)((float)w * Percent);									// new width
		int newX = x + (w - newW);												// new x coord
		if(startFrom == START_LEFT) foregroundRect = { newX, y, newW, h };		// Decrease from left
		else if (startFrom == START_RIGHT) foregroundRect = { x, y, newW, h };	// 2017/02/17 Decrease from right
	}
	else if (orientation == VERTICAL) {
		int ph = (int)((float)h * Percent);
		int py = y + (h - ph);
		foregroundRect = { x, py, w, ph };
	}
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &foregroundRect);
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), old.r, old.g, old.b, old.a);
}

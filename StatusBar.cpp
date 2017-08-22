#include "StatusBar.h"

StatusBar::StatusBar() {
}

StatusBar::~StatusBar() {
}

void StatusBar::playerHealthBar(int x, int y, int w, float health, SDL_Renderer *rend) {
	createStatusBar(x + (w / 4), y - 10, w / 2, 5, health / MAX_HEALTH, fgColour, bgColour, rend, HORIZONTAL);	// -10 Places 10 pixels above Player Ship
}

void StatusBar::virusTimer(int x, int y, int w, float virusTimer, SDL_Renderer *rend) {
	createStatusBar(x + w + 10, y + 10, 5, 60, virusTimer / VIRUS_TIMER, fgColourBlue, bgColourOrange, rend, VERTICAL);	// 
																														//bar.createStatusBar(, 5, (listOfEnemyVirus[index]->getHeight() / 3) * 2, virusBar / listOfEnemyVirus[index]->getTimer(), fgColourBlue, bgColourOrange, gRenderer, VERTICAL); // 2/3s the height of the virus
}
void StatusBar::virusTimerBlue(int x, int y, int w, float virusTimer, SDL_Renderer *rend) {
	createStatusBar(x + w + 10, y + 10, 5, 60, virusTimer / VIRUS_TIMER, fgColourBlue, bgColourBlue, rend, VERTICAL);	// 
																														//bar.createStatusBar(, 5, (listOfEnemyVirus[index]->getHeight() / 3) * 2, virusBar / listOfEnemyVirus[index]->getTimer(), fgColourBlue, bgColourOrange, gRenderer, VERTICAL); // 2/3s the height of the virus
}

void StatusBar::createStatusBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer *rend, int orientation) {	// Horizontal healthbar 2017/01/20 added if statement to decide orientation of health bar
	SDL_Rect fgrect;
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(rend, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(rend, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(rend, &bgrect);
	SDL_SetRenderDrawColor(rend, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	// Decide if Healthbar is horizontal or vertical
	if (orientation == HORIZONTAL) {
		int pw = (int)((float)w * Percent);
		int px = x + (w - pw);
		fgrect = { px, y, pw, h };
	}
	else if (orientation == VERTICAL) {
		int ph = (int)((float)h * Percent);
		int py = y + (h - ph);
		fgrect = { x, py, w, ph };
	}
	SDL_RenderFillRect(rend, &fgrect);
	SDL_SetRenderDrawColor(rend, old.r, old.g, old.b, old.a);
}
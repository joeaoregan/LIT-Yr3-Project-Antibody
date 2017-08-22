#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include "Button.h"
#include "Texture.h"

class HighScores {
public:
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gScoresMenuTextTexture1;
	Texture gScoresMenuTextTexture2;

	//Buttons objects
	Button gReturnToMenu;

	SDL_Rect gSpriteClipsScoresMenu[1];
	Texture gButtonSpriteSheetTexture3;

	void closeMenuMedia();
	void handleMenuEvents(SDL_Event& e);
	bool loadMenuMedia();
	void draw();
};

#endif
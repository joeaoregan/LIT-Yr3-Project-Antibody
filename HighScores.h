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
	Texture gScoresMenuTextTexture3;

	//Buttons objects
	Button gReturnToMenu;

	Button gScoressMenuButtons[1];
	SDL_Rect gSpriteClipsScoresMenu[1];
	Texture gButtonSpriteSheetTexture3;

	bool loadHighScoresMedia();
	void closeHighScoresMedia();
	void handleHighScoresEvents(SDL_Event& e);
	void draw();

};

#endif


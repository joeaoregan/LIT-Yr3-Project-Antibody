#ifndef ENTER_NAME_H
#define ENTER_NAME_H

#include "Button.h"
#include "Texture.h"

class EnterName {
public:
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gNameMenuTextTexture1;
	Texture gNameMenuTextTexture2;
	Texture gNameMenuTextTexture3;
	Texture gNameMenuTextTexture4;

	//Buttons objects
	Button gNameButtons[TOTAL_ENTER_NAME_BUTTONS];

	SDL_Rect gSpriteClipsName[TOTAL_ENTER_NAME_BUTTONS];
	Texture gButtonSpriteSheetTexture4;

	void closeMenuMedia();
	void handleMenuEvents(SDL_Event& e);
	bool loadMenuMedia();
	void draw();
};

#endif
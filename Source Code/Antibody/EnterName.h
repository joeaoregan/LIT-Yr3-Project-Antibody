/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnterName.h
	- Description:			Header file for the name entering system
	- Information:			FILL IN INFO HERE
	----------------------------------------------------------------------------------------------------------------------*/
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

	bool loadNameMedia();
	void closeNameMedia();
	void handleNameEvents(SDL_Event& e);
	void draw();
};

#endif
#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "Texture.h"

class Menu {
public:
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gMenuTextTexture1;
	Texture gMenuTextTexture2;
	Texture gMenuTextTexture3;
	Texture gMenuTextTexture4;
	Texture gMenuTextTexture5;
	Texture gMenuTextTexture6;
	Texture gMenuTextTexture7;
	Texture gMenuTextTexture8;

	//Buttons objects
	Button gButtons[TOTAL_MAIN_MENU_BUTTONS];
	Button gMenuButtons[TOTAL_MAIN_MENU_BUTTONS];

	SDL_Rect gSpriteClipsMenu[TOTAL_MAIN_MENU_BUTTONS];
	Texture gButtonSpriteSheetTexture;
	
	void closeMenuMedia();
	void handleMenuEvents(SDL_Event& e);
	bool loadMenuMedia();
	void draw();
	void drawPause();
};

#endif
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

	//Buttons objects
	Button gButtons[TOTAL_BUTTONS];
	Button gMenuButtons[TOTAL_BUTTONS];

	SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];
	Texture gButtonSpriteSheetTexture;
	
	void closeMenu();
	void handleMenuEvents(SDL_Event& e);
	bool loadMediaMenu();
	void draw();


	//Menu(int x, int y);							// Initializes the variables
	//~Menu();

	//Mix_Chunk *sound = Mix_LoadWAV("Audio/explosion.wav");		// Explosion sound fx
};

#endif
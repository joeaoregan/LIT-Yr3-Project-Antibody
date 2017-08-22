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

	//Buttons objects
	Button gButtons[TOTAL_BUTTONS];
	Button gMenuButtons[4];

	SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];
	Texture gButtonSpriteSheetTexture;
	
	void closeMenu();
	void handleMenuEvents(SDL_Event& e);
	bool loadMediaMenu(SDL_Renderer *rend);
	void draw(SDL_Renderer *rend);


	//Menu(int x, int y);							// Initializes the variables
	//~Menu();

	//Mix_Chunk *sound = Mix_LoadWAV("Audio/explosion.wav");		// Explosion sound fx
};

#endif
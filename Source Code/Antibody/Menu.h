/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Menu.h
	- Description:			header file for the Menu class.
	- Information:			Contains all function definitions and variables for Menu class.
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "Texture.h"

class Menu {
public:
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gMenuTextTexture1;	// Antibody
	Texture gMenuTextTexture2;
	Texture gMenuTextTexture3;
	Texture gMenuTextTexture4;
	Texture gMenuTextTexture5;
	Texture gMenuTextTexture6;
	Texture gMenuTextTexture7;
	Texture gMenuTextTexture8;	// Pause
	Texture gMenuTextTexture9;	// Resume
	Texture gMenuTextTexture10;	// Return to Main Menu from Pause

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

	void randomBackgroundColour();		// select a random background colour
};

#endif
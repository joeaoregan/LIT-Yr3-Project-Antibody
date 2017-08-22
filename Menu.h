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
	TTF_Font *gFont = NULL;		// Font to use when rendering text

	// Menu Text
	Texture gMenuTextTexture1;	// Antibody (Menu title text)
	Texture gMenuTextTexture2;	// Story Mode button text
	Texture gMenuTextTexture3;	// Single Player button text
	Texture gMenuTextTexture4;	// Two Player button text
	Texture gMenuTextTexture5;	// Settings button text
	Texture gMenuTextTexture6;	// High Scores button text
	Texture gMenuTextTexture7;	// Quit button text
	Texture gMenuTextTexture8;	// Pause button text
	Texture gMenuTextTexture9;	// Resume button text
	Texture gMenuTextTexture10;	// Return to Main Menu from Pause button text

	//Buttons objects
	//Button gDelete[TOTAL_MAIN_MENU_BUTTONS];		// Array of Main Menu buttons
	Button gMenuButtons[TOTAL_MAIN_MENU_BUTTONS];	// Array of Menu buttons

	SDL_Rect gSpriteClipsMenu[TOTAL_MAIN_MENU_BUTTONS];	// Button animation frames
	Texture gButtonSpriteSheetTexture;					// Button animation sprite sheet
	
	void closeMenuMedia();					// Free the Menu media
	void handleMenuEvents(SDL_Event& e);	// Handle events for menu buttons
	bool loadMenuMedia();					// Load the Menu media	
	void draw();							// Render Main Menu textures to screen
	void drawPause();						// Render Pause Menu textures to screen

	void randomBackgroundColour();			// Select a random menu background colour
};

#endif
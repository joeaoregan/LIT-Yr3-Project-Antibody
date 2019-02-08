/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					SettingsMenu.h
		- Description:			A menu containing settings for the game
		- Information:			Buttons are used to select options such as turn on /off music, Full Screen / Windowed
								This function handles the objects for the settings menu. The separate button class
								handles the transitions.

		- Log:
			2017/03/08			Added Settings Menu class
------------------------------------------------------------------------------------------------------------------------------------------------------- */

#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "Button.h"
#include "Texture.h"

class SettingsMenu {
public:
	TTF_Font *gFont = NULL;				// Font used to render text

	// Menu Text
	Texture gSettingsMenuTextTexture1;	// Settings Menu title text
	Texture gSettingsMenuTextTexture2;	// Music On button text
	Texture gSettingsMenuTextTexture3;	// Music Off button text
	Texture gSettingsMenuTextTexture4;	// Full Screen On / Off button text
	Texture gSettingsMenuTextTexture5;	// Main Menu button text
	Texture gSettingsMenuTextTexture6;	// Quit button text
	//Texture gSettingsMenuTextTexture7;// Unused

	//Buttons objects
	Button gSettingsMenuButtons[TOTAL_SETTINGS_MENU_BUTTONS];			// Array of buttons

	SDL_Rect gSpriteClipsSettingsMenu[TOTAL_SETTINGS_MENU_BUTTONS];		// Animation frames
	Texture gButtonSpriteSheetTexture2;									// Sprite sheet for buttons

	bool loadSettingsMedia();					// Load media for Settings Menu
	void closeSettingsMedia();					// Close media for Settings Menu
	void handleSettingsEvents(SDL_Event& e);	// Handle button events
	void draw();								// Render textures to screen
};

#endif
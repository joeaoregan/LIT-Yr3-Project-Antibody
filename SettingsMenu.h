#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "Button.h"
#include "Texture.h"

class SettingsMenu {
public:
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gSettingsMenuTextTexture1;
	Texture gSettingsMenuTextTexture2;
	Texture gSettingsMenuTextTexture3;
	Texture gSettingsMenuTextTexture4;
	Texture gSettingsMenuTextTexture5;
	Texture gSettingsMenuTextTexture6;
	Texture gSettingsMenuTextTexture7;	// Full Screen On / Off

	//Buttons objects
	//Button gButtons[TOTAL_MAIN_MENU_BUTTONS];
	Button gSettingsMenuButtons[TOTAL_SETTINGS_MENU_BUTTONS];

	SDL_Rect gSpriteClipsSettingsMenu[TOTAL_SETTINGS_MENU_BUTTONS];
	Texture gButtonSpriteSheetTexture2;

	bool loadSettingsMedia();
	void closeSettingsMedia();
	void handleSettingsEvents(SDL_Event& e);
	void draw();
};

#endif
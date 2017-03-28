/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					SettingsMenu.cpp
		- Description:			A menu containing settings for the game
		- Information:			Buttons are used to select options such as turn on /off music, Full Screen / Windowed
								This function handles the objects for the settings menu. The separate button class
								handles the transitions.

		- Log:
			2017/03/08			Added Settings Menu class
------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include "SettingsMenu.h"
#include <SDL_ttf.h>

/* 
	Load the media associated with the settings menu
*/
bool SettingsMenu::loadSettingsMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gSettingsMenuTextTexture1.loadFromRenderedText("SETTINGS", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render SETTINGS text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture2.loadFromRenderedText("Music On", textColour, gFont)) {		// can take out the new textColor objects
			printf("Failed to render Music On text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture3.loadFromRenderedText("Music Off", textColour, gFont)) {
			printf("Failed to render Music Off text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture4.loadFromRenderedText("Full Screen On/Off", textColour, gFont)) {
			printf("Failed to render Full Screen text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture5.loadFromRenderedText("Main Menu", textColour, gFont)) {
			printf("Failed to render Main Menu text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture6.loadFromRenderedText("Quit", textColour, gFont)) {
			printf("Failed to render Quit text texture!\n");
			success = false;
		}
		// Backgrounds
		if (!Texture::Instance()->load("Art/PlayerShipOutline.png", "shipOutlineID")) {				// 2017/03/07 Ship Outline Texture
			printf("Failed to load Ship Outline background texture!\n");							// Start Backround
			success = false;
		}

		// Set coordinates for the Settings Menu buttons
		gSettingsMenuTextTexture2.setX((SCREEN_WIDTH - gSettingsMenuTextTexture2.getWidth()) / 2);	// Music on
		gSettingsMenuTextTexture3.setX((SCREEN_WIDTH - gSettingsMenuTextTexture3.getWidth()) / 2);	// Music off
		gSettingsMenuTextTexture4.setX((SCREEN_WIDTH - gSettingsMenuTextTexture4.getWidth()) / 2);	// Full Screen On/Off
		gSettingsMenuTextTexture5.setX((SCREEN_WIDTH - gSettingsMenuTextTexture5.getWidth()) / 2);	// Main Menu
		gSettingsMenuTextTexture6.setX((SCREEN_WIDTH - gSettingsMenuTextTexture6.getWidth()) / 2);	// Quit the game

		gSettingsMenuTextTexture2.setY(200);
		gSettingsMenuTextTexture3.setY(250);
		gSettingsMenuTextTexture4.setY(300);
		gSettingsMenuTextTexture5.setY(350);
		gSettingsMenuTextTexture6.setY(400);
	}

	// Load button sprite image
	if (!gButtonSpriteSheetTexture2.loadFromFile("Art/buttonOne.png")) {							// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//	Set button animation sprites coordinates and dimensions
		for (int i = 0; i < TOTAL_SETTINGS_MENU_BUTTONS; ++i) {
			gSpriteClipsSettingsMenu[i].x = 0;
			gSpriteClipsSettingsMenu[i].y = i * 250;
			gSpriteClipsSettingsMenu[i].w = BUTTON_WIDTH_SETTINGS;
			gSpriteClipsSettingsMenu[i].h = BUTTON_HEIGHT;
		}

		// Set the positions for the Settings Menu buttons
		gSettingsMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH_SETTINGS) / 2, gSettingsMenuTextTexture2.getY());	// Button 1: MUSIC ON
		gSettingsMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH_SETTINGS) / 2, gSettingsMenuTextTexture3.getY());	// Button 2: MUSIC OFF
		gSettingsMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH_SETTINGS) / 2, gSettingsMenuTextTexture4.getY());	// Button 3: FULL SCREEN ON / OFF
		gSettingsMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH_SETTINGS) / 2, gSettingsMenuTextTexture5.getY());	// Button 4: RETURN TO SETTINGS
		gSettingsMenuButtons[4].setPosition((SCREEN_WIDTH - BUTTON_WIDTH_SETTINGS) / 2, gSettingsMenuTextTexture6.getY());	// Button 5: QUIT GAME
	}

	return success;
}

/*
	Handle the events for the settings menu objects
*/
void SettingsMenu::handleSettingsEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_SETTINGS_MENU_BUTTONS; ++i) {
		gSettingsMenuButtons[i].handleEvent(&e, i);	// Handle events for each button in the Settings Menu
	}
}

/*
	Close the media associated with the settings menu, on exiting the men
*/
void SettingsMenu::closeSettingsMedia() {
	std::cout << "Settings Menu: media cleared" << std::endl;

	// Buttons
	gButtonSpriteSheetTexture2.free();

	// Menu
	gSettingsMenuTextTexture1.free();	// Settings Menu heading clear
	gSettingsMenuTextTexture2.free();	// Music On button text clear
	gSettingsMenuTextTexture3.free();	// Music Off button text clear
	gSettingsMenuTextTexture4.free();	// Return To Settings button text clear
	gSettingsMenuTextTexture5.free();	// Quit Game button text clear
	gSettingsMenuTextTexture6.free();	// Full Screen On/Off button text clear
}

/*
	Render the graphics associated with the settings menu to the screen
*/
void SettingsMenu::draw() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 25, 100, 230, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);
	Texture::Instance()->renderMap("shipOutlineID", 0, 50, SCREEN_WIDTH, 620);

	for (int i = 0; i < TOTAL_SETTINGS_MENU_BUTTONS; ++i) {
		gSettingsMenuButtons[i].render(gButtonSpriteSheetTexture2, &gSpriteClipsSettingsMenu[gSettingsMenuButtons[i].mCurrentSprite]);
	}

	gSettingsMenuTextTexture1.render((SCREEN_WIDTH - gSettingsMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gSettingsMenuTextTexture1.getHeight()) / 12);
	gSettingsMenuTextTexture2.render(gSettingsMenuTextTexture2.getX(), gSettingsMenuTextTexture2.getY());	// MUSIC ON
	gSettingsMenuTextTexture3.render(gSettingsMenuTextTexture3.getX(), gSettingsMenuTextTexture3.getY());	// MUSIC OFF
	gSettingsMenuTextTexture4.render(gSettingsMenuTextTexture4.getX(), gSettingsMenuTextTexture4.getY());	// FULL SCREEN ON / OFF
	gSettingsMenuTextTexture5.render(gSettingsMenuTextTexture5.getX(), gSettingsMenuTextTexture5.getY());	// RETURN TO SETTINGS
	gSettingsMenuTextTexture6.render(gSettingsMenuTextTexture6.getX(), gSettingsMenuTextTexture6.getY());	// QUIT GAME

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

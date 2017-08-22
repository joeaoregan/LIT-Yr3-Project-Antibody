/*
	2017/03/08 Added Settings Menu class
*/
/*
	SETTINGS MENU:

	This function handles the objects for the settings menu. The separate button class
	handles the transitions.
*/

#include "SettingsMenu.h"
#include <SDL_ttf.h>

bool SettingsMenu::loadMenuMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gSettingsMenuTextTexture1.loadFromRenderedText("SETTINGS", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render SETTINGS text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture2.loadFromRenderedText("Music On", textColour, gFont)) {	// can take out the new textColor objects
			printf("Failed to render Music On text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture3.loadFromRenderedText("Music Off", textColour, gFont)) {
			printf("Failed to render Music Off text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture4.loadFromRenderedText("Main Menu", textColour, gFont)) {
			printf("Failed to render Main Menu text texture!\n");
			success = false;
		}
		if (!gSettingsMenuTextTexture5.loadFromRenderedText("Quit", textColour, gFont)) {
			printf("Failed to render Quit text texture!\n");
			success = false;
		}
		// Backgrounds
		if (!Texture::Instance()->load("Art/PlayerShipOutline.png", "shipOutlineID")) {				// 2017/03/07 Ship Outline Texture
			printf("Failed to load Ship Outline background texture!\n");							// Start Backround
			success = false;
		}

		gSettingsMenuTextTexture2.setX((SCREEN_WIDTH - gSettingsMenuTextTexture2.getWidth()) / 2);
		gSettingsMenuTextTexture3.setX((SCREEN_WIDTH - gSettingsMenuTextTexture3.getWidth()) / 2);
		gSettingsMenuTextTexture4.setX((SCREEN_WIDTH - gSettingsMenuTextTexture4.getWidth()) / 2);
		gSettingsMenuTextTexture5.setX((SCREEN_WIDTH - gSettingsMenuTextTexture5.getWidth()) / 2);

		gSettingsMenuTextTexture2.setY(200);
		gSettingsMenuTextTexture3.setY(250);
		gSettingsMenuTextTexture4.setY(300);
		gSettingsMenuTextTexture5.setY(350);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture2.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < TOTAL_SETTINGS_MENU_BUTTONS; ++i) {
			gSpriteClipsSettingsMenu[i].x = 0;
			gSpriteClipsSettingsMenu[i].y = i * 200;
			gSpriteClipsSettingsMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsSettingsMenu[i].h = BUTTON_HEIGHT;
		}

		gSettingsMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gSettingsMenuTextTexture2.getY());
		gSettingsMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gSettingsMenuTextTexture3.getY());
		gSettingsMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gSettingsMenuTextTexture4.getY());
		gSettingsMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gSettingsMenuTextTexture5.getY());
	}

	return success;
}

void SettingsMenu::handleMenuEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_SETTINGS_MENU_BUTTONS; ++i) {
		gSettingsMenuButtons[i].handleEvent(&e, i);
	}
}

void SettingsMenu::closeMenuMedia() {
	// Buttons
	gButtonSpriteSheetTexture2.free();

	// Menu
	gSettingsMenuTextTexture1.free();
	gSettingsMenuTextTexture2.free();
	gSettingsMenuTextTexture3.free();
	gSettingsMenuTextTexture4.free();
	gSettingsMenuTextTexture5.free();
	gSettingsMenuTextTexture6.free();
}

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
	gSettingsMenuTextTexture4.render(gSettingsMenuTextTexture4.getX(), gSettingsMenuTextTexture4.getY());	// RETURN TO SETTINGS
	gSettingsMenuTextTexture5.render(gSettingsMenuTextTexture5.getX(), gSettingsMenuTextTexture5.getY());	// QUIT GAME

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

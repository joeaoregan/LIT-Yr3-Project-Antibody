/*
2017/03/08 Added Settings Menu class
*/
/*
SETTINGS MENU:

This function handles the objects for the settings menu. The separate button class
handles the transitions.
*/

#include "HighScores.h"
#include <SDL_ttf.h>


bool HighScores::loadHighScoresMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gScoresMenuTextTexture1.loadFromRenderedText("HIGH SCORES", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render High Scores text texture!\n");
			success = false;
		}
		if (!gScoresMenuTextTexture2.loadFromRenderedText("Main Menu", textColour, gFont)) {
			printf("Failed to render Main Menu text texture!\n");
			success = false;
		}
		// Backgrounds
		if (!Texture::Instance()->load("Art/PlayerShipOutline.png", "shipOutlineID")) {				// 2017/03/07 Ship Outline Texture
			printf("Failed to load Ship Outline background texture!\n");							// Start Backround
			success = false;
		}

		gScoresMenuTextTexture2.setX((SCREEN_WIDTH - gScoresMenuTextTexture2.getWidth()) / 2);
		//gScoresMenuTextTexture2.setY(200);
		gScoresMenuTextTexture2.setY(SCREEN_HEIGHT - 200);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture3.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < 1; ++i) {
			gSpriteClipsScoresMenu[i].x = 0;
			gSpriteClipsScoresMenu[i].y = i * 200;
			gSpriteClipsScoresMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsScoresMenu[i].h = BUTTON_HEIGHT;
		}

		//gReturnToMenu.setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gScoresMenuTextTexture2.getY());
		//gReturnToMenu.setPosition(gScoresMenuTextTexture2.getX(), gScoresMenuTextTexture2.getY());
		gScoressMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gScoresMenuTextTexture2.getY());
	}

	return success;
}

void HighScores::handleHighScoresEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < 1; ++i) {
		gScoressMenuButtons[i].handleEvent(&e, i);
	}

	//gReturnToMenu.handleEvent(&e, 0);
}

void HighScores::closeHighScoresMedia() {
	// Buttons
	gButtonSpriteSheetTexture3.free();

	// Menu
	gScoresMenuTextTexture1.free();
	gScoresMenuTextTexture2.free();
}

void HighScores::draw() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 30, 240, 175, 255);		// Green
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);	// Lower the alpha value of the ship outline image
	Texture::Instance()->renderMap("shipOutlineID", 0, 40, SCREEN_WIDTH, 620);		// Draw ship outline image to screen

	// Draw 1 button
	//gReturnToMenu.render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gReturnToMenu.mCurrentSprite]);
	
	for (int i = 0; i < 1; i++) {
		gScoressMenuButtons[i].render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gScoressMenuButtons[i].mCurrentSprite]);
	}
	
	gScoresMenuTextTexture1.render((SCREEN_WIDTH - gScoresMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gScoresMenuTextTexture1.getHeight()) / 12);	// High Scores Heading
	gScoresMenuTextTexture2.render(gScoresMenuTextTexture2.getX(), gScoresMenuTextTexture2.getY());	// Return to menu from scores

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

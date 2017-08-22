/*
	2017/02/14 Added menu handling class
	2017/01/24 Added Menu to main code
	2017/01/19 Started to add game main menu
				Added working menu buttons
*/
/*
	MENU: 

	This function handles the objects for the game menu. The separate button class
	handles the transitions.
*/

#include "Menu.h"
#include <SDL_ttf.h>

bool Menu::loadMediaMenu() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gMenuTextTexture1.loadFromRenderedText("ANTIBODY", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture2.loadFromRenderedText("Story", textColour, gFont)) {	// can take out the new textColor objects
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture3.loadFromRenderedText("1 Player", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture4.loadFromRenderedText("2 Player", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture5.loadFromRenderedText("Settings", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture6.loadFromRenderedText("High Scores", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture7.loadFromRenderedText("Quit", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		gMenuTextTexture2.setX((SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2);
		gMenuTextTexture3.setX((SCREEN_WIDTH - gMenuTextTexture3.getWidth()) / 2);
		gMenuTextTexture4.setX((SCREEN_WIDTH - gMenuTextTexture4.getWidth()) / 2);
		gMenuTextTexture5.setX((SCREEN_WIDTH - gMenuTextTexture5.getWidth()) / 2);
		gMenuTextTexture6.setX((SCREEN_WIDTH - gMenuTextTexture6.getWidth()) / 2);
		gMenuTextTexture7.setX((SCREEN_WIDTH - gMenuTextTexture7.getWidth()) / 2);

		gMenuTextTexture2.setY(200);
		gMenuTextTexture3.setY(250);
		gMenuTextTexture4.setY(300);
		gMenuTextTexture5.setY(350);
		gMenuTextTexture6.setY(400);
		gMenuTextTexture7.setY(450);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
			gSpriteClipsMenu[i].x = 0;
			gSpriteClipsMenu[i].y = i * 200;
			gSpriteClipsMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsMenu[i].h = BUTTON_HEIGHT;
		}

		gMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture2.getY());
		gMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture3.getY());
		gMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture4.getY());
		gMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture5.getY());
		gMenuButtons[4].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture6.getY());
		gMenuButtons[5].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture7.getY());
	}

	return success;
}

void Menu::handleMenuEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].handleEvent(&e, i);
	}
}

void Menu::closeMenu() {
	// Buttons
	gButtonSpriteSheetTexture.free();

	// Menu
	gMenuTextTexture1.free();
	gMenuTextTexture2.free();
	gMenuTextTexture3.free();
	gMenuTextTexture4.free();
	gMenuTextTexture5.free();
	gMenuTextTexture6.free();
	gMenuTextTexture7.free();
}

void Menu::draw() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
		//gMenuButtons[i].render(gButtonSpriteSheetTexture, rend, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY());
	gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY());
	gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY());
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY());
	gMenuTextTexture6.render(gMenuTextTexture6.getX(), gMenuTextTexture6.getY());
	gMenuTextTexture7.render(gMenuTextTexture7.getX(), gMenuTextTexture7.getY());

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}
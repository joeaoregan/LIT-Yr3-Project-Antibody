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

Menu* Menu::s_pInstance = 0;

bool Menu::loadMenuMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		//if (!gMenuTextTexture1.loadFromRenderedText("ANTIBODY", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
		if (!gMenuTextTexture1.loadFromRenderedTextID("ANTIBODY", "menuHeadingID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		
		if (!gMenuTextTexture8.loadFromRenderedTextID("PAUSE", "menuPauseID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
		//if (!gMenuTextTexture8.loadFromRenderedText("PAUSE", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		
		if (!gMenuTextTexture2.loadFromRenderedTextID("Story", "menuStoryID", textColour, gFont)) {
		//if (!gMenuTextTexture2.loadFromRenderedText("Story", textColour, gFont)) {	// can take out the new textColor objects
			printf("Failed to render text texture!\n");
			success = false;
		}

		if (!gMenuTextTexture3.loadFromRenderedTextID("1 Player", "menu1PlayerID", textColour, gFont)) {
		//if (!gMenuTextTexture3.loadFromRenderedText("1 Player", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture4.loadFromRenderedTextID("2 Player", "menu2PlayerID", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture5.loadFromRenderedTextID("Settings", "menuSettingsID", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture6.loadFromRenderedTextID("High Scores", "menuHighScoresID", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture7.loadFromRenderedTextID("Quit", "menuQuitID", textColour, gFont)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
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

		gMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 200);
		gMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 250);
		gMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 300);
		gMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 350);
		gMenuButtons[4].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 400);
		gMenuButtons[5].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, 450);
	}

	return success;
}

void Menu::handleMenuEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].handleEvent(&e, i);
	}
}

void Menu::closeMenuMedia() {
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
	gMenuTextTexture8.free();
}

void Menu::draw() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
		//gMenuButtons[i].render(gButtonSpriteSheetTexture, rend, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	//int w, h;
	//SDL_QueryTexture(Texture::Instance()->getTexture("menuHeadingID"), NULL, NULL, &w, &h);
	
	gMenuTextTexture1.render("menuHeadingID", (SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);

	gMenuTextTexture2.render("menuStoryID", (SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2, 200);
	gMenuTextTexture3.render("menu1PlayerID", (SCREEN_WIDTH - gMenuTextTexture3.getWidth()) / 2, 250);
	gMenuTextTexture4.render("menu2PlayerID", (SCREEN_WIDTH - gMenuTextTexture4.getWidth()) / 2, 300);
	gMenuTextTexture5.render("menuSettingsID", (SCREEN_WIDTH - gMenuTextTexture5.getWidth()) / 2, 350);
	gMenuTextTexture6.render("menuHighScoresID", (SCREEN_WIDTH - gMenuTextTexture6.getWidth()) / 2, 400);
	gMenuTextTexture7.render("menuQuitID", (SCREEN_WIDTH - gMenuTextTexture7.getWidth()) / 2, 450);
	
	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

void Menu::drawPause() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture8.setX((SCREEN_WIDTH - gMenuTextTexture8.getWidth()) / 2);
	gMenuTextTexture8.setY(SCREEN_HEIGHT - gMenuTextTexture8.getHeight() - 10);

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY());	// STORY
	//gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY());	// GAME_1PLAYER
	//gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY());	// GAME_2PLAYER
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY());	// SETTINGS
	gMenuTextTexture6.render(gMenuTextTexture6.getX(), gMenuTextTexture6.getY());	// HIGH_SCORES
	gMenuTextTexture7.render(gMenuTextTexture7.getX(), gMenuTextTexture7.getY());	// QUIT
	gMenuTextTexture8.render(gMenuTextTexture8.getX(), gMenuTextTexture8.getY());	// QUIT

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}
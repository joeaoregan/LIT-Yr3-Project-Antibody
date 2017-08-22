#include "Menu.h"
#include <SDL_ttf.h>

bool Menu::loadMediaMenu(SDL_Renderer *rend) {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Lazy.ttf", 30);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gMenuTextTexture1.loadFromRenderedText("ANTIBODY", textColour, gFont, rend)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture2.loadFromRenderedText("New Game", textColour, gFont, rend)) {	// can take out the new textColor objects
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture3.loadFromRenderedText("Settings", textColour, gFont, rend)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture4.loadFromRenderedText("High Scores", textColour, gFont, rend)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture5.loadFromRenderedText("Quit", textColour, gFont, rend)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		gMenuTextTexture2.setX((SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2);
		gMenuTextTexture3.setX((SCREEN_WIDTH - gMenuTextTexture3.getWidth()) / 2);
		gMenuTextTexture4.setX((SCREEN_WIDTH - gMenuTextTexture4.getWidth()) / 2);
		gMenuTextTexture5.setX((SCREEN_WIDTH - gMenuTextTexture5.getWidth()) / 2);

		gMenuTextTexture2.setY((SCREEN_HEIGHT - gMenuTextTexture2.getHeight()) / 2.5);
		gMenuTextTexture3.setY((SCREEN_HEIGHT - gMenuTextTexture3.getHeight()) / 2.0);
		gMenuTextTexture4.setY((SCREEN_HEIGHT - gMenuTextTexture4.getHeight()) / 1.7);
		gMenuTextTexture5.setY((SCREEN_HEIGHT - gMenuTextTexture5.getHeight()) / 1.5);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("Art/buttonOne.png", rend)) {		// CHANGED ADDED RENDERER TO FUNCTION
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
}

void Menu::draw(SDL_Renderer *rend) {
	SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderClear(rend);

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, rend, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12, rend);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY(), rend);
	gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY(), rend);
	gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY(), rend);
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY(), rend);

	SDL_RenderPresent(rend);			// Update screen
}
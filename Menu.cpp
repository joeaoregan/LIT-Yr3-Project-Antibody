/*
	2017/03/06 Added singleton for menu
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

bool Menu::init() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0,255 };

		if (!Texture::Instance()->loadFromRenderedTextID("ANTIBODY", "menuHeadingID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!Texture::Instance()->loadFromRenderedTextID("PAUSE", "menuPauseID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		//Texture::Instance()->loadFromRenderedTextID("ANTIBODY", "menuHeadingID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100));
		//Texture::Instance()->loadFromRenderedTextID("PAUSE", "menuPauseID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100));

		// Buttons
		gMenuTextTexture1.loadFromRenderedTextID("Story", "menuStoryID", textColour, gFont);
		Texture::Instance()->loadFromRenderedTextID("1 Player", "menu1PlayerID", textColour, gFont);
		Texture::Instance()->loadFromRenderedTextID("2 Player", "menu2PlayerID", textColour, gFont);
		Texture::Instance()->loadFromRenderedTextID("Settings", "menuSettingsID", textColour, gFont);
		Texture::Instance()->loadFromRenderedTextID("High Scores", "menuHighScoresID", textColour, gFont);
		Texture::Instance()->loadFromRenderedTextID("Quit Scores", "menuQuitID", textColour, gFont);
		/*
		if (!gMenuTextTexture1.loadFromRenderedText("ANTIBODY", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		
		if (!gMenuTextTexture8.loadFromRenderedText("PAUSE", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
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
		*/

		// Set the button text positions
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

		// Set the button positions
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

bool Menu::clean() {
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

	return true;
}

void Menu::update() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
		//gMenuButtons[i].render(gButtonSpriteSheetTexture, rend, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}
	/*
	Texture::Instance()->loadFromRenderedTextID("Story", "menuStoryID", textColour, gFont);
	Texture::Instance()->loadFromRenderedTextID("1 Player", "menu1PlayerID", textColour, gFont);
	Texture::Instance()->loadFromRenderedTextID("2 Player", "menu2PlayerID", textColour, gFont);
	Texture::Instance()->loadFromRenderedTextID("Settings", "menuSettingsID", textColour, gFont);
	Texture::Instance()->loadFromRenderedTextID("High Scores", "menuHighScoresID", textColour, gFont);
	Texture::Instance()->loadFromRenderedTextID("Quit Scores", "menuQuitID", textColour, gFont);
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
	*/


	Texture::Instance()->render("menuHeadingID", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, (SCREEN_HEIGHT - Texture::Instance()->getHeight()) / 12);
	Texture::Instance()->render("menuPauseID", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 250);
	Texture::Instance()->render("menuPauseID", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 300);

	//Texture::Instance()->renderMap("gameTitleID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Texture::Instance()->renderMap("Story", SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2, 200);
	//Texture::Instance()->renderMap("Story", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 200);
	//gMenuTextTexture1.renderMap("Story", 0,0);
	//Texture::Instance()->render("Story", 100, 100, 100, 100);
	Texture::Instance()->render("1 Player", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 250);
	Texture::Instance()->render("2 Player", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 300);
	Texture::Instance()->render("Settings", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 350);
	Texture::Instance()->render("High Scores", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 400);
	Texture::Instance()->render("Quit Scores", (SCREEN_WIDTH - Texture::Instance()->getWidth()) / 2, 450);
	/*
	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY());	// STORY
	gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY());	// GAME_1PLAYER
	gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY());	// GAME_2PLAYER
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY());	// SETTINGS
	gMenuTextTexture6.render(gMenuTextTexture6.getX(), gMenuTextTexture6.getY());	// HIGH_SCORES
	gMenuTextTexture7.render(gMenuTextTexture7.getX(), gMenuTextTexture7.getY());	// QUIT
	*/
	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

void Menu::drawPause() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
		//gMenuButtons[i].render(gButtonSpriteSheetTexture, rend, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
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
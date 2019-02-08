/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Menu.cpp
	- Description:			cpp file for the Menu class.
	- Information:			This class handles the objects for the game menu. The separate button class handles the transitions.
	- Log
		2017/02/14		Added menu handling class
		2017/01/24		Added Menu to main code
		2017/01/19		Started to add game main menu	
						Added working menu buttons
	----------------------------------------------------------------------------------------------------------------------*/
#include "Menu.h"
#include <SDL_ttf.h>

SDL_Rect menuViewPort;		// 2017/03/18 Menu Info Screens

unsigned int createdByTimer2 = 0, createdByLastTime2 = 0, changeEverySecond2 = 0;

// Name: loadMenuMedia()
// Role: Loads textures and images for the menu
bool Menu::loadMenuMedia() {
	bool success = true;

	//SDL_Rect menuViewPort;		// 2017/03/18 Menu Info Screens
	menuViewPort.x = 570;
	menuViewPort.y = 200;
	menuViewPort.h = 300;
	menuViewPort.w = 400;

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
			printf("Failed to render Quit text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture8.loadFromRenderedText("PAUSE", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render Pause text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture9.loadFromRenderedText("RESUME", textColour, gFont)) {
			printf("Failed to render Pause to Resume text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture10.loadFromRenderedText("MAIN MENU", textColour, gFont)) {
			printf("Failed to render Pause to Main Menu text texture!\n");
			success = false;
		}
		// Backgrounds
		if (!Texture::Instance()->load("Art/PlayerShipOutline.png", "shipOutlineID")) {				// 2017/03/07 Ship Outline Texture
			printf("Failed to load Ship Outline background texture!\n");							// Start Backround
			success = false;
		}
		/*
		// Center buttons on X axis
		gMenuTextTexture2.setX((SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2);
		gMenuTextTexture3.setX((SCREEN_WIDTH - gMenuTextTexture3.getWidth()) / 2);
		gMenuTextTexture4.setX((SCREEN_WIDTH - gMenuTextTexture4.getWidth()) / 2);
		gMenuTextTexture5.setX((SCREEN_WIDTH - gMenuTextTexture5.getWidth()) / 2);
		gMenuTextTexture6.setX((SCREEN_WIDTH - gMenuTextTexture6.getWidth()) / 2);
		gMenuTextTexture7.setX((SCREEN_WIDTH - gMenuTextTexture7.getWidth()) / 2);
		gMenuTextTexture8.setX((SCREEN_WIDTH - gMenuTextTexture8.getWidth()) / 2);
		gMenuTextTexture9.setX((SCREEN_WIDTH - gMenuTextTexture9.getWidth()) / 2);
		gMenuTextTexture10.setX((SCREEN_WIDTH - gMenuTextTexture10.getWidth()) / 2);
		*/
		gMenuTextTexture2.setX(300 + (BUTTON_WIDTH - gMenuTextTexture2.getWidth()) / 2);
		gMenuTextTexture3.setX(300 + (BUTTON_WIDTH - gMenuTextTexture3.getWidth()) / 2);
		gMenuTextTexture4.setX(300 + (BUTTON_WIDTH - gMenuTextTexture4.getWidth()) / 2);
		gMenuTextTexture5.setX(300 + (BUTTON_WIDTH - gMenuTextTexture5.getWidth()) / 2);
		gMenuTextTexture6.setX(300 + (BUTTON_WIDTH - gMenuTextTexture6.getWidth()) / 2);
		gMenuTextTexture7.setX(300 + (BUTTON_WIDTH - gMenuTextTexture7.getWidth()) / 2);
		gMenuTextTexture8.setX(300 + (BUTTON_WIDTH - gMenuTextTexture8.getWidth()) / 2);
		gMenuTextTexture9.setX(300 + (BUTTON_WIDTH - gMenuTextTexture9.getWidth()) / 2);
		gMenuTextTexture10.setX(300 + (BUTTON_WIDTH - gMenuTextTexture10.getWidth()) / 2);

		gMenuTextTexture2.setY(200);
		gMenuTextTexture3.setY(250);
		gMenuTextTexture4.setY(300);
		gMenuTextTexture5.setY(350);
		gMenuTextTexture6.setY(400);
		gMenuTextTexture7.setY(450);
	}


	// Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < TOTAL_MAIN_MENU_BUTTONS; ++i) {
			gSpriteClipsMenu[i].x = 0;
			gSpriteClipsMenu[i].y = i * 200;
			gSpriteClipsMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsMenu[i].h = BUTTON_HEIGHT;
		}
		/*
		gMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture2.getY());
		gMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture3.getY());
		gMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture4.getY());
		gMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture5.getY());
		gMenuButtons[4].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture6.getY());
		gMenuButtons[5].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture7.getY());
		*/
		gMenuButtons[0].setPosition(300, gMenuTextTexture2.getY());
		gMenuButtons[1].setPosition(300, gMenuTextTexture3.getY());
		gMenuButtons[2].setPosition(300, gMenuTextTexture4.getY());
		gMenuButtons[3].setPosition(300, gMenuTextTexture5.getY());
		gMenuButtons[4].setPosition(300, gMenuTextTexture6.getY());
		gMenuButtons[5].setPosition(300, gMenuTextTexture7.getY());
	}

	return success;
}

// Name: handleMenuEvents()
// Role: React to button presses
void Menu::handleMenuEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_MAIN_MENU_BUTTONS; ++i) {
		gMenuButtons[i].handleEvent(&e, i);
	}
}

// Name: closeMenuMedia()
// Role: free menu textures from memory
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

// Name: Draw()
// Role: Render the menu buttons#
void Menu::draw() {
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	randomBackgroundColour();
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);					// Lower the alpha value of the ship outline image
	Texture::Instance()->renderMap("shipOutlineID", 0, 40, SCREEN_WIDTH, 620);						// Draw ship outline image to screen

	for (int i = 0; i < TOTAL_MAIN_MENU_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY());					// STORY
	gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY());					// GAME_1PLAYER
	gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY());					// GAME_2PLAYER
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY());					// SETTINGS
	gMenuTextTexture6.render(gMenuTextTexture6.getX(), gMenuTextTexture6.getY());					// HIGH_SCORES
	gMenuTextTexture7.render(gMenuTextTexture7.getX(), gMenuTextTexture7.getY());					// QUIT

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &menuViewPort);							// Switch to menu viewport

	createdByTimer2 = SDL_GetTicks();																// Get the current game running time
	if (createdByTimer2 > createdByLastTime2 + 1500) {												// Decrement countdown timer
		createdByLastTime2 = createdByTimer2;														// Store this time
		changeEverySecond2++;																		// Decrement the timer
	//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
	}


	if (changeEverySecond2 % 2 == 1) {
		//Texture::Instance()->renderMap(textureID, 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
		Texture::Instance()->renderMap("gameTitleID", 0, 0, 400, 300);
	}
	else if (changeEverySecond2 % 2 == 0) {															// Pause with image on screen for 1 second
		Texture::Instance()->renderMap("createdByID", 0, 0, 400, 300);
		changeEverySecond2 = 0;	// Reset timer
	}

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);									// Clear the current viewport to render to full window / screen

	SDL_RenderPresent(Game::Instance()->getRenderer());												// Update screen


}


// Name: drawPause()
// Role: Handling media for the pause state of the game
void Menu::drawPause() {
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	randomBackgroundColour();
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);					// Lower the alpha value of the ship outline image
	Texture::Instance()->renderMap("shipOutlineID", 0, 40, SCREEN_WIDTH, 620);						// Draw ship outline image to screen

	// Create 3 buttons
	for (int i = 0; i < 3; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture8.setX((SCREEN_WIDTH - gMenuTextTexture8.getWidth()) / 2);
	gMenuTextTexture8.setY(SCREEN_HEIGHT - gMenuTextTexture8.getHeight() - 10);

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12);	// ANTIBODY TITLE
	gMenuTextTexture9.render(gMenuTextTexture9.getX(), gMenuTextTexture2.getY());					// RESUME GAME -> place at button 1s Y position
	gMenuTextTexture10.render(gMenuTextTexture10.getX(), gMenuTextTexture3.getY());					// RESUME GAME -> place at button 2s Y position
	gMenuTextTexture7.render(gMenuTextTexture7.getX(), gMenuTextTexture4.getY());					// QUIT GAME -> place at button 2s Y position
	gMenuTextTexture8.render(gMenuTextTexture8.getX(), gMenuTextTexture8.getY());					// PAUSE TITLE

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &menuViewPort);							// Switch to menu viewport

	createdByTimer2 = SDL_GetTicks();																// Get the current game running time
	if (createdByTimer2 > createdByLastTime2 + 1500) {												// Decrement countdown timer
		createdByLastTime2 = createdByTimer2;														// Store this time
		changeEverySecond2++;																		// Decrement the timer
	//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
	}


	if (changeEverySecond2 % 2 == 1) {
		//Texture::Instance()->renderMap(textureID, 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
		Texture::Instance()->renderMap("gameTitleID", 0, 0, 400, 300);
	}
	else if (changeEverySecond2 % 2 == 0) {															// Pause with image on screen for 1 second
		Texture::Instance()->renderMap("levelID", 0, 0, 400, 300);
		changeEverySecond2 = 0;	// Reset timer
	}

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);									// Clear the current viewport to render to full window / screen
	SDL_RenderPresent(Game::Instance()->getRenderer());												// Update screen
}

bool changeMenuBGColour = true;

// Name: randomBackgroundColour()
// Role: Select a random background image for the menu
void Menu::randomBackgroundColour() {
	if (changeMenuBGColour) {
		int menuColour = rand() % 5; // a number 0 to 4

		if (menuColour == 0) SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);			// Purple
		else if (menuColour == 1) SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 10, 130, 230, 255);	// Blue
		else if (menuColour == 2) SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 30, 240, 175, 255);	// Green
		else if (menuColour == 3) SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 240, 240, 130, 255);	// Yellow
		else if (menuColour == 4) SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 240, 130, 130, 255);	// Red

		changeMenuBGColour = false;
	}
}
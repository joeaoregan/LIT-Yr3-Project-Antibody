/*
	2017/02/09 Added separate function for text and logos to Game class
	2017/02/08 Added separate splash screen class SplashScreen.h for displaying splash screens
				Moved press enter to continue for splash screens instead of delay before progressing to level
	2017/02/02 Added storyline at intro to game
	2017/01/20 Added game over message
	2017/01/18 Added splash screens at start of game, Game Title & Game Creators
				Added pressButtonToContinue() function for splash screens at start of game, so player can read writing at own pace
	2017/01/17 Added scrolling text to intro screens
				Added wrapped text to add new line character for level intro splash screens
	2017/01/11 Added flashing game over texture
*/
/*
	SPLASH SCREEN:

	Handles game intro screens and information screens at start of game, and transition screens between level with scores and level objectives.
	Displays final score and game winner at end of game.
*/

#include "SplashScreen.h"

enum levels {MENU, LEVEL_1, LEVEL_2, LEVEL_3};

int frame1 = 0;

int scrollOffset = SCREEN_HEIGHT;															// Scrolling offset for splash screens

/*	Initialise the images used for splash screens and logos */
bool SplashScreen::initSplashScreens() {
	bool success = true;
		
	// Init the level backdrops
	if (!gLevel1.loadFromFile("Art/Level1720.png")) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (!gLevel2.loadFromFile("Art/Level2720.png")) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (!gLevel3.loadFromFile("Art/Level3720.png")) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 3 texture!\n");
		success = false;
	}
	
	//Load sprite sheet texture
	if (!gPressEnterSpriteSheetTexture.loadFromFile("Art/PressEnterSpriteSheet2.png")) {	// Sprite sheet for Press Enter Button
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else {
		// Set sprite clips 19/01/2017 Added for loop
		for (int i = 0; i < 6; ++i) {
			gPressButtonToContinueSpriteClips[i].x = 0;
			if (i < 4)
				gPressButtonToContinueSpriteClips[i].y = i * 50;
			else if (i == 4)
				gPressButtonToContinueSpriteClips[i].y = 100;
			else if (i == 5)
				gPressButtonToContinueSpriteClips[i].y = 50;
			gPressButtonToContinueSpriteClips[i].w = 718;
			gPressButtonToContinueSpriteClips[i].h = 50;
		}
	}

	if (!gGameOverTextTexture.loadFromFile("Art/GameOver1.png")) {					// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}

	return success;
}

/* free the textures from memory when the game is finished */
void SplashScreen::closeSplashScreens() {
	//gEnemyShipTexture.free();
	//gVirusGreenTexture.free();
	//gVirusOrangeTexture.free();
	//gVirusBlueTexture.free();

	//gLevel1.free();
	//gLevel2.free();
	//gLevel3.free();
	gLevelObjectiveTextTexture.free();

	gPressEnterSpriteSheetTexture.free();
	
	// End of Level / Game Scores
	gFinalScoreTextTexture.free();
	gGameWinnerTextTexture.free();
	gGameOverTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
}

/*	Press button to continue message - pauses the screen until a button is pressed 
	This is rendered onto whatever background is already in place */
void SplashScreen::pressButtonToContinue(SDL_Event e) {
	bool continueGame = false;

	SDL_Rect* currentClip = &gPressButtonToContinueSpriteClips[frame1 / 6];	// Render current frame
	gPressEnterSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2 + 200, currentClip);

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
	++frame1;	// Go to next frame

	if (frame1 / 6 >= 4) {	// Cycle animation
		frame1 = 0;
	}

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN:
			continueGame = true;
			break;
		}

		break;
	}

	if (!continueGame) pressButtonToContinue(e);
}

/*	2017/02/26 changed to texture instance
	Display intro screens at start of game before menu */
bool SplashScreen::displayGameIntroSplashScreens() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);						// Clear the screen
	SDL_RenderClear(Game::Instance()->getRenderer());

	Texture::Instance()->renderMap("logoL1ID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_RenderPresent(Game::Instance()->getRenderer());													// Update screen
	SDL_Delay(1000);															// Pause with image on screen for 1 second

	scrollCreatedBySplashScreen(SCREEN_HEIGHT, 1);

	return false;
}

void SplashScreen::scrollCreatedBySplashScreen(int startAt, int seconds) {
	int stopAt = 0;
	
	if (startAt > 0) {
		while (startAt >= stopAt) {				// While greater than or equal to zero
			Texture::Instance()->renderMap("creatorL1ID", 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
			startAt -= 15;

			SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
		}
	}

	SDL_Delay(seconds * 1000);					// Pause with image on screen for a number of seconds
}

void SplashScreen::scrollDownL1Logo(int startAt) {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 12, 77, 255);			// Purple
	SDL_RenderClear(Game::Instance()->getRenderer());

	while (startAt <= 0) {				// While less than or equal to zero
		Texture::Instance()->renderMap("level1ID", 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
		startAt += 15;

		SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
	}
}

void SplashScreen::scrollRightL2Logo(int startAt) {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 12, 77, 255);			// Purple
	SDL_RenderClear(Game::Instance()->getRenderer());

	while (startAt <= 0) {				// While less than or equal to zero
		Texture::Instance()->renderMap("level2ID", startAt, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		startAt += 20;

		SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
	}
}

// Scroll a logo up or down the screen
void SplashScreen::scrollVerticalLogo(Texture &texture, int seconds, int rate, int startAt, int stopAt) {
	if (startAt > stopAt) {
		while (startAt >= stopAt) {				// While greater than or equal to zero
			texture.render(0, startAt);	// Team Member Names
			startAt -= rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
		}
	}
	else {
		while (startAt <= stopAt) {				// While less than or equal to zero
			texture.render(0, startAt);	// Team Member Names
			startAt += rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
		}
	}

	SDL_Delay(seconds * 1000);					// Pause with image on screen for a number of seconds

												//texture.free();							// Free Logo 2 from memory --> NEEDS TO STAY IN BACKGROUND, DON'T FREE
}
//	Level 1 background with scrolling text
bool SplashScreen::level1IntroScreens() {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy enemy virus and ships      \nThe player with the highest score\nIs the winner";
	
	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollDownL1Logo(-SCREEN_HEIGHT);

	//enemyInformationSplashScreenL1(rend);
	infoScreenL1Enemies(2, SCREEN_HEIGHT, gStoryA);
	infoScreenL1PowerUps(2, SCREEN_HEIGHT, gStoryB);

	// Objectives
	scrollDownL1Logo(-SCREEN_HEIGHT);

	//scrollL1Objectives(rend, gLevelObjectiveTextTexture);
	scrollUpText("level1ID", gLevelObjectiveTextTexture);
	
	return false;	// set display screens boolean to false so it stops, will continue repeating over and over if true
}

// Scroll text and image up the screen with information about the enemies in Level 1
void SplashScreen::infoScreenL1Enemies(int seconds, int startAt, Texture &story) {
	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";

	if (!gStoryA.loadFromRenderedText(storyPage1, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true)) {
		printf("Unable to render gStoryA level game objective texture!\n");
	}

	while (startAt >= 300) {																				// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());																				// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap("level1ID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);				// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 5;																						// Decrement the scrolling offset move the texture up the screen
		story.render((SCREEN_WIDTH - story.getWidth()) / 2, startAt);									// FOR TESTING

		Texture::Instance()->renderMap("greenVirusID", SCREEN_WIDTH - 175, startAt + 40, 75, 75);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap("orangeVirusID", SCREEN_WIDTH - 175, startAt + 140, 75, 75);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap("enemyShipID", SCREEN_WIDTH - 175, startAt + 250, 75, 75);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		SDL_RenderPresent(Game::Instance()->getRenderer());															// Update screen
	}

	SDL_Delay(seconds * 1000);
}
void SplashScreen::infoScreenL1PowerUps(int seconds, int startAt, Texture &story) {
	storyPage2 = "Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";

	if (!gStoryB.loadFromRenderedText(storyPage2, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true)) {
		printf("Failed to render gStoryB text texture!\n");
	}

	while (startAt >= 300) {												// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());												// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap("level1ID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 5;														// Decrement the scrolling offset move the texture up the screen

		story.render((SCREEN_WIDTH - story.getWidth()) / 2, startAt); // FOR TESTING

		Texture::Instance()->renderMap("healthPowerUpID", SCREEN_WIDTH - 160, startAt + 40, 60, 60);
		Texture::Instance()->renderMap("laserPowerUpID", SCREEN_WIDTH - 160, startAt + 140, 60, 48);
		Texture::Instance()->renderMap("rocketPowerUpID", SCREEN_WIDTH - 140, startAt + 200, 30, 60);

		SDL_RenderPresent(Game::Instance()->getRenderer());															// Update screen
	}

	SDL_Delay(seconds * 1000);
}

/*	2017/02/26: Edited to take an ID string to search texture map in texture class 
	Scroll text up the screen from the startAt point to the stopAt point, and show for a number of seconds before progressing
*/
void SplashScreen::scrollUpText(std::string backgroundID, Texture &text, int seconds, int rate, int startAt, int stopAt) {
	while (startAt >= stopAt) {					// While the text hasn't reached the stopping point
		SDL_RenderClear(Game::Instance()->getRenderer());					// Clear the screen
												//background.render(0, 0, rend);			// Static background
		Texture::Instance()->renderMap(backgroundID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= rate;						// Decrement the scrolling offset move the texture up the screen
		text.render((SCREEN_WIDTH - text.getWidth()) / 2, startAt); // FOR TESTING

		SDL_RenderPresent(Game::Instance()->getRenderer());				// Update screen
	}

	SDL_Delay(seconds * 1000);					// Pause with image on screen
												//background.free();						// Free Logo 2 from memory --> THE BACKGROUND NEEDS TO STAY IN PLACE
	text.free();								// Free Logo 2 from memory
}






















/*
// Level 2 background, with scrolling text
bool SplashScreen::level2IntroScreens(SDL_Renderer *rend) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy more enemy virus and ships\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	//scrollVerticalLogo(rend, gLevel2, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen
	scrollRightL2Logo(gRenderer, -SCREEN_WIDTH);

	enemyInformationSplashScreen(rend, gLevel2, gVirusGreenTexture, gVirusOrangeTexture, gVirusBlueTexture, gEnemyShipTexture, gEnemyShipTexture);

	// Objectives
	//scrollVerticalLogo(rend, gLevel2, 1, 10, -SCREEN_HEIGHT);
	scrollRightL2Logo(gRenderer, -SCREEN_WIDTH);

	scrollUpText(rend, "level2ID", gLevelObjectiveTextTexture);

	return false;	// set display screens boolean to false so it stops repeating over and over
}

// Level 3 background with scrolling text
//bool SplashScreen::level3IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip) {
bool SplashScreen::level3IntroScreens(SDL_Renderer *rend) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy even more enemy virus and ships\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel3, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen

	enemyInformationSplashScreen(rend, gLevel3, gVirusGreenTexture, gVirusOrangeTexture, gVirusBlueTexture, gEnemyShipTexture, gEnemyShipTexture);

	// Objectives
	scrollVerticalLogo(rend, gLevel3, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, "level3ID", gLevelObjectiveTextTexture);

	return false;	// set display screens boolean to false so it stops repeating over and over
}
*/

// Final Score For Level 1 to 3
void SplashScreen::level1FinalScore() {
	scrollDownL1Logo(-SCREEN_HEIGHT);
}
void SplashScreen::level2FinalScore() {
	scrollVerticalLogo(gLevel2, 1, 15, -SCREEN_HEIGHT);
}
void SplashScreen::level3FinalScore() {
	scrollVerticalLogo(gLevel3, 1, 15, -SCREEN_HEIGHT);
}

void SplashScreen::endOfGame(int level, std::string finalScore, std::string winner) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 40);										// Retro font size 40
	textColour = {0, 255, 0, 255};														// Green text colour
	TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);											// Use bold font
	std::string complete = "Complete!!!";

	if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, TTF_OpenFont("Fonts/Retro.ttf", 50))) {
		printf("Unable to render final scores texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(complete, {255, 255, 255, 255}, TTF_OpenFont("Fonts/Retro.ttf", 60))) {
		printf("Unable to render final scores texture!\n");
	}

	if (level == LEVEL_1) level1FinalScore();					// Scroll Level 1 background down from top of screen
	else if (level == LEVEL_2) level2FinalScore();				// Scroll Level 1 background down from top of screen
	else if (level == LEVEL_3) level3FinalScore();				// Scroll Level 1 background down from top of screen
	
	gGameOverTextTexture.setFlash(true);
	gGameOverTextTexture.flashGameObject(5);

	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x3C, 0x3C, 0x3C, 0xFF);			// Grey colour --> shows up in UI
	SDL_RenderClear(Game::Instance()->getRenderer());

	gLevel3.render(0, 0);										// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

	if (level == 1) scrollUpText("level1ID", gStoryB, 1, 15);			// 2nd page of text for story
	else if (level == 2) scrollUpText("level2ID", gStoryB, 1, 15);		// 2nd page of text for story

	gFinalScoreTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
	gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2); // FOR TESTING
	
	if (level > 3) {
		if (!gGameWinnerTextTexture.loadFromRenderedText(winner, textColour, gFont)) {
			printf("Unable to render GameWinnerTextTexture game winner texture!\n");
		}

		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, gFont)) {
			printf("Unable to render FinalScoreTextTexture final scores texture!\n");
		}
		
		gGameOverTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 100) / 2);		// FOR TESTING
		gGameWinnerTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameWinnerTextTexture.render((SCREEN_WIDTH - gGameWinnerTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameWinnerTextTexture.getHeight() + 450) / 2); // FOR TESTING
	}
}

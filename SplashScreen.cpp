#include "SplashScreen.h"
//#include <SDL_ttf.h>
//#include <sstream>					// For timer

enum levels {MENU, LEVEL_1, LEVEL_2, LEVEL_3};

int frame1 = 0;

int scrollOffset = SCREEN_HEIGHT;															// Scrolling offset for splash screens

/*	Initialise the images used for splash screens and logos */
bool SplashScreen::initSplashScreens(SDL_Renderer *rend) {
	bool success = true;

	// Init the objects to give information on
	if (!gEnemyShipTexture.loadFromFile("Art/EnemyShip.png", rend)) {					// Enemy Ship Texture
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	if (!gVirusGreenTexture.loadFromFile("Art/VirusGreen.png", rend)) {				// Enemy Virus Texture - Green
		printf("Failed to load Green Enemy Virus texture!\n");
		success = false;
	}
	if (!gVirusOrangeTexture.loadFromFile("Art/VirusOrange.png", rend)) {	// Enemy Virus Texture - Orange
		printf("Failed to load Orange Enemy Virus texture!\n");
		success = false;
	}
	if (!gVirusBlueTexture.loadFromFile("Art/VirusBlue.png", rend)) {	// Enemy Virus Texture - Orange
		printf("Failed to load Orange Enemy Virus texture!\n");
		success = false;
	}

	// Init the game title and credit screens
	if (!gGameLogoTexture.loadFromFile("Art/Logo1720.png", rend)) {							// Load the Game Title Logo
		printf("Failed to load Logo 1 - Game Logo texture!\n");
		success = false;
	}
	if (!gGameCreatorsTexture.loadFromFile("Art/Logo2720.png", rend)) {						// Load the Game Creators Logo
		printf("Failed to load Logo 2 - Game Creators texture!\n");
		success = false;
	}

	// Init the level backdrops
	if (!gLevel1.loadFromFile("Art/Level1720.png", rend)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (!gLevel2.loadFromFile("Art/Level2720.png", rend)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (!gLevel3.loadFromFile("Art/Level3720.png", rend)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 3 texture!\n");
		success = false;
	}

	//Load sprite sheet texture
	if (!gPressEnterSpriteSheetTexture.loadFromFile("Art/PressEnterSpriteSheet2.png", rend)) {	// Sprite sheet for Press Enter Button
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

	if (!gGameOverTextTexture.loadFromFile("Art/GameOver1.png", rend)) {					// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}

	return success;
}

/* free the textures from memory when the game is finished */
void SplashScreen::closeSplashScreens() {
	gGameLogoTexture.free();				// Free the game title screen from memory
	gGameCreatorsTexture.free();			// Free the credits image from memory

	gEnemyShipTexture.free();
	gVirusGreenTexture.free();
	gVirusOrangeTexture.free();
	gVirusBlueTexture.free();

	gLevel1.free();
	gLevel2.free();
	gLevel3.free();
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
void SplashScreen::pressButtonToContinue(SDL_Renderer *rend, SDL_Event e) {
	bool continueGame = false;

	SDL_Rect* currentClip = &gPressButtonToContinueSpriteClips[frame1 / 6];	// Render current frame
	gPressEnterSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2 + 200, rend, currentClip);

	SDL_RenderPresent(rend);			// Update screen
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

	if (!continueGame) pressButtonToContinue(rend, e);
}

/* Display intro screens at start of game before menu */
bool SplashScreen::displayGameIntroSplashScreens(SDL_Renderer *rend) {
	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);						// Clear the screen
	SDL_RenderClear(rend);

	gGameLogoTexture.render(0, 0, rend);										// Game Title

	SDL_RenderPresent(rend);													// Update screen
	SDL_Delay(1000);															// Pause with image on screen for 1 second

	scrollVerticalLogo(rend, gGameCreatorsTexture, 1, 15, SCREEN_HEIGHT );		// Scroll up Logo2 and delay for 1 second

	return false;
}

//	Level 1 background with scrolling text
bool SplashScreen::level1IntroScreens(SDL_Renderer *rend, Texture &health, Texture &Laser, Texture &rocket) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy enemy virus and ships      \nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel1, 0, 15, -SCREEN_HEIGHT);												// Scroll Level1 logo down the screen

	enemyInformationSplashScreen(rend, gLevel1, gVirusOrangeTexture, gEnemyShipTexture, health, Laser, rocket);

	// Objectives
	scrollVerticalLogo(rend, gLevel1, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, gLevel1, gLevelObjectiveTextTexture, 0);

	return false;	// set display screens boolean to false so it stops, will continue repeating over and over if true
}

// Level 2 background, with scrolling text
bool SplashScreen::level2IntroScreens(SDL_Renderer *rend) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy more enemy virus and ships\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel2, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen

	enemyInformationSplashScreen(rend, gLevel2, gVirusGreenTexture, gVirusOrangeTexture, gVirusBlueTexture, gEnemyShipTexture, gEnemyShipTexture);

	// Objectives
	scrollVerticalLogo(rend, gLevel2, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, gLevel2, gLevelObjectiveTextTexture, 0);

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

	scrollUpText(rend, gLevel3, gLevelObjectiveTextTexture, 0);

	return false;	// set display screens boolean to false so it stops repeating over and over
}


// Final Score For Level 1
void SplashScreen::level1FinalScore(SDL_Renderer *rend) {
	scrollVerticalLogo(rend, gLevel1, 1, 15, -SCREEN_HEIGHT);
}
void SplashScreen::level2FinalScore(SDL_Renderer *rend) {
	scrollVerticalLogo(rend, gLevel2, 1, 15, -SCREEN_HEIGHT);
}
void SplashScreen::level3FinalScore(SDL_Renderer *rend) {
	scrollVerticalLogo(rend, gLevel3, 1, 15, -SCREEN_HEIGHT);
}
void SplashScreen::endOfGame(SDL_Renderer *rend, int level, std::string finalScore, std::string winner) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 40);										// Retro font size 40
	textColour = {0, 255, 0, 255};														// Green text colour
	TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);											// Use bold font
	std::string complete = "Complete!!!";

	if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, TTF_OpenFont("Fonts/Retro.ttf", 50), rend)) {
		printf("Unable to render final scores texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(complete, {255, 255, 255, 255}, TTF_OpenFont("Fonts/Retro.ttf", 60), rend)) {
		printf("Unable to render final scores texture!\n");
	}

	if (level == LEVEL_1) level1FinalScore(rend);					// Scroll Level 1 background down from top of screen
	else if (level == LEVEL_2) level2FinalScore(rend);				// Scroll Level 1 background down from top of screen
	else if (level == LEVEL_3) level3FinalScore(rend);				// Scroll Level 1 background down from top of screen

	gGameOverTextTexture.setFlash(true);
	gGameOverTextTexture.flashGameObject(5);

	SDL_SetRenderDrawColor(rend, 0x3C, 0x3C, 0x3C, 0xFF);			// Grey colour --> shows up in UI
	SDL_RenderClear(rend);

	gLevel3.render(0, 0, rend);										// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

	if (level == 1) scrollUpText(rend, gLevel1, gStoryB, 1, 15);			// 2nd page of text for story
	else if (level == 2) scrollUpText(rend, gLevel2, gStoryB, 1, 15);		// 2nd page of text for story

	gFinalScoreTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
	gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2, rend); // FOR TESTING

	if (level > 3) {
		if (!gGameWinnerTextTexture.loadFromRenderedText(winner, textColour, gFont, rend)) {
			printf("Unable to render GameWinnerTextTexture game winner texture!\n");
		}

		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, gFont, rend)) {
			printf("Unable to render FinalScoreTextTexture final scores texture!\n");
		}

		gGameOverTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 100) / 2, rend);		// FOR TESTING
		gGameWinnerTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameWinnerTextTexture.render((SCREEN_WIDTH - gGameWinnerTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameWinnerTextTexture.getHeight() + 450) / 2, rend); // FOR TESTING
	}
}

// Scroll a logo up or down the screen
void SplashScreen::scrollVerticalLogo(SDL_Renderer *rend, Texture &texture, int seconds, int rate, int startAt, int stopAt) {
	if (startAt > stopAt) {
		while (startAt >= stopAt) {				// While greater than or equal to zero
			texture.render(0, startAt, rend);	// Team Member Names
			startAt -= rate;

			SDL_RenderPresent(rend);			// Update screen
		}
	}
	else {
		while (startAt <= stopAt) {				// While less than or equal to zero
			texture.render(0, startAt, rend);	// Team Member Names
			startAt += rate;

			SDL_RenderPresent(rend);			// Update screen
		}
	}

	SDL_Delay(seconds * 1000);					// Pause with image on screen for a number of seconds

	//texture.free();							// Free Logo 2 from memory --> NEEDS TO STAY IN BACKGROUND, DON'T FREE
}

// Scroll text up the screen from the startAt point to the stopAt point, and show for a number of seconds before progressing
void SplashScreen::scrollUpText(SDL_Renderer *rend, Texture &background, Texture &text, int seconds, int rate, int startAt, int stopAt) {
	while (startAt >= stopAt) {					// While the text hasn't reached the stopping point
		SDL_RenderClear(rend);					// Clear the screen
		background.render(0, 0, rend);			// Static background   gLevel1a

		startAt -= rate;						// Decrement the scrolling offset move the texture up the screen
		text.render((SCREEN_WIDTH - text.getWidth()) / 2, startAt, rend); // FOR TESTING

		SDL_RenderPresent(rend);				// Update screen
	}

	SDL_Delay(seconds * 1000);					// Pause with image on screen
	//background.free();						// Free Logo 2 from memory --> THE BACKGROUND NEEDS TO STAY IN PLACE
	text.free();								// Free Logo 2 from memory
}

// Scroll text and image up the screen with information about the enemies in Level 1
void SplashScreen::infoScreenL1Enemies(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &img1, Texture &img2, Texture &img3) {
	while (startAt >= 300) {												// First Part of story
		SDL_RenderClear(rend);												// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		background.render(0, 0, rend);										// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 5;														// Decrement the scrolling offset move the texture up the screen
		story.render((SCREEN_WIDTH - story.getWidth()) / 2, startAt, rend); // FOR TESTING
		img1.render(SCREEN_WIDTH - img1.getWidth() - 100, startAt + 40, rend);
		img2.render(SCREEN_WIDTH - img2.getWidth() - 100, startAt + 140, rend);
		img3.render(SCREEN_WIDTH - img3.getWidth() - 100, startAt + 250, rend);

		SDL_RenderPresent(rend);															// Update screen
	}

	SDL_Delay(seconds * 1000);
}
void SplashScreen::infoScreenL1PowerUps(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &img1, Texture &img2, Texture &img3) {
	while (startAt >= 300) {												// First Part of story
		SDL_RenderClear(rend);												// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		background.render(0, 0, rend);										// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 5;														// Decrement the scrolling offset move the texture up the screen
		story.render((SCREEN_WIDTH - story.getWidth()) / 2, startAt, rend); // FOR TESTING
		img1.render(SCREEN_WIDTH - img1.getWidth() - 100, startAt + 40, rend);
		img2.render(SCREEN_WIDTH - img2.getWidth() - 100, startAt + 140, rend);
		img3.render(SCREEN_WIDTH - img3.getWidth() - 110, startAt + 200, rend);

		SDL_RenderPresent(rend);															// Update screen
	}

	SDL_Delay(seconds * 1000);
}

void SplashScreen::enemyInformationSplashScreen(SDL_Renderer *rend, Texture &background, Texture &img2, Texture &img3, Texture &img4, Texture &img5, Texture &img6) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 255,255,255,255 };	// White font colour

	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	storyPage2 = "Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";
	storyPage3 = "Story 3 blah blah blah\nFill this\nIn Later";

	// Story
	if (!gStoryA.loadFromRenderedText(storyPage1, textColour, gFont, rend, true)) {
		printf("Unable to render gStoryA level game objective texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(storyPage2, textColour, gFont, rend, true)) {
		printf("Failed to render gStoryB text texture!\n");
	}
	if (!gStoryC.loadFromRenderedText(storyPage3, textColour, gFont, rend, true)) {
		printf("Failed to render gStoryC text texture!\n");
	}

	infoScreenL1Enemies(rend, 2, SCREEN_HEIGHT, background, gStoryA, gVirusGreenTexture, img2, img3);
	infoScreenL1PowerUps(rend, 2, SCREEN_HEIGHT, background, gStoryB, img4, img5, gVirusGreenTexture);

	//scrollUpText(rend, background, gStoryC, 2);									// 3rd page of text for story NO INFORMATION ON THIS YET
}



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

void SplashScreen::scrollDownLogo(int level, int startAt) {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 12, 77, 255);			// Purple
	SDL_RenderClear(Game::Instance()->getRenderer());

	while (startAt <= 0) {				// While less than or equal to zero
		if (level == LEVEL_1) Texture::Instance()->renderMap("level1ID", 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
		else if (level == LEVEL_2) Texture::Instance()->renderMap("level2ID", 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
		else if (level == LEVEL_3) Texture::Instance()->renderMap("level3ID", 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
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
bool SplashScreen::level1IntroScreens(int level) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };
	gLevelObjectiveTextTexture.free();
	if (level == 1) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";
	else if (level == 2) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";
	else if (level == 3) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";
	
	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, TTF_OpenFont("Fonts/Retro.ttf", 32), true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollDownLogo(level, -SCREEN_HEIGHT);								// Level logo for background
	infoScreenEnemies(level, 2, SCREEN_HEIGHT);							// Give info on the enemies in the current level
	if (level == LEVEL_1) infoScreenPowerUps(level, 2, SCREEN_HEIGHT);	// Give info on power ups in the current level
	infoScreenStory(level, 8, SCREEN_HEIGHT);							// Display the story
	scrollDownLogo(level, -SCREEN_HEIGHT);								// Scroll the background logo
	scrollUpText("level1ID", gLevelObjectiveTextTexture);
	
	return false;	// set display screens boolean to false so it stops, will continue repeating over and over if true
}


// Scroll text and image up the screen with information about the enemies in Level 1
void SplashScreen::infoScreenEnemies(int level, int seconds, int startAt) {
	std::string levelID, en1, en2, en3;
	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	gStoryA.free();
	if (!gStoryA.loadFromRenderedText(storyPage1, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 22), true)) {
		printf("Unable to render gStoryA level game objective texture!\n");
	}

	if (level == LEVEL_1) {
		levelID = "level1ID";
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "enemyShipID";
	}
	else if (level == LEVEL_2) {
		levelID = "level2ID";
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "enemyShipID";
	}
	else if (level == LEVEL_3) {
		levelID = "level3ID";
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "blueVirusID";
	}

	while (startAt >= 300) {																// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());									// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap(levelID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);			// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		
		startAt -= 10;																		// Decrement the scrolling offset move the texture up the screen
		gStoryA.render((SCREEN_WIDTH - gStoryA.getWidth()) / 2, startAt);					// FOR TESTING

		Texture::Instance()->renderMap(en1, SCREEN_WIDTH - 175, startAt + 50, 75, 75);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap(en2, SCREEN_WIDTH - 175, startAt + 170, 75, 75);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap(en3, SCREEN_WIDTH - 175, startAt + 280, 75, 75);		// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		SDL_RenderPresent(Game::Instance()->getRenderer());									// Update screen
	}

	SDL_Delay(seconds * 1000);
}

void SplashScreen::infoScreenPowerUps(int level, int seconds, int startAt) {
	storyPage1 = "Power Ups:\n\nGather golden ships to boost\nThe number of lives\n\n\nTo increase the time remaining\ngather the checkpoints!";
	storyPage2 = "More Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";
	gStoryB.free();

	if (!gStoryA.loadFromRenderedText(storyPage1, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 28), true)) {
		printf("Failed to render gStoryB text texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(storyPage2, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 27), true)) {
		printf("Failed to render gStoryB text texture!\n");
	}

	while (startAt >= 300) {															// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap("level1ID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 10;																	// Decrement the scrolling offset move the texture up the screen

		gStoryA.render((SCREEN_WIDTH - gStoryA.getWidth()) / 2, startAt);				// FOR TESTING

		Texture::Instance()->renderMap("lifePowerUpID", SCREEN_WIDTH - 200, startAt + 70, 60, 60);
		Texture::Instance()->renderMap("checkpointPowerUpID", SCREEN_WIDTH - 200, startAt + 225, 60, 48);

		SDL_RenderPresent(Game::Instance()->getRenderer());															// Update screen
	}

	SDL_Delay(seconds * 1000);

	startAt = SCREEN_HEIGHT;

	while (startAt >= 300) {															// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap("level1ID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 10;																	// Decrement the scrolling offset move the texture up the screen

		gStoryB.render((SCREEN_WIDTH - gStoryB.getWidth()) / 2, startAt);				// FOR TESTING

		Texture::Instance()->renderMap("healthPowerUpID", SCREEN_WIDTH - 200, startAt + 70, 60, 60);
		Texture::Instance()->renderMap("laserPowerUpID", SCREEN_WIDTH - 200, startAt + 210, 60, 48);
		Texture::Instance()->renderMap("rocketPowerUpID", SCREEN_WIDTH - 180, startAt + 300, 30, 60);

		SDL_RenderPresent(Game::Instance()->getRenderer());															// Update screen
	}

	SDL_Delay(seconds * 1000);
}

void SplashScreen::infoScreenStory(int level, int seconds, int startAt) {
	std::string levelID;

	if (level == LEVEL_1) {
		levelID = "level1ID";
		storyPage1 = "Dear Friend, you have made it just in time! We have a mission on our hands that will take all of your skills to succeed!! Our friend the brilliant scientist has been infected with a terrible virus by the evil Dr.G.";
		storyPage2 = "We will use the Shrink Ray to get into the scientists blood stream in our Antibody ships.Once inside the blood stream of our scientist friend we will have to RACE against the clock and follow the blood stream to get to the core of the virus that the evil Dr.G implanted in our friend";
		storyPage3 = "We will face countless enemies that we will need to dispose of. We will also be up against the clock as the scientist does not have long left! We need to hurry and get to the core of this virus asap!!";
	}
	else if (level == LEVEL_2) {
		levelID = "level2ID";
		storyPage1 = "You are making progress friend! You have passed the first test. However, you have further to travel in the blood stream to find the virus planted by the evil Dr.G.";
		storyPage2 = "You will acquire new weapons and boosts to help you on your path, you will need all the help you can get!";
		storyPage3 = "";
	}
	else if (level == LEVEL_3) {
		levelID = "level3ID";
		storyPage1 = "You have made it to the source of the virus! Not far ahead now!\nIt has been a tough road to get here friend, but I knew we could count on you!\nThe final part of this journey awaits you!! Destroy the source of the virus to save our friend!!";
		storyPage2 = "";
		storyPage3 = "";
	}
	gStoryA.free();
	gStoryB.free();
	gStoryC.free();

	if (!gStoryA.loadFromRenderedText(storyPage1, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 36), true)) {
		printf("Failed to render gStoryA text texture!\n");
	}
	if (storyPage2 != "") {
		if (!gStoryB.loadFromRenderedText(storyPage2, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 36), true)) {
			printf("Failed to render gStoryB text texture!\n");
		}
	}
	if (storyPage3 != "") {
		if (!gStoryC.loadFromRenderedText(storyPage3, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 36), true)) {
			printf("Failed to render gStoryC text texture!\n");
		}
	}

	while (startAt >= 300) {															// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap(levelID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		startAt -= 10;																	// Decrement the scrolling offset move the texture up the screen
		gStoryA.render((SCREEN_WIDTH - gStoryA.getWidth()) / 2, startAt);				// FOR TESTING
		SDL_RenderPresent(Game::Instance()->getRenderer());								// Update screen
	}

	SDL_Delay(seconds * 1000);

	if (storyPage2 != "") {
		startAt = SCREEN_HEIGHT;

		while (startAt >= 300) {															// Second Part of story
			SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
			Texture::Instance()->renderMap(levelID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
			startAt -= 10;																	// Decrement the scrolling offset move the texture up the screen
			gStoryB.render((SCREEN_WIDTH - gStoryB.getWidth()) / 2, startAt);				// FOR TESTING
			SDL_RenderPresent(Game::Instance()->getRenderer());								// Update screen
		}

		SDL_Delay(seconds * 1000);
	}

	if (storyPage3 != "") {
		startAt = SCREEN_HEIGHT;

		while (startAt >= 300) {															// Third Part of story
			SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
			Texture::Instance()->renderMap(levelID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
			startAt -= 10;																	// Decrement the scrolling offset move the texture up the screen
			gStoryC.render((SCREEN_WIDTH - gStoryC.getWidth()) / 2, startAt);				// FOR TESTING
			SDL_RenderPresent(Game::Instance()->getRenderer());								// Update screen
		}

		SDL_Delay(seconds * 1000);
	}
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





// Final Score For Level 1 to 3
void SplashScreen::level1FinalScore() {
	scrollDownLogo(LEVEL_1, -SCREEN_HEIGHT);
}
void SplashScreen::level2FinalScore() {
	scrollVerticalLogo(gLevel2, 1, 15, -SCREEN_HEIGHT);
}
void SplashScreen::level3FinalScore() {
	scrollVerticalLogo(gLevel3, 1, 15, -SCREEN_HEIGHT);
}

void SplashScreen::endOfGame(int level, std::string finalScore, std::string winner) {
	gFinalScoreTextTexture.free();
	gGameWinnerTextTexture.free();
	gGameOverTextTexture.free();
	gStoryB.free();

	// init
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
	
	gGameOverTextTexture.setFlash(true);						// Flash text
	gGameOverTextTexture.flashGameObject(5);

	// Render
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x3C, 0x3C, 0x3C, 0xFF);	// Grey colour --> shows up in UI
	SDL_RenderClear(Game::Instance()->getRenderer());

	gLevel3.render(0, 0);																// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

	if (level == 1) scrollUpText("level1ID", gStoryB, 1, 15);							// Set background to appear behind text depending on the level
	else if (level == 2) scrollUpText("level2ID", gStoryB, 1, 15);

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

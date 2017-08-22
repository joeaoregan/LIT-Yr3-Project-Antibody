#include "SplashScreen.h"
//#include <SDL_ttf.h>
//#include <sstream>					// For timer

Texture gLogo1, gLogo2;

enum levels {MENU, LEVEL_1, LEVEL_2, LEVEL_3};

int frame1 = 0;

int scrollOffset = SCREEN_HEIGHT;								// Scrolling offset for splash screens

bool SplashScreen::initSplashScreens(SDL_Renderer *rend) {
	bool success = true;

	if (!gLevel1.loadFromFile("Art/Level1720.png", rend)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (!gLevel2.loadFromFile("Art/Level2720.png", rend)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (!gLevel3.loadFromFile("Art/Level3720.png", rend)) {								// 10/01 Added Power Up - Load Power Up texture
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

	if (!gGameOverTextTexture.loadFromFile("Art/GameOver1.png", rend)) {				// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}

	return success;
}

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

void SplashScreen::closeSplashScreens() {
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

bool SplashScreen::displayGameIntroSplashScreens(SDL_Renderer *rend) {

	if (!gLogo1.loadFromFile("Art/Logo1720.png", rend)) {			// Load the Game Title Logo
		printf("Failed to load Logo 1 - Game Logo texture!\n");
	}
	if (!gLogo2.loadFromFile("Art/Logo2720.png", rend)) {			// Load the Game Creators Logo
		printf("Failed to load Logo 2 - Game Creators texture!\n");
	}

	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);			// Clear the screen
	SDL_RenderClear(rend);

	gLogo1.render(0, 0, rend);										// Game Title

	SDL_RenderPresent(rend);										// Update screen
	SDL_Delay(1000);												// Pause with image on screen for 1 second

	gLogo1.free();													// Free Logo 1 from memory

	scrollVerticalLogo(rend, gLogo2, 1, 15, SCREEN_HEIGHT );		// Scroll up Logo2 and delay for 1 second

	return false;
}

// Level 1 background with scrolling text
bool SplashScreen::level1IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip, Texture &health, Texture &Laser, Texture &rocket) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel1, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen

	enemyInformationSplashScreenOne(rend, gLevel1, virus, orangeVirus, enemyShip, health, Laser, rocket);

	// Objectives
	scrollVerticalLogo(rend, gLevel1, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, gLevel1, gLevelObjectiveTextTexture, 0);
}

// Level 2 background, with scrolling text
void SplashScreen::level2IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel2, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen

	enemyInformationSplashScreenTwo(rend, gLevel2, virus, orangeVirus, enemyShip, enemyShip, enemyShip, enemyShip);

	// Objectives
	scrollVerticalLogo(rend, gLevel2, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, gLevel2, gLevelObjectiveTextTexture, 0);
}

// Level 3 background with scrolling text
void SplashScreen::level3IntroScreens(SDL_Renderer *rend, Texture &virus, Texture &orangeVirus, Texture &enemyShip) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };

	std::string levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score\nIs the winner";

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, gFont, rend, true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollVerticalLogo(rend, gLevel3, 0, 15, -SCREEN_HEIGHT);											// Scroll Level1 logo down the screen

	enemyInformationSplashScreenThree(rend, gLevel3, virus, orangeVirus, enemyShip, enemyShip, enemyShip, virus);

	// Objectives
	scrollVerticalLogo(rend, gLevel3, 1, 10, -SCREEN_HEIGHT);

	scrollUpText(rend, gLevel3, gLevelObjectiveTextTexture, 0);
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
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 40);
	textColour = {0, 255, 0, 255};
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
			printf("Unable to render game winner texture!\n");
		}

		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, gFont, rend)) {
			printf("Unable to render final scores texture!\n");
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

void SplashScreen::enemyInformationSplashScreenOne(SDL_Renderer *rend, Texture &background, Texture &img1, Texture &img2, Texture &img3, Texture &img4, Texture &img5, Texture &img6) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 255,255,255,255 };	// White font colour

	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	storyPage2 = "Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";
	storyPage3 = "Dear Friend, you have made it just in time! We have a mission on our hands that will take all of your skills to succeed!! Our friend the brilliant scientist has been infected with a terrible virus by the evil Dr.G.\n\nWe will use the Shrink Ray to get into the scientists blood stream in our Antibody ships. Once inside the blood stream of our scientist friend we will have to RACE against the clock and follow the blood stream to get to the core of the virus that the evil Dr.G implanted in our friend\n\nWe will face countless enemies that we will need to dispose of. We will also be up against the clock as the scientist does not have long left! We need to hurry and get to the core of this virus asap!!";

		// Story
		if (!gStoryA.loadFromRenderedText(storyPage1, textColour, gFont, rend, true)) {
			printf("Unable to render level game objective texture!\n");
		}
		if (!gStoryB.loadFromRenderedText(storyPage2, textColour, gFont, rend, true)) {
			printf("Failed to render text texture!\n");
		}
		if (!gStoryC.loadFromRenderedText(storyPage3, textColour, gFont, rend, true)) {
			printf("Failed to render text texture!\n");
		}

	infoScreenL1Enemies(rend, 2, SCREEN_HEIGHT, background, gStoryA, img1, img2, img3);
	infoScreenL1PowerUps(rend, 2, SCREEN_HEIGHT, background, gStoryB, img4, img5, img6);

	scrollUpText(rend, background, gStoryC, 2);									// 3rd page of text for story NO INFORMATION ON THIS YET
}

void SplashScreen::enemyInformationSplashScreenTwo(SDL_Renderer *rend, Texture &background, Texture &img1, Texture &img2, Texture &img3, Texture &img4, Texture &img5, Texture &img6) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 255,255,255,255 };	// White font colour

	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	storyPage2 = "Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";
	storyPage3 = "You are making progress friend! You have passed the first test. However, you have further to travel in the blood stream to find the virus planted by the evil Dr.G.\n\nYou will acquire new weapons and boosts to help you on your path, you will need all the help you can get! ";

	// Story
	if (!gStoryA.loadFromRenderedText(storyPage1, textColour, gFont, rend, true)) {
		printf("Unable to render level game objective texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(storyPage2, textColour, gFont, rend, true)) {
		printf("Failed to render text texture!\n");
	}
	if (!gStoryC.loadFromRenderedText(storyPage3, textColour, gFont, rend, true)) {
		printf("Failed to render text texture!\n");
	}

	infoScreenL1Enemies(rend, 2, SCREEN_HEIGHT, background, gStoryA, img1, img2, img3);
	infoScreenL1PowerUps(rend, 2, SCREEN_HEIGHT, background, gStoryB, img4, img5, img6);

	scrollUpText(rend, background, gStoryC, 2);									// 3rd page of text for story NO INFORMATION ON THIS YET
}

void SplashScreen::enemyInformationSplashScreenThree(SDL_Renderer *rend, Texture &background, Texture &img1, Texture &img2, Texture &img3, Texture &img4, Texture &img5, Texture &img6) {
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 255,255,255,255 };	// White font colour

	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	storyPage2 = "Power Ups:\n\nPlayers can collect power ups\nTo increase health\n\n\nAnd to upgrade weapons such as the laser\n\n\nAnd collect projectiles such as missiles";
	storyPage3 = "You have made it to the source of the virus! Not far ahead now!\n\nIt has been a tough road to get here friend, but I knew we could count on you!\n\nThe final part of this journey awaits you!! Destroy the source of the virus to save our friend!!";

	// Story
	if (!gStoryA.loadFromRenderedText(storyPage1, textColour, gFont, rend, true)) {
		printf("Unable to render level game objective texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(storyPage2, textColour, gFont, rend, true)) {
		printf("Failed to render text texture!\n");
	}
	if (!gStoryC.loadFromRenderedText(storyPage3, textColour, gFont, rend, true)) {
		printf("Failed to render text texture!\n");
	}

	infoScreenL1Enemies(rend, 2, SCREEN_HEIGHT, background, gStoryA, img1, img2, img3);
	infoScreenL1PowerUps(rend, 2, SCREEN_HEIGHT, background, gStoryB, img4, img5, img6);

	scrollUpText(rend, background, gStoryC, 2);									// 3rd page of text for story NO INFORMATION ON THIS YET
}



#include "SplashScreen.h"
#include <SDL_ttf.h>
//#include <sstream>					// For timer

enum levels {MENU, LEVEL_1, LEVEL_2, LEVEL_3};

int scrollOffset = SCREEN_HEIGHT;								// Scrolling offset for splash screens

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

/*
std::string storyA = "The player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
std::string storyB = "Story 2 blah blah \nBrian fill this\nIn Later";
std::string storyC = "Story 3 blah blah blah\nBrian fill this\nIn Later";


void SplashScreen::displayLevelSplashScreen(std::string objective, SDL_Renderer *rend, int level) {
	// STORY
	textColour = { 255,255,255,255 };

	//if (!gStoryA.loadFromRenderedText(storyA, textColour, gFontRetro20A, rend, true)) {
	if (!gStoryA.loadFromRenderedText("test", textColour, gFontRetro20A, rend)) {
		printf("Unable to render level game objective texture!\n");
	}
	//if (!gStoryB.loadFromRenderedText(storyB, textColour, gFontRetro20A, rend, true)) {
	//	printf("Failed to render text texture!\n");
	//}
	//if (!gStoryC.loadFromRenderedText(storyC, textColour, gFontRetro20A, rend, true)) {
	//	printf("Failed to render text texture!\n");
	//}
	//scrollingOffsetLogo = 600;								// Start at bottom of screen
	/*
	//while (scrollingOffsetLogo >= 0) {
	gLevel1a.render(0, scrollOffset, rend);	// Scroll up Level 1 background
														
	scrollOffset = 600;								// Texture will start below window

	while (scrollOffset >= 300) {														// First Part of story
		SDL_RenderClear(rend);																// Clear the screen
		if (level == MENU) gLevel1a.render(0, 0, rend);							// Static background

		scrollOffset -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStoryA.render((SCREEN_WIDTH - gStoryA.getWidth()) / 2, scrollOffset, rend); // FOR TESTING
		gEnemyVirusTextureA.render(SCREEN_WIDTH - gEnemyVirusTextureA.getWidth() - 100, scrollOffset, rend);
		gEnemyVirusOrangeTextureA.render(SCREEN_WIDTH - gEnemyVirusOrangeTextureA.getWidth() - 100, scrollOffset + 100, rend);
		gEnemyShipTextureA.render(SCREEN_WIDTH - gEnemyShipTextureA.getWidth() - 100, scrollOffset + 200, rend);

		SDL_RenderPresent(rend);															// Update screen
	}

	SDL_Delay(2000);																			// Pause with image on screen





	scrollOffset = 600;								// Texture will start below window

	while (scrollOffset >= 300) {														// Second part of story
		SDL_RenderClear(rend);																// Clear the screen
		if (level == MENU) gLevel1a.render(0, 0, rend);							// Static background

		scrollOffset -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStoryB.render((SCREEN_WIDTH - gStoryB.getWidth()) / 2, scrollOffset, rend); // FOR TESTING

		SDL_RenderPresent(rend);			// Update screen
	}

	SDL_Delay(2000);										// Pause with image on screen																		// Pause with image on screen





	scrollOffset = 600;								// Texture will start below window

	while (scrollOffset >= 300) {														// Second part of story
		SDL_RenderClear(rend);																// Clear the screen
		if (level == 0) gLevel1a.render(0, 0, rend);							// Static background

		scrollOffset -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStoryC.render((SCREEN_WIDTH - gStoryC.getWidth()) / 2, scrollOffset, rend); // FOR TESTING

		SDL_RenderPresent(rend);						// Update screen
	}

	SDL_Delay(2000);										// Pause with image on screen




	// OBJECTIVES
	scrollOffset = -600;								// Logo will start above window

	while (scrollOffset <= 0) {
		gLevel1a.render(0, scrollOffset, rend);
		scrollOffset += 5;							// Decrement scrollling offset to move texture up the screen

		SDL_RenderPresent(rend);						// Update screen for each movement
	}

	scrollOffset = 600;								// Texture will start below window

	textColour = { 0, 255, 0, 255 };						// Green text for level objectives

	if (!gLevelObjectiveTextTextureA.loadFromRenderedText(objective, textColour, gFontRetro20A, rend, true)) {
		printf("Unable to render level game objective texture!\n");
	}

	while (scrollOffset >= 300) {
		SDL_RenderClear(rend);																// Clear the screen
		if (level == MENU) gLevel1a.render(0, 0, rend);							// Static background
		else if (level == LEVEL_1) gLevel1a.render(0, 0, rend);						// Static background
		else if (level == LEVEL_2) gLevel2a.render(0, 0, rend);					// Static background
		else if (level == LEVEL_3) gLevel3a.render(0, 0, rend);					// Static background

		scrollOffset -= 5;
		gLevelObjectiveTextTextureA.render((SCREEN_WIDTH - gLevelObjectiveTextTextureA.getWidth()) / 2, scrollOffset, rend); // FOR TESTING

		SDL_RenderPresent(rend);			// Update screen
	}

	//pressButtonToContinue();
	
}
*/

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


// Scroll text and image up the screen
void SplashScreen::scrollTextAndImage(SDL_Renderer *rend, int seconds, int startAt, Texture &background, Texture &story, Texture &tx1, Texture &tx2, Texture &tx3) {
	while (startAt >= 300) {												// First Part of story
		SDL_RenderClear(rend);												// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		background.render(0, 0, rend);										// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 5;														// Decrement the scrolling offset move the texture up the screen
		story.render((SCREEN_WIDTH - story.getWidth()) / 2, startAt, rend); // FOR TESTING
		tx1.render(SCREEN_WIDTH - tx1.getWidth() - 100, startAt, rend);
		tx2.render(SCREEN_WIDTH - tx2.getWidth() - 100, startAt + 100, rend);
		tx3.render(SCREEN_WIDTH - tx3.getWidth() - 100, startAt + 200, rend);

		SDL_RenderPresent(rend);															// Update screen
	}

	SDL_Delay(seconds * 1000);

}

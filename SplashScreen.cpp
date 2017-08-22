#include "SplashScreen.h"
//#include <SDL_ttf.h>
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

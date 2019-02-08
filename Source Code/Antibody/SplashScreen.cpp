/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					SplashScreen.cpp
		- Description:			Handles intro screens, information screens and their random movement
		- Information:			Game intro screens and information screens at start of game are created in this class, 
								and transition screens between level with scores and level objectives.
								Displays final score and game winner at end of game.

								Backgrounds have random scrolling, up / down / left / right to give a
								transition affect between title, logo, and information screens

		- Log:
			2017/03/06			Added function for randomly selecting the scrolling direction for level background logos
								Added function for choosing the level background ID based on the level
								Added array for loading textures
			2017/02/09			 Added separate function for text and logos to Game class
			2017/02/08			Added separate splash screen class SplashScreen.h for displaying splash screens
								Moved press enter to continue for splash screens instead of delay before progressing to level
			2017/02/02			Added storyline at intro to game
			2017/01/20			Added game over message
			2017/01/18			Added splash screens at start of game, Game Title & Game Creators
								Added pressButtonToContinue() function for splash screens at start of game, so player can read writing at own pace
			2017/01/17			Added scrolling text to intro screens
								Added wrapped text to add new line character for level intro splash screens
			2017/01/11			Added flashing game over texture
------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include "SplashScreen.h"
#include "Game.h"

int frame1 = 0;
int scrollOffset = SCREEN_HEIGHT;	// Scrolling offset for splash screens
const int NUM_TEXTURES = 5;

/*
	2D Array containing the path, ID, and identification to display for error / information messages
*/
std::string textures[NUM_TEXTURES][3] = {
	{ "Art/Logo1720.png", "gameTitleID", "Game Title" },
	{ "Art/Logo2720.png", "createdByID", "Created By" },
	{ "Art/Level1720.png", "level1ID", "Level 1 Backdrop" },
	{ "Art/Level2720.png", "level2ID", "Level 2 Backdrop" },
	{ "Art/Level3720.png", "level3ID", "Level 3 Backdrop" }
};

/*	
	Initialise the images used for splash screens and logos 
*/
bool SplashScreen::initSplashScreens() {
	bool success = true;

	levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";

	Texture::Instance()->loadFromRenderedTextID(levelObjective, "level1ObjectiveID", textColour, TTF_OpenFont("Fonts/Retro.ttf", 32)); // 2017/03/18
		
	// Init the game title and credit screens
	for (int i = 0; i < NUM_TEXTURES; i++) {
		if (!Texture::Instance()->load(textures[i][0], textures[i][1])) {					// Game Title Logo
			std::cout << "Failed to load " << textures[i][2] << " texture!" << std::endl;
			success = false;
		}
	}

	//Load animated sprite sheet texture
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

	// Load flashing texture
	if (!gGameOverTextTexture.loadFromFile("Art/GameOver1.png")) {					// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}

	return success;
}

/* 
	Free the textures from memory when the game is finished 
	or when the textures are not being used
*/
void SplashScreen::closeSplashScreens() {
	// Clear Game title texture
	if (Game::Instance()->getCurrentLevel() == GAME_INTRO) {
		Texture::Instance()->clearFromTextureMap("gameTitleID");
		Texture::Instance()->clearFromTextureMap("createdByID");

		std::cout << "GAME_INTRO media removed" << std::endl;
	}
	else {
		// Free splash screen textures
		gFinalScoreTextTexture.free();
		gGameWinnerTextTexture.free();
		gGameOverTextTexture.free();
		gPressEnterSpriteSheetTexture.free();
		gObjectiveTextTexture.free();
		gStoryA.free();
		gStoryB.free();
		gStoryC.free();

		// 2017/03/18 Clear textures from texture map
		if (Game::Instance()->getCurrentLevel() != GAME_INTRO) {
			for (int i = 0; i < NUM_TEXTURES; i++) {
				Texture::Instance()->clearFromTextureMap(textures[i][1]);
			}
		}

		//Free global font
		TTF_CloseFont(gFont);
		gFont = NULL;
	}
}

/*	
	Press button to continue message - pauses the screen until a button is pressed
	This is rendered onto whatever background is already in place
*/
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

/*
	Display intro screens at start of game before menu
	2017/02/26 changed to texture instance
*/
bool SplashScreen::displayGameTitleScreens() {
	// Set up the renderer
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);	// Clear the screen
	SDL_RenderClear(Game::Instance()->getRenderer());

	Texture::Instance()->renderMap("gameTitleID", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_RenderPresent(Game::Instance()->getRenderer());									// Update screen
	SDL_Delay(1000);																	// Pause with image on screen for 1 second

	scrollRandomBackground("createdByID", 20, 1);										// Scroll the created by texture in randomly

	// After GAME_INTRO title screens, clear game info media and go to the menu
	closeSplashScreens();
	Game::Instance()->setCurrentLevel(MENU);

	return false;
}

/*	
	Scroll Up, down, left, or right
	2017/03/06 Choose a random Level Number Background scrolling sequence
*/
void SplashScreen::scrollRandomBackground(std::string textureID, int rate, int seconds) {
	int scrollFrom = rand() % 4;

	if (scrollFrom == 0) scrollLogoHorizontal(textureID, seconds, rate, -SCREEN_WIDTH);
	else if (scrollFrom == 1) scrollLogoHorizontal(textureID, seconds, rate, SCREEN_WIDTH);
	else if (scrollFrom == 2) scrollLogoVertical(textureID, seconds, rate, -SCREEN_WIDTH);
	else if (scrollFrom == 3) scrollLogoVertical(textureID, seconds, rate, SCREEN_WIDTH);

}

// Scroll a logo left or right on the screen
void SplashScreen::scrollLogoHorizontal(std::string textureID, int seconds, int rate, int startAt, int stopAt) {
	//if (textureID != "createdByID") SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 12, 77, 255);			// Purple
	//SDL_RenderClear(Game::Instance()->getRenderer());

	if (startAt < stopAt) {
		// Scroll From Right
		while (startAt <= stopAt) {																// While less than or equal to zero
			Texture::Instance()->renderMap(textureID, startAt, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			startAt += rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());									// Update screen
		}
	}
	else {
		// Scroll From Left
		while (startAt >= stopAt) {																// While less than or equal to zero
			Texture::Instance()->renderMap(textureID, startAt, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			startAt -= rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());									// Update screen
		}
	}

	SDL_Delay(seconds * 1000);																// Pause with image on screen for a number of seconds
}

// Scroll a logo up or down the screen
//void SplashScreen::scrollVerticalLogo(Texture &texture, int seconds, int rate, int startAt, int stopAt) {
void SplashScreen::scrollLogoVertical(std::string textureID, int seconds, int rate, int startAt, int stopAt) {
	//if (textureID != "createdByID") SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 12, 77, 255);			// Purple
	//SDL_RenderClear(Game::Instance()->getRenderer());

	if (startAt > stopAt) {
		while (startAt >= stopAt) {								// While greater than or equal to zero
																//texture.render(0, startAt);							// Team Member Names
			Texture::Instance()->renderMap(textureID, 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
			startAt -= rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());	// Update screen
		}
	}
	else {
		while (startAt <= stopAt) {								// While less than or equal to zero
																//texture.render(0, startAt);							// Team Member Names
			Texture::Instance()->renderMap(textureID, 0, startAt, SCREEN_WIDTH, SCREEN_HEIGHT);
			startAt += rate;

			SDL_RenderPresent(Game::Instance()->getRenderer());	// Update screen
		}
	}

	SDL_Delay(seconds * 1000);									// Pause with image on screen for a number of seconds
}

//	Level 1 background with scrolling text
bool SplashScreen::levelIntroScreens(int level) {
	std::string levelID = "";
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 20);
	textColour = { 0, 255, 0, 255 };
	gObjectiveTextTexture.free();

	if (level == LEVEL_1) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";
	else if (level == LEVEL_2) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";
	else if (level == LEVEL_3) levelObjective = "Destroy the enemy virus and nano bots\nThe player with the highest score is the winner\n\nBeat the clock to complete the level!";

	if (!gObjectiveTextTexture.loadFromRenderedText(levelObjective, textColour, TTF_OpenFont("Fonts/Retro.ttf", 32), true)) {	// Green text for level objectives
		printf("Unable to render level game objective texture!\n");
	}

	scrollRandomBackground(chooseBackground(level));				// Choose level background, scrolling randomly from left, right, top, or bottom
	infoScreenEnemies(level, 2, SCREEN_HEIGHT);						// Give info on the enemies in the current level
	infoScreenPowerUps(level, 2, SCREEN_HEIGHT);					// Give info on power ups in the current level
	infoScreenStory(level, 8, SCREEN_HEIGHT);						// Display the story
	scrollRandomBackground(chooseBackground(level));				// Choose level background, scrolling randomly from left, right, top, or bottom
	scrollUpText(chooseBackground(level), gObjectiveTextTexture);	// Scroll up the current level objective

	return false;	// set display screens boolean to false so it stops, will continue repeating over and over if true
}

// Scroll text and image up the screen with information about the enemies in Level 1
void SplashScreen::infoScreenEnemies(int level, int seconds, int startAt) {
	std::string en1, en2, en3;
	storyPage1 = "Enemies:\n\nThe player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
	gStoryA.free();
	if (!gStoryA.loadFromRenderedText(storyPage1, { 255,255,255,255 }, TTF_OpenFont("Fonts/Retro.ttf", 22), true)) {
		printf("Unable to render gStoryA level game objective texture!\n");
	}

	if (level == LEVEL_1) {
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "enemyShipID";
	}
	else if (level == LEVEL_2) {
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "enemyShipID";
	}
	else if (level == LEVEL_3) {
		en1 = "greenVirusID";
		en2 = "orangeVirusID";
		en3 = "blueVirusID";
	}

	while (startAt >= 300) {																		// First Part of story
		SDL_RenderClear(Game::Instance()->getRenderer());											// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap(chooseBackground(level), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		SDL_RenderClear(Game::Instance()->getRenderer());											// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
		Texture::Instance()->renderMap(chooseBackground(level), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= 10;																				// Decrement the scrolling offset move the texture up the screen
		gStoryA.render((SCREEN_WIDTH - gStoryA.getWidth()) / 2, startAt);							// FOR TESTING

		Texture::Instance()->renderMap(en1, SCREEN_WIDTH - 175, startAt + 50, 75, 75);				// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap(en2, SCREEN_WIDTH - 175, startAt + 170, 75, 75);				// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME
		Texture::Instance()->renderMap(en3, SCREEN_WIDTH - 175, startAt + 280, 75, 75);				// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		SDL_RenderPresent(Game::Instance()->getRenderer());											// Update screen
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
		Texture::Instance()->renderMap(chooseBackground(level), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

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
		Texture::Instance()->renderMap(chooseBackground(level), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

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
	if (level == LEVEL_1) {
		storyPage1 = "Dear Friend, you have made it just in time! We have a mission on our hands that will take all of your skills to succeed!! Our friend the brilliant scientist has been infected with a terrible virus by the evil Dr.G.";
		storyPage2 = "We will use the Shrink Ray to get into the scientists blood stream in our Antibody ships.Once inside the blood stream of our scientist friend we will have to RACE against the clock and follow the blood stream to get to the core of the virus that the evil Dr.G implanted in our friend";
		storyPage3 = "We will face countless enemies that we will need to dispose of. We will also be up against the clock as the scientist does not have long left! We need to hurry and get to the core of this virus asap!!";
	}
	else if (level == LEVEL_2) {
		storyPage1 = "You are making progress friend! You have passed the first test. However, you have further to travel in the blood stream to find the virus planted by the evil Dr.G.";
		storyPage2 = "You will acquire new weapons and boosts to help you on your path, you will need all the help you can get!";
		storyPage3 = "";
	}
	else if (level == LEVEL_3) {
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

	scrollUpText(chooseBackground(level), gStoryA, 1, 10, SCREEN_HEIGHT, 300);							// Story page 1
	SDL_Delay(seconds * 1000);									// Pause with image on screen
	if (storyPage2 != "") scrollUpText(chooseBackground(level), gStoryB, 1, 10, SCREEN_HEIGHT, 300);	// Story page 2
	SDL_Delay(seconds * 1000);									// Pause with image on screen
	if (storyPage3 != "") scrollUpText(chooseBackground(level), gStoryC, 1, 10, SCREEN_HEIGHT, 300);	// Story page 3
	SDL_Delay(seconds * 1000);									// Pause with image on screen
}

/*
	Scroll text up the screen from the startAt point to the stopAt point, and show for a number of seconds before progressing

	2017/02/26: Edited to take an ID string to search texture map in texture class
*/
void SplashScreen::scrollUpText(std::string backgroundID, Texture &text, int seconds, int rate, int startAt, int stopAt) {
	while (startAt >= stopAt) {															// While the text hasn't reached the stopping point
		SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen

		Texture::Instance()->renderMap(backgroundID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME

		startAt -= rate;																// Decrement the scrolling offset move the texture up the screen
		text.render((SCREEN_WIDTH - text.getWidth()) / 2, startAt);						// FOR TESTING

		SDL_RenderPresent(Game::Instance()->getRenderer());								// Update screen
	}

	SDL_RenderClear(Game::Instance()->getRenderer());
	Texture::Instance()->renderMap(backgroundID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	// Static background	AND THE BACKGROUND NEEDS TO BE BEHIND THE TEXT EACH TIME									// Clear the screen		NEED TO CLEAR THE SCREEN EACH TIME OR GET STREAKY TEXT
	text.render((SCREEN_WIDTH - text.getWidth()) / 2, startAt);							// FOR TESTING
	SDL_RenderPresent(Game::Instance()->getRenderer());									// Update screen

	SDL_Delay(seconds * 1000);															// Pause with image on screen
}

std::string SplashScreen::chooseBackground(int level) {
	std::string textureID = "";

	if (level == LEVEL_1) textureID = "level1ID";
	else if (level == LEVEL_2) textureID = "level2ID";
	else if (level == LEVEL_3) textureID = "level3ID";

	return textureID;
}

void SplashScreen::endOfGame(int level, std::string finalScore, std::string winner) {
	gFinalScoreTextTexture.free();
	gGameWinnerTextTexture.free();
	gGameOverTextTexture.free();
	gStoryB.free();

	// init
	gFont = TTF_OpenFont("Fonts/Retro.ttf", 40);										// Retro font size 40
	textColour = { 0, 255, 0, 255 };														// Green text colour
	TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);											// Use bold font
	std::string complete = "Complete!!!";

	if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, TTF_OpenFont("Fonts/Retro.ttf", 50))) {
		printf("Unable to render final scores texture!\n");
	}
	if (!gStoryB.loadFromRenderedText(complete, { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 60))) {
		printf("Unable to render final scores texture!\n");
	}

	scrollRandomBackground(chooseBackground(level));									// Choose level background, scrolling randomly from left, right, top, or bottom

	gGameOverTextTexture.setFlash(true);												// Flash text
	gGameOverTextTexture.flashGameObject(5);

	// Render
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x3C, 0x3C, 0x3C, 0xFF);	// Grey colour --> shows up in UI
	SDL_RenderClear(Game::Instance()->getRenderer());

	scrollUpText(chooseBackground(level), gStoryB, 1, 15);								// Set background to appear behind text depending on the level, and scroll the text

	gFinalScoreTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
	gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2); // FOR TESTING

																																						   // If the game is over display the game winner message and final scores for player(s)
	if (Game::Instance()->gameOver == true) {
		if (!gGameWinnerTextTexture.loadFromRenderedText(winner, textColour, gFont)) {
			printf("Unable to render GameWinnerTextTexture game winner texture!\n");
		}

		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScore, textColour, gFont)) {
			printf("Unable to render FinalScoreTextTexture final scores texture!\n");
		}

		gGameOverTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 100) / 2);		// FOR TESTING
		gGameWinnerTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
		gGameWinnerTextTexture.render((SCREEN_WIDTH - gGameWinnerTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameWinnerTextTexture.getHeight() + 450) / 2);	// FOR TESTING
	}
}
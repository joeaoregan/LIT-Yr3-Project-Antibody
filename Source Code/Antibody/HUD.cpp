/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					GameObject.cpp
	- Description:			cpp file for the gameobject class.
	- Information:			This class contains all the information relavent to the player dashboard, including lives, scores, and weapon indicators
							for each player. Weapon indicators include, current laser grade, number of rockets, and an indicator for when the player
							speed boost is active, displaying a status bar for when the boost timer runs out.

							The game map is also displayed here in mini form, which can be resized by pressing a button on the keyboard or gamepad.
							There is also an animated game creator text on the bottom of the display.
	- Log:
		2017/03/20		Moved additional render functionality from Game class
		2017/03/18		Cut 2 mb/sec memory leak by loading createdByTextTexture text in 3 separate textures only once in the game in Texture class
		2017/03/03		Fixed rendered text so that it is only updated or loaded when needed, as it eats too much memory
						Moved some text functions back out of Texture class to HUD class
						Added a timer to created by text, so it only updates when the timer changes and not constantly
						Added a variable to store the previous rocket number, so the text displayed only renders again when changed
						Loading Speed Boost text for indicator only once in HUD load function, saving more memory wasting
						Added a previous state variable for scores, does the same thing as the rocket number indicator
		2017/02/21		All indicators now scroll left to right on start up
		2017/02/21		Moved player lives, scores, speed boost indicator, rocket indicator, and created by text to head up display
		2017/02/19		Added rocket icon to viewoport displaying information on the number of rockets in the players inventory
	----------------------------------------------------------------------------------------------------------------------*/
#include "HUD.h"
#include <sstream>
#include "GameObject.h"	// 2017/03/20 For Weapon indicators
#include "StatusBar.h"	// 2017/03/20 Speed boost timer

StatusBar HUDbar;

void setViewport2(SDL_Rect &rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

unsigned int createdByTimer = 0, createdByLastTime = 0, changeEverySecond = 0;

bool HUD::loadLevelStuff() {
	miniMap = true;													// 2017/03/20 Set display mini version of map true

	// View ports
	//setViewport2(gameVP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// Main Game Screen
	setViewport2(UIVP, 0, 600, SCREEN_WIDTH, 120);					// Bottom of screen UI / Info
	// Player 1
	setViewport2(weaponVP1, 10, 600, 60, 60);						// Current Main Weapon Selected
	setViewport2(rocketVP1, 70, 600, 60, 60);						// Current Main Weapon Selected
	setViewport2(boostVP1, 130, 600, 60, 60);						// Current Main Weapon Selected
	// Player 2
	setViewport2(weaponVP2, SCREEN_WIDTH - 70, 600, 60, 60);		// Current Main Weapon Selected
	setViewport2(rocketVP2, SCREEN_WIDTH - 130, 600, 60, 60);		// Current Main Weapon Selected
	setViewport2(boostVP2, SCREEN_WIDTH - 190, 600, 60, 60);		// Current Main Weapon Selected

	bool success = true;

	//Texture::Instance()->loadFromRenderedTextID("Level " + std::to_string(Game::Instance()->getCurrentLevel()), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20)); // 2017/03/18 Moved from Game class

	// 2017/03/03 Moved to init as text only needs to be loaded once because it never changed, will consider changing to image
	if (!gSpeedBoostTextTexture.loadFromRenderedText("Speed\nBoost", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 13), true)) {		// Green Text
		printf("speedBoostText(): Unable to render Speed Boost User Interface Text Texture!\n");
	}

	// Created by text at the bottom of the heads up display
	if (!gCreatedByTextTexture1.loadFromRenderedText("ANTIBODY", { 50, 200, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {			// Green Text
		printf("createdByText(): Unable to render Created By Text Texture!\n");
	}
	if (!gCreatedByTextTexture2.loadFromRenderedText("A GAME BY", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		printf("createdByText(): Unable to render Created By Text Texture!\n");
	}
	if (!gCreatedByTextTexture3.loadFromRenderedText("JOE O'REGAN, SEAN HORGAN, BRIAN RYAN", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		printf("createdByText(): Unable to render Created By Text Texture!\n");
	}

	gHUDFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gHUDFont == NULL) {
		printf("Failed to load gHUDFont (Retro, 16) font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	if (!gP1LivesTexture.loadFromFile("Art/Player1ShipSmall.png")) {				// Player 1 Lives Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmall.png")) {				// Player 2 Lives Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	}
	if (!gPowerUpRocketTexture.loadFromFile("Art/PowerUpRocket.png")) {			// Rocket Power Up Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}
	/*
	if (!gCreatedByTextTexture.loadFromRenderedText("ANTIBODY", { 50, 200, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		printf("createdByText(): Unable to render Created By Text Texture!\n");
	}
	gSpeedBoostTextTexture.speedBoostText("Speed\nBoost");// Create the text

	void Texture::speedBoostText(std::string textureText, SDL_Renderer* rend) {
	*/

	return success;
}

void HUD::resetHUD() {
	//gTimeTextTexture.setFlash(false);		// Reset the timer flash

	setViewport2(mapVP, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// Reset the map to small size // 2017/03/20 Moved from Game class
	Texture::Instance()->modifyAlpha(255, "profID");				// 2017/03/20 Moved from Game class

	weaponScrolling = 60;
}

void HUD::closeLevelStuff() {
	gLevelTextTexture.free();
	gSpeedBoostTextTexture.free();
	gPowerUpRocketTexture.free();
	gNumRocketsTextTexture1.free();
	gNumRocketsTextTexture2.free();
	gCreatedByTextTexture1.free();
	gCreatedByTextTexture2.free();
	gCreatedByTextTexture3.free();
	gP1LivesTexture.free();
	gP2LivesTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();
	//gTimeTextTexture.free();
	//gNumRocketsTextTexture2.free();
}

void HUD::render() {
	if (weaponScrolling > 0) weaponScrolling--;

	bool numPlayers2 = Game::Instance()->twoPlayer;
	scoreP1 = Game::Instance()->player1Score;
	scoreP2 = Game::Instance()->player2Score;

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &Game::Instance()->gameViewport);					// Game Viewport
	
	displayLevelNum(Game::Instance()->getCurrentLevel());														// Display Level Number in top left corner of game screen

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &UIVP);												// User Interface Viewport
	
	playerScore(Game::Instance()->twoPlayer, Game::Instance()->player1Score, Game::Instance()->player2Score);	// Player Scores
	//headsUpDisplay.percentageNinjaStarKills(twoPlayer, ninjaStarP1Counter, ninjaStarP2Counter);
	//headsUpDisplay.playerScoresCounter(twoPlayer, scoreTextP1counter, scoreTextP2counter);

	// 2017/02/22 Add check for player being alive
	if (Game::Instance()->twoPlayer && aliveP1 && aliveP2)														// If it is a 2 player game and both Players are alive
		rendPlayerLives(livesP1, livesP2);																		// Show lives for both players
	else if (aliveP1 == false && aliveP2)																		// If only player 2 is alive
		rendPlayerLives(0, livesP2);																			
	else if (aliveP1 && (aliveP2 == false && !Game::Instance()->twoPlayer))										// If it is a 2 player game and only player 1 is alive
		rendPlayerLives(livesP1);

	if (aliveP1)
		rendPlayerLives(livesP1);																				// Lives for Player 1 when only player 1

	createdByText();																							// Show creater animated text at bottom-centre of HUD

	/* Professor Mini Map */
	//SDL_RenderSetViewport(Game::Instance()->getRenderer(), &Game::Instance()->mapViewport);					// User Interface Viewport
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &mapVP);												// User Interface Viewport

	Texture::Instance()->renderMap("profID");
	shipPositionOnMap();																						// Display ship position on map;

	// Player 1 Info
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &weaponVP1);											// Laser Grade ViewPort
	if (gradeP1 == LASER_SINGLE) Texture::Instance()->weaponIndicator("laserPowerUpID", weaponScrolling);		// Show single laser indicator
	else if (gradeP1 == LASER_DOUBLE) Texture::Instance()->weaponIndicator("laserPowerUpV2ID", weaponScrolling);// Show double laser indicator
	else if (gradeP1 == LASER_TRIPLE) Texture::Instance()->weaponIndicator("laserPowerUpV3ID", weaponScrolling);// Show triple laser indicator

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &rocketVP1);											// Rocket Amount ViewPort

	if (aliveP1) {																								// If player 1 is alive
		rocketIndicator(rocketsP1, PLAYER_1, aliveP1);															// Number of rockets for Player 1
	}
	else rocketIndicator(0, false, PLAYER_1);

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &boostVP1);											// Speed Boost ViewPort for Player 1
	if (aliveP1) speedBoostIndicator(speedP1);																	// 2017/02/22 Added check to make sure player is alive
	else speedBoostIndicator(false);

	HUDbar.speedBoostBar(timerP1);																				// Show the Player 1 speed boost status bar

	// Player 2 Info
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &weaponVP2);											// Laser Grade ViewPort for Player 2
	if (gradeP2 == LASER_SINGLE) Texture::Instance()->weaponIndicator("laserPowerUpID", weaponScrolling);		// Show single laser indicator
	else if (gradeP2 == LASER_DOUBLE) Texture::Instance()->weaponIndicator("laserPowerUpV2ID", weaponScrolling);// Show double laser indicator
	else if (gradeP2 == LASER_TRIPLE) Texture::Instance()->weaponIndicator("laserPowerUpV3ID", weaponScrolling);// Show triple laser indicator
	
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &rocketVP2);											// Rocket Amount ViewPort for Player 2

	if (Game::Instance()->twoPlayer && aliveP2) {																// If it is a 2 player game and Player 2 is alive
		rocketIndicator(rocketsP2, PLAYER_2, aliveP2);															// Number of rockets for Player 2
	}
	else if (Game::Instance()->twoPlayer && !aliveP2) rocketIndicator(0, false, PLAYER_2);						// If it is a 2 player game and Player 2 is not alive

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &boostVP2);											// Speed Boost ViewPort for Player 2

	if (Game::Instance()->twoPlayer && aliveP2) speedBoostIndicator(speedP2);									// 2017/02/22 Added check to make sure player is alive
	else if (Game::Instance()->twoPlayer && !aliveP2) speedBoostIndicator(false);

	if (Game::Instance()->twoPlayer) HUDbar.speedBoostBar(timerP1, START_RIGHT);								// If 2 player game draw Player 2 speed boost bar, bar moves in opposite direction to Player 1s

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);												// Reset Viewport

	// Draw lines around weapon indicators
	if (aliveP1) 
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0, 255, 0, 255);								// Set Colour for squares around viewports to green
	else if (Game::Instance()->twoPlayer && !aliveP1) 
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 125, 125, 125, 255);							// Set colour for box outlines grey
	
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &weaponVP1);											// Draw squares around the Player 1 viewports
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &rocketVP1);
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &boostVP1);
	
	if (Game::Instance()->twoPlayer && aliveP2)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0, 255, 0, 255);								// Set Colour for squares around viewports to green
	if (!Game::Instance()->twoPlayer)
		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 125, 125, 125, 255);							// Set draw colour to grey

	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &weaponVP2);											// Draw squares around the Player 2 viewports
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &rocketVP2);
	SDL_RenderDrawRect(Game::Instance()->getRenderer(), &boostVP2);
}

void HUD::getPlayerInfo(bool a1, bool a2, int l1, int l2, int g1, int g2, int r1, int r2, bool sp1, bool sp2, float t1, float t2) {
	aliveP1 = a1;
	aliveP2 = a2;
	livesP1 = l1;
	livesP2 = l2;
	gradeP1 = g1;
	gradeP2 = g2;
	rocketsP1 = r1;
	rocketsP2 = r2;
	speedP1 = sp1;
	speedP2 = sp2;
	timerP1 = t1;
	timerP2 = t2;
}

/*
	2017/03/19 Minimap positions

	Show the player ships position on the map
*/
void HUD::shipPositionOnMap() {
	if (!miniMap) {
		// 10, 350 start coords
		// 180, 260 end of level one coords // start of level 2 
		//gEnemyBossEyesSpriteSheetTexture.render(10, 350, &gEnemyBossEyes[frames / 5]);	// Temp image to show positions
		//gEnemyBossEyesSpriteSheetTexture.render(210, 260, &gEnemyBossEyes[frames / 5]);	// Temp image to show positions
		//gEnemyBossEyesSpriteSheetTexture.render(440, 300, &gEnemyBossEyes[frames / 5]);	// Temp image to show positions
		//gEnemyBossEyesSpriteSheetTexture.render(355, 50, &gEnemyBossEyes[frames / 5]);	// Temp image to show positions

		Texture::Instance()->renderMap("mapShipID", 10, 350, 30, 14);	// Start level 1
		Texture::Instance()->renderMap("mapShipID", 210, 260, 30, 14);	// End level 1 / start level 2
		Texture::Instance()->renderMap("mapShipID", 440, 300, 30, 14);	// End level 2 / Start level 3
		Texture::Instance()->renderMap("mapShipID", 355, 50, 30, 14);	// End game
	}
}

/* 
	Displays the current level of the game

	Fixed memory leak by only updating when the level changes
*/
int previousLevelNum = 100;

void HUD::displayLevelNum(int levelNum) {
	if (previousLevelNum != levelNum)		// Try and only render a new one when it's needed870
		Texture::Instance()->loadFromRenderedTextID("Level " + std::to_string(levelNum), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	previousLevelNum = levelNum;			// 2017/03/19 STOPS MEMORY LEAK

	Texture::Instance()->render("levelID", 10, 8);	// 2017/03/19 Display the level number
}

/*	2017/02/21: Moved from Game.cpp

	Display the score for each player

	Fixed memory leak, by only updating the players scores when they change from previous value
*/
int previousScore1 = 10, previousScore2 = 10;

void HUD::playerScore(bool twoPlayer, int scoreP1, int scoreP2) {
	std::stringstream score1Text, score2Text;
	if (previousScore1 != scoreP1) {
		score1Text << "P1: " << scoreP1;															// Player 1 score
		gP1ScoreTextTexture.free();
		gP1ScoreTextTexture.UIText(score1Text.str().c_str());										// Render text - Use a string to render the current P1 Score to a texture
	}
	previousScore1 = scoreP1;
	gP1ScoreTextTexture.render(10, 55);																// Score for Player 1
	
	if (twoPlayer) {
		if (previousScore2 != scoreP2) {
			score2Text << "P2: " << scoreP2;														// Player 2 score
			gP2ScoreTextTexture.free();
			gP2ScoreTextTexture.UIText(score2Text.str().c_str());									// Render text - Use a string to render the current P2 Score to a texture
		}
		gP2ScoreTextTexture.render(SCREEN_WIDTH - gP2ScoreTextTexture.getWidth() - 10, 55);			// Score for Player 2
	}
	previousScore2 = scoreP2;
}

/*
	Function unused as wasting too much memory rendering text
*/
void HUD::percentageNinjaStarKills(bool twoPlayer, int ninja1, int ninja2) {
	Texture gNinja1, gNinja2;

	std::stringstream ninjaStarKillsP1, ninjaStarKillsP2;

	ninjaStarKillsP1 << "Ninja 1: " << ninja1;														// Player 1 score
	gNinja1.UIText(ninjaStarKillsP1.str().c_str(), 10);									// Render text - Use a string to render the current P1 Score to a texture
	gNinja1.render(10 + 200, 5);															// Score for Player 1
	if (twoPlayer) {
		ninjaStarKillsP2 << "Ninja 2: " << ninja2;													// Player 2 score
		gNinja2.UIText(ninjaStarKillsP2.str().c_str(), 10);								// Render text - Use a string to render the current P2 Score to a texture
		gNinja2.render(SCREEN_WIDTH - gNinja2.getWidth() - 10 - 200, 5);		// Score for Player 2
	}
	gNinja1.free();
	gNinja2.free();
}
/*
	Function unused as wasting too much memory rendering text
*/
void HUD::playerScoresCounter(bool twoPlayer, int scoreP1, int scoreP2) {
	Texture gScoreText1, gScoreText2;

	std::stringstream ninjaStarKillsP1, ninjaStarKillsP2;

	ninjaStarKillsP1 << "Score Text 1: " << scoreP1;										// Player 1 score
	gScoreText1.UIText(ninjaStarKillsP1.str().c_str(), 10);									// Render text - Use a string to render the current P1 Score to a texture
	gScoreText1.render(10 + 200, 15);														// Score for Player 1
	if (twoPlayer) {
		ninjaStarKillsP2 << "Score Text 2: " << scoreP2;									// Player 2 score
		gScoreText2.UIText(ninjaStarKillsP2.str().c_str(), 10);								// Render text - Use a string to render the current P2 Score to a texture
		gScoreText2.render(SCREEN_WIDTH - gScoreText2.getWidth() - 10 - 200, 15);			// Score for Player 2
	}

	gScoreText1.free();
	gScoreText2.free();
}

/*	2017/02/21: Moved from Game.cpp

	Display the speed boost indicator
	Indicates if speed boost is currently active for a player
	and how much time is remaining with a status bar

	Fixed memory leak by rendering the speed boost text only once in the load function
*/
int scroll = 60;

void HUD::speedBoostIndicator(bool boost) {
	if (scroll > 0) scroll--;

	gSpeedBoostTextTexture.modifyAlpha(150);					// Keep alpha values independent
	if (boost) gSpeedBoostTextTexture.modifyAlpha(255);			// Keep alpha values independent

	//gSpeedBoostTextTexture.render((60 - gSpeedBoostTextTexture.getWidth()) / 2, (60 - gSpeedBoostTextTexture.getHeight()) / 2, gRenderer);
	gSpeedBoostTextTexture.render(scroll + 3, 5);
}

/*	2017/02/21: Moved from Game.cpp

	Display the rocket indicator,
	Indicates number of rockets each player has remaining

	Fixed so it only updates when the number of rockets changes as cost of rendering textures is too high
*/
int previousNumRockets1, previousNumRockets2;

void HUD::rocketIndicator(int numRockets, int player, bool alive) {
	gPowerUpRocketTexture.modifyAlpha(255);									// Keep alpha values independent, show bright if alive
	if (numRockets <= 0 || !alive) gPowerUpRocketTexture.modifyAlpha(50);	// Fade out the rocket image if player has no rockets
	gPowerUpRocketTexture.render(scroll + 15, -2, NULL, 45);				// 1st //weaponScrolling = 60;
	//gPowerUpRocketTexture.free();											// Test: Hides the rocket image

	if (player == PLAYER_1) {
		if (previousNumRockets1 != numRockets) {
			//std::cout << "LOAD FROM RENDERED TEXT PLAYER 1 ROCKET" << std::endl;
			gNumRocketsTextTexture1.free();
			gNumRocketsTextTexture1.numRocketsLeft(std::to_string(numRockets));
		}
		previousNumRockets1 = numRockets;
		gNumRocketsTextTexture1.modifyAlpha(150);
		gNumRocketsTextTexture1.render((60 - gNumRocketsTextTexture1.getWidth()) / 2, (60 - gNumRocketsTextTexture1.getHeight()) / 2);
	}
	else if (player == PLAYER_2) {
		if (previousNumRockets2 != numRockets) {
			//std::cout << "LOAD FROM RENDERED TEXT PLAYER 2 ROCKET" << std::endl;
			gNumRocketsTextTexture2.free();
			gNumRocketsTextTexture2.numRocketsLeft(std::to_string(numRockets));
		}
		previousNumRockets2 = numRockets;
		gNumRocketsTextTexture2.modifyAlpha(150);
		gNumRocketsTextTexture2.render((60 - gNumRocketsTextTexture2.getWidth()) / 2, (60 - gNumRocketsTextTexture2.getHeight()) / 2);
	}

	//gPowerUpRocketTexture2.free();
}

/*	
	Display the created by text at bottom of heads up display

	2017/02/21 Moved from Game.cpp
	2017/03/18 Fixed 2 mb/s memory leak by making sure created by text is rendered only in the load function
*/
void HUD::createdByText() {
	//gCreatedByTextTexture.free();
	//gCreatedByTextTexture.createdByText();

	createdByTimer = SDL_GetTicks();										// Get the current game running time
	if (createdByTimer > createdByLastTime + 1500) {						// Decrement countdown timer
		createdByLastTime = createdByTimer;									// Store this time
		changeEverySecond++;												// Decrement the timer
	//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
	}

	/* 2017/03/18 Cut 2 mb/sec memory leak by loading createdByTextTexture text in 3 separate textures only once in the game */
	if (changeEverySecond % 3 == 1) {
		//if (!gCreatedByTextTexture.loadFromRenderedText("ANTIBODY", { 50, 200, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		//	printf("createdByText(): Unable to render Created By Text Texture!\n");
		//}
		gCreatedByTextTexture1.render((SCREEN_WIDTH - gCreatedByTextTexture1.getWidth()) / 2, 120 - gCreatedByTextTexture1.getHeight() - 8);
	}
	else if (changeEverySecond % 3 == 2) {
		//if (!gCreatedByTextTexture.loadFromRenderedText("A GAME BY", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		//	printf("createdByText(): Unable to render Created By Text Texture!\n");
		//}
		//createdByTimer == SDL_GetTicks();
		gCreatedByTextTexture2.render((SCREEN_WIDTH - gCreatedByTextTexture2.getWidth()) / 2, 120 - gCreatedByTextTexture2.getHeight() - 8);
	}
	else if (changeEverySecond % 3 == 0) {
		//if (!gCreatedByTextTexture.loadFromRenderedText("JOE O'REGAN, SEAN HORGAN, BRIAN RYAN", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {				// Green Text
		//	printf("createdByText(): Unable to render Created By Text Texture!\n");
		//}
		gCreatedByTextTexture3.render((SCREEN_WIDTH - gCreatedByTextTexture3.getWidth()) / 2, 120 - gCreatedByTextTexture3.getHeight() - 8);
		changeEverySecond = 0;	// Reset timer
	}

		//gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, 120 - gCreatedByTextTexture.getHeight() - 8);
}	

/*	2017/02/21: Moved from Game.cpp

	Render the players lives to the player dashboard
*/
void HUD::rendPlayerLives(int livesP1, int livesP2) {
	if (livesP1 > 0)
		gP1LivesTexture.render(10, 120 - gP1LivesTexture.getHeight() - 10);
	if (livesP1 > 1)
		gP1LivesTexture.render(20 + gP1LivesTexture.getWidth(), 120 - gP1LivesTexture.getHeight() - 10);
	if (livesP1 > 2)
		gP1LivesTexture.render(30 + (gP1LivesTexture.getWidth() * 2), 120 - gP1LivesTexture.getHeight() - 10);

	if (livesP2 > 0)
		gP2LivesTexture.render(SCREEN_WIDTH - gP2LivesTexture.getWidth() - 10, 120 - gP2LivesTexture.getHeight() - 10);
	if (livesP2 > 1)
		gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 2) - 20, 120 - gP2LivesTexture.getHeight() - 10);
	if (livesP2 > 2)
		gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 3) - 30, 120 - gP2LivesTexture.getHeight() - 10);

	//Texture::Instance()->render("levelID", 10, 8);	// Display the level number NEEDS TO BE IN DIFFERENT VIEW PORT
}


/*
std::stringstream timeText;

void HUD::gameTime(int currentTime, SDL_Renderer *rend) {
//timeText.str("");																	// Set text to be rendered - string stream - print the time since timer last started - initialise empty

//timeText << "Time: " << currentTime;												// Set the game timer

//gTimeTextTexture.flashGameObject(8);

//gTimeTextTexture.UITextTimer("test", rend, currentTime);
gTimeTextTexture.UIText("test", rend);

//gTimeTextTexture.UITextTimer(timeText.str().c_str(), rend, currentTime);			// Render Text - Use a string to render the current Game Time to a Texture

//gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());						// Flash the timer
gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8, rend);	// LAZY
}
*/

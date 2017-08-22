#include "HUD.h"
#include <sstream>


bool HUD::loadLevelStuff(SDL_Renderer *rend) {
	bool success = true;

	if (!gP1LivesTexture.loadFromFile("Art/Player1ShipSmall.png", rend)) {				// Player 1 Lives Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
//	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmall.png", rend)) {				// Player 2 Lives Texture
	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmallOld.png", rend)) {				// Player 2 Lives Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	}
	if (!gPowerUpRocketTexture2.loadFromFile("Art/PowerUpRocket.png", rend)) {			// Rocket Power Up Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}

	return success;
}

void HUD::resetHUD() {
	//gTimeTextTexture.setFlash(false);		// Reset the timer flash
}

void HUD::closeLevelStuff() {
	gLevelTextTexture.free();

	//gTimeTextTexture.free();
	gCreatedByTextTexture.free();

	gP1LivesTexture.free();
	gP2LivesTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();

	gSpeedBoostTextTexture.free();

	gPowerUpRocketTexture2.free();
	gNumRocketsTextTexture1.free();
	//gNumRocketsTextTexture2.free();
}

void HUD::displayLevelNum(int levelNum, SDL_Renderer *rend) {
	gLevelTextTexture.UIText("Level " + std::to_string(levelNum), rend);	// Render text - Use a string to render the current Level to a texture
	gLevelTextTexture.render(10, 8, rend);
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

	//gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());							// Flash the timer
	gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8, rend);	// LAZY
}
*/
/*	2017/02/21: Moved from Game.cpp

	Display the score for each player
*/
void HUD::playerScore(SDL_Renderer *rend, bool twoPlayer, int scoreP1, int scoreP2) {
	std::stringstream score1Text, score2Text;

	score1Text << "P1: " << scoreP1;															// Player 1 score
	gP1ScoreTextTexture.UIText(score1Text.str().c_str(), rend);									// Render text - Use a string to render the current P1 Score to a texture
	gP1ScoreTextTexture.render(10, 55, rend);													// Score for Player 1
	if (twoPlayer) {
		score2Text << "P2: " << scoreP2;															// Player 2 score
		gP2ScoreTextTexture.UIText(score2Text.str().c_str(), rend);									// Render text - Use a string to render the current P2 Score to a texture
		gP2ScoreTextTexture.render(SCREEN_WIDTH - gP2ScoreTextTexture.getWidth() - 10, 55, rend);	// Score for Player 2
	}
}

/*	2017/02/21: Moved from Game.cpp

	Display the speed boost indicator
	Indicates if speed boost is currently active for a player
	and how much time is remaining
*/

int scroll = 60;

void HUD::speedBoostIndicator(bool boost, SDL_Renderer *rend) {
	if (scroll > 0) scroll--;

	gSpeedBoostTextTexture.speedBoostText("Speed\nBoost", rend);// Create the text

	gSpeedBoostTextTexture.modifyAlpha(150);					// Keep alpha values independent
	if (boost) gSpeedBoostTextTexture.modifyAlpha(255);			// Keep alpha values independent

	//gSpeedBoostTextTexture.render((60 - gSpeedBoostTextTexture.getWidth()) / 2, (60 - gSpeedBoostTextTexture.getHeight()) / 2, gRenderer);
	gSpeedBoostTextTexture.render(scroll + 3, 5, rend);
}

/*	2017/02/21: Moved from Game.cpp

	Display the rocket indicator,
	Indicates number of rockets each player has remaining
*/
void HUD::rocketIndicator(int numRockets, int player, bool alive, SDL_Renderer *rend) {
	gPowerUpRocketTexture2.modifyAlpha(255);								// Keep alpha values independent, show bright if alive
	if (numRockets <= 0 || !alive) gPowerUpRocketTexture2.modifyAlpha(50);	// Fade out the rocket image if player has no rockets
	gPowerUpRocketTexture2.render(scroll + 15, -2, rend, NULL, 45);			// 1st //weaponScrolling = 60;

	gNumRocketsTextTexture1.numRocketsLeft(std::to_string(numRockets), rend);
	gNumRocketsTextTexture1.modifyAlpha(150);
	gNumRocketsTextTexture1.render((60 - gNumRocketsTextTexture1.getWidth()) / 2, (60 - gNumRocketsTextTexture1.getHeight()) / 2, rend);
}

/*	2017/02/21: Moved from Game.cpp

	Display the created by text at bottom of heads up display
*/
void HUD::createdByText(SDL_Renderer *rend) {
	gCreatedByTextTexture.createdByText(rend);
	gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, 120 - gCreatedByTextTexture.getHeight() - 8, rend);
}

/*	2017/02/21: Moved from Game.cpp

	Render the players lives to the player dashboard
*/
void HUD::rendPlayerLives(SDL_Renderer *rend, int livesP1, int livesP2) {
		if (livesP1 > 0)
			gP1LivesTexture.render(10, 120 - gP1LivesTexture.getHeight() - 10, rend);
		if (livesP1 > 1)
			gP1LivesTexture.render(20 + gP1LivesTexture.getWidth(), 120 - gP1LivesTexture.getHeight() - 10, rend);
		if (livesP1 > 2)
			gP1LivesTexture.render(30 + (gP1LivesTexture.getWidth() * 2), 120 - gP1LivesTexture.getHeight() - 10, rend);

		if (livesP2 > 0)
			gP2LivesTexture.render(SCREEN_WIDTH - gP2LivesTexture.getWidth() - 10, 120 - gP2LivesTexture.getHeight() - 10, rend);
		if (livesP2 > 1)
			gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 2) - 20, 120 - gP2LivesTexture.getHeight() - 10, rend);
		if (livesP2 > 2)
			gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 3) - 30, 120 - gP2LivesTexture.getHeight() - 10, rend);
}

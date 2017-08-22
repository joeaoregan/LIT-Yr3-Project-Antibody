/*
	2017/02/21 All indicators now scroll left to right on start up
	2017/02/21 Moved player lives, scores, speed boost indicator, rocket indicator, and created by text to head up display
	2017/02/19 Added rocket icon to viewoport displaying information on the number of rockets in the players inventory
*/
/*
	HEADS UP DISPLAY (HUD):

	This class contains all the information relavent to the player dashboard, including lives, scores, and weapon indicators
	for each player. Weapon indicators include, current laser grade, number of rockets, and an indicator for when the player
	speed boost is active, displaying a status bar for when the boost timer runs out.

	The game map is also displayed here in mini form, which can be resized by pressing a button on the keyboard or gamepad.
	There is also an animated game creator text on the bottom of the display.
*/
#include "HUD.h"
#include <sstream>


bool HUD::loadLevelStuff() {
	bool success = true;

	if (!gP1LivesTexture.loadFromFile("Art/Player1ShipSmall.png")) {				// Player 1 Lives Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
//	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmall.png")) {				// Player 2 Lives Texture
	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmallOld.png")) {				// Player 2 Lives Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	}
	if (!gPowerUpRocketTexture2.loadFromFile("Art/PowerUpRocket.png")) {			// Rocket Power Up Texture
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
	gSpeedBoostTextTexture.free();
	gPowerUpRocketTexture2.free();
	gNumRocketsTextTexture1.free();
	gCreatedByTextTexture.free();
	gP1LivesTexture.free();
	gP2LivesTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();
	//gTimeTextTexture.free();
	//gNumRocketsTextTexture2.free();
}

void HUD::displayLevelNum(int levelNum) {
	gLevelTextTexture.UIText("Level " + std::to_string(levelNum));	// Render text - Use a string to render the current Level to a texture
	gLevelTextTexture.render(10, 8);
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
/*	2017/02/21: Moved from Game.cpp

	Display the score for each player
*/
void HUD::playerScore(bool twoPlayer, int scoreP1, int scoreP2) {
	std::stringstream score1Text, score2Text;
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();

	score1Text << "P1: " << scoreP1;															// Player 1 score
	gP1ScoreTextTexture.UIText(score1Text.str().c_str());										// Render text - Use a string to render the current P1 Score to a texture
	gP1ScoreTextTexture.render(10, 55);															// Score for Player 1
	if (twoPlayer) {
		score2Text << "P2: " << scoreP2;														// Player 2 score
		gP2ScoreTextTexture.UIText(score2Text.str().c_str());									// Render text - Use a string to render the current P2 Score to a texture
		gP2ScoreTextTexture.render(SCREEN_WIDTH - gP2ScoreTextTexture.getWidth() - 10, 55);		// Score for Player 2
	}
}

void HUD::percentageNinjaStarKills(bool twoPlayer, int ninja1, int ninja2) {
	Texture gNinja1, gNinja2;
	gNinja1.free();
	gNinja2.free();

	std::stringstream ninjaStarKillsP1, ninjaStarKillsP2;

	ninjaStarKillsP1 << "Ninja 1: " << ninja1;														// Player 1 score
	gNinja1.UIText(ninjaStarKillsP1.str().c_str(), 10);									// Render text - Use a string to render the current P1 Score to a texture
	gNinja1.render(10 + 200, 5);															// Score for Player 1
	if (twoPlayer) {
		ninjaStarKillsP2 << "Ninja 2: " << ninja2;													// Player 2 score
		gNinja2.UIText(ninjaStarKillsP2.str().c_str(), 10);								// Render text - Use a string to render the current P2 Score to a texture
		gNinja2.render(SCREEN_WIDTH - gNinja2.getWidth() - 10 - 200, 5);		// Score for Player 2
	}
}

void HUD::playerScoresCounter(bool twoPlayer, int scoreP1, int scoreP2) {
	Texture gScoreText1, gScoreText2;

	std::stringstream ninjaStarKillsP1, ninjaStarKillsP2;

	ninjaStarKillsP1 << "Score Text 1: " << scoreP1;														// Player 1 score
	gScoreText1.UIText(ninjaStarKillsP1.str().c_str(), 10);									// Render text - Use a string to render the current P1 Score to a texture
	gScoreText1.render(10 + 200, 15);															// Score for Player 1
	if (twoPlayer) {
		ninjaStarKillsP2 << "Score Text 2: " << scoreP2;													// Player 2 score
		gScoreText2.UIText(ninjaStarKillsP2.str().c_str(), 10);								// Render text - Use a string to render the current P2 Score to a texture
		gScoreText2.render(SCREEN_WIDTH - gScoreText2.getWidth() - 10 - 200, 15);		// Score for Player 2
	}

	gScoreText1.free();
	gScoreText2.free();
}

/*	2017/02/21: Moved from Game.cpp

	Display the speed boost indicator
	Indicates if speed boost is currently active for a player
	and how much time is remaining
*/

int scroll = 60;

void HUD::speedBoostIndicator(bool boost) {
	if (scroll > 0) scroll--;
	gSpeedBoostTextTexture.free();

	gSpeedBoostTextTexture.speedBoostText("Speed\nBoost");// Create the text

	gSpeedBoostTextTexture.modifyAlpha(150);					// Keep alpha values independent
	if (boost) gSpeedBoostTextTexture.modifyAlpha(255);			// Keep alpha values independent

	//gSpeedBoostTextTexture.render((60 - gSpeedBoostTextTexture.getWidth()) / 2, (60 - gSpeedBoostTextTexture.getHeight()) / 2, gRenderer);
	gSpeedBoostTextTexture.render(scroll + 3, 5);
}

/*	2017/02/21: Moved from Game.cpp

	Display the rocket indicator,
	Indicates number of rockets each player has remaining
*/
void HUD::rocketIndicator(int numRockets, int player, bool alive) {
	gPowerUpRocketTexture2.free();
	gPowerUpRocketTexture2.modifyAlpha(255);								// Keep alpha values independent, show bright if alive
	if (numRockets <= 0 || !alive) gPowerUpRocketTexture2.modifyAlpha(50);	// Fade out the rocket image if player has no rockets
	gPowerUpRocketTexture2.render(scroll + 15, -2, NULL, 45);			// 1st //weaponScrolling = 60;

	gNumRocketsTextTexture1.numRocketsLeft(std::to_string(numRockets));
	gNumRocketsTextTexture1.modifyAlpha(150);
	gNumRocketsTextTexture1.render((60 - gNumRocketsTextTexture1.getWidth()) / 2, (60 - gNumRocketsTextTexture1.getHeight()) / 2);
}

/*	2017/02/21: Moved from Game.cpp

	Display the created by text at bottom of heads up display
*/
void HUD::createdByText() {
	gCreatedByTextTexture.free();
	gCreatedByTextTexture.createdByText();
	gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, 120 - gCreatedByTextTexture.getHeight() - 8);
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

}

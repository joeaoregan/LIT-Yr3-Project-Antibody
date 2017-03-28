/*----------------------------------------------------------------------------------------------------------------------------
	- Name:					HighScores.cpp

	- Description:			Contains functions for reading the data in the highscore.txt file and rendering this data back to the highscore window.
							Function for loading all the media needed to render the window
							Function for drawing all of the rendered images/text to the window
	- Log:
		2017/03/08			Added HighScores menu class
------------------------------------------------------------------------------------------------------------------------------*/

#include "HighScores.h"
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Texture.h"

Texture scoreTextTexture;
std::string line;
void readScoresFromTextFile();
void outputScoresToConsole();

bool HighScores::loadHighScoresMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gScoresMenuTextTexture1.loadFromRenderedText("HIGH SCORES", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render High Scores text texture!\n");
			success = false;
		}
		if (!gScoresMenuTextTexture2.loadFromRenderedText("Main Menu", textColour, gFont)) {
			printf("Failed to render Main Menu text texture!\n");
			success = false;
		}
		// Backgrounds
		if (!Texture::Instance()->load("Art/PlayerShipOutline.png", "shipOutlineID")) {				// 2017/03/07 Ship Outline Texture
			printf("Failed to load Ship Outline background texture!\n");							// Start Backround
			success = false;
		}

		gScoresMenuTextTexture2.setX((SCREEN_WIDTH - gScoresMenuTextTexture2.getWidth()) / 2);
		//gScoresMenuTextTexture2.setY(200);
		gScoresMenuTextTexture2.setY(SCREEN_HEIGHT - 200);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture3.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < 1; ++i) {
			gSpriteClipsScoresMenu[i].x = 0;
			gSpriteClipsScoresMenu[i].y = i * 200;
			gSpriteClipsScoresMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsScoresMenu[i].h = BUTTON_HEIGHT;
		}

		//gReturnToMenu.setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gScoresMenuTextTexture2.getY());
		//gReturnToMenu.setPosition(gScoresMenuTextTexture2.getX(), gScoresMenuTextTexture2.getY());
		gScoressMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gScoresMenuTextTexture2.getY());
	}

	readScoresFromTextFile();			// 2017/03/21 Read in the scores stored in external text file

	return success;
}

void readScoresFromTextFile() {
	std::string playerName;
	std::stringstream highScores;

	std::ifstream infile;				// file to read in
	infile.open("highscore.txt");		// Name of the file

	//std::cout << "Reading high scores from file" << std::endl;

	// Structure of names and scores
	struct PlayerScores {
		std::string name;
		int score;
	};

	PlayerScores tempScoreDetailsStructForSorting;	// Temp name and score for sorting scores read in

	const int maxNumScores = 10;					// the max amount of scores to read in

	PlayerScores scoreTable[11];					// structures of names and scores

	int everyScoreReadInIterator = 0;				// Iterator to read in each score

	// Read in scores
	if (infile.is_open()) {
		//for (int i = 0; i < 10; i++){
		while (getline(infile, scoreTable[everyScoreReadInIterator].name) && getline(infile, playerName) && everyScoreReadInIterator <= maxNumScores) {
			//getline(infile, player);

			scoreTable[everyScoreReadInIterator].score = stoi(playerName);
			++everyScoreReadInIterator;
		}

		infile.close();								// Close the file after reading
	}

	// Sort the scores
	for (int i = 1; i < everyScoreReadInIterator; i++) {
		for (int j = 0; j < everyScoreReadInIterator - i; j++) {
			if (scoreTable[j].score < scoreTable[j + 1].score) { // Sort Largest Score To Smallest in the struct
				tempScoreDetailsStructForSorting = scoreTable[j];
				scoreTable[j] = scoreTable[j + 1];
				scoreTable[j + 1] = tempScoreDetailsStructForSorting;
			}
		}
	}

	// Format the string for output to screen
	for (int i = 0; i < everyScoreReadInIterator; i++) {
		highScores << std::setw(3) << std::to_string(i + 1) << ". " << std::left << std::setw(14) << std::setfill('.') << scoreTable[i].name << std::right << std::setw(8) << std::to_string(scoreTable[i].score) << std::setfill(' ') << "\n";
	}

	// If there is no scores, output no scores message
	if (everyScoreReadInIterator <= 0) highScores << "No scores!";

	// Output the scores and names as 1 wrapped text string
	scoreTextTexture.loadFromRenderedText(highScores.str().c_str(), { 50, 50, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);
	//scoreText.loadFromRenderedText("test", { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);
}

void HighScores::handleHighScoresEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < 1; ++i) {
		gScoressMenuButtons[i].handleEvent(&e, i);
	}

	//gReturnToMenu.handleEvent(&e, 0);
}

/*
	Clear the media associated with the high scores table
*/
void HighScores::closeHighScoresMedia() {
	// Buttons
	gButtonSpriteSheetTexture3.free(); // Sprite for button animation clear

	// Menu text
	gScoresMenuTextTexture1.free();		// High Scores menu heading clear
	gScoresMenuTextTexture2.free();		// Return to main menu Button text clear
	scoreTextTexture.free();			// Clear the high scores texture
}

/*
	Display a heading for the High Scores Menu
	Followed by the high scores read in from a text file
	A button takes the user back to the main menu or pressing "Esc"
*/
void HighScores::draw() {
	outputScoresToConsole(); // 2017/03/21 Read scores form text file and output to console

	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 30, 240, 175, 255);		// Green
	SDL_RenderClear(Game::Instance()->getRenderer());								// Clear the screen filling it with the Render Draw Colour

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);	// Lower the alpha value of the ship outline image
	Texture::Instance()->renderMap("shipOutlineID", 0, 40, SCREEN_WIDTH, 620);		// Draw ship outline image to screen

	// Draw 1 button
	//gReturnToMenu.render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gReturnToMenu.mCurrentSprite]);
	
	for (int i = 0; i < 1; i++) {
		gScoressMenuButtons[i].render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gScoressMenuButtons[i].mCurrentSprite]);						// Render the buttons in the array
	}
	
	gScoresMenuTextTexture1.render((SCREEN_WIDTH - gScoresMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gScoresMenuTextTexture1.getHeight()) / 12);// High Scores Heading
	gScoresMenuTextTexture2.render(gScoresMenuTextTexture2.getX(), gScoresMenuTextTexture2.getY());														// Return to menu from scores
	
	scoreTextTexture.render((SCREEN_WIDTH - scoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - scoreTextTexture.getHeight()) / 2.5);											// Display the score read in from a text file

	SDL_RenderPresent(Game::Instance()->getRenderer());																									// Update screen
}

/*
	2017/03/21 This function reads in the scores from a text file, highscore.txt
	and outputs them to the console window
*/
void outputScoresToConsole() {
	std::ifstream a_file("highscore.txt");		// Open the highscore text file

	if (a_file.is_open()) {						// If the file is open
		while (getline(a_file, line)) {			// Read each line of the file
			std::cout << line << std::endl;		// Output each line to the console
		}

		a_file.close();							// Close the file
	}
	else {										// Error message
		std::cout << "Error: Unable to open high scores file" << std::endl;
	}
}

/*
	2017/03/08 Added Settings Menu class
*/
/*
	SETTINGS MENU:

	This function handles the objects for the settings menu. The separate button class
	handles the transitions.
*/

#include "HighScores.h"
#include <SDL_ttf.h>
#include <iostream>

#include <sstream>
#include <fstream>

#include <string>

#include <iomanip>
#include "Texture.h"

Texture dumbassScoresTextTexture;	//2017/03/21
Texture assClown;
std::string line;

using namespace std;

string TOTAL_DATA; //string to store input from file

/* 2017/03/21 Joe */

string readScoresFromTextFile() //function to read from file and store values in return string
{
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

	// Think this sorts the scores

	//for (int i = 1; i < eachScore + 1; i++) {
	//	for (int j = 0; j < eachScore + 1 - i; j++) {
	for (int i = 1; i < everyScoreReadInIterator; i++) {
		for (int j = 0; j < everyScoreReadInIterator - i; j++) {
			//if (strcmp(scoreTable[j].plname, scoreTable[j + 1].plname) > 0)
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

	//bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
	//Texture::Instance()->loadFromRenderedText(highScore, highScores.str().c_str(), "highScoresID", { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), Game::Instance()->getRenderer, true);
	dumbassScoresTextTexture.loadFromRenderedText(highScores.str().c_str(), { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);

	assClown.loadFromRenderedText("You have to call the actual function for it to work you fuckin idiot!!!\n\nYour function probably worked fine", { 0, 0, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);

	//scores.loadFromRenderedText("fuckface", { 100, 100, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);
	/*

	ifstream b_file("highscore.txt");

	if (b_file.is_open())
	{
			while (getline(b_file, TOTAL_DATA))
			{
				b_file >> TOTAL_DATA;
				cout << TOTAL_DATA << endl;
			}
			b_file.close();
	}
	else cout << "Unable to open file";
	*/

	return TOTAL_DATA;
}

bool HighScores::loadHighScoresMedia()	 {
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

		//if statement which loads function readfile() to render high scores
		//if (!gScoresMenuTextTexture3.loadFromRenderedText(readFile(), textColour, TTF_OpenFont("Fonts/Retro.ttf", 20), true)) {
		if (!gScoresMenuTextTexture3.loadFromRenderedText("shitbag!", textColour, TTF_OpenFont("Fonts/Retro.ttf", 20), true)) {
					printf("What the fuck is this shit numbnuts!\n");
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

	return success;
}

void HighScores::handleHighScoresEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < 1; ++i) {
		gScoressMenuButtons[i].handleEvent(&e, i);
	}

	//gReturnToMenu.handleEvent(&e, 0);
}

void HighScores::closeHighScoresMedia() {
	// Buttons
	gButtonSpriteSheetTexture3.free();

	// Menu
	gScoresMenuTextTexture1.free();
	gScoresMenuTextTexture2.free();
	gScoresMenuTextTexture3.free();
}

void HighScores::draw() {





	ifstream a_file("highscore.txt");

	if (a_file.is_open())
	{
		while (getline(a_file, line))
		{
			cout << "fuck off brian" << endl;
			cout << line << '\n';
		}
		a_file.close();
	}
	else cout << "Unable to open file";



	readScoresFromTextFile();














	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 30, 240, 175, 255);		// Green
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_SetTextureAlphaMod(Texture::Instance()->getTexture("shipOutlineID"), 100);	// Lower the alpha value of the ship outline image
	Texture::Instance()->renderMap("shipOutlineID", 0, 40, SCREEN_WIDTH, 620);		// Draw ship outline image to screen

	// Draw 1 button
	//gReturnToMenu.render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gReturnToMenu.mCurrentSprite]);
	
	for (int i = 0; i < 1; i++) {
		gScoressMenuButtons[i].render(gButtonSpriteSheetTexture3, &gSpriteClipsScoresMenu[gScoressMenuButtons[i].mCurrentSprite]);
	}
	
	gScoresMenuTextTexture1.render((SCREEN_WIDTH - gScoresMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gScoresMenuTextTexture1.getHeight()) / 12);	// High Scores Heading
	gScoresMenuTextTexture2.render(gScoresMenuTextTexture2.getX(), gScoresMenuTextTexture2.getY());	// Return to menu from scores
	//gScoresMenuTextTexture3.render((SCREEN_WIDTH - gScoresMenuTextTexture3.getWidth()) / 2, (SCREEN_HEIGHT - gScoresMenuTextTexture3.getHeight()) / 2.5);
	
	dumbassScoresTextTexture.render((SCREEN_WIDTH - gScoresMenuTextTexture3.getWidth()) / 2, (SCREEN_HEIGHT - gScoresMenuTextTexture3.getHeight()) / 2.5);
	assClown.render(100, 400);

	SDL_RenderPresent(Game::Instance()->getRenderer());			// Update screen
}

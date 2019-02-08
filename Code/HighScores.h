/*----------------------------------------------------------------------------------------------------------------------------
	- Name:					HighScores.h

	- Description:			Contains functions for reading the data in the highscore.txt file and rendering this data back to the highscore window.
							Function for loading all the media needed to render the window
							Function for drawing all of the rendered images/text to the window
	- Log:
		2017/03/08			Added HighScores menu class
------------------------------------------------------------------------------------------------------------------------------*/

#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include "Button.h"
#include "Texture.h"

class HighScores {
public:
	TTF_Font *gFont = NULL;							// The font to be used to render High Scores menu text

	// Menu Text
	Texture gScoresMenuTextTexture1;				// Title for HighScores menu
	Texture gScoresMenuTextTexture2;				// Button text

	//Buttons objects
	Button gReturnToMenu;							// Button to return to the main menu

	Button gScoresMenuButtons[1];					// Array of buttons
	SDL_Rect gSpriteClipsScoresMenu[1];				// The current frame of button animation
	Texture gButtonSpriteSheetTexture3;				// Button animation sprite sheet

	bool loadHighScoresMedia();						// Load high scores media including button sprites, and rendering text to textures
	void closeHighScoresMedia();					// Free the High Scores media from memory
	void handleHighScoresEvents(SDL_Event& e);		// Handle events for each button
	void draw();									// Render the buttons and text textures
};

#endif
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
	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gScoresMenuTextTexture1;
	Texture gScoresMenuTextTexture2;

	//Buttons objects
	Button gReturnToMenu;

	Button gScoressMenuButtons[1];
	SDL_Rect gSpriteClipsScoresMenu[1];
	Texture gButtonSpriteSheetTexture3;

	bool loadHighScoresMedia();
	void closeHighScoresMedia();
	void handleHighScoresEvents(SDL_Event& e);
	void draw();
};

#endif
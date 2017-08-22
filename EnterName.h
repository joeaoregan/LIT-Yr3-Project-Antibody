/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnterName.h
	- Description:			Header file for the name entering system
	- Information:			The enter name state is where the player will enter their name before beginning level 1,
							This name will be used to store the name along with the score of the player in the High Scores
							table, if the player achieves a high enough score. A separate state is needed as entering text
							from the keyboard will interfere with the keyboard controls for the player playing the game.
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef ENTER_NAME_H
#define ENTER_NAME_H

#include "Button.h"
#include "Texture.h"

class EnterName {
public:
	TTF_Font *gFont = NULL;									// Set the font for the states text

	// Menu Text
	Texture gNameMenuTextTexture1;							// Enter Name title text
	Texture gNameMenuTextTexture2;							// Return to Menu text
	Texture gNameMenuTextTexture3;							// Reset the text entered
	Texture gNameMenuTextTexture4;							// Enter Name prompt text

	//Buttons objects
	Button gNameButtons[TOTAL_ENTER_NAME_BUTTONS];			// Array of buttons

	SDL_Rect gSpriteClipsName[TOTAL_ENTER_NAME_BUTTONS];	// Sprite for button animation
	Texture gButtonSpriteSheetTexture4;						// Sprite animation texture

	bool loadNameMedia();									// Load the media for Enter Name state
	void closeNameMedia();									// Free the media for Enter Name state from memory
	void handleNameEvents(SDL_Event& e);					// Handle events for Enter Name state
	void draw();											// Render the enter name state
};

#endif
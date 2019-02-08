/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnterName.cpp
	- Description:			cpp file for the name entering system. MAYBE MORE INFO HERE
	- Information:			FILL IN INFO HERE
	- Log:
		2017/02/14 Added menu handling class
		2017/01/24 Added Menu to main code
		2017/01/19 Started to add game main menu
		Added working menu buttons
	----------------------------------------------------------------------------------------------------------------------*/
/*
NAME ENTERING MENU:

This function handles the objects for the game menu. The separate button class
handles the transitions.
*/

#include "EnterName.h"
#include <SDL_ttf.h>

SDL_Event event;

bool EnterName::loadNameMedia() {
	bool success = true;

	gFont = TTF_OpenFont("Fonts/Retro.ttf", 16);	// Open the font
	if (gFont == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColour = { 0,0,0 };

		if (!gNameMenuTextTexture1.loadFromRenderedText("Enter Name", textColour, TTF_OpenFont("Fonts/Retro.ttf", 100))) {
			printf("Failed to render Enter Name Title text texture!\n");
			success = false;
		}
		if (!gNameMenuTextTexture2.loadFromRenderedText("Menu", textColour, gFont)) {	// can take out the new textColor objects
			printf("Failed to render Entername to Menu text texture!\n");
			success = false;
		}
		if (!gNameMenuTextTexture3.loadFromRenderedText("Reset", textColour, gFont)) {
			printf("Failed to render Reset Button text texture!\n");
			success = false;
		}
		if (!gNameMenuTextTexture4.loadFromRenderedText("Please Enter Your Name: ", textColour, gFont)) {
			printf("Failed to render Enter Name text texture!\n");
			success = false;
		}

		gNameMenuTextTexture2.setX((SCREEN_WIDTH - gNameMenuTextTexture2.getWidth()) / 2);
		gNameMenuTextTexture3.setX((SCREEN_WIDTH - gNameMenuTextTexture3.getWidth()) / 2);

		gNameMenuTextTexture2.setY(200);
		gNameMenuTextTexture3.setY(250);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture4.loadFromFile("Art/buttonOne.png")) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < TOTAL_ENTER_NAME_BUTTONS; ++i) {
			gSpriteClipsName[i].x = 0;
			gSpriteClipsName[i].y = i * 200;
			gSpriteClipsName[i].w = BUTTON_WIDTH;
			gSpriteClipsName[i].h = BUTTON_HEIGHT;
		}

		gNameButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gNameMenuTextTexture2.getY());
		gNameButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gNameMenuTextTexture3.getY());
	}


	//Texture::Instance()->loadEnterNameText("Please Enter Your Name:");

	return success;
}


bool renderText;
std::string inputText = "Name";

void EnterName::handleNameEvents(SDL_Event& e) {
	// Handle button events
	for (int i = 0; i < TOTAL_ENTER_NAME_BUTTONS; ++i) {
		gNameButtons[i].handleEvent(&e, i);
	}



}

void EnterName::closeNameMedia() {
	// Buttons
	gButtonSpriteSheetTexture4.free();

	// Menu
	gNameMenuTextTexture1.free();
	gNameMenuTextTexture2.free();
	gNameMenuTextTexture3.free();
}

void EnterName::draw() {
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 117, 10, 10, 255);
	SDL_RenderClear(Game::Instance()->getRenderer());

	for (int i = 0; i < TOTAL_ENTER_NAME_BUTTONS; ++i) {
		gNameButtons[i].render(gButtonSpriteSheetTexture4, &gSpriteClipsName[gNameButtons[i].mCurrentSprite]);
	}

	gNameMenuTextTexture1.render((SCREEN_WIDTH - gNameMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gNameMenuTextTexture1.getHeight()) / 12);
	gNameMenuTextTexture2.render(gNameMenuTextTexture2.getX(), gNameMenuTextTexture2.getY());	// RETURN TO MAIN MENU
	gNameMenuTextTexture3.render(gNameMenuTextTexture3.getX(), gNameMenuTextTexture3.getY());	// RESET
	gNameMenuTextTexture4.render(50, 300);	// RESET

	//Texture::Instance()->loadInputText(inputText);
	//Texture::Instance()->renderMap("inputTextID", 50, 150, 100, 100);

	SDL_RenderPresent(Game::Instance()->getRenderer());											// Update screen


	/*

	//bool Game::enterName() {
	//bool Game::enterName() {

	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x00, 0x00, 0x00, 0xFF);	// Clear background
	Texture::Instance()->draw("enterNameID", 50, 100, 400, 20);		// Display enter name message
	Texture::Instance()->loadInputText(inputText);
	//Texture::Instance()->drawText("inputTextID", 50, 150);
	Texture::Instance()->renderMap("inputTextID", 50, 150, 100, 100);

	renderText = false;		// flag that keeps track of whether we need to update the texture

	while (SDL_PollEvent(&event) != 0) {
		//User requests quit
		//if (e.type == SDL_QUIT) {
		//	quit = true;
		//}
		//Special key input
		//else 
		if (event.type == SDL_KEYDOWN) {
			//Handle backspace
			if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {	// backspace -> remove the last character from the string
																				//lop off character
				inputText.pop_back();
				renderText = true;		// Set the text update flag
			}
			//Handle copy
			else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + c -> copy the text to the clip board
				SDL_SetClipboardText(inputText.c_str());
			}
			//Handle paste
			else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + v -> get the text from the clipboard
				inputText = SDL_GetClipboardText();
				renderText = true;		// Set the text update flag
			}
			else if (event.key.keysym.sym == SDLK_RETURN) {

				
				//Game::Instance()->player1->setName(inputText);

				
				//Game::Instance()->setName(inputText);
				Game::Instance()->nameEntered = true;
			}
		}
		//Special text input event
		else if (event.type == SDL_TEXTINPUT) {
			//Not copy or pasting
			if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
				//Append character
				inputText += event.text.text;
				renderText = true;
			}
		}
	}


	//Rerender text if needed
	if (renderText) {
		//Text is not empty
		if (inputText != "") {
			Texture::Instance()->loadInputText(inputText);
		}
		//Text is empty
		else {
			Texture::Instance()->loadInputText(" ");
		}
	}
	*/
	//	return nameEntered;
	//}
}




/*
bool renderText;
std::string inputText = "Name";

//bool Game::enterName() {
bool Game::enterName() {
SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);	// Clear background
Texture::Instance()->draw("enterNameID", 50, 100, 400, 20);		// Display enter name message
Texture::Instance()->loadInputText(inputText);
//Texture::Instance()->drawText("inputTextID", 50, 150);
Texture::Instance()->renderMap("inputTextID", 50, 150, 100, 100);

renderText = false;		// flag that keeps track of whether we need to update the texture

while (SDL_PollEvent(&e) != 0) {
//User requests quit
if (e.type == SDL_QUIT) {
quit = true;
}
//Special key input
else if (e.type == SDL_KEYDOWN) {
//Handle backspace
if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {	// backspace -> remove the last character from the string
//lop off character
inputText.pop_back();
renderText = true;		// Set the text update flag
}
//Handle copy
else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + c -> copy the text to the clip board
SDL_SetClipboardText(inputText.c_str());
}
//Handle paste
else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + v -> get the text from the clipboard
inputText = SDL_GetClipboardText();
renderText = true;		// Set the text update flag
}
else if (e.key.keysym.sym == SDLK_RETURN) {
player1->setName(inputText);
//Game::Instance()->setName(inputText);
nameEntered = true;
}
}
//Special text input event
else if (e.type == SDL_TEXTINPUT) {
//Not copy or pasting
if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
//Append character
inputText += e.text.text;
renderText = true;
}
}
}


//Rerender text if needed
if (renderText) {
//Text is not empty
if (inputText != "") {
Texture::Instance()->loadInputText(inputText);
}
//Text is empty
else {
Texture::Instance()->loadInputText(" ");
}
}

return nameEntered;
}
*/
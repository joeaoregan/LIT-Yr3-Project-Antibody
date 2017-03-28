#ifndef LBUTTON_H
#define LBUTTON_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"

//Button constants
const int BUTTON_WIDTH = 160;
const int BUTTON_WIDTH_SETTINGS = 250;
const int BUTTON_HEIGHT = 40;
const int TOTAL_MAIN_MENU_BUTTONS = 6;
const int TOTAL_SETTINGS_MENU_BUTTONS = 5;
const int TOTAL_ENTER_NAME_BUTTONS = 2;

enum ButtonSprite {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	//BUTTON_SPRITE_TOTAL = TOTAL_MAIN_MENU_BUTTONS
};

enum button_state { MOUSE_OUT, MOUSE_OVER, CLICKED };

//The mouse button
class Button {
public:
	void setCallback(void(*callback)()) { m_callback = callback; }	// Callbacks for buttons
	int getCallbackID() { return m_callbackID; }
		
	Button();														// Initializes internal variables
		
	void setPosition(int x, int y);									// Sets top left position
		
	//void handleEvent(SDL_Event* e, LTexture test);
	void handleEvent(SDL_Event* e, int buttonSelected);				// Handles mouse event

	void render(Texture &texture, SDL_Rect *currentClip);			// Rendering function
	//void render(Texture &texture, SDL_Renderer *rend, SDL_Rect *currentClip);		// Rendering function
	//void init();
	SDL_Point mPosition;

	ButtonSprite getButtonSprite() { return mCurrentSprite; }
	void setButtonSprite(ButtonSprite bs) { mCurrentSprite = bs; }

	ButtonSprite mCurrentSprite;									// Currently used global sprite - Sprite enumeration

private:
	void(*m_callback)();

	int m_callbackID;

	bool m_bReleased;
};

#endif
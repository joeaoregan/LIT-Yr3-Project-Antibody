#include <SDL.h>
#include <iostream>
#include "LButton.h"
#include "Game.h"

enum { NEW_GAME, SETTINGS, HIGH_SCORES, QUIT };

LButton::LButton() {
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e, int buttonSelected) {
//	SDL_Color textColorOne = { 255, 255, 255 };
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;	// Check if mouse is in button

							//Mouse is left of the button
		if (x < mPosition.x) {
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH) {
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y) {
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT) {
			inside = false;
		}

		//Mouse is outside button
		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;	// Sprite 0
		}

		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;	// Set sprite mouse over 1
																	//std::cout << "Mouse Motion" << std::endl;
																	// THIS ONE PROBABLY NOT NEEDED
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;			// Set sprite mouse down 2
				std::cout << "Mouse Button Down" << std::endl;

				if (buttonSelected == NEW_GAME) {
					std::cout << "Selected: Start A New Game!" << std::endl;
					Game game;
					game.update();
					game.close();
					// Call a function in Game.cpp in the Main Project
				}

				else if (buttonSelected == SETTINGS) {
					std::cout << "Selected: Go To Settings Menu" << std::endl;
					init();
					// Call a function in Game.cpp in the Main Project
				}
				else if (buttonSelected == HIGH_SCORES) {
					std::cout << "Selected: View High Scores" << std::endl;
					init();
					// Call a function in Game.cpp in the Main Project
				}
				else if (buttonSelected == QUIT) {
					std::cout << "Selected: Quit The Game" << std::endl;
					close();//closes window using funciton in main - - - void LButton::close()
							// Call a function in Game.cpp in the Main Project
				}

				// USE THIS ONT TO HIGHLIGHT
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;			// Set sprite mouse up 3
				std::cout << "Mouse Button Up" << std::endl;

				// GO TO MENU OPTION
				break;
			}
		}
	}
}

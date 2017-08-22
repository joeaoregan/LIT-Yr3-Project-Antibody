/*
	2017/02/27:	User game singleton to access renderer
	2017/01/19 Started working on menu functionality with buttons
*/
/*
	BUTTON:

	This class handles the buttons the player can interact with in the game menus
*/
#include "Button.h"
#include "Game.h"
#include "Audio.h"
//#include <SDL.h>

enum mainMenuButtons { STORY, GAME_1PLAYER, GAME_2PLAYER, GO_TO_SETTINGS, MENU_TO_HIGH_SCORES, QUIT };
enum settingsMenuButtons { MUSIC_ON, MUSIC_OFF, MAIN_MENU, QUIT_SETTINGS };
enum highScoresButtons { SCORES_TO_MENU };
enum nameButtons { RESET, NAME_TO_MENU };

//SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];

Button::Button() {
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEvent(SDL_Event* e, int buttonSelected) {
	if (Game::Instance()->getCurrentLevel() == ENTER_NAME) {
		switch (e->key.keysym.sym) {
		case  SDLK_BACKSPACE: if (Game::Instance()->inputText.length() > 0) {	// backspace -> remove the last character from the string
																				//lop off character
			Game::Instance()->inputText.pop_back();
			Game::Instance()->renderText = true;		// Set the text update flag
		}
							  break;
		case SDLK_c: if (SDL_GetModState() & KMOD_CTRL) {
			SDL_SetClipboardText(Game::Instance()->inputText.c_str());
		}
					 break;
		case SDLK_v: if (SDL_GetModState() & KMOD_CTRL) {
			Game::Instance()->inputText = SDL_GetClipboardText();
			Game::Instance()->renderText = true;		// Set the text update flag
		}
		case SDLK_RETURN:
		case SDL_KEYDOWN: Game::Instance()->nameEntered = true;
			break;
		}
	}

//	SDL_Color textColorOne = { 255, 255, 255 };
	//If mouse event happened

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		//Get mouse position
		//MainMenu menu;
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
				//std::cout << "Mouse Motion" << std::endl; // THIS ONE PROBABLY NOT NEEDED
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;			// Set sprite mouse down 2
				std::cout << "Mouse Button Down" << std::endl;
				//std::cout << "Level: " << game.getCurrentLevel() << std::endl;

				if (Game::Instance()->getCurrentLevel() == MENU) {
					if (buttonSelected == STORY) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						//game.setCurrentLevel(1);
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						//game.twoPlayer = false;
						//game.update();
						Game::Instance()->setCurrentLevel(1);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = true;
						//Game::Instance()->update();
						// Call a function in Game.cpp in the Main Project
					}
					else if (buttonSelected == GAME_1PLAYER) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						Game::Instance()->setCurrentLevel(1);									// TEST ENTER NAME
																								//Game::Instance()->setCurrentLevel(ENTER_NAME);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = false;
					}
					else if (buttonSelected == GAME_2PLAYER) {
						std::cout << "Selected: 2 Player Game!" << std::endl;
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = true;
						Game::Instance()->setCurrentLevel(LEVEL_1);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
					else if (buttonSelected == GO_TO_SETTINGS) {
						std::cout << "Selected: Go To Settings Menu" << std::endl;
						Game::Instance()->setCurrentLevel(SETTINGS);
					}
					else if (buttonSelected == MENU_TO_HIGH_SCORES) {
						Game::Instance()->setCurrentLevel(HIGH_SCORES);
						std::cout << "Selected: View High Scores" << std::endl;
					}
					else if (buttonSelected == QUIT) {
						std::cout << "Selected: Quit The Game" << std::endl;
						Game::Instance()->close();
						//Game::Instance()->setCurrentLevel(ENTER_NAME);		// TEST ENTER NAME
					}
				}
				if (Game::Instance()->getCurrentLevel() == PAUSE) {
					if (buttonSelected == STORY) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						//game.setCurrentLevel(1);
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						//game.twoPlayer = false;
						//game.update();
						Game::Instance()->setCurrentLevel(1);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = true;
						//Game::Instance()->update();
						// Call a function in Game.cpp in the Main Project
					}
					else if (buttonSelected == GAME_1PLAYER) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						Game::Instance()->setCurrentLevel(1);									// TEST ENTER NAME
																								//Game::Instance()->setCurrentLevel(ENTER_NAME);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = false;
					}
					else if (buttonSelected == GAME_2PLAYER) {
						std::cout << "Selected: 2 Player Game!" << std::endl;
						//std::cout << "Level: " << game.getCurrentLevel() << std::endl;
						Game::Instance()->twoPlayer = true;
						Game::Instance()->setCurrentLevel(LEVEL_1);
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
					else if (buttonSelected == GO_TO_SETTINGS) {
						std::cout << "Selected: Go To Settings Menu" << std::endl;
						Game::Instance()->setCurrentLevel(SETTINGS);
					}
					else if (buttonSelected == MENU_TO_HIGH_SCORES) {
						Game::Instance()->setCurrentLevel(HIGH_SCORES);
						std::cout << "Selected: View High Scores" << std::endl;
					}
					else if (buttonSelected == QUIT) {
						std::cout << "Selected: Quit The Game" << std::endl;
						Game::Instance()->close();
						//Game::Instance()->setCurrentLevel(ENTER_NAME);		// TEST ENTER NAME
					}
				}
				// Handle button events for settings menu
				else if (Game::Instance()->getCurrentLevel() == SETTINGS) {
					if (buttonSelected == MUSIC_ON) {
						Audio::Instance()->playMusic();
					}
					else if (buttonSelected == MUSIC_OFF) {
						Audio::Instance()->stopMusic();						// Stop the music
					}
					else if (buttonSelected == MAIN_MENU) {
						Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->settingsMenuLoaded = false;		// menu media not loaded
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
					else if (buttonSelected == QUIT_SETTINGS) {
						std::cout << "Selected: Quit The Game" << std::endl;
						Game::Instance()->close();
					}
				}
				// Handle button events for High Score menu
				else if (Game::Instance()->getCurrentLevel() == HIGH_SCORES) {
					if (buttonSelected == SCORES_TO_MENU) {
						Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->highScoresLoaded = false;		// High Scores media not loaded after clearing NEED TO SET CLEAR
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
				}

				// Handle button events for Enter Name menu
				else if (Game::Instance()->getCurrentLevel() == ENTER_NAME) {
					if (buttonSelected == RESET) {
						//Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->highScoresLoaded = false;		// High Scores media not loaded after clearing NEED TO SET CLEAR
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
					if (buttonSelected == NAME_TO_MENU) {
						Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->highScoresLoaded = false;		// High Scores media not loaded after clearing NEED TO SET CLEAR
						std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl;
					}
				}
				// USE THIS ONE TO HIGHLIGHT
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

// Render the current button sprite at the button position
//
void Button::render(Texture &texture, SDL_Rect *currentClip) {
	texture.render(mPosition.x, mPosition.y, currentClip);	// Show current button spriteCHANGED - RENDERER IS ADDED
//void Button::render(Texture &texture, SDL_Renderer *rend, SDL_Rect *currentClip) {
	//texture.render(mPosition.x, mPosition.y, rend, currentClip);							// Show current button spriteCHANGED - RENDERER IS ADDED
}

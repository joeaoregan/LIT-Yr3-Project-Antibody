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

#include "SettingsMenu.h"
#include "HighScores.h"
//#include <SDL.h>

SettingsMenu settingsButton;
HighScores highScoresButton;

enum mainMenuButtons { STORY, GAME_1PLAYER, GAME_2PLAYER, GO_TO_SETTINGS, MENU_TO_HIGH_SCORES, QUIT };
enum settingsMenuButtons { MUSIC_ON, MUSIC_OFF, FULL_SCREEN_TOGGLE, MAIN_MENU, QUIT_SETTINGS };
enum highScoresButtons { SCORES_TO_MENU };
enum nameButtons { RESET, NAME_TO_MENU };
enum pauseMenu { RESUME_GAME, PAUSE_TO_MAIN, QUIT_PAUSE };

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
	SDL_Color textColorOne = { 255, 255, 255 };	//If mouse event happened	
	
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		//Get mouse position
		//MainMenu menu;
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;											// Check if mouse is in button
		
		if (x < mPosition.x) inside = false;						// Mouse is left of the button
		else if (x > mPosition.x + BUTTON_WIDTH) inside = false;	// Mouse is right of the button		
		else if (y < mPosition.y) inside = false;					// Mouse above the button		
		else if (y > mPosition.y + BUTTON_HEIGHT) inside = false;	// Mouse below the button

		//Mouse is outside button
		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;				// Sprite 0
		}
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;	// Set sprite mouse over 1
				//std::cout << "Mouse Motion" << std::endl;			// THIS ONE PROBABLY NOT NEEDED
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;			// Set sprite mouse down 2
				std::cout << "Mouse Button Down" << std::endl;

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

				// Handle Main Menu Buttons
				else if (Game::Instance()->getCurrentLevel() == MENU) {
					if (buttonSelected == STORY) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						Game::Instance()->setCurrentLevel(LEVEL_1);
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = true;
					}
					else if (buttonSelected == GAME_1PLAYER) {
						std::cout << "Selected: 1 Player Game!" << std::endl;
						Game::Instance()->setCurrentLevel(LEVEL_1);								// TEST ENTER NAME
						//Game::Instance()->setCurrentLevel(ENTER_NAME);
						Game::Instance()->twoPlayer = false;
						Game::Instance()->displayLevelIntro = false;
					}
					else if (buttonSelected == GAME_2PLAYER) {
						std::cout << "Selected: 2 Player Game!" << std::endl;
						Game::Instance()->setCurrentLevel(LEVEL_1);
						Game::Instance()->twoPlayer = true;
						Game::Instance()->displayLevelIntro = false;
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

				// Handle Pause Menu Buttons
				else if (Game::Instance()->getCurrentLevel() == PAUSE) {
					if (buttonSelected == RESUME_GAME) {
						std::cout << "Selected: Return To Current Game!" << std::endl;
						Game::Instance()->setCurrentLevel(Game::Instance()->levelToPause);		// Return to the level the game was in before pausing
					}
					else if (buttonSelected == PAUSE_TO_MAIN) {
						std::cout << "Selected: Return To Main Menu!" << std::endl;
						Game::Instance()->setCurrentLevel(MENU);
					}
					else if (buttonSelected == QUIT_PAUSE) {
						std::cout << "Selected: Quit The Game" << std::endl;
						Game::Instance()->close();
					}
				}

				// Handle button events for settings menu
				else if (Game::Instance()->getCurrentLevel() == SETTINGS) {
					if (buttonSelected == MUSIC_ON) {
						Audio::Instance()->playPauseMusic();					// Play the original music soundtrack
					}
					else if (buttonSelected == MUSIC_OFF) {
						Audio::Instance()->stopMusic();							// Stop the music
					}
					else if (buttonSelected == FULL_SCREEN_TOGGLE) {
						Game::Instance()->fullScreenOrWindowed();				// Make the game full screen or windowed
					}
					else if (buttonSelected == MAIN_MENU) {
						Game::Instance()->setCurrentLevel(MENU);				// Change game state to Main Menu
						settingsButton.closeSettingsMedia();					// Clear the media associated with the Settings Menu
						//Game::Instance()->settingsMenuLoaded = false;			// menu media not loaded
					}
					else if (buttonSelected == QUIT_SETTINGS) {
						std::cout << "Selected: Quit The Game" << std::endl;
						settingsButton.closeSettingsMedia();					// Clear the media associated with the Settings Menu
						Game::Instance()->close();
					}
				}

				// Handle button events for High Score menu
				else if (Game::Instance()->getCurrentLevel() == HIGH_SCORES) {
					if (buttonSelected == SCORES_TO_MENU) {
						Game::Instance()->setCurrentLevel(MENU);
						highScoresButton.closeHighScoresMedia();				// Close the media associated with the High Scores menu on exit
						//Game::Instance()->highScoresLoaded = false;			// High Scores media not loaded after clearing NEED TO SET CLEAR
					}
				}

				// Handle button events for Enter Name menu
				else if (Game::Instance()->getCurrentLevel() == ENTER_NAME) {
					if (buttonSelected == RESET) {
						//Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->highScoresLoaded = false;		.// High Scores media not loaded after clearing NEED TO SET CLEAR
					}
					if (buttonSelected == NAME_TO_MENU) {
						Game::Instance()->setCurrentLevel(MENU);
						//Game::Instance()->highScoresLoaded = false;		// High Scores media not loaded after clearing NEED TO SET CLEAR
					}
				}

				std::cout << "Level: " << Game::Instance()->getCurrentLevel() << std::endl; // Display current level

				// USE THIS ONE TO HIGHLIGHT
				break;



			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;				// Set sprite mouse up 3
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
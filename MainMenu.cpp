//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include "LButton.h"
#include "LTexture.h"
#include "MainMenu.h"
#include "Game.h"

bool init();					// Starts up SDL and creates window
bool loadMedia();				// Loads media


SDL_Window* gWindowMenu = NULL;		// The window we'll be rendering to
SDL_Renderer* gRendererMenu = NULL;	// The window renderer

TTF_Font *gFontMenu = NULL;			// Globally used font

									//Mouse button sprites
SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;
//LTexture gBGTexture;

//Buttons objects
LButton gButtons[TOTAL_BUTTONS];

LButton gBrianButtons[4];

//Rendered texture
LTexture gTextTexture;
LTexture gTextTextureOne;
LTexture gTextTextureTwo;
LTexture gTextTextureThree;
LTexture gTextTextureFour;

bool MainMenu::init() {

	bool success = true;	// Initialization flag

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {	// Initialize SDL
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindowMenu = SDL_CreateWindow("MAIN MENU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindowMenu == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create vsynced renderer for window
			gRendererMenu = SDL_CreateRenderer(gWindowMenu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRendererMenu == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRendererMenu, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool MainMenu::loadMedia() {
	bool success = true;	// Loading success flag
	SDL_Color textColor = { 0, 0, 0 };

	gFontMenu = TTF_OpenFont(".\\Fonts\\lazy.ttf", 28);
	if (gFontMenu == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		//Render text
		if (!gTextTexture.loadFromRenderedText("ANTIBODY", textColor, gFontMenu, gRendererMenu)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		if (!gTextTextureOne.loadFromRenderedText("New Game", { 0,0,0 }, gFontMenu, gRendererMenu)) {	// can take out the new textColor objects
			printf("Failed to render text texture!\n");
			success = false;
		}

		if (!gTextTextureTwo.loadFromRenderedText("Settings", textColor, gFontMenu, gRendererMenu)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		if (!gTextTextureThree.loadFromRenderedText("High Scores", textColor, gFontMenu, gRendererMenu)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		if (!gTextTextureFour.loadFromRenderedText("Quit", textColor, gFontMenu, gRendererMenu)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		gTextTextureOne.setX((SCREEN_WIDTH - gTextTextureOne.getWidth()) / 2);
		gTextTextureTwo.setX((SCREEN_WIDTH - gTextTextureTwo.getWidth()) / 2);
		gTextTextureThree.setX((SCREEN_WIDTH - gTextTextureThree.getWidth()) / 2);
		gTextTextureFour.setX((SCREEN_WIDTH - gTextTextureFour.getWidth()) / 2);

		gTextTextureOne.setY((SCREEN_HEIGHT - gTextTextureOne.getHeight()) / 2.5);
		gTextTextureTwo.setY((SCREEN_HEIGHT - gTextTextureTwo.getHeight()) / 2.0);
		gTextTextureThree.setY((SCREEN_HEIGHT - gTextTextureThree.getHeight()) / 1.7);
		gTextTextureFour.setY((SCREEN_HEIGHT - gTextTextureFour.getHeight()) / 1.5);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile(".\\Art\\buttonOne.png", gRendererMenu)) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
			gSpriteClipsMenu[i].x = 0;
			gSpriteClipsMenu[i].y = i * 200;
			gSpriteClipsMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsMenu[i].h = BUTTON_HEIGHT;
		}

		gBrianButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gTextTextureOne.getY());
		gBrianButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gTextTextureTwo.getY());
		gBrianButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gTextTextureThree.getY());
		gBrianButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gTextTextureFour.getY());
	}

	return success;
}

void MainMenu::close() {
	//Free loaded images
	gTextTexture.free();
	gTextTextureOne.free();
	gTextTextureTwo.free();
	gTextTextureThree.free();
	gTextTextureFour.free();

	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer(gRendererMenu);
	SDL_DestroyWindow(gWindowMenu);
	gWindowMenu = NULL;
	gRendererMenu = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MainMenu::update() {
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool quit = false;						// Main loop flag

			SDL_Event e;							// Event handler

			while (!quit) {						// While application is running
				while (SDL_PollEvent(&e) != 0) {	// Handle events on queue
					if (e.type == SDL_QUIT) {		// User requests quit
						quit = true;
					}

					//Handle button events
					for (int i = 0; i < TOTAL_BUTTONS; ++i) {
						//gButtons[i].handleEvent(&e);
						gBrianButtons[i].handleEvent(&e, i);
					}
				}
				render();
			}
		}
	}

	//Free resources and close SDL
	close();

}

void MainMenu::render() {
	//Clear screen
	//SDL_SetRenderDrawColor(gRendererMenu, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawColor(gRendererMenu, 255, 0x0, 0x0, 255);
	SDL_RenderClear(gRendererMenu);

	//Render buttons, all the buttons are rendered to the screen
	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		//gButtons[i].render();
		gBrianButtons[i].render();
	}

	gTextTextureOne.render(gTextTextureOne.getX(), gTextTextureOne.getY(), gRendererMenu);
	gTextTextureTwo.render(gTextTextureTwo.getX(), gTextTextureTwo.getY(), gRendererMenu);
	gTextTextureThree.render(gTextTextureThree.getX(), gTextTextureThree.getY(), gRendererMenu);
	gTextTextureFour.render(gTextTextureFour.getX(), gTextTextureFour.getY(), gRendererMenu);

	gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 12, gRendererMenu);

	//Update screen
	SDL_RenderPresent(gRendererMenu);
}

// Render the current button sprite at the button position
void LButton::render() {
	//Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, gRendererMenu, &gSpriteClipsMenu[mCurrentSprite]);	// CHANGED - RENDERER IS ADDED
}

void LButton::init()
{
	bool success = true;	// Initialization flag

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {	// Initialize SDL
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindowMenu = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindowMenu == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create vsynced renderer for window
			gRendererMenu = SDL_CreateRenderer(gWindowMenu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRendererMenu == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRendererMenu, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
}

//function to close window when quit selected
void LButton::close()
{
	//Destroy window
	SDL_DestroyRenderer(gRendererMenu);
	SDL_DestroyWindow(gWindowMenu);
	gWindowMenu = NULL;
	gRendererMenu = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


/*	
	Joe O'Regan
	K00203642
	05/02/2017

	AntiBody Unit Test:

	Split screen race mode test case
	Each player has a separate viewport in which they operate
	A ghost ship represents the opposite players position on screen

	
	Particles are just mini-animations. The animations will be spawned 
	around a Player to create a trail of coloured shimmering particles
*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>				// For updating text
#include <string>
#include <stdlib.h>
#include "Game.h"
#include "Texture.h"			// Handle textures
#include "Particle.h"			// Render particles for player ship engine
#include "Player.h"				// Handle Players

SDL_Window* gWindow = NULL;		// The window we'll be rendering to

SDL_Renderer* gRenderer = NULL;	// The window renderer

//Scene textures
Texture gBGTexture1;				// Player 1 background
Texture gBGTexture2;				// Player 2 background
Texture gPlayer1Texture;			// Player 1 ship
Texture gPlayer2Texture;			// Player 2 ship
Texture gPlayer1GhostTexture;		// Player 1 ghost ship
Texture gPlayer2GhostTexture;		// Player 2 ghost ship
Texture gDarkBlueParticleTexture;	// Particle
Texture gMediumBlueParticleTexture;	// Particle
Texture gLightBlueParticleTexture;	// Particle
Texture gShimmerTexture;			// Particle
			
Texture gP1Distance;				// Player 1 distance text
Texture gP2Distance;				// Player 2 distance text
Texture gWinner;					// Game winner text

SDL_Color textColour;				// Set the text colour
TTF_Font *gFontRetro20 = NULL;		// Globally used font 2017-01-25 Changed to Retro font which is more readable

int backgroundLoopCounter1 = 0;		// Number of times Player 1 background has looped
int backgroundLoopCounter2 = 0;
int scrollingOffset1 = 0;			// initialise background scrolling offset
int scrollingOffset2 = 0;			// Player 2 background scrolling offset

int p1Xmove = 0;					// Player 1 position on X coord measured in units
int p2Xmove = 0;

Player *player1 = new Player(gDarkBlueParticleTexture, gMediumBlueParticleTexture, gLightBlueParticleTexture);	// Player 1 that will be moving around on the screen
Player *player2 = new Player(gDarkBlueParticleTexture, gMediumBlueParticleTexture, gLightBlueParticleTexture);	// Player 2 that will be moving around on the screen

bool Game::init() {
	bool success = true;			// Initialization flag

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("ANTIBODY 'Separate Screen & Ghost Ship Test' By Joe O'Regan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);	//Initialize renderer color

				int imgFlags = IMG_INIT_PNG;	//Initialize PNG loading
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

/*
	Load the media for the game
*/
bool Game::loadMedia() {
	bool success = true;	//Loading success flag

	textColour = { 255, 50, 50, 255 };

	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		//Render text
		//if (!gP1Distance.loadFromRenderedText("ANTIBODY", textColour, gFontRetro20, gRenderer)) {
		printf("Failed to render text texture!\n");
		//	success = false;
		//}
	}


	//Load background texture
	if (!gBGTexture1.loadFromFile("Art/bgHalf.png", gRenderer)) {
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gBGTexture2.loadFromFile("Art/bgHalf.png", gRenderer)) {
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Load Player Ship and ghost ship textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.bmp", gRenderer)) {
		printf("Failed to load Player 1 Ship texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.bmp", gRenderer)) {
		printf("Failed to load Player 2 Ship texture!\n");
		success = false;
	}
	if (!gPlayer1GhostTexture.loadFromFile("Art/GhostShip1.bmp", gRenderer)) {
		printf("Failed to load Ghost Ship P1 texture!\n");
		success = false;
	}
	if (!gPlayer2GhostTexture.loadFromFile("Art/GhostShip2.bmp", gRenderer)) {
		printf("Failed to load Ghost Ship P2 texture!\n");
		success = false;
	}

	//Load Dark Particle texture
	if (!gDarkBlueParticleTexture.loadFromFile("Art/particleDarkBlue.bmp", gRenderer)) {
		printf("Failed to load red texture!\n");
		success = false;
	}

	//Load Medium Particle texture
	if (!gMediumBlueParticleTexture.loadFromFile("Art/particleMediumBlue.bmp", gRenderer)) {
		printf("Failed to load green texture!\n");
		success = false;
	}

	//Load Light Particle texture
	if (!gLightBlueParticleTexture.loadFromFile("Art/particleLightBlue.bmp", gRenderer)) {
		printf("Failed to load blue texture!\n");
		success = false;
	}

	//Load shimmer texture
	if (!gShimmerTexture.loadFromFile("Art/shimmer.bmp", gRenderer)) {
		printf("Failed to load shimmer texture!\n");
		success = false;
	}

	//Set texture transparency
	gDarkBlueParticleTexture.modifyAlpha(150);	// Alpha of 150 gives particles a semi transparent look
	gMediumBlueParticleTexture.modifyAlpha(150);
	gLightBlueParticleTexture.modifyAlpha(150);
	gShimmerTexture.modifyAlpha(150);

	return success;
}

/*
	Contains the main game loop
*/
void Game::update() {
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

			(*player2).setPlayer(2);
			(*player2).setY(240);
			
			std::stringstream distance1, distance2;
			//distance2.str("");

			//While application is running
			while (!quit) {
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					(*player1).handleEvent(e, 1);		// Handle input for Player 1
					(*player2).handleEvent(e, 2);		// Handle input for Player 2
				}

				(*player1).move();						// Move the Player
				(*player2).move();						// Move the Player

				scrollBackground();						// Scroll the background for both Players

				p1Xmove = (*player1).getX();			// Set variable for tracking distance
				p2Xmove = (*player2).getX();

				(*player1).setMapX((gBGTexture1.getWidth() * backgroundLoopCounter1) + abs(scrollingOffset1) + p1Xmove);	// distance background has travelled
				(*player2).setMapX((gBGTexture2.getWidth() * backgroundLoopCounter2) + abs(scrollingOffset2) + p2Xmove);

				std::cout << "P1: " << (*player1).getMapX() << " P2: " << (*player2).getMapX() << std::endl;

				distance1.str("");
				distance1 << "P1: " << (*player1).getMapX() / 100;	// Player 1 current distance travelled
				distance2.str("");
				distance2 << "P2: " << (*player2).getMapX() / 100;	// Player 2 current distance travelled
				
				if (!gP1Distance.loadFromRenderedText(distance1.str().c_str(), textColour, gFontRetro20, gRenderer)) {
					printf("Failed to render text texture!\n");
				}

				if (!gP2Distance.loadFromRenderedText(distance2.str().c_str(), textColour, gFontRetro20, gRenderer)) {
					printf("Failed to render text texture!\n");
				}

				render();								// Draw game objects to screen
			}
		}
	}
}

/*
	Scroll the background for each Players viewport
*/
void Game::scrollBackground() {
	// Player 1 screen
	if ((*player1).getX() > 100 && (*player1).getVelX() > 0)
		scrollingOffset1 -= (*player1).getVelX() + 2;
	else
		scrollingOffset1 -= 3;

	if (scrollingOffset1 < -gBGTexture1.getWidth()) {
		scrollingOffset1 = 0;				// update the scrolling background
		p1Xmove = 0;
		backgroundLoopCounter1++;
		std::cout << "Player 1 Background has looped " << backgroundLoopCounter1 << " times" << std::endl;
	}

	// Player 2 screen
	if ((*player2).getX() > 100 && (*player2).getVelX() > 0)
		scrollingOffset2 -= (*player2).getVelX() + 2;
	else
		scrollingOffset2 -= 3;

	if (scrollingOffset2 < -gBGTexture2.getWidth()) {
		scrollingOffset2 = 0;			// update the scrolling background
		p2Xmove = 0;
		backgroundLoopCounter2++;
		std::cout << "Player 2 Background has looped " << backgroundLoopCounter2 << " times" << std::endl;
	}
}

/*
	Draw objects to screen
	Render the Players, Ghost Ships, Backgrounds, Particles, Postition Counter, and Current Race Leader Text
*/
void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x0, 0x0, 0xFF);
	SDL_RenderClear(gRenderer);

	// Render background - Player 1
	gBGTexture1.render(scrollingOffset1, 0, gRenderer);
	gBGTexture1.render(scrollingOffset1 + gBGTexture1.getWidth(), 0, gRenderer);
	gBGTexture1.render(scrollingOffset1 + (gBGTexture1.getWidth() * 2), 0, gRenderer);

	gP1Distance.render(SCREEN_WIDTH - gP1Distance.getWidth() - 10, 8, gRenderer);

	// Render background - Player 2
	gBGTexture2.render(scrollingOffset2, 240, gRenderer);
	gBGTexture2.render(scrollingOffset2 + gBGTexture2.getWidth(), 240, gRenderer);
	gBGTexture2.render(scrollingOffset2 + (gBGTexture2.getWidth() * 2), 240, gRenderer);

	gP2Distance.render(SCREEN_WIDTH - gP2Distance.getWidth() - 10, 248, gRenderer);

	if ((*player1).getMapX() / 100 > 50 && (*player1).getMapX() > (*player2).getMapX()) {
		if (!gWinner.loadFromRenderedText("Player 1 Is The Winner!!!", { 255,255,255,255 }, gFontRetro20, gRenderer)) {
			printf("Failed to render text texture!\n");
		}
	}
	else if ((*player2).getMapX() / 100 > 50 && (*player2).getMapX() > (*player1).getMapX()) {
		if (!gWinner.loadFromRenderedText("Player 2 Is The Winner!!!", { 255,255,255,255 }, gFontRetro20, gRenderer)) {
			printf("Failed to render text texture!\n");
		}
	}
	else if ((*player1).getMapX() > (*player2).getMapX()) {
		if (!gWinner.loadFromRenderedText("Player 1 Is In The Lead", { 255,255,255,255 }, gFontRetro20, gRenderer)) {
			printf("Failed to render text texture!\n");
		}
	}
	else if ((*player2).getMapX() > (*player1).getMapX()) {
		if (!gWinner.loadFromRenderedText("Player 2 Is In The Lead", { 255,255,255,255 }, gFontRetro20, gRenderer)) {
			printf("Failed to render text texture!\n");
		}
	}
	else {
		if (!gWinner.loadFromRenderedText("", textColour, gFontRetro20, gRenderer)) {
			printf("Failed to render text texture!\n");
		}
	}

	gWinner.render((SCREEN_WIDTH - gWinner.getWidth()) / 2, 500, gRenderer);

	//gPlayer1GhostTexture.render((*player1).getX(), (*player1).getY() + 240, gRenderer);
	gPlayer1GhostTexture.render((*player1).getX() + (*player1).getMapX() - (*player2).getMapX(), (*player1).getY() + 240, gRenderer);
	//gPlayer2GhostTexture.render((*player2).getX(), (*player2).getY() - 240, gRenderer);
	gPlayer2GhostTexture.render((*player2).getX() + (*player2).getMapX() - (*player1).getMapX(), (*player2).getY() - 240, gRenderer);

	(*player1).render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticleTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);	// Render objects
	(*player2).render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticleTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);	// Render objects
	//(*player1).render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);	// Render objects
	//(*player2).render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);	// Render objects

	SDL_RenderPresent(gRenderer);	//Update screen

}

/*
	Clear media when finished
*/
void Game::close() {
	//Free loaded images
	gBGTexture1.free();
	gBGTexture2.free();
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gPlayer1GhostTexture.free();
	gPlayer2GhostTexture.free();
	gDarkBlueParticleTexture.free();
	gMediumBlueParticleTexture.free();
	gLightBlueParticleTexture.free();
	gShimmerTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
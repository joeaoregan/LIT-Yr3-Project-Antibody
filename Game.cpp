#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "LTexture.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Laser.h"
#include <list>

/*
	Laser + Enemy Ship

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
*/

bool init();					// Starts up SDL and creates window
bool loadMedia();				// Loads media//void close();

SDL_Window* gWindow = NULL;		// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;	// The window renderer

//Scene textures
LTexture gBGTexture;
LTexture gShipTexture;
LTexture gEnemyShipTexture;
LTexture gLaserTexture; // SEAN: Created Texture for Laser

// SEAN: Move ship object outside of main so spawnLaser funtion can use it
Ship ship;									// Declare a ship object that will be moving around on the screen
EnemyShip enemy;

// SEAN : Created list and iterator for laser objects
std::list<Laser*> listOfLaserObjects;		// List to store laser objects
// Create global iterators to cycle through laser objects
std::list<Laser*>::const_iterator iter;		// Make them read only

/*gRenderer*/

bool LTexture::loadFromFile(std::string path) {
	free();													// Get rid of preexisting texture

	SDL_Texture* newTexture = NULL;							// The final texture

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));	// Color key image

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);						// Create texture from surface pixels
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);	// Get rid of old loaded surface
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen

	// Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);	// Render to screen
}



bool init() {

	enemy.spawn();

//bool Game::init() {
	bool success = true;					// Initialization flag

											// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.03 by Joe O'Regan & Se\u00E1n Horgan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// Create vsynced renderer for window
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);										// Initialize renderer color

				int imgFlags = IMG_INIT_PNG;																	// Initialize PNG loading
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;			// Loading success flag

									// Load Ship texture
	if (!gShipTexture.loadFromFile(".\\Art\\Player1Ship.png")) {
		printf("Failed to load Player texture!\n");
		success = false;
	}

	// Load Enemy Ship texture
	//if (!gEnemyShipTexture.loadFromFile(".\\Art\\EnemyShip.png")) {
	if (!gEnemyShipTexture.loadFromFile(".\\Art\\EnemyShipOld.png")) {	// 2017/08/11
		printf("Failed to load Enemy texture!\n");
		success = false;
	}

	// Load background texture
	if (!gBGTexture.loadFromFile(".\\Art\\bg2.png")) {
		printf("Failed to load background texture!\n");
		success = false;
	}

	// SEAN: Load Laser texture
	if (!gLaserTexture.loadFromFile(".\\Art\\LaserBeam.png")) {
		printf("Failed to load Laser texture!\n");
		success = false;
	}

	return success;
}

void Game::close() {
	// Free loaded images
	gShipTexture.free();
	gEnemyShipTexture.free();
	gBGTexture.free();
	gLaserTexture.free();

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//int main(int argc, char* args[]) {
void Game::update(){
	// Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool quit = false;							// Main loop flag

			SDL_Event e;								// Event handler

			int scrollingOffset = 0;					// Declare the background scrolling offset

			// While application is running
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit	EXIT - CLOSE WINDOW
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					ship.handleEvent(e);				// Handle input for the ship
				}

				ship.move();							// Update ship movement
				enemy.moveEnemy();

				// Scroll background
				--scrollingOffset;
				if (scrollingOffset < -gBGTexture.getWidth()) {
					scrollingOffset = 0;				// update the scrolling background
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render background
				gBGTexture.render(scrollingOffset, 0);
				gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);

				ship.render();							// render the ship over the background
				enemy.render();

				// SEAN: Cycle through list of laser objects and render them to screen
				for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {

					(*iter++)->render();	// Render the laser
				}// end for

  				SDL_RenderPresent(gRenderer);			// Update screen



				// SEAN: Cycle through list of laser objects and move them
				//if (!listOfLaserObjects.empty()) {
				//while (listOfLaserObjects.begin() != NULL) {
					for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
						(*iter++)->move();					// Move the laser

					}// end for
				//}

				destroyLaser();
			}
		}
	}
}

void Game::destroyLaser() {
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		//for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end(); iter++) {
		//(*iter)->erase();					// Move the laser
		//while (!listOfLaserObjects.empty()) {
		if (!(*iter)->getLaserAlive()) {
			iter = listOfLaserObjects.erase(iter);
			//iter.~iter();
			std::cout << "destroy laser" << std::endl;

		}
		else {
			iter++;
			//std::cout << "increment" << std::endl;
		}
		//}
	}// end for
}

// SEAN: Function to spawn laser at ships location
void Game::spawnLaser() {
	Laser* p_Laser = new Laser();
	p_Laser->spawn(ship.getShipX() + 65, ship.getShipY() + 30, 20);
	listOfLaserObjects.push_back(p_Laser);

}// end spawnLaser

void Ship::render() {
	gShipTexture.render(mPosX, mPosY);					// Show the ship
}

// SEAN: Function to render the laser objects to the screen
void Laser::render() {
	gLaserTexture.render(mPosX, mPosY);					// Show the Laser
}

void EnemyShip::render() {
	gEnemyShipTexture.render(mEnPosX, mEnPosY);
}

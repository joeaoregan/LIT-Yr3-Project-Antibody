#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "LTexture.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Laser.h"
#include <list>

/*
    Flash Ship After Collision + Screen size

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
        Joe: Changed getCollision() for ship and enemyship
*/

Uint8 a = 255;					// Modulation component for flashing objects
bool flash = false;

//bool init();					// Starts up SDL and creates window
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


int scrollingOffset = 0;					// Declare the background scrolling offset

bool checkCollision(SDL_Rect* a, SDL_Rect* b);

// SEAN : Created list and iterator for laser objects
std::list<Laser*> listOfLaserObjects;		// List to store laser objects
std::list<Laser*>::const_iterator iter;		// Create global iterators to cycle through laser objects - Make them read only

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

bool Game::init() {
	enemy.spawn();

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

		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.06 by Joe O'Regan & Se\u00E1n Horgan - Flash On Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Create Window with name */
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
	bool success = true;			                                // Loading success flag

	if (!gShipTexture.loadFromFile(".\\Art\\Player1Ship.png")) {	    // Load Ship texture
		printf("Failed to load Player texture!\n");
		success = false;
	}

	if (!gEnemyShipTexture.loadFromFile(".\\Art\\EnemyVirus.png")) {// Load Enemy Ship texture
		printf("Failed to load Enemy texture!\n");
		success = false;
	}

	if (!gBGTexture.loadFromFile(".\\Art\\Background800.png")) {	// Load background texture
		printf("Failed to load background texture!\n");
		success = false;
	}

	if (!gLaserTexture.loadFromFile(".\\Art\\LaserGreen.png")) {	// SEAN: Load Laser texture
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
	if (!init()) {									// Start up SDL and create window
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia()) {							// Load media
			printf("Failed to load media!\n");
		}
		else {
			bool quit = false;						// Main loop flag

			while (!quit) {							// While application is running
				playerFlashOnCollide();

				quit = playerInput(quit);			// 2017/01/09 JOE: Handle input from player

				renderGameObjects();

				moveGameObjects();

				destroyGameObjects();				// 2017-01-09 JOE: Destroy the game objects when finished on the screen
			}
		}
	}
}

bool Game::playerInput(bool quit = false) {
	SDL_Event e;										// Event handler

	// Handle events on queue
	while (SDL_PollEvent(&e) != 0) {
		// User requests quit	EXIT - CLOSE WINDOW
		if (e.type == SDL_QUIT) {
			quit = true;
		}

		ship.handleEvent(e);							// Handle input for the ship
	}

	return quit;
}

void Game::moveGameObjects() {// SEAN: Cycle through list of laser objects and move them
	ship.move();							// Update ship movement
	checkCollision(ship.getCollider(), enemy.getCollider());
	enemy.moveEnemy();

	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		(*iter++)->move();					// Move the laser
	}
}

void Game::renderGameObjects() {// Scroll background
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

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderDrawRect(gRenderer, &enemy.getCollider());  // 2017/08/11 Changed
	//SDL_RenderDrawRect(gRenderer, &ship.getCollider());   // 2017/08/11 Changed
	SDL_RenderDrawRect(gRenderer, enemy.getCollider());
	SDL_RenderDrawRect(gRenderer, ship.getCollider());

	gShipTexture.setAlpha(a);				/* Set the Alpha value for Enemy */
	ship.render();							// render the ship over the background
	enemy.render();

	// SEAN: Cycle through list of laser objects and render them to screen
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {

		(*iter++)->render();	// Render the laser
	}

	SDL_RenderPresent(gRenderer);			// Update screen
}

void Game::destroyGameObjects() {
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		if (!(*iter)->getLaserAlive()) {
			iter = listOfLaserObjects.erase(iter);
			std::cout << "Laser Destroyed." << std::endl;
		}
		else {
			iter++;
		}
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

bool checkCollision(SDL_Rect* a, SDL_Rect* b){
	//The sides of the rectangles
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;
    /*
    // Old Version
	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	*/

	//Calculate the sides of rect A
	leftA = (*a).x;                                                 // 2017-08-11 Changed
	rightA = (*a).x + (*a).w;
	topA = (*a).y;
	bottomA = (*a).y + (*a).h;

	//Calculate the sides of rect B
	leftB = (*b).x;                                                 // 2017-08-11 Changed
	rightB = (*b).x + (*b).w;
	topB = (*b).y;
	bottomB = (*b).y + (*b).h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)	{
		return false;
	}

	if (topA >= bottomB)	{
		return false;
	}

	if (rightA <= leftB)	{
		return false;
	}

	if (leftA >= rightB)	{
		return false;
	}

	std::cout << "Collision!" << std::endl;
	//playerFlashOnCollide();
	flash = true;

	ship.setShipX(ship.getShipX() - ship.getShipVelX());
	ship.setShipColX(ship.getShipX());

	ship.setShipY(ship.getShipY() - ship.getShipVelY());
	ship.setShipColY(ship.getShipY());

	return true;	//If none of the sides from A are outside B
}


int counter = 0;

void Game::playerFlashOnCollide() {
		if (flash) {
			if (alphaDown > 5) {
				alphaDown -= 10;
				if (a < 5) a = 5;
				else a = alphaDown;
				if (alphaDown <= 5) alphaUp = 5;
			}
			if (alphaUp < 255) {
				alphaUp += 10;
				if (a > 255) a = 255;
				else a = alphaUp;
				if (alphaUp >= 255) alphaDown = 255;
			}

			if (counter > 150) {	// takes 25 decrements of 10 to set alpha to 5, and 25 increments to set alpha back to 255, 50 = 1 flash approx.
				flash = false;
				counter = 0;
			}
		}
		//else a = 255;	// visible -> dont need changed default a value to 255

		counter++;
}

// 09/01 Edited background to be 800 x 600 instead of 600 * 480

/*
    Enemy Ships fires laser

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
        Joe: Changed getCollision() for ship and enemyship
        Joe: Add relative path for asset files in "Music" and "SoundFX" directories
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>			// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include "Game.h"
#include "LTexture.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "EnemyVirus.h"			// 2017/01/10 JOE: Added Seans virus enemy
#include "Laser.h"
#include "LaserEnemy.h"			// 2017/01/10
#include "NinjaStar.h"
#include "BloodCell.h"			// 2017/01/10 JOE: Added Blood Cell
#include "BloodCellSmall.h"		// 2017/01/10 JOE: Added Small Blood Cell

//The music that will be played
Mix_Music *gMusic = NULL;		// Mix_Music: Data type for music
//Mix_Music *gEngineFX = NULL;	// 2017/01/10 JOE: Change Engine effect to music, turn off when no enemy ship on screen

//The sound effects that will be used (pointers)
Mix_Chunk *gNinjaFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserEFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gEngineFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds

bool init();					// Starts up SDL and creates window
bool loadMedia();				// Loads media//void close();

SDL_Window* gWindow = NULL;		// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;	// The window renderer
Uint8 a = 0;					// Modulation component

int scrollingOffset = 0;		// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)

int degrees = 0;
int degreesBC = 0;				// 2017/01/10 JOE: Added degrees for blood cell rotation
int degreesBCS = 0;
int alphaUp = 5, alphaDown = 5;

//Scene textures
LTexture gBGTexture;			// Background
LTexture gShipTexture;			// Player ship
LTexture gEnemyShipTexture;		// Enemy ship
LTexture gEnemyVirusTexture;	// Enemy Virus
LTexture gLaserGreenTexture;	// Texture for Laser weapon
LTexture gLaserBlueTexture;		// Texture for Laser weapon
LTexture gNinjaStarTexture;		// Texture for Ninja Star weapon
LTexture gBloodCellTexture;		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
LTexture gBloodCellSmallTexture;// Texture for Smaller Blood Cell
//LTexture gGO;

// SEAN: Move ship object outside of main so spawnLaser funtion can use it
Ship player;					// Declare a ship object that will be moving around on the screen
EnemyShip* enemy1 = new EnemyShip();
EnemyShip* enemy2 = new EnemyShip();
EnemyVirus* virus1 = new EnemyVirus();

std::list<EnemyShip*> listOfEnemyShips;				// 2017/01/09 JOE: List to store laser objects
std::list<EnemyShip*>::const_iterator iterES;		// 2017/01/09 JOE: Make them read only
std::list<EnemyVirus*> listOfEnemyVirus;			// 2017/01/09 JOE: List to store laser objects
std::list<EnemyVirus*>::const_iterator iterEV;		// 2017/01/09 JOE: Make them read only
std::list<BloodCell*> listOfBloodCells;				// 2017/01/10 JOE: List to store laser objects
std::list<BloodCell*>::const_iterator iterBC;		// 2017/01/10 JOE: Make them read only
std::list<BloodCellSmall*> listOfSmallBloodCells;	// 2017/01/10 JOE: List to store laser objects
std::list<BloodCellSmall*>::const_iterator iterSBC;	// 2017/01/10 JOE: Make them read only
// SEAN : Created list and iterator for laser objects
std::list<Laser*> listOfLaserObjects;				// List to store laser objects
std::list<Laser*>::const_iterator iter;				// Make them read only
std::list<LaserEnemy*> listOfEnemyLaserObjects;		// 2017/01/10
std::list<LaserEnemy*>::const_iterator iterEL;		// 2017/01/10

std::list<NinjaStar*> listOfNinjaStarObjects;		// 2017/01/09 JOE: List to store Ninja Star objects
std::list<NinjaStar*>::const_iterator iterNS;		// 2017/01/09 JOE: Create global iterators to cycle through laser objects - Make them read only


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
	bool success = true;							// Initialization flag

	srand(static_cast<unsigned int>(time(0)));		// Seed the random number

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {	// 2017/01/09 JOE: SOUND - Neet do initialise audio with video
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.10 by Joe O'Regan & Se\u00E1n Horgan - Enemy Laser", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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

				//call Mix_oopenAudio to Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)	// sound frequencey, sample format, hardware channels, sample size
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());	// report errors with SDL_mixer
					success = false;
				}

				Mix_Volume(-1, MIX_MAX_VOLUME);	// sets the volume for all channels MIX_MAX_VOLUME = 128 BALANCES OUT THE VOLUMES A BIT BETTER - LEAVE IN

				//If there is no music playing
				//if (Mix_PlayingMusic() == 0)
				//{
				//Play the music
				//	Mix_PlayMusic(gMusic, -1);	// start if not playing
				//}
			}
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;			// Loading success flag

	// Load Ship texture
	if (!gShipTexture.loadFromFile(".\\Art\\Player1Ship.png")) {        // 2017/08/10 Was PlayerShip
		printf("Failed to load Player texture!\n");
		success = false;
	}
	// Load Enemy Ship texture
	//if (!gEnemyShipTexture.loadFromFile("EnemyShip.png")) {
	if (!gEnemyShipTexture.loadFromFile(".\\Art\\EnemyShip.png")) {  // 2017/08/10 Was EnemyShip
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	// Load Enemy Virus texture
	//if (!gEnemyVirusTexture.loadFromFile("EnemyVirus.png")) {
	if (!gEnemyVirusTexture.loadFromFile(".\\Art\\EnemyVirus.png")) {
		printf("Failed to load Enemy Virus texture!\n");
		success = false;
	}
	// Load Blood Cell texture
	if (!gBloodCellTexture.loadFromFile(".\\Art\\BloodCell.png")) {			    // 10/01 Added Blood Cell
		printf("Failed to load Blood Cell texture!\n");
		success = false;
	}
	// Load Blood Cell texture
	if (!gBloodCellSmallTexture.loadFromFile(".\\Art\\BloodCellSmall.png")) {		// 10/01 Added Blood Cell
		printf("Failed to load Small Blood Cell texture!\n");
		success = false;
	}
	// Load background texture
	if (!gBGTexture.loadFromFile(".\\Art\\Background800.png")) {				// 09/01 Edited background to be 800 x 600 instead of 600 * 480
		printf("Failed to load background texture!\n");
		success = false;
	}

	// Load Green Laser texture
	if (!gLaserGreenTexture.loadFromFile(".\\Art\\LaserGreen.png")) {
		printf("Failed to load Green Laser texture!\n");
		success = false;
	}

	// Load Blue Laser texture
	if (!gLaserBlueTexture.loadFromFile(".\\Art\\LaserBlue.png")) {
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}

	// Load Ninja Star texture
	if (!gNinjaStarTexture.loadFromFile(".\\Art\\NinjaStar.png")) {
		printf("Failed to load Ninja Star texture!\n");
		success = false;
	}

	//Load music
	//gMusic = Mix_LoadMUS(".\\Music\\SleepNow.wav");	// Load music
	gMusic = Mix_LoadMUS(".\\Music\\SleepNow2.wav");	// Load music
	if (gMusic == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	/*
	gEngineFX = Mix_LoadMUS("Engine1.wav");	// Load music
	if (gEngineFX == NULL) {
		printf("Failed to load engine effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	} */
	//Load sound effects
	gNinjaFX = Mix_LoadWAV(".\\SoundFx\\Swoosh1.wav");	// Load sound effects
	if (gNinjaFX == NULL) {
		printf("Failed to load ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gLaserFX = Mix_LoadWAV(".\\SoundFx\\LaserPlayer.wav");	// Load sound effects
	if (gLaserFX == NULL) {
		printf("Failed to load laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserEFX = Mix_LoadWAV(".\\SoundFx\\LaserEnemy.wav");	// Load sound effects   //2017-08-10 Use existing Sound Effect
	if (gLaserEFX == NULL) {
		printf("Failed to load enemy laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//gEngineFX = Mix_LoadWAV("Engine4.wav");	// Load sound effects
	//if (gEngineFX == NULL) {
	//	printf("Failed to load engine sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	//	success = false;
	//}

	//Mix_PlayMusic(gMusic, -1);
	//Mix_PlayMusic(gEngineFX, -1);	// can only play one music track at a time

	return success;
}

void Game::close() {
	// Free loaded images
	gShipTexture.free();
	gEnemyShipTexture.free();
	gEnemyVirusTexture.free();
	gBGTexture.free();
	gLaserGreenTexture.free();
	gLaserBlueTexture.free();
	gNinjaStarTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();
	//gGO.free();

	//Free the sound effects
	Mix_FreeChunk(gNinjaFX);	// Free a sound effect
	Mix_FreeChunk(gLaserFX);	// Free a sound effect
	Mix_FreeChunk(gLaserEFX);	// Free a sound effect
	Mix_FreeChunk(gEngineFX);	// Free a sound effect

	//Free the music
	Mix_FreeMusic(gMusic);	// Free music
	gMusic = NULL;
	//Mix_FreeMusic(gEngineFX);	// Free music
	//gEngineFX = NULL;

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
	} else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			bool quit = false;							// Main loop flag

			// While application is running
			while (!quit) {
				// Handle events on queue
				playerFlashOnCollide();					// 2017-01-09 JOE: The player texture flashes on collision with other Game Objects

				quit = playerInput(quit);				// 2017/01/09 JOE: Handle input from player

				renderGameObjects();					// 2017-01-09 JOE: Render the game objects to the screen

				moveGameObjects();						// 2017-01-09 JOE: Move the game objects on the screen

  				SDL_RenderPresent(gRenderer);			// Update screen

				destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen

				//audio();								// 2017-01-10 JOE: Handle the audio for game objects

				spawnEnemies();							// 2017/01/10 JOE: Spawn enemies and obstacles at random coords and distances apart
			}
		}
	}
}
/*
void Game::audio() {
	// Cycle through list of Enemy ships and play engine sound
	if (listOfEnemyShips.size() > 0){
	//for (iterES = listOfEnemyShips.begin(); iterES != listOfEnemyShips.end();) {
		//if ((*iterES++)->getX() < 800 && (*iterES++)->getX() > 0 - (*iterES)->getESwidth())
		//if ((*iterES++)->getX() == 800) {


			//Mix_PlayChannel(-1, gEngineFX, 0);
			//Mix_FadeInChannel(-1, gEngineFX, 0, 1000);			// TOO LOUD


			//std::cout << "test audio" << std::endl;
		//}
	}
	if (listOfEnemyShips.size() == 1 && (*listOfEnemyShips.begin())->getX() < 0)
		Mix_FadeOutChannel(-1, 300);
}
*/
bool Game::playerInput(bool quit = false) {
	SDL_Event e;								// Event handler

	while (SDL_PollEvent(&e) != 0) {
		// User requests quit	EXIT - CLOSE WINDOW
		if (e.type == SDL_QUIT) {
			quit = true;
		}

		player.handleEvent(e);				// Handle input for the ship
	}
	return quit;
}

void Game::renderGameObjects() {
	//int scrollingOffset = 0;					// Declare the background scrolling offset

	degrees += 5;								// Number of degrees to rotate spinning objects
	degrees %= 360;
	degreesBC += 1;								// Number of degrees to rotate spinning objects
	degreesBC %= 360;
	degreesBCS += 2;								// Number of degrees to rotate spinning objects
	degreesBCS %= 360;

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

	// Cycle through list of small Blood Cells obstacles and render to screen
	for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
		(*iterSBC++)->render();	// Render the blood cell
	}
	// Cycle through list of Enemy ships and render to screen
	for (iterES = listOfEnemyShips.begin(); iterES != listOfEnemyShips.end();) {
		(*iterES++)->render();	// Render the enemy ship
	}
	// Cycle through list of Enemy Virus and render to screen
	for (iterEV = listOfEnemyVirus.begin(); iterEV != listOfEnemyVirus.end();) {
		(*iterEV++)->render();	// Render the enemy virus
	}
	// Cycle through list of Blood Cells obstacles and render to screen
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		(*iterBC++)->render();	// Render the blood cell
	}

	// Cycle through list of laser objects and render them to screen
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		(*iter++)->render();	// Render the laser
	}
	for (iterEL = listOfEnemyLaserObjects.begin(); iterEL != listOfEnemyLaserObjects.end();) {
		(*iterEL++)->render();	// Render the laser
	}
	for (iterNS = listOfNinjaStarObjects.begin(); iterNS != listOfNinjaStarObjects.end();) {
		(*iterNS++)->render();	// Render the ninja star
	}

	/* Set the Alpha value for Enemy */
	//gEnemyShipTexture.setAlpha(a);			// will flash for all enemies NO GOOD
	gShipTexture.setAlpha(a);
	player.render();							// render the ship over the background
}

// Move the game objects on screen
void Game::moveGameObjects() {
	player.movement();						// Update ship movement

	// Cycle through lists of Enemys and move them
	for (iterES = listOfEnemyShips.begin(); iterES != listOfEnemyShips.end();) {
		(*iterES)->movement();	// Move the enemy ship
		spawnEnemyLaser((*iterES++)->getX(), (*iterES)->getY());
	}
	// Cycle through list of Enemy virus and move them
	for (iterEV = listOfEnemyVirus.begin(); iterEV != listOfEnemyVirus.end();) {
		(*iterEV++)->movement(player.getX(), player.getY());	// 2017/01/10 JOE: Move the enemy virus towards the player ship (change from player object to just player coords)
	}
	// Cycle through list of Blood Cells and move them
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		(*iterBC++)->movement();	// 2017/01/10 JOE: Move the blood cells in a wavey line
	}
	// Cycle through list of Small Blood Cells and move them
	for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
		(*iterSBC++)->movement();	// 2017/01/10 JOE: Move the blood cells in a wavey line
	}

	// Cycle through lists of weapons and move them
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		(*iter++)->movement();		// Move the laser
	}
	for (iterEL = listOfEnemyLaserObjects.begin(); iterEL != listOfEnemyLaserObjects.end();) {
		(*iterEL++)->movement();	// Move the enemy laser
	}
	for (iterNS = listOfNinjaStarObjects.begin(); iterNS != listOfNinjaStarObjects.end();) {
		(*iterNS++)->movement();	// Move the ninja star
	}
}
// Destroy Game Objects
void Game::destroyGameObjects() {
	for (iterES = listOfEnemyShips.begin(); iterES != listOfEnemyShips.end();) {
		if (!(*iterES)->getAlive()) {
			iterES = listOfEnemyShips.erase(iterES);
			std::cout << "destroy enemy ship" << std::endl;
		}
		else {
			iterES++;
		}
	}
	for (iterEV = listOfEnemyVirus.begin(); iterEV != listOfEnemyVirus.end();) {
		if (!(*iterEV)->getAlive()) {
			iterEV = listOfEnemyVirus.erase(iterEV);
			std::cout << "destroy enemy virus" << std::endl;
		}
		else {
			iterEV++;
		}
	}
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		if (!(*iterBC)->getAlive()) {
			iterBC = listOfBloodCells.erase(iterBC);
			std::cout << "destroy blood cell" << std::endl;
		}
		else {
			iterBC++;
		}
	}
	for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
		if (!(*iterSBC)->getAlive()) {
			iterSBC = listOfSmallBloodCells.erase(iterSBC);
			std::cout << "destroy small blood cell" << std::endl;
		}
		else {
			iterSBC++;
		}
	}
	for (iter = listOfLaserObjects.begin(); iter != listOfLaserObjects.end();) {
		if (!(*iter)->getAlive()) {
			iter = listOfLaserObjects.erase(iter);
			std::cout << "destroy laser" << std::endl;
		}
		else {
			iter++;
		}
	}
	for (iterEL = listOfEnemyLaserObjects.begin(); iterEL != listOfEnemyLaserObjects.end();) {
		if (!(*iterEL)->getAlive()) {
			iterEL = listOfEnemyLaserObjects.erase(iterEL);
			std::cout << "destroy enemy laser" << std::endl;
		}
		else {
			iterEL++;
		}
	}
	for (iterNS = listOfNinjaStarObjects.begin(); iterNS != listOfNinjaStarObjects.end();) {
		if (!(*iterNS)->getAlive()) {
			iterNS = listOfNinjaStarObjects.erase(iterNS);
			std::cout << "destroy ninja star" << std::endl;
		}
		else {
			iterNS++;
		}
	}
}

void Game::playerFlashOnCollide() {
	if (alphaUp < 255) {
		alphaUp += 10;

		if (a > 255) a = 255;
		else a = alphaUp;

		if (alphaUp >= 255) alphaDown = 255;
	}

	if (alphaDown > 5) {
		alphaDown -= 10;

		if (a < 5) a = 5;
		else a = alphaDown;

		if (alphaDown <= 5) alphaUp = 5;
	}
}

// Decide how many of each enemy / obstacle on screen at a given time
void Game::spawnEnemies() {
	if (listOfEnemyShips.size() <= 1) {
		spawnEnemyShip();
	}
	if (listOfEnemyVirus.size() == 0) {
		spawnEnemyVirus();
	}
	if (listOfBloodCells.size() <= 8) {
		spawnBloodCell();
	}
	if (listOfSmallBloodCells.size() <= 12) {
		spawnSmallBloodCell();
	}
}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 8 + 1;
	randomY = rand() % 8 + 1;
	randomSpeed = rand() % 3 + 3;

	x = SCREEN_WIDTH + (randomX * 50);
	y = (randomY * 60);

	//int y = SCREEN_HEIGHT / 2;
	EnemyShip* p_Enemy = new EnemyShip();
	//p_Enemy->spawn(800, y, -5);
	p_Enemy->spawn(x, y, -randomSpeed);
	listOfEnemyShips.push_back(p_Enemy);
}

void Game::spawnEnemyVirus() {
	int x, y, randomX, randomY;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;

	x = SCREEN_WIDTH + (randomX * 50);
	y = (randomY * 120) - 80;

	//int y = SCREEN_HEIGHT / 2;
	EnemyVirus* p_Virus = new EnemyVirus();
	//p_Virus->spawn(800, y, -2);
	p_Virus->spawn(x, y, -2);
	listOfEnemyVirus.push_back(p_Virus);
}

void Game::spawnBloodCell() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 8 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 250);
	y = (randomY * 60);

	BloodCell* p_BloodCell = new BloodCell();
	p_BloodCell->spawn(x, y, -randomSpeed);
	listOfBloodCells.push_back(p_BloodCell);
}
void Game::spawnSmallBloodCell() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 8 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 150);
	y = (randomY * 60);

	BloodCellSmall* p_SmallBloodCell = new BloodCellSmall();
	p_SmallBloodCell->spawn(x, y, -randomSpeed);
	listOfSmallBloodCells.push_back(p_SmallBloodCell);
}

//void Game::engineFX() {
//	Mix_PlayChannel(-1, gEngineFX, 0);
//}

// Spawn Weapon at ships location
void Game::spawnLaser() {
	Laser* p_Laser = new Laser();
	p_Laser->spawn(player.getX(), player.getY());
	listOfLaserObjects.push_back(p_Laser);
	Mix_PlayChannel(-1, gLaserFX, 0);
}
void Game::spawnNinjaStar() {
	NinjaStar* p_NinjaStar = new NinjaStar();
	p_NinjaStar->spawn(player.getX(), player.getY());
	listOfNinjaStarObjects.push_back(p_NinjaStar);
	Mix_PlayChannel(-1, gNinjaFX, 0);
}
void Game::spawnEnemyLaser(int shipX, int shipY) {
	LaserEnemy* p_LaserE = new LaserEnemy();

	//for (iterEL = listOfEnemyLaserObjects.begin(); iterEL != listOfEnemyLaserObjects.end();) {
		//if ((*iterEL++)->getX() % 100 == 0) {
	//		p_LaserE->spawn((*iterEL)->getX(), (*iterEL)->getY());
	//		listOfEnemyLaserObjects.push_back(p_LaserE);
			//Mix_PlayChannel(-1, gLaserFX, 0);
		//}
		//else continue;
	//}
	if (shipX % 100 == 0) {
		p_LaserE->spawn(shipX, shipY);
		listOfEnemyLaserObjects.push_back(p_LaserE);
		Mix_PlayChannel(-1, gLaserEFX, 0);
	}

	//p_LaserE->spawn(ship.getX(), EnemyShip.getY());
	//listOfEnemyLaserObjects.push_back(p_LaserE);
}

void Ship::render() {
	gShipTexture.render(player.getX(), player.getY());				// Show the ship
}



// Render the laser objects to the screen
void Laser::render() {
	gLaserGreenTexture.render(getX(), getY());
}
void LaserEnemy::render() {
	gLaserBlueTexture.render(getX(), getY());
}
/* Render the ninja star objects to the screen*/
void NinjaStar::render() {
	gNinjaStarTexture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
}
// Enemies and Obstacles
void EnemyShip::render() {
	gEnemyShipTexture.render(getX(), getY());
}

void EnemyVirus::render() {
	gEnemyVirusTexture.render(getX(), getY());
}
void BloodCell::render() {
	//gBloodCell.render(getX(), getY());
	gBloodCellTexture.render(getX(), getY(), NULL, -degreesBC, NULL, SDL_FLIP_NONE);
}
void BloodCellSmall::render() {
	gBloodCellSmallTexture.render(getX(), getY(), NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
}
//void GameObject::render() {
//	gGO.render(getX(), getY());
//}
/*
void GameObject::renderTexture(LTexture x) {
	x.render(getX(), getY());
}
*/

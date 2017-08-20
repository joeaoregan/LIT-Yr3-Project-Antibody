// 10/01 Sean Move ship object outside of main so spawnLaser funtion can use it
// 09/01 Edited background to be 800 x 600 instead of 600 * 480

/*
    Add Timer and Text, and fonts are needed to show numbers

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
        Joe: Changed getCollision() for ship and enemyship
        Joe: Add relative path for asset files in "Music" and "SoundFX" directories
*/

#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
//#include <sstream>		// For timer

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
#include "WhiteBloodCell.h"
#include "PowerUp.h"
#include <vector>



// Testing
EnemyShip enemy;

bool checkCollision(SDL_Rect a, SDL_Rect b);




int playerAlpha = 255;					// Modulation component for flashing objects
int gameOverAlpha = 255;
int timerAlpha = 255;
bool playerFlash = false;
bool gameOverFlash = true;
bool timerFlash = false;
bool gameOver = false;

//The sound effects that will be used (pointers)
Mix_Chunk *gNinjaFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserEFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gExplosionFX = NULL;


SDL_Window* gWindow = NULL;		// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;	// The window renderer
Uint8 a = 0;					// Modulation component

int scrollingOffset = 0;		// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)

int degrees = 0;
int degreesBC = 0;				// 2017/01/10 JOE: Added degrees for blood cell rotation
int degreesBCS = 0;

// Scene textures
LTexture gBGTexture;			// Background
LTexture gBGStartTexture;
LTexture gBGEndTexture;
LTexture gGameOverTextTexture;
// Objects and weapons
LTexture gShipTexture;			// Player ship
LTexture gEnemyShipTexture;		// Enemy ship
LTexture gEnemyVirusTexture;	// Enemy Virus
LTexture gLaserGreenTexture;	// Texture for Laser weapon
LTexture gLaserBlueTexture;		// Texture for Laser weapon
LTexture gNinjaStarTexture;		// Texture for Ninja Star weapon
LTexture gBloodCellTexture;		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
LTexture gBloodCellSmallTexture;// Texture for Smaller Blood Cell
LTexture gWhiteBloodCellTexture;		// Texture for White Blood Cell
LTexture gPowerUpTexture;				// Texture for Health Box Power Up

LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
LTexture gLevelTextTexture;

#define TIMER 15				// Time to start counting down from in seconds
Uint32 startTime = 6000;			// Unsigned integer 32-bits

TTF_Font *gFont = NULL;			//Globally used font
//Uint32 startTime = 0;						// Current start time - Unsigned integer 32-bits

Ship player;					// Declare a ship object that will be moving around on the screen
//EnemyShip* enemy1 = new EnemyShip();
//EnemyShip* enemy2 = new EnemyShip();
//EnemyVirus* virus1 = new EnemyVirus();

// Lists and iterators
std::list<EnemyShip*> listOfEnemyShips;				// 2017/01/09 JOE: List to store laser objects
std::list<EnemyShip*>::const_iterator iterES;		// 2017/01/09 JOE: Make them read only
std::list<EnemyVirus*> listOfEnemyVirus;			// 2017/01/09 JOE: List to store laser objects
std::list<EnemyVirus*>::const_iterator iterEV;		// 2017/01/09 JOE: Make them read only
std::list<BloodCell*> listOfBloodCells;				// 2017/01/10 JOE: List to store laser objects
std::list<BloodCell*>::const_iterator iterBC;		// 2017/01/10 JOE: Make them read only
std::list<BloodCellSmall*> listOfSmallBloodCells;	// 2017/01/10 JOE: List to store laser objects
std::list<BloodCellSmall*>::const_iterator iterSBC;	// 2017/01/10 JOE: Make them read only
std::list<Laser*> listOfLaserObjects;				// List to store laser objects
std::list<Laser*>::const_iterator iter;				// Make them read only
std::list<LaserEnemy*> listOfEnemyLaserObjects;		// 2017/01/10
std::list<LaserEnemy*>::const_iterator iterEL;		// 2017/01/10
std::list<NinjaStar*> listOfNinjaStarObjects;		// 2017/01/09 JOE: List to store Ninja Star objects
std::list<NinjaStar*>::const_iterator iterNS;		// 2017/01/09 JOE: Create global iterators to cycle through laser objects - Make them read only
std::list<WhiteBloodCell*> listOfWhiteBloodCells;
std::list<WhiteBloodCell*>::const_iterator iterWBC;

// Vectors
std::vector<PowerUp*> listOfPowerUps;


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
	bool success = true;							// Initialization flag

	enemy.spawn(100, 100);

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
		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.16 by Joe O'Regan & Se\u00E1n Horgan - Timer, Collisions, and Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//call Mix_oopenAudio to Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {									// sound frequencey, sample format, hardware channels, sample size
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());			// report errors with SDL_mixer
					success = false;
				}

				Mix_Volume(-1, MIX_MAX_VOLUME);	// sets the volume for all channels MIX_MAX_VOLUME = 128 BALANCES OUT THE VOLUMES A BIT BETTER - LEAVE IN
			}
		}
	}

	return success;
}

bool Game::loadMedia() {
	bool success = true;			// Loading success flag

	//Open the font
	//gFont = TTF_OpenFont("22_timing/lazy.ttf", 28);
	gFont = TTF_OpenFont(".\\Font\\lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColor = { 0, 100, 200, 255 };								// Set text color as blue
		TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);								// Use bold font

		if (!gPromptTextTexture.loadFromRenderedText("A Game By Sean Horgan And Joe O'Regan", textColor)) {
			printf("Unable to render prompt text texture!\n");
			success = false;
		}
		if (!gLevelTextTexture.loadFromRenderedText("Level 1", textColor)) {
			printf("Unable to render level text texture!\n");
			success = false;
		}
	}

	// Load Textures
	//if (!gShipTexture.loadFromFile("PlayerShip.png")) {					// Ship Texture
	if (!gShipTexture.loadFromFile(".\\Art\\Player1Ship.png")) {             // Ship Texture 2017/08/10 Was PlayerShip
		printf("Failed to load Player texture!\n");
		success = false;
	}
	//if (!gEnemyShipTexture.loadFromFile("EnemyShip.png")) {				// Enemy Ship Texture
	if (!gEnemyShipTexture.loadFromFile(".\\Art\\EnemyShip.png")) {             // Enemy Ship Texture
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	//if (!gEnemyVirusTexture.loadFromFile("EnemyVirus.png")) {			        // Enemy Virus Texture
	if (!gEnemyVirusTexture.loadFromFile(".\\Art\\EnemyVirus.png")) {
		printf("Failed to load Enemy Virus texture!\n");
		success = false;
	}
	if (!gBloodCellTexture.loadFromFile(".\\Art\\BloodCell.png")) {				// 10/01 Added Large Blood Cell
		printf("Failed to load Blood Cell texture!\n");
		success = false;
	}
	if (!gBloodCellSmallTexture.loadFromFile(".\\Art\\BloodCellSmall.png")) {	// 10/01 Added Small Blood Cell
		printf("Failed to load Small Blood Cell texture!\n");
		success = false;
	}
	if (!gBGTexture.loadFromFile(".\\Art\\Background800.png")) {				// 09/01 Edited background to be 800 x 600 instead of 600 * 480
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gBGStartTexture.loadFromFile(".\\Art\\bgBegin.png")) {					// Background start texture
		printf("Failed to load start background texture!\n");
		success = false;
	}
	if (!gBGEndTexture.loadFromFile(".\\Art\\bgEnd.png")) {						// Background end texture
		printf("Failed to load end background texture!\n");
		success = false;
	}
	if (!gLaserGreenTexture.loadFromFile(".\\Art\\LaserGreen.png")) {			// Green Laser Texture
		printf("Failed to load Green Laser texture!\n");
		success = false;
	}
	if (!gLaserBlueTexture.loadFromFile(".\\Art\\LaserBlue.png")) {				// Blue Laser Texture
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}
	if (!gNinjaStarTexture.loadFromFile(".\\Art\\NinjaStarBlue.png")) {			// Ninja Star Texture
		printf("Failed to load Ninja Star texture!\n");
		success = false;
	}
	if (!gGameOverTextTexture.loadFromFile(".\\Art\\GameOverTEST.png")) {		// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}
	if (!gWhiteBloodCellTexture.loadFromFile(".\\Art\\WhiteCell.png")) {				// 10/01 Added Blood Cell
		printf("Failed to load White Blood Cell texture!\n");
		success = false;
	}
	if (!gPowerUpTexture.loadFromFile(".\\Art\\HealthBox.png")) {						// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Health Box texture!\n");
		success = false;
	}

	//Load music
	//gMusic = Mix_LoadMUS("SleepNow.wav");	// Load music
	gMusic = Mix_LoadMUS(".\\Music\\SleepNow2.wav");	// Load music
	if (gMusic == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	//gNinjaFX = Mix_LoadWAV("Swoosh.wav");				// Load sound effects
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

	//Mix_PlayMusic(gMusic, -1);	// START THE MUSIC WHEN GAME STARTS

	return success;
}

void Game::close() {
	// Free loaded images
	gShipTexture.free();
	gEnemyShipTexture.free();
	gEnemyVirusTexture.free();
	gBGTexture.free();
	gBGStartTexture.free();
	gBGEndTexture.free();
	gGameOverTextTexture.free();

	gLaserGreenTexture.free();
	gLaserBlueTexture.free();
	gNinjaStarTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();

	gTimeTextTexture.free();
	gPromptTextTexture.free();
	gLevelTextTexture.free();

	// 2017-01-15 new stuff
	gWhiteBloodCellTexture.free();
	gPowerUpTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Free the sound effects
	Mix_FreeChunk(gNinjaFX);	// Ninja Star sound effect
	Mix_FreeChunk(gLaserFX);	// Laser sound effect
	Mix_FreeChunk(gLaserEFX);	// Enemy Laser sound effect

	//Free the music
	Mix_FreeMusic(gMusic);		// Free music
	gMusic = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
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

			SDL_Color textColor = { 0, 100, 200, 255 };

			unsigned int lastTime = 0, currentTime, countdownTimer = TIMER;	// TEST TIMING

			//In memory text stream
			// string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
			std::stringstream timeText;		// string stream

			while (!quit) {								// While application is running

				flashGameObject(playerAlpha, playerFlash, 10, 4);	// Flash player ship when it has a collision, flash at faster rate, flash 4 times
				flashGameObject(gameOverAlpha, gameOverFlash, 5);	// Flash game over at end of game, flash at slower rate for 5 than 10
				flashGameObject(timerAlpha, timerFlash, 8);			// Flash timer when time is running out

				quit = playerInput(quit);				// 2017/01/09 JOE: Handle input from player





				timeText.str("");									// Set text to be rendered - string stream - print the time since timer last started - initialise empty

				currentTime = SDL_GetTicks();

				if (currentTime > lastTime + 1000) {
					lastTime = currentTime;

					countdownTimer -= 1;

					std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
				}

				// Countdown Timer
				if (countdownTimer > TIMER && countdownTimer < TIMER + 6) {
					timeText << "Game Over";
					gameOver = true;
				}
				else if (countdownTimer >= 0 && countdownTimer <= TIMER) {
					timeText << "Time: " << countdownTimer;
					gameOver = false;
				}
				if (countdownTimer <= 0 || countdownTimer > TIMER + 6) {
					timeText << "Game Over";
					gameOver = true;
					countdownTimer = TIMER + 5;	// flash game over for 5 seconds
				}

				// Time running out change colour to red
				if (countdownTimer >= 0 && countdownTimer <= 5) {
					textColor = { 255, 0, 0, 255 };
					timerFlash = true;
				}
				else {
					textColor = { 0, 100, 200, 255 };
					timerFlash = false;
				}

				//Render text - Get a string from it and use it to render the current time to a texture
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
					printf("Unable to render time texture!\n");
				}






				playerFlashOnCollide();					// 2017-01-09 JOE: The player texture flashes on collision with other Game Objects

				spawnEnemies();							// 2017/01/10 JOE: Spawn enemies and obstacles at random coords and distances apart

				renderGameObjects();					// 2017-01-09 JOE: Render the game objects to the screen

				moveGameObjects();						// 2017-01-09 JOE: Move the game objects on the screen

				destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen
			}
		}
	}
}

bool Game::playerInput(bool quit = false) {
	// Handle events on queue
	SDL_Event e;							// Event handler

	//SDL_Color textColor = { 0, 0, 0, 255 };	//Set text color as green

	// In memory text stream
	// string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
	std::stringstream timeText;		// string stream

	while (SDL_PollEvent(&e) != 0) {
		// User requests quit	EXIT - CLOSE WINDOW
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		// Reset start time on return keypress
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
			startTime = SDL_GetTicks();		// time since the program started in milliseconds
		}
		// Play / Pause music
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym) {
				// Play/Pause music on a m key press, stop music on 0
			case SDLK_m:
				//If there is no music playing
				if (Mix_PlayingMusic() == 0) {
					//Play the music
					Mix_PlayMusic(gMusic, -1);	// start if not playing
				}
				//If music is being played
				else {
					//If the music is paused
					if (Mix_PausedMusic() == 1)	// check if the music is paused
					{
						//Resume the music
						Mix_ResumeMusic();			// resume music
					}
					//If the music is playing
					else {
						//Pause the music
						Mix_PauseMusic();			// pause music
					}
				}
				break;

			case SDLK_0:
				Mix_HaltMusic();					// Stops music
				break;
			}
		}
		player.handleEvent(e);				// Handle input for the ship
	}

	//Set text to be rendered - string stream - print the time since timer last started
	timeText.str("");			// initialise empty
	timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime; // current time - relative start time

	return quit;
}

int backgroundLoopCounter = 0;
#define BACKGROUND_TIMES 4

void Game::renderGameObjects() {
	degrees += 5;								// Number of degrees to rotate spinning objects
	degrees %= 360;
	degreesBC += 1;								// Number of degrees to rotate spinning objects
	degreesBC %= 360;
	degreesBCS += 2;							// Number of degrees to rotate spinning objects
	degreesBCS %= 360;

	if (backgroundLoopCounter <= BACKGROUND_TIMES) scrollingOffset -= 5;
	if (scrollingOffset < -gBGTexture.getWidth()) {
		scrollingOffset = 0;					// update the scrolling background

		backgroundLoopCounter++;				// count the number of times the background has looped
		std::cout << "Background has looped " << backgroundLoopCounter << " times" << std::endl;
	}

	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// Render background
	if (backgroundLoopCounter < 1)
		gBGStartTexture.render(scrollingOffset, 0);			// 1st
	else if (backgroundLoopCounter > BACKGROUND_TIMES)
		gBGEndTexture.render(scrollingOffset, 0);			// end background
	else
		gBGTexture.render(scrollingOffset, 0);				// 3rd and every odd number

	if (backgroundLoopCounter < BACKGROUND_TIMES)
		gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);		// 2nd background (and every even number)
	else
		gBGEndTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);		// end background

	if (gameOver == false) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_RenderDrawRect(gRenderer, &player.getCollider());

		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
			(*iterSBC++)->render();	// Render the blood cell
		}
		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
			(*iterWBC++)->render();	// Render the blood cell
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

		// Cycle through list of power up objects and render them to screen
		for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
			listOfPowerUps[index]->render();
			//SDL_RenderDrawRect(gRenderer, &listOfPowerUps[index]->getCollider());
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

		// Render Text
		gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, SCREEN_HEIGHT - gPromptTextTexture.getHeight() - 8);
		gLevelTextTexture.render(10, 8);
		gTimeTextTexture.setAlpha(timerAlpha);	// Flash the timer
		gTimeTextTexture.render(600, 8);

		// Set the Alpha value for player when flashing
		gShipTexture.setAlpha(playerAlpha);
		player.render();							// render the ship over the background
		//player.renderTexture(gShipTexture, player.getX(), player.getY());

	}
	else if (gameOver == true) {
		gGameOverTextTexture.setAlpha(gameOverAlpha);
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() + 250) / 2); // FOR TESTING
	}

	SDL_RenderPresent(gRenderer);				// Update screen
}

void Game::moveGameObjects() {
	player.movement();							// Update ship movement
	checkCollision(player.getCollider(), enemy.getCollider());

	player.setColliderX(player.getX());
	player.setColliderY(player.getY());

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

	for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
		(*iterWBC++)->movement();	// Render the blood cell
	}
	// Cycle through list of Power Ups and move them
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		listOfPowerUps[index]->movement();
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
	for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
		if (!(*iterWBC)->getAlive()) {
			iterWBC = listOfWhiteBloodCells.erase(iterWBC);
			std::cout << "destroy white blood cell" << std::endl;
		}
		else {
			iterWBC++;
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
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		if (!listOfPowerUps[index]->getAlive()) {
			listOfPowerUps.erase(listOfPowerUps.begin() + index);
			std::cout << "Power Up Destroyed." << std::endl;
			index--;
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

//int counter = 0;

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

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

	//If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	std::cout << "Collision!" << std::endl;
	playerFlash = true;

	//enemy.mEnAlive = false;

	player.setX(player.getX() - player.getVelX());
	player.setColliderX(player.getX());

	player.setY(player.getY() - player.getVelY());
	player.setColliderY(player.getY());

	return true;	//If none of the sides from A are outside B
}

void Game::flashGameObject(int &alpha, bool &flash, int rate, int times) {
	if (flash) {
		if (alphaDown > 5) {
			alphaDown -= rate;
			if (alpha < 5) alpha = 5;
			else alpha = alphaDown;
			if (alphaDown <= 5) alphaUp = 5;
		}
		if (alphaUp < 255) {
			alphaUp += rate;
			if (alpha > 255) alpha = 255;
			else alpha = alphaUp;
			if (alphaUp >= 255) alphaDown = 255;
		}

		if (times != 0 && counter > times * 50) {	// takes 25 decrements of 10 to set alpha to 5, and 25 increments to set alpha back to 255, 50 = 1 flash approx.
			flash = false;
			counter = 0;
			alpha = 255;
		}
	}
	else alpha = 255;	// Set visibility back to maximum

	counter++;
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
	if (listOfWhiteBloodCells.size() <= 2) {
		spawnWhiteBloodCell();
	}
	if (listOfPowerUps.size() == 0) {
		spawnPowerUp();
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
	p_Enemy->spawn(x, y, -randomSpeed);
	listOfEnemyShips.push_back(p_Enemy);
}

void Game::spawnEnemyVirus() {
	int x, y, randomX, randomY;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;

	x = SCREEN_WIDTH + (randomX * 50);
	y = (randomY * 120) - 80;

	EnemyVirus* p_Virus = new EnemyVirus();
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
void Game::spawnWhiteBloodCell() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 150);
	y = (randomY * 120) - 80;

	WhiteBloodCell* p_WhiteBloodCell = new WhiteBloodCell();
	p_WhiteBloodCell->spawn(x, y, -randomSpeed);
	listOfWhiteBloodCells.push_back(p_WhiteBloodCell);
}

// Spawn Weapon at ships location
void Game::spawnLaser() {
	Laser* p_Laser = new Laser();
	p_Laser->spawn(player.getX(), player.getY());
	listOfLaserObjects.push_back(p_Laser);
	Mix_PlayChannel(-1, gLaserFX, 0);
}

void Game::spawnEnemyLaser(int shipX, int shipY) {
	LaserEnemy* p_LaserE = new LaserEnemy();

	if (shipX % 100 == 0) {
		p_LaserE->spawn(shipX, shipY);
		listOfEnemyLaserObjects.push_back(p_LaserE);
		Mix_PlayChannel(-1, gLaserEFX, 0);
	}
}

void Game::spawnNinjaStar() {
	NinjaStar* p_NinjaStar = new NinjaStar();
	p_NinjaStar->spawn(player.getX(), player.getY());
	listOfNinjaStarObjects.push_back(p_NinjaStar);
	Mix_PlayChannel(-1, gNinjaFX, 0);
}

void Game::spawnPowerUp() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 150);
	y = (randomY * 120) - 80;
	PowerUp* p_PowerUp = new PowerUp();
	p_PowerUp->spawn(x, y, -randomSpeed);
	listOfPowerUps.push_back(p_PowerUp);
}

// Render the game objects to the screen
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
// Enemies and Obstacles
void EnemyShip::render() {
	gEnemyShipTexture.render(getX(), getY());
}
void EnemyVirus::render() {
	gEnemyVirusTexture.render(getX(), getY());
}
void WhiteBloodCell::render() {
	gWhiteBloodCellTexture.render(getX(), getY(), NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
}
void PowerUp::render() {
	gPowerUpTexture.render(getX(), getY());
}
// Rotating objects
void NinjaStar::render() {
	gNinjaStarTexture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);	// Render Ninja Star to screen
}
void BloodCell::render() {
	//gBloodCell.render(getX(), getY());
	gBloodCellTexture.render(getX(), getY(), NULL, -degreesBC, NULL, SDL_FLIP_NONE);
}
void BloodCellSmall::render() {
	gBloodCellSmallTexture.render(getX(), getY(), NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
}


void GameObject::renderTexture(LTexture ltexture, int x, int y) {
	ltexture.render(x, y);
}




#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
	free();	//Get rid of preexisting texture

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);	//Render text surface
	if (textSurface != NULL) {
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	//Get rid of old surface
	}
	else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	return mTexture != NULL;	// Return success
}
#endif

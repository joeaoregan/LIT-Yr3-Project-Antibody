// 09/01 Edited background to be 800 x 600 instead of 600 * 480

/*
    Game Up To Now - Combined - 2 Player

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
        Joe: Changed getCollision() for ship and enemyship
        Joe: Add relative path for asset files in "Music" and "SoundFX" directories
*/

#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include <sstream>				// For timer

#include <SDL_mixer.h>			// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <cmath>
#include "Game.h"
#include "LTexture.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "EnemyVirus.h"			// 2017/01/10 JOE: Added Seans virus enemy
#include "Laser.h"
#include "NinjaStar.h"
#include "BloodCell.h"			// 2017/01/10 JOE: Added Blood Cell
#include "BloodCellSmall.h"		// 2017/01/10 JOE: Added Small Blood Cell
#include "WhiteBloodCell.h"
#include "PowerUp.h"			// 2017/01/10 SEAN: Added Power Up
#include "LaserEnemy.h"

static const int NUMBER_OF_SONGS = 3;

int player1Alpha = 255;				// Modulation component for flashing objects
int player2Alpha = 255;				// Modulation component for flashing objects
int gameOverAlpha = 255;
int timerAlpha = 255;
bool playerFlash = false;
bool gameOverFlash = true;
bool timerFlash = false;
bool gameOver = false;

int p1Score = 0;					// Game score
int p2Score = 0;

SDL_Event e;						// Event handler

SDL_Joystick* gController1 = NULL;	// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Joystick* gController2 = NULL;	// Game Controller 1 handler - Data type for a game controller is SDL_Joystick

//The music that will be played
Mix_Music *gMusic1 = NULL;		// Mix_Music: Data type for music
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;
unsigned int currentSong;					// Play a random song when the game starts

//The sound effects that will be used (pointers)
Mix_Chunk *gNinjaFX1 = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gNinjaFX2 = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX1 = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX2 = NULL;	// 2017/01/17 Player 2 Laser
Mix_Chunk *gLaserEFX = NULL;	// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gExplosionFX = NULL;

bool init();					// Starts up SDL and creates window
bool loadMedia();				// Loads media//void close();
bool checkCollision(SDL_Rect a, SDL_Rect b);

SDL_Window* gWindow = NULL;		// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;	// The window renderer
Uint8 a = 0;					// Modulation component

int scrollingOffset = 0;		// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)

int degrees = 0;
int degreesBC = 0;				// 2017/01/10 JOE: Added degrees for blood cell rotation
int degreesBCS = 0;
int alphaUp = 5, alphaDown = 5;

// Scene textures
LTexture gBGTexture;			// Background
LTexture gBGStartTexture;
LTexture gBGEndTexture;
LTexture gGameOverTextTexture;
// Objects and weapons
LTexture gPlayer1Texture;		// Player 1 ship
LTexture gPlayer2Texture;		// Player 2 ship
LTexture gEnemyShipTexture;		// Enemy ship
LTexture gEnemyVirusTexture;	// Enemy Virus
LTexture gLaserGreenTexture;	// Texture for Player 1 Laser weapon
LTexture gLaserOrangeTexture;	// Texture for Player 2 Laser weapon
LTexture gLaserBlueTexture;		// Texture for Enemy Laser weapon
LTexture gNinjaStarBlueTexture;	// Texture for Ninja Star weapon
LTexture gNinjaStarYellowTexture; // Texture for Ninja Star weapon
LTexture gBloodCellTexture;		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
LTexture gBloodCellSmallTexture;// Texture for Smaller Blood Cell
LTexture gWhiteBloodCellTexture;// Texture for White Blood Cell
LTexture gPowerUpTexture;		// Texture for Health Box Power Up

LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
LTexture gLevelTextTexture;
LTexture gScoreTextTexture;
LTexture gFinalScoreTextTexture;

#define TIMER 15				// Time to start counting down from in seconds
Uint32 startTime = 6000;		// Unsigned integer 32-bits

TTF_Font *gFont = NULL;			//Globally used font
TTF_Font *gFont2 = NULL;
int font = 0;
//Uint32 startTime = 0;			// Current start time - Unsigned integer 32-bits

// SEAN: Move ship object outside of main so spawnLaser funtion can use it
Ship player1;					// Declare a ship object that will be moving around on the screen
Ship player2;
EnemyShip* enemy1 = new EnemyShip();
EnemyShip* enemy2 = new EnemyShip();
EnemyVirus* virus1 = new EnemyVirus();

std::vector<Mix_Music*> listOfMusic;
std::vector<EnemyShip*> listOfEnemyShips;			// 2017/01/09 JOE: List to store laser objects
//std::list<EnemyShip*>::const_iterator iterES;	// 2017/01/09 JOE: Make them read only
std::vector<EnemyVirus*> listOfEnemyVirus;		// 2017/01/09 JOE: List to store laser objects
//std::list<EnemyVirus*>::const_iterator iterEV;	// 2017/01/09 JOE: Make them read only
std::list<BloodCell*> listOfBloodCells;			// 2017/01/10 JOE: List to store laser objects
std::list<BloodCell*>::const_iterator iterBC;	// 2017/01/10 JOE: Make them read only
std::list<BloodCellSmall*> listOfSmallBloodCells;			// 2017/01/10 JOE: List to store laser objects
std::list<BloodCellSmall*>::const_iterator iterSBC;	// 2017/01/10 JOE: Make them read only
std::list<WhiteBloodCell*> listOfWhiteBloodCells;
std::list<WhiteBloodCell*>::const_iterator iterWBC;
std::vector<PowerUp*> listOfPowerUps;
std::list<LaserEnemy*> listOfEnemyLaserObjects;		// 2017/01/10
std::list<LaserEnemy*>::const_iterator iterEL;		// 2017/01/10
//std::list<PowerUp*>::const_iterator iterPU;
// SEAN : Created list and iterator for laser objects
std::vector<Laser*> listOfLaserObjects;			// List to store laser objects
//std::list<Laser*>::const_iterator iter;			// Make them read only

std::list<NinjaStar*> listOfNinjaStarObjects;	// 2017/01/09 JOE: List to store Ninja Star objects
std::list<NinjaStar*>::const_iterator iterNS;	// 2017/01/09 JOE: Create global iterators to cycle through laser objects - Make them read only


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
	bool success = true;						// Initialization flag

	srand(static_cast<unsigned int>(time(0)));	// Seed the random number

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {	// 2017/01/09 JOE: SOUND - Neet do initialise audio with video
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Check for joysticks
		if (SDL_NumJoysticks() < 1)	{						// check if there is at least one joystick connected.
			printf("Warning: No joysticks connected!\n");
		}
		else {
			//Load joystick
			gController1 = SDL_JoystickOpen(1);			// open the joystick at index 0
			if(SDL_NumJoysticks() > 2)
				gController2 = SDL_JoystickOpen(2);			// open the joystick at index 0
			printf("Joystick connected\n");				// DETECTS JOYSTICK
			if (gController1 == NULL) {
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		// Create window
		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.19 by Joe O'Regan & Se\u00E1n Horgan - Combined Game Features: 2 Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {	// sound frequencey, sample format, hardware channels, sample size
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());	// report errors with SDL_mixer
					success = false;
				}

				Mix_Volume(-1, MIX_MAX_VOLUME);	// sets the volume for all channels MIX_MAX_VOLUME = 128 BALANCES OUT THE VOLUMES A BIT BETTER - LEAVE IN
			}
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;			// Loading success flag

	// Open the font
	//gFont = TTF_OpenFont("22_timing/lazy.ttf", 28);
	gFont = TTF_OpenFont(".\\Font\\lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColor = { 0, 100, 200, 255 };								// Set text color as blue
		TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);								// Use bold font

		if (!gPromptTextTexture.loadFromRenderedText("A Game By Sean Horgan And Joe O'Regan", textColor, 1)) {
			printf("Unable to render prompt text texture!\n");
			success = false;
		}
		if (!gLevelTextTexture.loadFromRenderedText("Level 1", textColor, 1)) {
			printf("Unable to render level text texture!\n");
			success = false;
		}
	}

	//gFont2 = TTF_OpenFont("Fonts/KunstlerScript.ttf", 72);
	gFont2 = TTF_OpenFont(".\\Font\\KunstlerScript.ttf", 72);
	if (gFont2 == NULL) {
		printf("Failed to load kunstler font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
//		SDL_Color textColor = { 0, 100, 200, 255 };
		TTF_SetFontStyle(gFont2, TTF_STYLE_BOLD);							    // Use bold font

	}

	// Load Textures
	if (!gPlayer1Texture.loadFromFile(".\\Art\\Player1Ship.png")) {				// Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile(".\\Art\\Player2Ship.png")) {				// Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gEnemyShipTexture.loadFromFile(".\\Art\\NanobotOld.png")) {			// Enemy Ship Texture
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	if (!gEnemyVirusTexture.loadFromFile(".\\Art\\EnemyVirus.png")) {			// Enemy Virus Texture
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
	if (!gLaserOrangeTexture.loadFromFile(".\\Art\\LaserOrange.png")) {			// Green Laser Texture
		printf("Failed to load Orange Laser texture!\n");
		success = false;
	}
	if (!gLaserBlueTexture.loadFromFile(".\\Art\\LaserBlue.png")) {				// Blue Laser Texture
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}
	if (!gNinjaStarBlueTexture.loadFromFile(".\\Art\\NinjaStarBlue.png")) {			// Ninja Star Texture
		printf("Failed to load Blue Ninja Star texture!\n");
		success = false;
	}
	if (!gNinjaStarYellowTexture.loadFromFile(".\\Art\\NinjaStarYellow.png")) {			// Ninja Star Texture
		printf("Failed to load Yellow Ninja Star texture!\n");
		success = false;
	}
	if (!gGameOverTextTexture.loadFromFile(".\\Art\\GameOver.png")) {		// Game Over Text
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
	gMusic1 = Mix_LoadMUS(".\\Music\\GameSong1.wav");	// Load music
	if (gMusic1 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gMusic2 = Mix_LoadMUS(".\\Music\\GameSong2.mp3");	// Load music
	if (gMusic2 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gMusic3 = Mix_LoadMUS(".\\Music\\GameSong3.mp3");	// Load music
	if (gMusic3 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gNinjaFX1 = Mix_LoadWAV(".\\SoundFx\\Swoosh1.wav");	// Load sound effects
	if (gNinjaFX1 == NULL) {
		printf("Failed to load P1 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gNinjaFX2 = Mix_LoadWAV(".\\SoundFx\\Swoosh2.wav");	// Load sound effects
	if (gNinjaFX2 == NULL) {
		printf("Failed to load P2 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX1 = Mix_LoadWAV(".\\SoundFx\\Laser1.wav");	// Load sound effects
	if (gLaserFX1 == NULL) {
		printf("Failed to load P1 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX2 = Mix_LoadWAV(".\\SoundFx\\Laser2.wav");	// Load sound effects
	if (gLaserFX2 == NULL) {
		printf("Failed to load P2 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserEFX = Mix_LoadWAV(".\\SoundFx\\LaserEnemy.wav");	// Load sound effects
	if (gLaserEFX == NULL) {
		printf("Failed to load enemy laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gExplosionFX = Mix_LoadWAV(".\\SoundFx\\explosion.wav");	// Load sound effects
	if (gExplosionFX == NULL) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Add songs to vector
	listOfMusic.push_back(gMusic1);
	listOfMusic.push_back(gMusic2);
	listOfMusic.push_back(gMusic3);

	currentSong = rand() % 3;						// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);

	return success;
}

void Game::close() {
	// Free loaded images
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gEnemyShipTexture.free();
	gEnemyVirusTexture.free();
	gBGTexture.free();
	gBGStartTexture.free();
	gBGEndTexture.free();
	gGameOverTextTexture.free();

	gLaserGreenTexture.free();
	gLaserOrangeTexture.free();
	gLaserBlueTexture.free();
	gNinjaStarBlueTexture.free();
	gNinjaStarYellowTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();
	gWhiteBloodCellTexture.free();
	gPowerUpTexture.free();

	gTimeTextTexture.free();
	gPromptTextTexture.free();
	gLevelTextTexture.free();
	gScoreTextTexture.free();
	gFinalScoreTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	TTF_CloseFont(gFont2);
	gFont2 = NULL;

	//Free the sound effects
	Mix_FreeChunk(gNinjaFX1);	// Free a sound effect
	Mix_FreeChunk(gNinjaFX2);	// Free a sound effect
	Mix_FreeChunk(gLaserFX1);	// Free a sound effect
	Mix_FreeChunk(gLaserFX2);	// Free a sound effect
	Mix_FreeChunk(gExplosionFX);	// Free a sound effect

	//Free the music
	Mix_FreeMusic(gMusic1);	// Free music
	gMusic1 = NULL;
	Mix_FreeMusic(gMusic2);	// Free music
	gMusic2 = NULL;
	Mix_FreeMusic(gMusic3);	// Free music
	gMusic3 = NULL;


	//Close game controllers
	SDL_JoystickClose(gController1); // After we're done with the joystick, we close it with SDL_JoystickClose.
	gController1 = NULL;
	SDL_JoystickClose(gController2);
	gController2 = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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

			if (SDL_PollEvent(&e) != 0) {

				if (SDL_NumJoysticks() > 0) {
					printf("Joystick connected %d\n", e.jaxis.which);												// DETECTS JOYSTICK
					std::cout << "Number of joystics: " << SDL_NumJoysticks() << std::endl;

					std::cout << "Controller Name: " << SDL_JoystickName(gController1) << std::endl;				// Name of joystick
					std::cout << "Number of buttons: " << SDL_JoystickNumButtons(gController1) << std::endl;		// Number of useable buttons
					std::cout << "Number of axes: " << SDL_JoystickNumAxes(gController1) << std::endl;				// Number of axes on the controller, includes sticks and triggers.
					std::cout << "Number of trackballs: " << SDL_JoystickNumBalls(gController1) << std::endl;		// No trackballs on NVidia Shield Controller
					std::cout << "Number of hats: " << SDL_JoystickNumHats(gController1) << std::endl << std::endl;	// Hats = d-pad on NVidia Shield Controller

					if (SDL_NumJoysticks() > 2) {
						std::cout << "Controller Name: " << SDL_JoystickName(gController2) << std::endl;				// Name of joystick
						std::cout << "Number of buttons: " << SDL_JoystickNumButtons(gController2) << std::endl;		// Number of useable buttons
						std::cout << "Number of axes: " << SDL_JoystickNumAxes(gController2) << std::endl;				// Number of axes on the controller, includes sticks and triggers.
						std::cout << "Number of trackballs: " << SDL_JoystickNumBalls(gController2) << std::endl;		// No trackballs on NVidia Shield Controller
						std::cout << "Number of hats: " << SDL_JoystickNumHats(gController2) << std::endl << std::endl;	// Hats = d-pad on NVidia Shield Controller
					}
				}
			}

			//In memory text stream
			// string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
			std::stringstream timeText;		// string stream
			std::stringstream scoreText;	// string stream
			// While application is running
			while (!quit) {								// While application is running

				flashGameObject(player1Alpha, playerFlash, 10, 4);	// Flash player ship when it has a collision, flash at faster rate, flash 4 times
				flashGameObject(gameOverAlpha, gameOverFlash, 5);	// Flash game over at end of game, flash at slower rate for 5 than 10
				flashGameObject(timerAlpha, timerFlash, 8);			// Flash timer when time is running out

				quit = playerInput(quit);				// 2017/01/09 JOE: Handle input from player


				timeText.str("");									// Set text to be rendered - string stream - print the time since timer last started - initialise empty
				scoreText.str("");

				scoreText << "Score: " << p1Score;

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
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, 1)) {
					printf("Unable to render time texture!\n");
				}
				textColor = { 0, 100, 200, 255 };
				if (!gScoreTextTexture.loadFromRenderedText(scoreText.str().c_str(), textColor, 1)) {
					printf("Unable to render score texture!\n");
				}
				textColor = { 72, 0, 255, 255 };
				if (!gFinalScoreTextTexture.loadFromRenderedText(scoreText.str().c_str(), textColor, 2)) {
					printf("Unable to render score texture!\n");
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
//	SDL_Color textColor = { 0, 0, 0, 255 };	//Set text color as green

	// In memory text stream
	// string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
	//std::stringstream timeText;		// string stream
	while (SDL_PollEvent(&e) != 0) {
		// User requests quit	EXIT - CLOSE WINDOW
		if (e.type == SDL_QUIT) {
			quit = true;
		}// Reset start time on return keypress
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
			startTime = SDL_GetTicks();		// time since the program started in milliseconds
		}
		// Play / Pause music
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				// Play/Pause music on a m key press, stop music on 0
			case SDLK_m:
				if (Mix_PlayingMusic() == 0) {						// If there is no music playing
					Mix_PlayMusic(listOfMusic[currentSong], -1);	// Play the music
				}
				else {												// If music is being played
					if (Mix_PausedMusic() == 1) {					// Check if the music is paused
						Mix_ResumeMusic();							// Resume music
					}
					else {											// If the music is playing
						Mix_PauseMusic();							// Pause the music
					}
				}
				break;
			case SDLK_l:											// Pick next track on the list
				if (currentSong < listOfMusic.size() - 1)
					currentSong++;
				else
					currentSong = 0;

				Mix_PlayMusic(listOfMusic[currentSong], -1);
				break;
			case SDLK_k:											// Pick previous track on the list
				if (currentSong > 0)
					currentSong--;
				else
					currentSong = listOfMusic.size() - 1;

				Mix_PlayMusic(listOfMusic[currentSong], -1);
				break;
			case SDLK_0:
				Mix_HaltMusic();									// Stops music
				break;
			}
		}
		player1.handleEvent(e, 1);									// Handle input for Player 1
		player2.handleEvent(e, 2);									// Handle input for Player 2
	}

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
		gBGEndTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);	// end background


	if (gameOver == false) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SDL_RenderDrawRect(gRenderer, &player1.getCollider());

		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
			(*iterSBC++)->render();	// Render the blood cell
		}

		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
			(*iterWBC++)->render();	// Render the blood cell
		}
		// Cycle through list of Enemy ships and render to screen
		for (unsigned int index = 0; index != listOfEnemyShips.size(); ++index) {
			listOfEnemyShips[index]->render();
			//SDL_RenderDrawRect(gRenderer, &listOfEnemyShips[index]->getCollider());
		}
		// Cycle through list of Enemy Virus and render to screen
		for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
			listOfEnemyVirus[index]->render();
			//SDL_RenderDrawRect(gRenderer, &listOfEnemyVirus[index]->getCollider());
		}
		// Cycle through list of Blood Cells obstacles and render to screen
		for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
			(*iterBC++)->render();	// Render the blood cell
		}

		// Cycle through list of power up objects and render them to screen
		for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
			listOfPowerUps[index]->render();
//			SDL_RenderDrawRect(gRenderer, &listOfPowerUps[index]->getCollider());               ///////////////////////////////////////////////////////////////////
		}

		// Cycle through list of laser objects and render them to screen
		for (unsigned int index = 0; index != listOfLaserObjects.size(); ++index) {
			listOfLaserObjects[index]->render(listOfLaserObjects[index]->getPlayer());
			//SDL_RenderDrawRect(gRenderer, &listOfLaserObjects[index]->getLaserCollider());
		}
		for (iterEL = listOfEnemyLaserObjects.begin(); iterEL != listOfEnemyLaserObjects.end();) {
			(*iterEL++)->render();	// Render the laser
		}
		for (iterNS = listOfNinjaStarObjects.begin(); iterNS != listOfNinjaStarObjects.end();) {
			(*iterNS++)->render((*iterNS)->getPlayer());	// Render the ninja star
		}

		// Render Text
		gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, SCREEN_HEIGHT - gPromptTextTexture.getHeight() - 8);
		gLevelTextTexture.render(10, 8);
		gTimeTextTexture.setAlpha(timerAlpha);	// Flash the timer
		gTimeTextTexture.render(600, 8);
		gScoreTextTexture.render((SCREEN_WIDTH - gScoreTextTexture.getWidth()) / 2, 8);

		// Set the Alpha value for player when flashing
		gPlayer1Texture.setAlpha(player1Alpha);
		player1.render();							// render the ship over the background
		gPlayer2Texture.setAlpha(player2Alpha);
		player2.render();							// render the ship over the background
	}
	else if (gameOver == true) {
		gGameOverTextTexture.setAlpha(gameOverAlpha);
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 300) / 2); // FOR TESTING
		gFinalScoreTextTexture.setAlpha(gameOverAlpha);
		gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2); // FOR TESTING
	}

	SDL_RenderPresent(gRenderer);				// Update screen
}

void Game::moveGameObjects() {
	player1.movement();						// Update ship movement
	player2.movement();

	// Cycle through lists of Enemys and move them
	for (int index = 0; index != listOfEnemyShips.size(); ++index) {
		listOfEnemyShips[index]->movement();
		spawnEnemyLaser(listOfEnemyShips[index]->getX(), listOfEnemyShips[index]->getY());
		//SDL_RenderDrawRect(gRenderer, &listOfLaserObjects[index]->getLaserCollider());
	}
	// Cycle through list of Enemy virus and move them
	for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
		if(abs(listOfEnemyVirus[index]->getX() - player1.getX()) < abs(listOfEnemyVirus[index]->getX() - player2.getX()))	// absolute values to see which is closer on x axis, player1 or 2, and move towards that player
			listOfEnemyVirus[index]->movement(player1.getX(), player1.getY());
		else
			listOfEnemyVirus[index]->movement(player2.getX(), player2.getY());
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
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		if (checkCollision(player1.getCollider(), listOfPowerUps[index]->getCollider()) == true) {
			p1Score += listOfPowerUps[index]->getScore();
			listOfPowerUps[index]->setAlive(false);
			std::cout << "Power Up Picked Up by Player!\n";
		}
	}

	// Cycle through lists of weapons and move them
	for (unsigned int index = 0; index != listOfLaserObjects.size(); ++index) {
		listOfLaserObjects[index]->movement();
		for (unsigned int index1 = 0; index1 != listOfEnemyVirus.size(); ++index1) {
			if (checkCollision(listOfLaserObjects[index]->getLaserCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
				p1Score += listOfEnemyVirus[index1]->getScore();	// Add score to total
				listOfEnemyVirus[index1]->setAlive(false);
				listOfLaserObjects[index]->setAlive(false);
				std::cout << "Enemy Virus Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
		for (unsigned int index2 = 0; index2 != listOfEnemyShips.size(); ++index2) {
			if (checkCollision(listOfLaserObjects[index]->getLaserCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
				p1Score += listOfEnemyShips[index2]->getScore();	// Add score to total
				listOfEnemyShips[index2]->setAlive(false);
				listOfLaserObjects[index]->setAlive(false);
				std::cout << "Enemy Ship Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
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
	for (unsigned int index = 0; index != listOfEnemyShips.size(); ++index) {
		if (!listOfEnemyShips[index]->getAlive()) {
			listOfEnemyShips.erase(listOfEnemyShips.begin() + index);
			std::cout << "Enemy Ship Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
		if (!listOfEnemyVirus[index]->getAlive()) {
			listOfEnemyVirus.erase(listOfEnemyVirus.begin() + index);
			std::cout << "Enemy Virus Destroyed." << std::endl;
			index--;
		}
	}// end for
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
			std::cout << "destroy blood cell" << std::endl;
		}
		else {
			iterWBC++;
		}
	}
	for (unsigned int index = 0; index != listOfLaserObjects.size(); ++index) {
		if (!listOfLaserObjects[index]->getAlive()) {
			listOfLaserObjects.erase(listOfLaserObjects.begin() + index);
			std::cout << "Laser Destroyed." << std::endl;
			index--;
		}
	}// end for
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
	}// end for
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
	if (listOfEnemyVirus.size() < 2) {
		spawnEnemyVirus();
	}
	if (listOfBloodCells.size() <= 5) {
		spawnBloodCell();
	}
	if (listOfSmallBloodCells.size() <= 8) {
		spawnSmallBloodCell();
	}
	if(listOfWhiteBloodCells.size() <= 2) {
		spawnWhiteBloodCell();
	}
	if (listOfPowerUps.size() == 0) {
		spawnPowerUp();
	}
}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 3;

	x = SCREEN_WIDTH + (randomX * 50);
	y = (randomY * 120) - 80;

	//int y = SCREEN_HEIGHT / 2;
	EnemyShip* p_Enemy = new EnemyShip();
	//p_Enemy->spawn(800, y, -5);
	p_Enemy->spawn(x, y, -randomSpeed, p_Enemy->getCollider());
	listOfEnemyShips.push_back(p_Enemy);
}

void Game::spawnEnemyVirus() {
	int x, y, randomX, randomY;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	x = SCREEN_WIDTH + (randomX * 50);
	y = (randomY * 120) - 80;

	EnemyVirus* p_Virus = new EnemyVirus();
	p_Virus->spawn(x, y, -4, -2, p_Virus->getCollider());
	listOfEnemyVirus.push_back(p_Virus);
}

void Game::spawnBloodCell() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 200);
	y = (randomY * 120) - 80;

	BloodCell* p_BloodCell = new BloodCell();
	p_BloodCell->spawn(x, y, -randomSpeed);
	listOfBloodCells.push_back(p_BloodCell);
}
void Game::spawnSmallBloodCell() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 150);
	y = (randomY * 120) - 80;

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
	p_Laser->spawn(player1.getX(), player1.getY(), p_Laser->getLaserCollider());
	listOfLaserObjects.push_back(p_Laser);
	if(!gameOver) Mix_PlayChannel(-1, gLaserFX1, 0);
}
void Game::spawnLaser(int x, int y, int player, int velocity) {
	Laser* p_Laser = new Laser();
	p_Laser->spawn(x + 65, y + 30, velocity);	// adjust spawn position to front of ship
	p_Laser->setPlayer(player);					// 2017/01/17 Set the player the laser belongs too
	listOfLaserObjects.push_back(p_Laser);
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gLaserFX2, 0);
	}
}
void Game::spawnEnemyLaser(int shipX, int shipY) {
	LaserEnemy* p_LaserE = new LaserEnemy();

	if (shipX % 100 == 0) {
		p_LaserE->spawn(shipX, shipY);
		listOfEnemyLaserObjects.push_back(p_LaserE);
		Mix_PlayChannel(-1, gLaserEFX, 0);
	}
}
void Game::spawnNinjaStar(int x, int y, int player) {	// player to spawn for and their coords
	NinjaStar* p_NinjaStar = new NinjaStar();
	p_NinjaStar->spawn(x, y);
	p_NinjaStar->setPlayer(player);					// 2017/01/17 Set the player the laser belongs too
	listOfNinjaStarObjects.push_back(p_NinjaStar);
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gNinjaFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gNinjaFX2, 0);
	}
}

void Game::spawnPowerUp() {
	int x, y, randomX, randomY, randomSpeed;
	randomX = rand() % 5 + 1;
	randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + 1;

	x = SCREEN_WIDTH + (randomX * 150);
	y = (randomY * 120) - 80;
	PowerUp* p_PowerUp = new PowerUp();
	p_PowerUp->spawn(x, y, -randomSpeed);								// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	listOfPowerUps.push_back(p_PowerUp);
}

void Ship::render() {
	gPlayer1Texture.render(player1.getX(), player1.getY());				// Show the ship
	gPlayer2Texture.render(player2.getX(), player2.getY());				// Show the ship
}

// Render the laser objects to the screen
void Laser::render(int player) {
	if (player == 1)
		gLaserOrangeTexture.render(getX(), getY());
	else if (player == 2)
		gLaserGreenTexture.render(getX(), getY());
}
void LaserEnemy::render() {
	gLaserBlueTexture.render(getX(), getY());
}
/* Render the laser objects to the screen*/
void NinjaStar::render(int player) {
	if(player == 1)
		gNinjaStarYellowTexture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
	else if (player == 2)
		gNinjaStarBlueTexture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
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
void WhiteBloodCell::render() {
	gWhiteBloodCellTexture.render(getX(), getY(), NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
}
void PowerUp::render() {
	gPowerUpTexture.render(getX(), getY());
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

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

	std::cout << "Collision!\n";

	//Handle ship collision with enemy (MOVE TO SEPERATE FUNCTION)
	/*ship.setShipX(ship.getShipX() - ship.getShipVelX());
	ship.setShipColX(ship.getShipX());

	ship.setShipY(ship.getShipY() - ship.getShipVelY());
	ship.setShipColY(ship.getShipY());*/

	//If none of the sides from A are outside B
	return true;
}

SDL_Surface* textSurface;

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, int font) {
	free();	//Get rid of preexisting texture

	if (font == 1)
		textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);	//Render text surface
	if (font == 2)
		textSurface = TTF_RenderText_Solid(gFont2, textureText.c_str(), textColor);	//Render text surface


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

// 09/01 Edited background to be 800 x 600 instead of 600 * 480
// 2017/01/23 set up levels and background

/*
    Moved Render Functions, Fixed Saw

    2017-08-11:
        Joe: Change window title
        Joe: Add relative path for asset files in "Art" directory
        Joe: Changed getCollision() for ship and enemyship
        Joe: Add relative path for asset files in "Music" and "SoundFX" directories
*/

#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include <sstream>					// For timer
#include <string.h>

#include <SDL_mixer.h>				// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <cmath>
#include "Game.h"
#include "LTexture.h"
#include "Player.h"
#include "EnemyShip.h"
#include "EnemyVirus.h"				// 2017/01/10 JOE: Added Seans virus enemy
#include "Laser.h"
#include "NinjaStar.h"
#include "Saw.h"					// 2017/01/17 Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell
#include "BloodCellSmall.h"			// 2017/01/10 JOE: Added Small Blood Cell
#include "WhiteBloodCell.h"
#include "PowerUp.h"				// 2017/01/10 SEAN: Added Power Up
#include "LaserEnemy.h"
#include "Particle.h"

#define SPAWN_NUM_ENEMY_SHIPS 1			// WAS 2
#define SPAWN_NUM_ENEMY_VIRUS 1			// WAS 2
#define SPAWN_NUM_BLOOD_CELL 4			// WAS 6
#define SPAWN_NUM_BLOOD_CELL_S 5		// WAS 9
#define SPAWN_NUM_BLOOD_CELL_WHITE 2	// WAS 3
#define SPAWN_NUM_POWER_UPS 1

// Particles
LTexture gDarkBlueParticleTexture;
LTexture gMediumBlueParticlTexture;
LTexture gLightBlueParticleTexture;
LTexture gShimmerTexture;

// Render Healthbars
enum healthBarOrientation { VERTICAL, HORIZONTAL };
void renderHealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation);	// 2017/01/20 Added orientation

#define PLAYER_1 1
#define PLAYER_2 2
#define NUM_PLAYERS 2
#define BACKGROUND_SCROLL_TIMES 5
#define MAX_HEALTH 100.0
#define GAME_TIMER 15				// Time to start counting down from in seconds
#define NUMBER_OF_SONGS = 3;

// Time
Uint32 startTime = 6000;			// Unsigned integer 32-bits
unsigned int lastTime = 0, currentTime, countdownTimer = GAME_TIMER;	// TEST TIMING

// Scrolling and Rotation
int degrees = 0;
int degreesBC = 0;					// 2017/01/10 JOE: Added degrees for blood cell rotation
int degreesBCS = 0;

int backgroundLoopCounter = 0;
int scrollingOffset = 0;			// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)
int scrollingOffsetLogo = 600;		// Scrolling offset for splash screens

// FPS
#define FRAME_VALUES 10
Uint32 frametimes[FRAME_VALUES];	// An array to store frame times:
Uint32 frametimelast;				// Last calculated SDL_GetTicks
Uint32 framecount;					// total frames rendered
float framespersecond;				// the value you want
void fpsinit();
void fpsthink();

// Animation
bool displayLogo = true;
int frame = 0, frameUp = 0, frameDown = 0;											// Current animation frame
const int ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[6];
SDL_Rect gEnemySpriteClips[ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;
LTexture gEnemySpriteSheetTexture;
int enemyframe = 0;

// Alpha values for flashing objects
int player1Alpha = 255;				// Modulation component for flashing objects
int player2Alpha = 255;				// Modulation component for flashing objects
int gameOverAlpha = 255;
int timerAlpha = 255;

bool player1Flash = false;
bool player2Flash = false;
bool gameOverFlash = true;
bool timerFlash = false;
int alphaUp = 5, alphaDown = 5;

SDL_Event e;						// Event handler

// Joystick
SDL_Joystick* gController1 = NULL;	// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Joystick* gController2 = NULL;	// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Haptic*	gControllerHaptic = NULL;	// 2017/01/18 Haptic (Force Feedback) added

//The music that will be played
Mix_Music *gMusic1 = NULL;			// Mix_Music: Data type for music
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;
int currentSong;					// Play a random song when the game starts

//The sound effects that will be used (pointers)
Mix_Chunk *gNinjaFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gNinjaFX2 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX2 = NULL;		// 2017/01/17 Player 2 Laser
Mix_Chunk *gLaserEFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gExplosionFX = NULL;
Mix_Chunk *gSawFX = NULL;

bool init();						// Starts up SDL and creates window
bool loadMedia();					// Loads media//void close();
bool checkCollision(SDL_Rect a, SDL_Rect b);

SDL_Window* gWindow = NULL;			// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;		// The window renderer
Uint8 a = 0;						// Modulation component

// Text
SDL_Color textColor;
TTF_Font *gFont = NULL;				// Globally used font
TTF_Font *gFont2 = NULL;
std::string l1Objective = "Destroy enemy virus and ships\nThe player with the highest score\nIs the winner";

//Player player1;						// SEAN: Move ship object outside of main so spawnLaser funtion can use it
//Player player2;						// Declare a ship object that will be moving around on the screen

// Scene textures
LTexture gBGTexture;				// Background
LTexture gBGStartTexture;
LTexture gBGEndTexture;
LTexture gGameOverTextTexture;
// Objects and weapons
LTexture gPlayer1Texture;			// Player 1 ship
LTexture gP1LivesTexture;			// Player 1 Small ship for number of lives
LTexture gPlayer2Texture;			// Player 2 ship
LTexture gP2LivesTexture;			// Player 2 Small Ship for number of lives
LTexture gEnemyVirusTexture;		// Enemy Virus
LTexture gLaserGreenTexture;		// Texture for Player 1 Laser weapon
LTexture gLaserOrangeTexture;		// Texture for Player 2 Laser weapon
LTexture gLaserBlueTexture;			// Texture for Enemy Laser weapon
LTexture gNinjaStarBlueTexture;		// Texture for Ninja Star weapon
LTexture gNinjaStarYellowTexture;	// Texture for Ninja Star weapon
LTexture gSawTexture;				// Texture for Ninja Star weapon
LTexture gBloodCellTexture;			// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
LTexture gBloodCellSmallTexture;	// Texture for Smaller Blood Cell
LTexture gWhiteBloodCellTexture;	// Texture for White Blood Cell
LTexture gPowerUpTexture;			// Texture for Health Box Power Up
// Splash Screens / Logos
LTexture gLogo1;					// 2017/01/18 Texture for game Splash Screen 1
LTexture gLogo2;					// 2017/01/18 Texture for game Splash Screen 2
LTexture gLevel1;					// 2017/01/18 Texture for level Splash Screen 1
LTexture gLevel2;					// 2017/01/18 Texture for level Splash Screen 2
LTexture gLevel3;					// 2017/01/18 Texture for level Splash Screen 3

LTexture gTimeTextTexture;
LTexture gCreatedByTextTexture;
LTexture gLevelTextTexture;
LTexture gP1ScoreTextTexture;
LTexture gP2ScoreTextTexture;
LTexture gFPSTextTexture;
LTexture gFinalScoreTextTexture;
LTexture gGameWinnerTextTexture;
LTexture gLevel1ObjectiveTextTexture;

// Vectors for objects that have collisions
std::vector<PowerUp*> listOfPowerUps;
std::vector<LaserEnemy*> listOfEnemyLaserObjects;		// 2017/01/10
std::vector<Laser*> listOfLaserObjects;					// List to store laser object
std::vector<Mix_Music*> listOfMusic;					// List of Music tracks
std::vector<EnemyShip*> listOfEnemyShips;				// 2017/01/09 JOE: List to store laser objects
std::vector<EnemyVirus*> listOfEnemyVirus;				// 2017/01/09 JOE: List to store laser objects
std::vector<NinjaStar*> listOfNinjaStarObjects;			// 2017/01/09 JOE: List to store Ninja Star objects

// Lists - objects with no collisions (yet)
std::list<BloodCell*> listOfBloodCells;					// 2017/01/10 JOE: List to store laser objects
std::list<BloodCell*>::const_iterator iterBC;			// 2017/01/10 JOE: Make them read only
std::list<BloodCellSmall*> listOfSmallBloodCells;		// 2017/01/10 JOE: List to store laser objects
std::list<BloodCellSmall*>::const_iterator iterSBC;		// 2017/01/10 JOE: Make them read only
std::list<Saw*> listOfSawObjects;						// 2017/01/17: List to store Saw objects
std::list<Saw*>::const_iterator iterSaw;				// 2017/01/17: Create global iterators to cycle through Saw objects - Make them read only
std::list<WhiteBloodCell*> listOfWhiteBloodCells;
std::list<WhiteBloodCell*>::const_iterator iterWBC;
//std::list<LaserEnemy*>::const_iterator iterEL;		// 2017/01/10 Make them read only
//std::list<PowerUp*>::const_iterator iterPU;s
//std::list<Laser*>::const_iterator iter;
//std::list<EnemyVirus*>::const_iterator iterEV;
//std::list<EnemyShip*>::const_iterator iterES;
//std::list<NinjaStar*> listOfNinjaStarObjects;			// 2017/01/09 JOE: List to store Ninja Star objects
//std::list<NinjaStar*>::const_iterator iterNS;			// 2017/01/09 JOE: Create global iterators to cycle through laser objects - Make them read only

Player player1(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);
Player player2(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);

bool init() {
	// Test Player stuff
	//Player player1(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);

	std::cout << player1.getName() << "! Health: " << player1.getHealth() << " " << player2.getName() << "! Health: " << player2.getHealth();
	player1.setName("Player 1");
	player2.setName("Player 2");

	bool success = true;						// Initialization flag

	srand(static_cast<unsigned int>(time(0)));	// Seed the random number

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0) {	// 2017/01/09 JOE: SOUND - Neet do initialise audio with video
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

			// NEEDS TO BE 0 FOR XBOX CONTROLLER, NEEDS A CHECK FOR NVIDIA CONTROLLER, AS ITS TAKING UP TWO CONTROLLER SLOTS
			//if (strcmp(SDL_JoystickName(gController1), "NVIDIA Shield") == 0) {
				gController1 = SDL_JoystickOpen(0);			// open the joystick at index 1
			//}
			//else 	gController1 = SDL_JoystickOpen(0);

			if (SDL_NumJoysticks() == 2)
				gController2 = SDL_JoystickOpen(1);
			else if(SDL_NumJoysticks() > 2)
				gController2 = SDL_JoystickOpen(2);			// open the joystick at index 0

			printf("Joystick connected\n");				// DETECTS JOYSTICK
			if (gController1 == NULL) {
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
			else{
				//Get controller haptic device
				gControllerHaptic = SDL_HapticOpenFromJoystick(gController1);
				if (gControllerHaptic == NULL) {
					printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
				}
				else {
					//Get initialize rumble
					if (SDL_HapticRumbleInit(gControllerHaptic) < 0) {
						printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
					}
				}
			}
		}

		// Create window
		gWindow = SDL_CreateWindow("JOURNEY TO THE CENTER OF MY HEADACHE v1.31 by Joe O'Regan & Se\u00E1n Horgan: Moved Render Functions, Fixed Saw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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

	// Particles
	//Load Dark Particle texture
	if (!gDarkBlueParticleTexture.loadFromFile(".\\Art\\particleDarkBlue.bmp", gRenderer)) {
		printf("Failed to load red texture!\n");
		success = false;
	}
	//Load Medium Particle texture
	if (!gMediumBlueParticlTexture.loadFromFile(".\\Art\\particleMediumBlue.bmp", gRenderer)) {
		printf("Failed to load green texture!\n");
		success = false;
	}
	//Load Light Particle texture
	if (!gLightBlueParticleTexture.loadFromFile(".\\Art\\particleLightBlue.bmp", gRenderer)) {
		printf("Failed to load blue texture!\n");
		success = false;
	}
	//Load shimmer texture
	if (!gShimmerTexture.loadFromFile(".\\Art\\shimmer.bmp", gRenderer)) {
		printf("Failed to load shimmer texture!\n");
		success = false;
	}

	//Set texture transparency
	gDarkBlueParticleTexture.modifyAlpha(150);	// Alpha of 192 gives particles a semi transparent look
	gMediumBlueParticlTexture.modifyAlpha(150);
	gLightBlueParticleTexture.modifyAlpha(150);
	gShimmerTexture.modifyAlpha(150);

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

		if (!gCreatedByTextTexture.loadFromRenderedText("A Game By Sean Horgan And Joe O'Regan", textColor, gFont, gRenderer)) {
			printf("Unable to render prompt text texture!\n");
			success = false;
		}
		if (!gLevelTextTexture.loadFromRenderedText("Level 1", textColor, gFont, gRenderer)) {
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
		SDL_Color textColor = { 0, 100, 200, 255 };
		TTF_SetFontStyle(gFont2, TTF_STYLE_BOLD);											// Use bold font
	}

	// Load Textures
	if (!gPlayer1Texture.loadFromFile(".\\Art\\Player1Ship.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile(".\\Art\\Player2Ship.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gP1LivesTexture.loadFromFile(".\\Art\\Player1ShipSmall.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
	if (!gP2LivesTexture.loadFromFile(".\\Art\\Player2ShipSmall.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	}
	if (!gEnemyVirusTexture.loadFromFile(".\\Art\\EnemyVirus.png", gRenderer)) {				// Enemy Virus Texture
		printf("Failed to load Enemy Virus texture!\n");
		success = false;
	}
	if (!gBloodCellTexture.loadFromFile(".\\Art\\BloodCell.png", gRenderer)) {					// 10/01 Added Large Blood Cell
		printf("Failed to load Blood Cell texture!\n");
		success = false;
	}
	if (!gBloodCellSmallTexture.loadFromFile(".\\Art\\BloodCellSmall.png", gRenderer)) {		// 10/01 Added Small Blood Cell
		printf("Failed to load Small Blood Cell texture!\n");
		success = false;
	}
	if (!gBGTexture.loadFromFile(".\\Art\\Background800.png", gRenderer)) {						// 09/01 Edited background to be 800 x 600 instead of 600 * 480
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gBGStartTexture.loadFromFile(".\\Art\\bgBegin.png", gRenderer)) {						// Background start texture
		printf("Failed to load start background texture!\n");
		success = false;
	}
	if (!gBGEndTexture.loadFromFile(".\\Art\\bgEnd.png", gRenderer)) {							// Background end texture
		printf("Failed to load end background texture!\n");
		success = false;
	}
	if (!gLaserGreenTexture.loadFromFile(".\\Art\\LaserGreen.png", gRenderer)) {				// Green Laser Texture
		printf("Failed to load Green Laser texture!\n");
		success = false;
	}
	if (!gLaserOrangeTexture.loadFromFile(".\\Art\\LaserOrange.png", gRenderer)) {				// Green Laser Texture
		printf("Failed to load Orange Laser texture!\n");
		success = false;
	}
	if (!gLaserBlueTexture.loadFromFile(".\\Art\\LaserBlue.png", gRenderer)) {					// Blue Laser Texture
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}
	if (!gNinjaStarBlueTexture.loadFromFile(".\\Art\\NinjaStarBlue.png", gRenderer)) {			// Ninja Star Texture
		printf("Failed to load Blue Ninja Star texture!\n");
		success = false;
	}
	if (!gNinjaStarYellowTexture.loadFromFile(".\\Art\\NinjaStarYellow.png", gRenderer)) {		// Ninja Star Texture
		printf("Failed to load Yellow Ninja Star texture!\n");
		success = false;
	}
	if (!gSawTexture.loadFromFile(".\\Art\\SawBlue.png", gRenderer)) {							// Ninja Star Texture
		printf("Failed to load Blue Saw texture!\n");
		success = false;
	}
	if (!gGameOverTextTexture.loadFromFile(".\\Art\\GameOver.png", gRenderer)) {				// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}
	if (!gWhiteBloodCellTexture.loadFromFile(".\\Art\\WhiteCell.png", gRenderer)) {				// 10/01 Added Blood Cell
		printf("Failed to load White Blood Cell texture!\n");
		success = false;
	}
	if (!gPowerUpTexture.loadFromFile(".\\Art\\HealthBox.png", gRenderer)) {					// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Health Box texture!\n");
		success = false;
	}
	if (!gLogo1.loadFromFile(".\\Art\\Logo1.png", gRenderer)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Logo 1 texture!\n");
		success = false;
	}
	if (!gLogo2.loadFromFile(".\\Art\\Logo2.png", gRenderer)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Logo 2 texture!\n");
		success = false;
	}
	if (!gLevel1.loadFromFile(".\\Art\\Level1.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (!gLevel2.loadFromFile(".\\Art\\Level2.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (!gLevel3.loadFromFile(".\\Art\\Level3.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 3 texture!\n");
		success = false;
	}

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile(".\\Animation\\PressEnterSpriteSheet.png", gRenderer)) {	// Sprite sheet for Press Enter Button
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else {
		// Set sprite clips 19/01/2017 Added for loop
		for (int i = 0; i < 6; ++i) {
			gSpriteClips[i].x = 0;
			if(i < 4)
				gSpriteClips[i].y = i * 94;
			else if (i == 4)
				gSpriteClips[i].y = 188;
			else if (i == 5)
				gSpriteClips[i].y = 94;
			gSpriteClips[i].w = 718;
			gSpriteClips[i].h = 94;
		}
	}

	if (!gEnemySpriteSheetTexture.loadFromFile(".\\Animation\\EnemySpriteSheet2.png", gRenderer)) {	// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Ship animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (int i = 0; i < 4; ++i) {
			gEnemySpriteClips[i].x = 0;
			gEnemySpriteClips[i].y = i * 50;
			gEnemySpriteClips[i].w = 120;
			gEnemySpriteClips[i].h = 50;
		}
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
	gNinjaFX1 = Mix_LoadWAV(".\\SoundFX\\Swoosh1.wav");	// Load sound effects
	if (gNinjaFX1 == NULL) {
		printf("Failed to load P1 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gNinjaFX2 = Mix_LoadWAV(".\\SoundFX\\Swoosh2.wav");	// Load sound effects
	if (gNinjaFX2 == NULL) {
		printf("Failed to load P2 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX1 = Mix_LoadWAV(".\\SoundFX\\Laser1.wav");	// Load sound effects
	if (gLaserFX1 == NULL) {
		printf("Failed to load P1 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX2 = Mix_LoadWAV(".\\SoundFX\\Laser2.wav");	// Load sound effects
	if (gLaserFX2 == NULL) {
		printf("Failed to load P2 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserEFX = Mix_LoadWAV(".\\SoundFX\\LaserEnemy.wav");	// Load sound effects
	if (gLaserEFX == NULL) {
		printf("Failed to load enemy laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gExplosionFX = Mix_LoadWAV(".\\SoundFX\\explosion.wav");	// Load sound effects
	if (gExplosionFX == NULL) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gSawFX = Mix_LoadWAV(".\\SoundFX\\Saw.wav");	// Load sound effects
	if (gSawFX == NULL) {
		printf("Failed to load Saw sound effect! SDL_mixer Error: %s\n", Mix_GetError());
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
	// Particles
	gDarkBlueParticleTexture.free();
	gMediumBlueParticlTexture.free();
	gLightBlueParticleTexture.free();
	gShimmerTexture.free();

	// Free loaded images
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gP1LivesTexture.free();
	gP2LivesTexture.free();
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
	gSawTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();
	gWhiteBloodCellTexture.free();
	gPowerUpTexture.free();
	gLogo1.free();
	gLogo2.free();
	gLevel1.free();
	gLevel2.free();
	gLevel3.free();
	// free animations
	gSpriteSheetTexture.free();
	gEnemySpriteSheetTexture.free();

	gTimeTextTexture.free();
	gCreatedByTextTexture.free();
	gLevelTextTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();
	gFPSTextTexture.free();
	gFinalScoreTextTexture.free();
	gGameWinnerTextTexture.free(); // gLevel1ObjectiveTextTexture
	gLevel1ObjectiveTextTexture.free();

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
	Mix_FreeChunk(gSawFX);	// Free a sound effect

	//Free the music
	Mix_FreeMusic(gMusic1);	// Free music
	gMusic1 = NULL;
	Mix_FreeMusic(gMusic2);	// Free music
	gMusic2 = NULL;
	Mix_FreeMusic(gMusic3);	// Free music
	gMusic3 = NULL;

	//Close game controllers
	SDL_HapticClose(gControllerHaptic);	// Finished with Haptic device
	SDL_JoystickClose(gController1); // After we're done with the joystick, we close it with SDL_JoystickClose.
	gController1 = NULL;
	SDL_JoystickClose(gController2);
	gController2 = NULL;
	gControllerHaptic = NULL;

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

void Game::update(){
	// Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	} else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			//Player player1(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);

			bool quit = false;							// Main loop flag

			if (SDL_PollEvent(&e) != 0) {
				gamepadInfo();							// Display gamepad information
			}
			// MAIN GAME LOOP:  While application is running
			while (!quit) {								// While application is running
				//if (player1.getAlive() && player2.getAlive() && player1.getNumLives() > 0 && player2.getNumLives() > 0) gameOver = true;
				//else gameOver = false;
				// Test game over
				//gameOver = true;

				quit = playerInput(quit);				// 2017/01/09 JOE: Handle input from player

				if (displayLogo) displayGameLogos();	// 2017/01/18 Splash screens at start of game

				//fpsthink();

				//if (player1.getAlive() && player2.getAlive()) gameOver = true;

				if(!gameOver) spawnMovingObjects();		// 2017/01/10 JOE: Spawn enemies and obstacles at random coords and distances apart

				renderGameObjects();					// 2017-01-09 JOE: Render the game objects to the screen

				if(!gameOver) moveGameObjects();		// 2017-01-09 JOE: Move the game objects on the screen

				collisionCheck();

				destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen
			}
		}
	}
}

void Game::pressButtonToContinue() {
	bool continueGame = false;
	//std::cout << "Press Button To Continue" << std::endl;

	SDL_Rect* currentClip = &gSpriteClips[frame / 6];	// Render current frame
	gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2 + 200, gRenderer, currentClip);

	SDL_RenderPresent(gRenderer);			// Update screen
	++frame;	// Go to next frame

	if (frame / 6 >= ANIMATION_FRAMES) {	// Cycle animation
		frame = 0;
	}
	/*
	if (frameUp < 3) {
		++frameUp;
		std::cout << "Frame: " << frame << std::endl;
		++frame;
		if (frameUp == 3)  frameDown = 3;
	}
	if (frameDown >= 0) {
		--frameDown;
		std::cout << "Frame: " << frame << std::endl;
		--frame;
		if (frameDown <= 0 ) frameUp = 0;
	}
	*/
	//SDL_RenderPresent(gRenderer);			// Update screen SDL_PollEvent

	//while (SDL_WaitEvent(&e)) {
	while (SDL_PollEvent(&e)) {
		//std::cout << "test 1" << std::endl;

		switch (e.type) {
			std::cout << "test 2" << std::endl;
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
		case SDL_KEYDOWN:
			printf("Key press detected\n");
			continueGame = true;
			std::cout << "test 3" << std::endl;
			break;
			//if (e.type == SDL_JOYBUTTONDOWN) {
		}
		//std::cout << "test 4" << std::endl;
		break;
	}

	if (!continueGame) pressButtonToContinue();
}

void Game::displayGameLogos() {
	/*
	// Clear screen
	//if (scrollingOffsetLogo == 600) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gLogo1.render(0, 0, gRenderer);

		SDL_RenderPresent(gRenderer);			// Update screen
		SDL_Delay(1000);						// Pause with image on screen
	//}

	while (scrollingOffsetLogo >= 0) {
		gLogo2.render(0, scrollingOffsetLogo, gRenderer);
		scrollingOffsetLogo -= 10;

		SDL_RenderPresent(gRenderer);			// Update screen
	}

	SDL_Delay(1000);						// Pause with image on screen

	scrollingOffsetLogo = -600;				// Logo will start above window

	while (scrollingOffsetLogo <= 0) {
		gLevel1.render(0, scrollingOffsetLogo, gRenderer);
		scrollingOffsetLogo += 5;

		SDL_RenderPresent(gRenderer);			// Update screen
	}
	*/

	scrollingOffsetLogo = 600;				// Texture will start below window

	textColor = { 255, 255, 255, 255 };

	if (!gLevel1ObjectiveTextTexture.loadFromRenderedText(l1Objective, textColor, gFont, gRenderer, true)) { // gLevel1ObjectiveTextTexture
		printf("Unable to render level 1 game objective texture!\n");
	}

	while (scrollingOffsetLogo >= 300) {
		SDL_RenderClear(gRenderer);
		gLevel1.render(0, 0, gRenderer);										// Static background

		scrollingOffsetLogo -= 5;
		gLevel1ObjectiveTextTexture.render(100, scrollingOffsetLogo, gRenderer); // FOR TESTING

		SDL_RenderPresent(gRenderer);			// Update screen
	}

	pressButtonToContinue();

	displayLogo = false;
}

void Game::gamepadInfo() {
	if (SDL_NumJoysticks() > 0) {
		if (strcmp(SDL_JoystickName(gController1), "NVIDIA Shield") == 0) {
			std::cout << "nv test" << std::endl;
			// put test here to make NVIDIA Shield controller as 2 controllers
		}

		std::cout << "joystick instance id: " << SDL_JoystickInstanceID(gController1) << std::endl;

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			const char *name = SDL_GameControllerNameForIndex(i);
			if (name) {
				printf("Joystick %i has game controller name '%s'\n", i, name);
			}
			else {
				printf("Joystick %i has no game controller name.\n", i);
			}
		}

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

void Game::displayText() {
	// Splash Screen
	textColor = { 72, 0, 255, 255 };

	if (!gLevel1ObjectiveTextTexture.loadFromRenderedText(l1Objective, textColor, gFont2, gRenderer)) { // gLevel1ObjectiveTextTexture
		printf("Unable to render level 1 game objective texture!\n");
	}

	//In memory text stream - string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
	std::stringstream timeText;		// string stream
	std::stringstream score1Text;	// string stream
	std::stringstream score2Text;	// string stream
	std::string finalScores;
	std::string gameWinner;
	std::stringstream framesPerSec;

	timeText.str("");				// Set text to be rendered - string stream - print the time since timer last started - initialise empty
	score1Text.str("");
	score2Text.str("");
	framesPerSec.str("");
	framesPerSec << "FPS: " << framespersecond;
	score1Text << "P1: " << player1.getScore();
	score2Text << "P2: " << player2.getScore();
	finalScores = "Player 1: " + std::to_string(player1.getScore()) + " Player 2: " + std::to_string(player2.getScore());


	// Game Over
	if (gameOver == true) {
		if (player1.getScore() > player2.getScore())
			gameWinner = "Player 1 Wins";
		else if (player2.getScore() > player1.getScore())
			gameWinner = "Player 2 Wins";
		else
			gameWinner = "It's a draw";

		textColor = { 72, 0, 255, 255 };
		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScores, textColor, gFont2, gRenderer)) {
			printf("Unable to render final scores texture!\n");
		}
		if (!gGameWinnerTextTexture.loadFromRenderedText(gameWinner, textColor, gFont2, gRenderer)) {
			printf("Unable to render game winner texture!\n");
		}
	}
	// Levels
	else {
		currentTime = SDL_GetTicks();

		// Countdown Timer


		//if (countdownTimer > GAME_TIMER && countdownTimer < GAME_TIMER + 6) {
		//	timeText << "Game Over";
		//	gameOver = true;
		//}
		//else
		if (countdownTimer >= 0 && countdownTimer <= GAME_TIMER) {
			timeText << "Time: " << countdownTimer;
			gameOver = false;
		}
		if (countdownTimer <= 0 || countdownTimer > GAME_TIMER + 6) {
			timeText << "Game Over";
			gameOver = true;
			//countdownTimer = GAME_TIMER + 5;	// flash game over for 5 seconds
		}

		if (currentTime > lastTime + 1000) {
			lastTime = currentTime;
			countdownTimer -= 1;
			//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
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
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gFont, gRenderer)) {
			printf("Unable to render time texture!\n");
		}
		textColor = { 0, 100, 200, 255 };
		if (!gP1ScoreTextTexture.loadFromRenderedText(score1Text.str().c_str(), textColor, gFont, gRenderer)) {
			printf("Unable to render P1 score texture!\n");
		}
		if (!gP2ScoreTextTexture.loadFromRenderedText(score2Text.str().c_str(), textColor, gFont, gRenderer)) {
			printf("Unable to render P2 score texture!\n");
		}
		if (!gFPSTextTexture.loadFromRenderedText(framesPerSec.str().c_str(), textColor, gFont, gRenderer)) {
			printf("Unable to render FPS texture!\n");
		}
	}
}

bool Game::playerInput(bool quit = false) {
	SDL_Color textColor = { 0, 0, 0, 255 };	//Set text color as green

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
			case SDLK_l:
				musicForward();										// Pick next track on the list
				break;
			case SDLK_k:
				musicBack();										// Pick previous track on the list
				break;
			case SDLK_0:
				Mix_HaltMusic();									// Stops music
				break;
			}
		}
		//Joystick button press
		else if (e.type == SDL_JOYBUTTONDOWN) {
			//Play rumble at 75% strenght for 500 milliseconds
			if (SDL_HapticRumblePlay(gControllerHaptic, 0.5, 200) != 0) {
				printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
			}
		}

		player1.handleEvent(e, 1);									// Handle input for Player 1
		player2.handleEvent(e, 2);									// Handle input for Player 2
	}

	return quit;
}

void Game::musicForward() {								// Pick next track on the list
	if (currentSong + 1 < listOfMusic.size())			// If the current song number (0 number start value) is less than the number of tracks on the list
		currentSong++;									// go to next track on list
	else
		currentSong = 0;								// or else go back to start of list

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}
void Game::musicBack() {								// Pick previous track on the list
	if (currentSong > 0)
		currentSong--;
	else
		currentSong = listOfMusic.size() - 1;

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}

void Game::renderGameObjects() {
	//gameOver = true;

	degrees += 5;										// Number of degrees to rotate spinning objects
	degrees %= 360;
	degreesBC += 1;										// Number of degrees to rotate spinning objects
	degreesBC %= 360;
	degreesBCS += 2;									// Number of degrees to rotate spinning objects
	degreesBCS %= 360;

	displayText();										// 2017/01/17: Display the game text

	flashGameObject(player1Alpha, player1Flash, 10, 4);	// Flash player ship when it has a collision, flash at faster rate, flash 4 times
	flashGameObject(player2Alpha, player2Flash, 10, 4);	// Flash player ship when it has a collision, flash at faster rate, flash 4 times

	flashGameObject(gameOverAlpha, gameOverFlash, 5);	// Flash game over at end of game, flash at slower rate for 5 than 10
	flashGameObject(timerAlpha, timerFlash, 8);			// Flash timer when time is running out

	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);



	if (gameOver == false) {

		fpsthink();										// No need to do this if the game is over

		if (backgroundLoopCounter <= BACKGROUND_SCROLL_TIMES) scrollingOffset -= 5;
		if (scrollingOffset < -gBGTexture.getWidth()) {
			scrollingOffset = 0;							// update the scrolling background

			backgroundLoopCounter++;						// count the number of times the background has looped
			std::cout << "Background has looped " << backgroundLoopCounter << " times" << std::endl;
		}

		// Render background
		if (backgroundLoopCounter < 1)
			gBGStartTexture.render(scrollingOffset, 0, gRenderer);			// 1st
		else if (backgroundLoopCounter > BACKGROUND_SCROLL_TIMES)
			gBGEndTexture.render(scrollingOffset, 0, gRenderer);			// end background
		else
			gBGTexture.render(scrollingOffset, 0, gRenderer);				// 3rd and every odd number

		if (backgroundLoopCounter < BACKGROUND_SCROLL_TIMES)
			gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0, gRenderer);		// 2nd background (and every even number)
		else
			gBGEndTexture.render(scrollingOffset + gBGTexture.getWidth(), 0, gRenderer);	// end background




	//if (gameOver == false) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_RenderDrawRect(gRenderer, &player1.getCollider());

		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
			(*iterSBC++)->render(gBloodCellSmallTexture, gRenderer, -degreesBCS);	// Render the blood cell
		}

		// Cycle through list of small Blood Cells obstacles and render to screen
		for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
			(*iterWBC++)->render(gWhiteBloodCellTexture, gRenderer, -degreesBCS);	// Render the blood cell
		}
		// Cycle through list of Enemy ships and render to screen
		for (int index = 0; index != listOfEnemyShips.size(); ++index) {
			listOfEnemyShips[index]->render(gEnemySpriteSheetTexture, gRenderer, &gEnemySpriteClips[enemyframe / 10], enemyframe);
			//SDL_RenderDrawRect(gRenderer, &listOfEnemyShips[index]->getCollider());
		}
		// Cycle through list of Enemy Virus and render to screen
		for (int index = 0; index != listOfEnemyVirus.size(); ++index) {
			listOfEnemyVirus[index]->render(gEnemyVirusTexture, gRenderer);
			//SDL_RenderDrawRect(gRenderer, &listOfEnemyVirus[index]->getCollider());
		}
		// Cycle through list of Blood Cells obstacles and render to screen
		for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
			(*iterBC++)->render(gBloodCellTexture, gRenderer, -degreesBC);	// Render the blood cell
		}

		// Cycle through list of power up objects and render them to screen
		for (int index = 0; index != listOfPowerUps.size(); ++index) {
			listOfPowerUps[index]->render(gPowerUpTexture, gRenderer);
			//SDL_RenderDrawRect(gRenderer, &listOfPowerUps[index]->getCollider());
		}

		// Cycle through list of laser objects and render them to screen
		for (int index = 0; index != listOfLaserObjects.size(); ++index) {
			listOfLaserObjects[index]->render(listOfLaserObjects[index]->getPlayer(), gLaserOrangeTexture, gLaserGreenTexture, gRenderer);
			//SDL_RenderDrawRect(gRenderer, &listOfLaserObjects[index]->getLaserCollider());
		}
		for (int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
			listOfEnemyLaserObjects[index]->render(gLaserBlueTexture, gRenderer);
			//SDL_RenderDrawRect(gRenderer, &listOfEnemyLaserObjects[index]->getELaserCollider());
		}
		for (int index = 0; index != listOfNinjaStarObjects.size(); ++index) {
			if (listOfNinjaStarObjects[index]->getPlayer() == PLAYER_1)
				listOfNinjaStarObjects[index]->render(degrees, gNinjaStarYellowTexture, gRenderer);	// Yellow ninja star for player 1
			else
				listOfNinjaStarObjects[index]->render(degrees, gNinjaStarBlueTexture, gRenderer);	// Blue ninja star for player 2
			//SDL_RenderDrawRect(gRenderer, &listOfNinjaStarObjects[index]->getNinjaStarCollider());
		}
		for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
			(*iterSaw++)->render(gSawTexture, gRenderer, degrees);	// Render the ninja star
		}

		// Render Text
		gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, SCREEN_HEIGHT - gCreatedByTextTexture.getHeight() - 8, gRenderer);
		gLevelTextTexture.render((SCREEN_WIDTH - gLevelTextTexture.getWidth()) / 1.5, 8, gRenderer);
		gTimeTextTexture.modifyAlpha(timerAlpha);	// Flash the timer
		gTimeTextTexture.render(600, 8, gRenderer);
		gP1ScoreTextTexture.render(10, 8, gRenderer);
		gP2ScoreTextTexture.render(100, 8, gRenderer);
		gFPSTextTexture.render(200, 8, gRenderer);

		// Health Bars for Players
		SDL_Color fgColour = { 0, 255, 0, 255 };								// Set text color as blue
		SDL_Color bgColour = { 255, 0, 0, 255 };

		if (player1.getAlive()) {
			renderHealthBar(player1.getX() + (player1.getWidth() / 4), player1.getY() - 10, player1.getWidth() / 2, 5, player1.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);
			gPlayer1Texture.modifyAlpha(player1Alpha);
			player1.render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gP1LivesTexture, gRenderer);
		}// render the ship over the background
		if (player2.getAlive()) {
			renderHealthBar(player2.getX() + (player2.getWidth() / 4), player2.getY() - 10, player2.getWidth() / 2, 5, player2.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);
			gPlayer2Texture.modifyAlpha(player2Alpha);
			player2.render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gP2LivesTexture, gRenderer);							// render the ship over the background
		}

		//if(player1.getAlive())
		//	renderHealthBar(player1.getX() + (player1.getWidth() / 4), player1.getY() - 10, player1.getWidth() / 2, 5, player1.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);
		//if(player2.getAlive())
		//	renderHealthBar(player2.getX() + (player2.getWidth() / 4), player2.getY() - 10, player2.getWidth() / 2, 5, player2.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);

		// Set the Alpha value for player when flashing
		//gPlayer1Texture.modifyAlpha(player1Alpha);
		//player1.render();							// render the ship over the background
		//player1.render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);
		//SDL_RenderDrawRect(gRenderer, &player1.getCollider());

		//gPlayer2Texture.modifyAlpha(player2Alpha);
		//player2.render();							// render the ship over the background
		//player2.render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);
		//SDL_RenderDrawRect(gRenderer, &player2.getCollider());
	}
	else if (gameOver == true) {
		gGameOverTextTexture.modifyAlpha(gameOverAlpha);
		gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 300) / 2, gRenderer); // FOR TESTING
		gFinalScoreTextTexture.modifyAlpha(gameOverAlpha);
		gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2, gRenderer); // FOR TESTING
		gGameWinnerTextTexture.modifyAlpha(gameOverAlpha);
		gGameWinnerTextTexture.render((SCREEN_WIDTH - gGameWinnerTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameWinnerTextTexture.getHeight() + 450) / 2, gRenderer); // FOR TESTING
	}

	SDL_RenderPresent(gRenderer);			// Update screen
}

void Game::moveGameObjects() {
	if (player1.getAlive()) player1.movement();						// Update ship movement
	if (player2.getAlive()) player2.movement();

	// Cycle through lists of Enemys and move them
	for (int index = 0; index != listOfEnemyShips.size(); ++index) {
		listOfEnemyShips[index]->movement();
		spawnEnemyLaser(listOfEnemyShips[index]->getX(), listOfEnemyShips[index]->getY());
		//SDL_RenderDrawRect(gRenderer, &listOfLaserObjects[index]->getLaserCollider());
	}
	// Cycle through list of Enemy virus and move them
	for (int index = 0; index != listOfEnemyVirus.size(); ++index) {
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
	for (int index = 0; index != listOfPowerUps.size(); ++index) {
		listOfPowerUps[index]->movement();
	}
	// Cycle through lists of weapons and move them
	for (int index = 0; index != listOfLaserObjects.size(); ++index) {
		listOfLaserObjects[index]->movement();
	}
	for (int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
		listOfEnemyLaserObjects[index]->movement();
	}
	for (int index = 0; index != listOfNinjaStarObjects.size(); ++index) {
		listOfNinjaStarObjects[index]->movement();
		//SDL_RenderDrawRect(gRenderer, &listOfNinjaStarObjects[index]->getNinjaStarCollider());
	}
	for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
		if ((*iterSaw)->getPlayer() == PLAYER_1)
			(*iterSaw++)->movement(player1.getX(), player1.getY());	// Move the ninja star
		else if ((*iterSaw)->getPlayer() == PLAYER_2)
			(*iterSaw++)->movement(player2.getX(), player2.getY());	// Move the ninja star
	}
}

// Destroy Game Objects
void Game::destroyGameObjects() {
	for (int index = 0; index != listOfEnemyShips.size(); ++index) {
		if (!listOfEnemyShips[index]->getAlive()) {
			listOfEnemyShips.erase(listOfEnemyShips.begin() + index);
			//std::cout << "Enemy Ship Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (int index = 0; index != listOfEnemyVirus.size(); ++index) {
		if (!listOfEnemyVirus[index]->getAlive()) {
			listOfEnemyVirus.erase(listOfEnemyVirus.begin() + index);
			//std::cout << "Enemy Virus Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		if (!(*iterBC)->getAlive()) {
			iterBC = listOfBloodCells.erase(iterBC);
			//std::cout << "destroy blood cell" << std::endl;
		}
		else {
			iterBC++;
		}
	}
	for (iterSBC = listOfSmallBloodCells.begin(); iterSBC != listOfSmallBloodCells.end();) {
		if (!(*iterSBC)->getAlive()) {
			iterSBC = listOfSmallBloodCells.erase(iterSBC);
			//std::cout << "destroy small blood cell" << std::endl;
		}
		else {
			iterSBC++;
		}
	}
	for (iterWBC = listOfWhiteBloodCells.begin(); iterWBC != listOfWhiteBloodCells.end();) {
		if (!(*iterWBC)->getAlive()) {
			iterWBC = listOfWhiteBloodCells.erase(iterWBC);
			//std::cout << "destroy blood cell" << std::endl;
		}
		else {
			iterWBC++;
		}
	}
	for (int index = 0; index != listOfLaserObjects.size(); ++index) {
		if (!listOfLaserObjects[index]->getAlive()) {
			listOfLaserObjects.erase(listOfLaserObjects.begin() + index);
			//std::cout << "Laser Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
		if (!listOfEnemyLaserObjects[index]->getAlive()) {
			listOfEnemyLaserObjects.erase(listOfEnemyLaserObjects.begin() + index);
			std::cout << "Enemy Laser Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (int index = 0; index != listOfNinjaStarObjects.size(); ++index) {
		if (!listOfNinjaStarObjects[index]->getAlive()) {
			listOfNinjaStarObjects.erase(listOfNinjaStarObjects.begin() + index);
			std::cout << "Ninja Star Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
		if (!(*iterSaw)->getAlive()) {
			iterSaw = listOfSawObjects.erase(iterSaw);
			//std::cout << "destroy saw" << std::endl;
		}
		else {
			iterSaw++;
		}
	}
	for (int index = 0; index != listOfPowerUps.size(); ++index) {
		if (!listOfPowerUps[index]->getAlive()) {
			listOfPowerUps.erase(listOfPowerUps.begin() + index);
			//std::cout << "Power Up Destroyed." << std::endl;
			index--;
		}
	}// end for
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
void Game::spawnMovingObjects() {
	if(player1.getAlive() == false && player1.getNumLives() > 0) spawnPlayer(PLAYER_1);
	if(player2.getAlive() == false && player2.getNumLives() > 0) spawnPlayer(PLAYER_2);


	if (!player1.getAlive() && !player2.getAlive()) gameOver = true;

	if (listOfEnemyShips.size() < SPAWN_NUM_ENEMY_SHIPS) {
		spawnEnemyShip();
	}
	if (listOfEnemyVirus.size() < SPAWN_NUM_ENEMY_VIRUS) {
		spawnEnemyVirus();
	}
	if (listOfBloodCells.size() < SPAWN_NUM_BLOOD_CELL) {
		spawnBloodCell();
	}
	if (listOfSmallBloodCells.size() < SPAWN_NUM_BLOOD_CELL_S) {
		spawnSmallBloodCell();
	}
	if(listOfWhiteBloodCells.size() < SPAWN_NUM_BLOOD_CELL_WHITE) {
		spawnWhiteBloodCell();
	}
	if (listOfPowerUps.size() < SPAWN_NUM_POWER_UPS) {
		spawnPowerUp();
	}
}
void Game::spawnPlayer(int player) {
	int y = rand() % 5 + 1;

	if (player == PLAYER_1) {
		player1.spawn(0, (y * 110) - 50);						// 2017/01/20: Spawn Player 1 at random Y coord
		player1.setAlive(true);
	}
	else if (player == PLAYER_2) {
		player2.spawn(0, (y * 110) - 50);
		if (player2.getY() == player1.getY()) spawnPlayer(2);	// 2017/01/20: Spawn Player 2 at random Y coord + different to Player 1
		player2.setAlive(true);
		std::cout << "player1.getY() " << player1.getY() << " player2.getY() " << player2.getY() << std::endl;
	}
}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 50, 3);

	EnemyShip* p_Enemy = new EnemyShip();
	p_Enemy->spawn(x, y, -randomSpeed, p_Enemy->getCollider());
	listOfEnemyShips.push_back(p_Enemy);
}
void Game::spawnEnemyVirus() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 150);

	EnemyVirus* p_Virus = new EnemyVirus();
	p_Virus->spawn(x, y, -4, -2, p_Virus->getCollider());
	listOfEnemyVirus.push_back(p_Virus);
}
void Game::spawnBloodCell() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 200);

	BloodCell* p_BloodCell = new BloodCell();
	p_BloodCell->spawn(x, y, -randomSpeed);
	listOfBloodCells.push_back(p_BloodCell);
}
void Game::spawnSmallBloodCell() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 100);

	BloodCellSmall* p_SmallBloodCell = new BloodCellSmall();
	p_SmallBloodCell->spawn(x, y, -randomSpeed);
	listOfSmallBloodCells.push_back(p_SmallBloodCell);
}
void Game::spawnWhiteBloodCell() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 150);

	WhiteBloodCell* p_WhiteBloodCell = new WhiteBloodCell();
	p_WhiteBloodCell->spawn(x, y, -randomSpeed);
	listOfWhiteBloodCells.push_back(p_WhiteBloodCell);
}
void Game::spawnPowerUp() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 200);

	PowerUp* p_PowerUp = new PowerUp();
	p_PowerUp->spawn(x, y, -randomSpeed);								// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	listOfPowerUps.push_back(p_PowerUp);
}
void Game::spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier, int speed) {	// 2017-01-20 Separate out common randomness
	int randomX = rand() % 5 + 1;
	int randomY = rand() % 5 + 1;
	randomSpeed = rand() % 3 + speed;

	x = SCREEN_WIDTH + (randomX * xMuliplier);
	y = (randomY * 120) - 80;
}
// Spawn Weapon at ships location
/*
void Game::spawnLaser(int x, int y, int player, int velocity) {
	Laser* p_Laser = new Laser();
	p_Laser->spawn(x + 65, y + 30, velocity);											// adjust spawn position to front of ship
	p_Laser->setPlayer(player);															// 2017/01/17 Set the player the laser belongs too
	listOfLaserObjects.push_back(p_Laser);
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gLaserFX2, 0);
	}
}
*/
void Game::spawnLaser(int x, int y, int player, int velocity, int grade) {
	Laser* p_Laser1 = new Laser();

	p_Laser1->spawn(x + 65, y + 25, velocity);
	p_Laser1->setPlayer(player);
	listOfLaserObjects.push_back(p_Laser1);

	//if (grade == 1) {		// FIRE 2 MORE LASERS AT ANGLES
		Laser* p_Laser2 = new Laser();
		Laser* p_Laser3 = new Laser();
		p_Laser2->spawn(x + 65, y + 30, velocity);
		p_Laser2->setPlayer(player);
		p_Laser2->setAngle(1);
		p_Laser2->setGrade(1);
		listOfLaserObjects.push_back(p_Laser2);
		p_Laser3->spawn(x + 65, y + 35, velocity);
		p_Laser3->setPlayer(player);
		p_Laser3->setAngle(2);
		p_Laser3->setGrade(1);
		listOfLaserObjects.push_back(p_Laser3);
	//}
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gLaserFX2, 0);
	}
}
void Game::spawnEnemyLaser(int shipX, int shipY) {
	LaserEnemy* p_LaserE = new LaserEnemy();
	int randomLaser = rand() % 3 + 1;
	int distanceBetweenShots = ( 50 * randomLaser ) + 50;								// 2017/01/20 More random shooting from enemies
	//if (shipX % 100 == 0) {
	if (shipX % distanceBetweenShots < 5) {												// 2017-01-20 Not all ships were firing
		p_LaserE->spawn(shipX, shipY, p_LaserE->getCollider());
		listOfEnemyLaserObjects.push_back(p_LaserE);
		Mix_PlayChannel(-1, gLaserEFX, 0);
	}
}
void Game::spawnNinjaStar(int x, int y, int player) {				// player to spawn for and their coords
	NinjaStar* p_NinjaStar = new NinjaStar();
	p_NinjaStar->spawn(x, y, p_NinjaStar->getCollider());
	p_NinjaStar->setPlayer(player);									// 2017/01/17 Set the player the laser belongs too
	listOfNinjaStarObjects.push_back(p_NinjaStar);
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gNinjaFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gNinjaFX2, 0);
	}
}
//void Game::spawnSaw(int x, int y, int player, bool sawActive) {		// player to spawn for and their coords, turn on if inacive, off if active
void Game::spawnSaw(int x, int y, int player) {		// player to spawn for and their coords, turn on if inacive, off if active
	if (player == PLAYER_1 && !player1.getSawActive()) {	// IF SAW IS ALREADY ACTIVE KILL IT OTHERWISE SPAWN IT - Individual saw for each player
		Saw* p_Saw = new Saw();								// Create new saw
		p_Saw->spawn(x, y);									// spawn the saw
		p_Saw->setPlayer(player);							// set the saw to the current player
		listOfSawObjects.push_back(p_Saw);					// add to list of saws
		player1.setSawActive(true);							// show saw
		if (!gameOver) Mix_PlayChannel(-1, gSawFX, 0);
	}
	else if (player == PLAYER_2 && !player2.getSawActive()) {
		Saw* p_Saw = new Saw();
		p_Saw->spawn(x, y);
		p_Saw->setPlayer(player);
		listOfSawObjects.push_back(p_Saw);
		player2.setSawActive(true);
		if (!gameOver) Mix_PlayChannel(-1, gSawFX, 0);
	}
	else {
		for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
			if (player1.getSawActive() && player == PLAYER_1) {					// if saw is active
				player1.setSawActive(false);									// hide saw
				iterSaw = listOfSawObjects.erase(iterSaw);						// erase
			}
			else if (player2.getSawActive() && player == PLAYER_2) {			// if saw is active
				player2.setSawActive(false);									// hide saw
				iterSaw = listOfSawObjects.erase(iterSaw);						// erase
			}
			else {
				iterSaw++;
			}
		}
	}
}
/*
void Player::render() {
	//if (player1.getAlive()) gPlayer1Texture.render(player1.getX(), player1.getY(), gRenderer);	// Show P1 ship
	player1.render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);

	if (player1.getNumLives() > 0)
		gP1LivesTexture.render(10, SCREEN_HEIGHT - gP1LivesTexture.getHeight() - 10, gRenderer);
	if (player1.getNumLives() > 1)
		gP1LivesTexture.render(10 + gP1LivesTexture.getWidth(), SCREEN_HEIGHT - gP1LivesTexture.getHeight() - 10, gRenderer);
	if (player1.getNumLives() > 2)
		gP1LivesTexture.render(10 + (gP1LivesTexture.getWidth() * 2), SCREEN_HEIGHT - gP1LivesTexture.getHeight() - 10, gRenderer);

	//if (player2.getAlive()) gPlayer2Texture.render(player2.getX(), player2.getY(), gRenderer);	// Show P2 ship
	player2.render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);

	if (player2.getNumLives() > 0)
		gP2LivesTexture.render(SCREEN_WIDTH - gP2LivesTexture.getWidth() - 10, SCREEN_HEIGHT - gP2LivesTexture.getHeight() - 10, gRenderer);
	if (player2.getNumLives() > 1)
		gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 2) - 10, SCREEN_HEIGHT - gP2LivesTexture.getHeight() - 10, gRenderer);
	if (player2.getNumLives() > 2)
		gP2LivesTexture.render(SCREEN_WIDTH - (gP2LivesTexture.getWidth() * 3) - 10, SCREEN_HEIGHT - gP2LivesTexture.getHeight() - 10, gRenderer);
}
// Render the laser objects to the screen
void Laser::render(int player) {
	if (player == PLAYER_1)
		gLaserOrangeTexture.render(getX(), getY(), gRenderer);
	else if (player == PLAYER_2)
		gLaserGreenTexture.render(getX(), getY(), gRenderer);
}
void LaserEnemy::render() {
	gLaserBlueTexture.render(getX(), getY(), gRenderer);
}
// Render the Ninja Star objects to the screen
void NinjaStar::render(int player) {																// Render different colour ninja star
	if (player == PLAYER_1)
		gNinjaStarYellowTexture.render(getX(), getY(), gRenderer, NULL, degrees, NULL, SDL_FLIP_NONE);
	else if (player == PLAYER_2)
		gNinjaStarBlueTexture.render(getX(), getY(), gRenderer, NULL, degrees, NULL, SDL_FLIP_NONE);
}

void Saw::render() {
	//if (player == 1)
	//	gSawTexture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
	//else if (player == 2)
		gSawTexture.render(getX(), getY(), gRenderer, NULL, degrees, NULL, SDL_FLIP_NONE);
}

// Enemies and Obstacles
void EnemyShip::render() {
	SDL_Rect* currentClip = &gEnemySpriteClips[enemyframe / 10];		// Render current frame
	//std::cout << enemyframe / 10 << std::endl;
	gEnemySpriteSheetTexture.render(getX(), getY(), gRenderer, currentClip);

	++enemyframe;	// Go to next frame

	if (enemyframe >= ANIMATION_FRAMES * 10) {	// Cycle animation
		enemyframe = 0;
	}
}
void EnemyVirus::render() {
	gEnemyVirusTexture.render(getX(), getY(), gRenderer);
}
//void BloodCell::render() {
//	gBloodCellTexture.render(getX(), getY(), gRenderer, NULL, -degreesBC, NULL, SDL_FLIP_NONE);
//}
//void BloodCellSmall::render() {
//	gBloodCellSmallTexture.render(getX(), getY(), gRenderer, NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
//}
void WhiteBloodCell::render() {
	gWhiteBloodCellTexture.render(getX(), getY(), gRenderer, NULL, -degreesBCS, NULL, SDL_FLIP_NONE);
}

void PowerUp::render() {
	gPowerUpTexture.render(getX(), getY(), gRenderer);
}
*/
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

	//std::cout << "Collision!\n";

	//Handle ship collision with enemy (MOVE TO SEPERATE FUNCTION)
	/*ship.setShipX(ship.getShipX() - ship.getShipVelX());
	ship.setShipColX(ship.getShipX());

	ship.setShipY(ship.getShipY() - ship.getShipVelY());
	ship.setShipColY(ship.getShipY());*/

	//If none of the sides from A are outside B
	return true;
}

// This function gets called once on startup.
void fpsinit() {
	// Set all frame times to 0ms.
	memset(frametimes, 0, sizeof(frametimes));
	framecount = 0;
	framespersecond = 0;
	frametimelast = SDL_GetTicks();
}

void fpsthink() {
	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;
	Uint32 i;

	// frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
	// This value rotates back to 0 after it hits FRAME_VALUES.
	frametimesindex = framecount % FRAME_VALUES;

	getticks = SDL_GetTicks();	// store the current time

	frametimes[frametimesindex] = getticks - frametimelast;	// save the frame time value

	frametimelast = getticks;	// save the last frame time for the next fpsthink

	framecount++;	// increment the frame count

					// Work out the current framerate

					// The code below could be moved into another function if you don't need the value every frame.

					// I've included a test to see if the whole array has been written to or not. This will stop
					// strange values on the first few (FRAME_VALUES) frames.
	if (framecount < FRAME_VALUES) {
		count = framecount;
	}
	else {
		count = FRAME_VALUES;
	}

	framespersecond = 0;	// add up all the values and divide to get the average frame time.
	for (i = 0; i < count; i++) {
		framespersecond += frametimes[i];
	}

	framespersecond /= count;

	framespersecond = 1000.f / framespersecond;	// now to make it an actual frames per second value...
}

void Game::collisionCheck() {
	// Check if Player 1  or 2 has collided with an enemy virus or ship
	for (int index1 = 0; index1 != listOfEnemyVirus.size(); ++index1) {
		if (checkCollision(player1.getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
			if (player1.getSawActive()) {
				listOfEnemyVirus[index1]->setAlive(false);						// If saw is active kill that enemy
			}
			else
				managePlayerHealth(PLAYER_1, listOfEnemyVirus[index1]->getScore() / 3, "Enemy Virus");	// Take off 5 health
		}
		else if (checkCollision(player2.getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
			if (player2.getSawActive()) {
				listOfEnemyVirus[index1]->setAlive(false);						// If saw is active kill that enemy
			}
			else
				managePlayerHealth(PLAYER_2, listOfEnemyVirus[index1]->getScore() / 3, "Enemy Virus");	// Take off 5 health
		}
	}

	for (int index2 = 0; index2 != listOfEnemyShips.size(); ++index2) {
		if (checkCollision(player1.getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
			if (player1.getSawActive()) {
				listOfEnemyShips[index2]->setAlive(false);										// If saw is active kill that enemy
			}
			else
				managePlayerHealth(PLAYER_1, listOfEnemyShips[index2]->getScore() / 5, "Enemy Ship");	// Take off 5 health
		}
		else if (checkCollision(player2.getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
			if (player2.getSawActive()) {
				listOfEnemyShips[index2]->setAlive(false);										// If saw is active kill that enemy
			}
			else
				managePlayerHealth(PLAYER_2, listOfEnemyShips[index2]->getScore() / 5, "Enemy Ship");	// Take off 5 health
		}
	}

	// Check if Player 1 or 2 has picked up a power up
	for (int index = 0; index != listOfPowerUps.size(); ++index) {
		if (checkCollision(player1.getCollider(), listOfPowerUps[index]->getCollider()) == true) {
			player1.setScore(player1.getScore() + listOfPowerUps[index]->getScore());
			//player1.setHealth(player1.getHealth() + listOfPowerUps[index]->getScore());

			managePlayerHealth(PLAYER_1, -listOfPowerUps[index]->getScore());
			listOfPowerUps[index]->setAlive(false);
		}
		else if (checkCollision(player2.getCollider(), listOfPowerUps[index]->getCollider()) == true) {
			player2.setScore(player2.getScore() + listOfPowerUps[index]->getScore());
			//player2.setHealth(player2.getHealth() + listOfPowerUps[index]->getScore());

			managePlayerHealth(PLAYER_2, -listOfPowerUps[index]->getScore());
			listOfPowerUps[index]->setAlive(false);
			//std::cout << "Power Up Picked Up by " << player2.getName() << "!\n";
		}
	}

	// Cycle through lists of Player Lasers and check collision with other game objects
	for (int index = 0; index != listOfLaserObjects.size(); ++index) {
		for (int index1 = 0; index1 != listOfEnemyVirus.size(); ++index1) {														// Check if collision with Virus
			if (checkCollision(listOfLaserObjects[index]->getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
				if (listOfLaserObjects[index]->getPlayer() == PLAYER_1)
					player1.setScore(player1.getScore() + listOfEnemyVirus[index1]->getScore());
				if (listOfLaserObjects[index]->getPlayer() == PLAYER_2)
					player2.setScore(player2.getScore() + listOfEnemyVirus[index1]->getScore());

				listOfEnemyVirus[index1]->setAlive(false);
				listOfLaserObjects[index]->setAlive(false);
				//std::cout << "Enemy Virus Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
		for (int index2 = 0; index2 != listOfEnemyShips.size(); ++index2) {
			if (checkCollision(listOfLaserObjects[index]->getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {	// Check for Player Laser collision with Enemy Ship
				if (listOfLaserObjects[index]->getPlayer() == PLAYER_1)
					player1.setScore(player1.getScore() + listOfEnemyShips[index2]->getScore());
				if (listOfLaserObjects[index]->getPlayer() == PLAYER_2)
					player2.setScore(player2.getScore() + listOfEnemyShips[index2]->getScore());

				listOfEnemyShips[index2]->setAlive(false);
				listOfLaserObjects[index]->setAlive(false);
				//std::cout << "Enemy Ship Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
	}
	// Cycle through Ninja Stars and check collision on enemies
	for (int index = 0; index != listOfNinjaStarObjects.size(); ++index) {
		listOfNinjaStarObjects[index]->movement();
		for (int index1 = 0; index1 != listOfEnemyVirus.size(); ++index1) {
			if (checkCollision(listOfNinjaStarObjects[index]->getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
				player1.setScore(player1.getScore() + listOfEnemyVirus[index1]->getScore());
				listOfEnemyVirus[index1]->setAlive(false);
				listOfNinjaStarObjects[index]->setAlive(false);
				//std::cout << "Enemy Virus Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
		for (int index2 = 0; index2 != listOfEnemyShips.size(); ++index2) {
			if (checkCollision(listOfNinjaStarObjects[index]->getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
				player1.setScore(player1.getScore() + listOfEnemyShips[index2]->getScore());
				listOfEnemyShips[index2]->setAlive(false);
				listOfNinjaStarObjects[index]->setAlive(false);
				//std::cout << "Enemy Ship Killed by Player!\n";
				Mix_PlayChannel(-1, gExplosionFX, 0);
			}
		}
	}

	// Check if Enemy Laser has collided with Player 1 or 2
	for (int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
		if (checkCollision(listOfEnemyLaserObjects[index]->getCollider(), player1.getCollider()) == true) {
			managePlayerHealth(PLAYER_1, listOfEnemyLaserObjects[index]->getScore());
			listOfEnemyLaserObjects[index]->setAlive(false);
		}
		else if (checkCollision(listOfEnemyLaserObjects[index]->getCollider(), player2.getCollider()) == true) {
			managePlayerHealth(PLAYER_2, listOfEnemyLaserObjects[index]->getScore());
			listOfEnemyLaserObjects[index]->setAlive(false);
		}
	}
}
void Game::managePlayerHealth(int player, int score, std::string name) {
	if (player == PLAYER_1) {
		player1Flash = true;										// Flash on collision with Game Object
		player1.setHealth(player1.getHealth() - score);

		if (player1.getNumLives() <= 0) {
			player1.setSawActive(false);
			player1.setAlive(false);
		}
		else if (player1.getHealth() <= 0 && player1.getAlive()){
			player1.setNumLives(player1.getNumLives() - 1);
			if(player1.getNumLives() > 0) spawnPlayer(PLAYER_1);
			player1.setHealth(100);
		}
	}
	else if (player == PLAYER_2) {
		player2Flash = true;										// Flash on collision with Game Object
		player2.setHealth(player2.getHealth() - score);

		if (player2.getNumLives() <= 0) {
			player2.setSawActive(false);
			player2.setAlive(false);
		}
		else if (player2.getHealth() <= 0 && player2.getAlive()) {
			player2.setNumLives(player2.getNumLives() - 1);
			if(player2.getNumLives() > 0) spawnPlayer(PLAYER_2);
			player2.setHealth(100);
		}

		if (player2.getAlive() && SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds 2017/01/20 Moved to player 2, was rumbling for both players
			printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
		}
	}

	if (score > 0) {
		Mix_PlayChannel(-1, gExplosionFX, 0);				// Play Explosion sound effect
		if (player == PLAYER_1) std::cout << "Player 1 has collided with " << name << "! Health: " << player1.getHealth();
		if (player == PLAYER_2) std::cout << "Player 2 has collided with " << name << "! Health: " << player2.getHealth();
	}
	else if (score < 0) std::cout << "Player" << player << " has received a power up of " << -score << " health";

	//if (SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds
	//	printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
	//}
}
void renderHealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation) {	// Horizontal healthbar 2017/01/20 added if statement to decide orientation of health bar
	SDL_Rect fgrect;
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(gRenderer, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(gRenderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(gRenderer, &bgrect);
	SDL_SetRenderDrawColor(gRenderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	// Decide if Healthbar is horizontal or vertical
	if (orientation == HORIZONTAL) {
		int pw = (int)((float)w * Percent);
		int px = x + (w - pw);
		fgrect = { px, y, pw, h };
	}
	else if (orientation == VERTICAL){
		int ph = (int)((float)h * Percent);
		int py = y + (h - ph);
		fgrect = { x, py, w, ph };
	}
	SDL_RenderFillRect(gRenderer, &fgrect);
	SDL_SetRenderDrawColor(gRenderer, old.r, old.g, old.b, old.a);
}

int Game::getNumPlayers() {
	return mNumPlayers;
}
void Game::setNumPlayers(int n) {
	mNumPlayers = n;
}

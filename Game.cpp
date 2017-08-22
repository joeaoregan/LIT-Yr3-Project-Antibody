// 2017/01/25	Added explosions when lasers collide with Enemy Ships and Virus
//				Fixed error for Player Message Text
//				Fixed Ninja Star scoring for Player 2
// 2017/01/24	Changed fonts and graphics at start of level, and start and end of scrolling background
//				Added Menu to main code
//				Changed to 1280 x 720 from 800 x 600
// 2017/01/23	Set up levels and background
// 2017/01/09	Edited background to be 800 x 600 instead of 600 x 480

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"					// Game header file, with functions and variabls
#include <sstream>					// For timer
#include <SDL_mixer.h>				// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include "LTexture.h"				// Game textures
#include "Player.h"					// Player class
#include "EnemyShip.h"				// Enemy ship class
#include "EnemyVirus.h"				// 2017/01/10 JOE: Added Seans virus enemy
#include "Laser.h"					// Player Laser weapon
#include "NinjaStar.h"				// Player Ninja Star weapon
#include "Saw.h"					// 2017/01/17 Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell obstacle
#include "PowerUp.h"				// 2017/01/10 SEAN: Added Power Up
#include "LaserEnemy.h"				// The laser the enemy firesF
#include "Particle.h"				// Particles for the ship engine
#include "Button.h"
#include "Explosion.h"				// 2017/01/25 Added explosions for Player Laser colliding with Enemy Ships and Virus
#include "FPS.h"
#include "Rocket.h"					// 2017-02-06
#include <string.h>
#include <math.h>

bool p1RocketActive = false;
bool p2RocketActive = false;

bool checkCollision(SDL_Rect *a, SDL_Rect *b);

FPS fps;							// 2017/02/01 Moved FPS functionality to it's own class

SDL_Rect gameViewport;				// Main game screen view port
SDL_Rect UIViewport;				// Menu below main game screen view port
SDL_Rect mapViewport;				// Map indicating the ships current location in the professors body
SDL_Rect weaponViewport1;			// Indicates the currently selected main weapon
SDL_Rect weaponViewport2;			// Indicates the currently selected main weapon
SDL_Texture* gTest = NULL;			// Background texture
//SDL_Texture* gWeapon = NULL;		// Background texture

// Game & Level Testing
bool quit = false;					// Main loop flag
bool testMode = true;				// Game is in testing
bool displayIntro = true;			// false means off
bool displayLevelIntro = true;		// Display the information splash screen at the start of a level

// Particles
LTexture gDarkBlueParticleTexture;		// Dark blue engine particle
LTexture gMediumBlueParticlTexture;		// Medium blue engine particle
LTexture gLightBlueParticleTexture;		// Light blue engine particle
LTexture gShimmerTexture;				// Shimmer engine particle

// Render Healthbars
enum healthBarOrientation { VERTICAL, HORIZONTAL };
void renderHealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation);	// 2017/01/20 Added orientation
float virusBar = 0.0;

// Time
Uint32 startTime = 6000;			// Unsigned integer 32-bits
unsigned int lastTime = 0, currentTime, countdownTimer = GAME_TIMER;	// TEST TIMING
unsigned int newTime = 3.0;

// Scrolling
int backgroundLoopCounter = 0;		// Number of times the background image has looped
int scrollingOffset = 0;			// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)
int scrollingOffsetLogo = 600;		// Scrolling offset for splash screens
//int weaponScrolling = 60;

// Animation
int frame = 0;											// Current animation frame
const int ANIMATION_FRAMES = 4;							// Number of frames of animation for Enemy Ship
const int EXPLOSION_ANIMATION_FRAMES = 12;				// Number of frames of animation for Explosions
SDL_Rect gPressButtonToContinueSpriteClips[6];			// Sprite frames for Press Button to Continue animation
SDL_Rect gEnemySpriteClips[ANIMATION_FRAMES];			// Sprite frames for Enemy Ship animation
SDL_Rect gOrangeVirusSpriteClips[6];		// Sprite frames for Orange Virus animation
SDL_Rect gExplosionClips[EXPLOSION_ANIMATION_FRAMES];	// Sprite frames for Explosion animation

LTexture gPressEnterSpriteSheetTexture;					// Press Enter to Continue sprite sheet
LTexture gEnemySpriteSheetTexture;						// Enemy sprite sheet
LTexture gExplosionSpriteSheetTexture;					// explosion sprite sheet
LTexture gOrangeVirusSpriteSheetTexture;				// Orange Virus sprite sheet
int enemyFrame = 0;										// Frame count for speed of Enemy animation
int explosionFrame = 0;									// Frame count for speed of explosion animation

SDL_Event e;						// Event handler

// Joystick
SDL_Joystick* gController1 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Joystick* gController2 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Haptic*	gControllerHaptic = NULL;	// 2017/01/18 Haptic (Force Feedback) added

//The music that will be played
Mix_Music *gMusic1 = NULL;				// Mix_Music: Data type for music
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;
unsigned int currentSong;				// Play a random song when the game starts

//The sound effects that will be used (pointers)
Mix_Chunk *gNinjaFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gNinjaFX2 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gLaserFX2 = NULL;		// 2017/01/17 Player 2 Laser
Mix_Chunk *gLaserEFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
Mix_Chunk *gExplosionFX = NULL;		// Explosion sound fx
Mix_Chunk *gSawFX = NULL;			// Saw sound fx

SDL_Window* gWindow = NULL;			// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;		// The window renderer

// Text
SDL_Color textColour;				// Set the text colour
TTF_Font *gFontRetro20 = NULL;		// Globally used font 2017-01-25 Changed to Retro font which is more readable
TTF_Font *gFontRetro40 = NULL;		// Same as previous font with larger size
TTF_Font *gFontLazy30Menu = NULL;	// Globally used font
std::string l1Objective = "Destroy enemy virus and ships      \nThe player with the highest score\nIs the winner";
std::string l2Objective = "Destroy more enemy virus and ships\nThe player with the highest score\nIs the winner";
std::string l3Objective = "Destroy even more enemy virus and ships\nThe player with the highest score\nIs the winner";
int gamerOverMessageDisplayCounter = 0;		// Length of time to display game over message
int playerMessageCounter = MESSAGE_TIME;	// Time to display player notification messages
int pointsValueCounter = MESSAGE_TIME;		// Time to display score for killing Enemy message
std::string playerMessage;					// Player notification messages, Yellow writing appearing in the middle of the game screen
std::string pointsValue;					// Player notification messages, Yellow writing appearing in the middle of the game screen

// Scene textures
LTexture gBGTexture;				// Background
LTexture gBGStartTexture;			// Start of background
LTexture gBGEndTexture;				// End of background scrolling
LTexture gGameOverTextTexture;		// End of game, game over texture
// Objects and weapons
LTexture gPlayer1Texture;			// Player 1 ship
LTexture gP1LivesTexture;			// Player 1 Small ship for number of lives
LTexture gPlayer2Texture;			// Player 2 ship
LTexture gP2LivesTexture;			// Player 2 Small Ship for number of lives
LTexture gEnemyShipTexture;			// Enemy Ship for info screen
LTexture gEnemyVirusTexture;		// Enemy Virus
LTexture gEnemyVirusOrangeTexture;	// Enemy Virus Orange
LTexture gVirusFireballTexture;		// Enemy Virus Fireball
LTexture gLaserGreenTexture;		// Texture for Player 1 Laser weapon
LTexture gLaserOrangeTexture;		// Texture for Player 2 Laser weapon
LTexture gLaserBlueTexture;			// Texture for Enemy Laser weapon
LTexture gPowerUpHealthTexture;		// Texture for Health Box Power Up
LTexture gPowerUpLaserTexture;		// Texture for Health Box Power Up
LTexture gPowerUpLaserTextureV2;	// Texture for Health Box Power Up
LTexture gRocketTexture;
LTexture gPowerUpRocketTexture;
// Rotating Objects and Weapons (degrees to rotate in brackets)
LTexture gNinjaStarBlueTexture(5);	// Texture for Ninja Star weapon
LTexture gNinjaStarYellowTexture(5);// Texture for Ninja Star weapon // 2017-01-30 with rotation angle of 5 degrees
LTexture gSawTexture(5);			// Texture for Ninja Star weapon
LTexture gBloodCellTexture(1);		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
LTexture gBloodCellSmallTexture(2);	// Texture for Smaller Blood Cell
LTexture gWhiteBloodCellTexture(2);	// Texture for White Blood Cell
// Splash Screens / Logos
LTexture gLogo1;					// 2017/01/18 Texture for game Splash Screen 1
LTexture gLogo2;					// 2017/01/18 Texture for game Splash Screen 2
LTexture gLevel1;					// 2017/01/18 Texture for level Splash Screen 1
LTexture gLevel2;					// 2017/01/18 Texture for level Splash Screen 2
LTexture gLevel3;					// 2017/01/18 Texture for level Splash Screen 3
// UI
LTexture gTimeTextTexture;			// Countdown time displayed in game screen
LTexture gCreatedByTextTexture;		// Created by message at bottom of screen for demo
LTexture gLevelTextTexture;			// Current level displayed at top of game screen
LTexture gP1ScoreTextTexture;		// Player 1 current score
LTexture gP2ScoreTextTexture;		// Player 2 current score
LTexture gFPSTextTexture;			// Frames Per Second displayed at top of screen
LTexture gFinalScoreTextTexture;	// Final score displayed at end of level / end of game
LTexture gGameWinnerTextTexture;	// Game winner displayed at end of game
LTexture gLevelObjectiveTextTexture;// Objective for each level
LTexture gPlayerMessageTextTexture;	// Player notification messages for picking up objects etc.
LTexture gPointsValueTextMessage1;	// Points value for a destroyed enemy Virus or Ship
LTexture gPointsValueTextMessage2;	// Points value for a destroyed enemy Virus or Ship
// Story Text
LTexture gStory1;					// 2017/02/01
LTexture gStory2;					// 2017/02/01
LTexture gStory3;					// 2017/02/01

// Menu Text
LTexture gMenuTextTexture1;
LTexture gMenuTextTexture2;
LTexture gMenuTextTexture3;
LTexture gMenuTextTexture4;
LTexture gMenuTextTexture5;

//Buttons objects
Button gButtons[TOTAL_BUTTONS];
Button gMenuButtons[4];

SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

// Vectors for objects that have collisions
std::vector<PowerUp*> listOfPowerUps;					// List of power up objects
std::vector<LaserEnemy*> listOfEnemyLaserObjects;		// 2017/01/10
std::vector<Mix_Music*> listOfMusic;					// List of Music tracks
std::vector<EnemyShip*> listOfEnemyShips;				// 2017/01/09 JOE: List to store laser objects
std::vector<EnemyVirus*> listOfEnemyVirus;				// 2017/01/09 JOE: List to store laser objects
std::vector<Explosion*> listOfExplosions;				// 2017/01/25 Added Explosions list

std::vector<Weapon*> listOfPlayerWeapons;
std::vector<GameObject*> listOfGameObjects;				// 2017/01/31 Using to display the scores for each object killed

// Lists - objects with no collisions (yet)
std::list<BloodCell*> listOfBloodCells;					// 2017/01/10 JOE: List to store laser objects
std::list<BloodCell*>::const_iterator iterBC;			// 2017/01/10 JOE: Make them read only
std::list<Saw*> listOfSawObjects;						// 2017/01/17: List to store Saw objects
std::list<Saw*>::const_iterator iterSaw;				// 2017/01/17: Create global iterators to cycle through Saw objects - Make them read only

Player player1(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);	// Create a player with particles for engine
Player player2(gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture);

SDL_Texture* loadTexture(std::string path);	// Loads individual image as texture

SDL_Texture* loadTexture(std::string path) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);	//Get rid of old loaded surface
	}

	return newTexture;
}

bool Game::init() {
	resetGame(getCurrentLevel());			// Initialise variables depending on level

	// View ports
	gameViewport.x = 0;						// Main Game Screen
	gameViewport.y = 0;
	gameViewport.w = SCREEN_WIDTH;
	gameViewport.h = SCREEN_HEIGHT_GAME;
	UIViewport.x = 0;						// Bottom of screen UI / Info
	UIViewport.y = 600;
	UIViewport.w = SCREEN_WIDTH;
	UIViewport.h = 120;
	mapViewport.x = 525;					// Map
	mapViewport.y = 550;
	mapViewport.w = 230;
	mapViewport.h = 168;
	weaponViewport1.x = 10;					// Current Main Weapon Selected
	weaponViewport1.y = 600;
	weaponViewport1.w = 60;
	weaponViewport1.h = 60;
	weaponViewport2.x = SCREEN_WIDTH - 60 - 10;					// Current Main Weapon Selected
	weaponViewport2.y = 600;
	weaponViewport2.w = 60;
	weaponViewport2.h = 60;

	std::cout << "Player 1 Health: " << player1.getHealth() << " " << "Player 2 Health: " << player2.getHealth() << std::endl;		// Player health at start of game
	std::cout << "Player 1 Lives: " << player1.getNumLives() << " " << "Player 2 Lives: " << player2.getNumLives() << std::endl;
	player1.setName("Player 1");	// Names for players
	player2.setName("Player 2");
	if (testMode) player1.setNumLives(NUM_LIVES);
	if (testMode) player2.setNumLives(NUM_LIVES);

	bool success = true;						// Initialization flag

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
			//} else 	gController1 = SDL_JoystickOpen(0);

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
		gWindow = SDL_CreateWindow("Antibody", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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

bool Game::loadMedia() {
	bool success = true;			// Loading success flag

	textColour = { 255, 255, 255, 255 };

	gFontLazy30Menu = TTF_OpenFont("Fonts/Lazy.ttf", 30);	// Open the font
	if (gFontLazy30Menu == NULL) {
		printf("XXX Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		//Render text
		if (!gMenuTextTexture1.loadFromRenderedText("ANTIBODY", textColour, gFontLazy30Menu, gRenderer)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture2.loadFromRenderedText("New Game", { 0,0,0 }, gFontLazy30Menu, gRenderer)) {	// can take out the new textColor objects
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture3.loadFromRenderedText("Settings", textColour, gFontLazy30Menu, gRenderer)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture4.loadFromRenderedText("High Scores", textColour, gFontLazy30Menu, gRenderer)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gMenuTextTexture5.loadFromRenderedText("Quit", textColour, gFontLazy30Menu, gRenderer)) {
			printf("Failed to render text texture!\n");
			success = false;
		}

		gMenuTextTexture2.setX((SCREEN_WIDTH - gMenuTextTexture2.getWidth()) / 2);
		gMenuTextTexture3.setX((SCREEN_WIDTH - gMenuTextTexture3.getWidth()) / 2);
		gMenuTextTexture4.setX((SCREEN_WIDTH - gMenuTextTexture4.getWidth()) / 2);
		gMenuTextTexture5.setX((SCREEN_WIDTH - gMenuTextTexture5.getWidth()) / 2);

		gMenuTextTexture2.setY((SCREEN_HEIGHT - gMenuTextTexture2.getHeight()) / 2.5);
		gMenuTextTexture3.setY((SCREEN_HEIGHT - gMenuTextTexture3.getHeight()) / 2.0);
		gMenuTextTexture4.setY((SCREEN_HEIGHT - gMenuTextTexture4.getHeight()) / 1.7);
		gMenuTextTexture5.setY((SCREEN_HEIGHT - gMenuTextTexture5.getHeight()) / 1.5);
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("Art/buttonOne.png", gRenderer)) {		// CHANGED ADDED RENDERER TO FUNCTION
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else {
		//Set sprites
		for (unsigned int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
			gSpriteClipsMenu[i].x = 0;
			gSpriteClipsMenu[i].y = i * 200;
			gSpriteClipsMenu[i].w = BUTTON_WIDTH;
			gSpriteClipsMenu[i].h = BUTTON_HEIGHT;
		}

		gMenuButtons[0].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture2.getY());
		gMenuButtons[1].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture3.getY());
		gMenuButtons[2].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture4.getY());
		gMenuButtons[3].setPosition((SCREEN_WIDTH - BUTTON_WIDTH) / 2, gMenuTextTexture5.getY());
	}

	gTest = loadTexture("Art/Prof.png");
	if (gTest == NULL) {
		printf("Failed to load Professor texture image!\n");
		success = false;
	}
//	gWeapon = loadTexture("Art/LaserGun2.png");
//	if (gWeapon == NULL) {
//		printf("Failed to load LaserGun texture image!\n");
//		success = false;
//	}
	// Particles
	if (!gDarkBlueParticleTexture.loadFromFile("Art/particleDarkBlue.bmp", gRenderer)) {	// Load Dark Particle texture
		printf("Failed to load red texture!\n");
		success = false;
	}
	if (!gMediumBlueParticlTexture.loadFromFile("Art/particleMediumBlue.bmp", gRenderer)) {	// Load Medium Particle texture
		printf("Failed to load green texture!\n");
		success = false;
	}
	if (!gLightBlueParticleTexture.loadFromFile("Art/particleLightBlue.bmp", gRenderer)) {	// Load Light Particle texture
		printf("Failed to load blue texture!\n");
		success = false;
	}
	if (!gShimmerTexture.loadFromFile("Art/shimmer.bmp", gRenderer)) {						// Load shimmer texture
		printf("Failed to load shimmer texture!\n");
		success = false;
	}

	// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };													// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);										// Use bold font

		if (!gCreatedByTextTexture.loadFromRenderedText("A Game By Se�n Horgan and Joe O'Regan", textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render prompt text texture!\n");
			success = false;
		}
	}

	gFontRetro40 = TTF_OpenFont("Fonts/Retro.ttf", 40);
	if (gFontRetro40 == NULL) {
		printf("Failed to load kunstler font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 0, 255, 0, 255 };
		TTF_SetFontStyle(gFontRetro40, TTF_STYLE_BOLD);											// Use bold font
	}

	// Load Textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile("Art/Player2ShipOld.png", gRenderer)) {					// Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gP1LivesTexture.loadFromFile("Art/Player1ShipSmall.png", gRenderer)) {				// Ship Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmallOld.png", gRenderer)) {				// Ship Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	} // gVirusFireballTexture
	if (!gVirusFireballTexture.loadFromFile("Art/VirusFireball.png", gRenderer)) {				// Enemy Virus Texture
		printf("Failed to load Enemy Virus Orange Fireball texture!\n");
		success = false;
	}
	if (!gEnemyShipTexture.loadFromFile("Art/EnemyShip.png", gRenderer)) {				// Enemy Virus Texture
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	if (!gEnemyVirusTexture.loadFromFile("Art/VirusGreen.png", gRenderer)) {				// Enemy Virus Texture
		printf("Failed to load Enemy Virus texture!\n");
		success = false;
	}
	if (!gEnemyVirusOrangeTexture.loadFromFile("Art/VirusOrange.png", gRenderer)) {				// Enemy Virus Texture
		printf("Failed to load Enemy Virus Orange texture!\n");
		success = false;
	}
	if (!gBloodCellTexture.loadFromFile("Art/BloodCell.png", gRenderer)) {					// 10/01 Added Large Blood Cell
		printf("Failed to load Blood Cell texture!\n");
		success = false;
	}
	if (!gBloodCellSmallTexture.loadFromFile("Art/BloodCellSmall.png", gRenderer)) {		// 10/01 Added Small Blood Cell
		printf("Failed to load Small Blood Cell texture!\n");
		success = false;
	}
	if (!gBGTexture.loadFromFile("Art/Background720.png", gRenderer)) {						// 09/01 Edited background to be 800 x 600 instead of 600 * 480
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gBGStartTexture.loadFromFile("Art/bgBegin720a.png", gRenderer)) {						// Background start texture
		printf("Failed to load start background texture!\n");
		success = false;
	}
	if (!gBGEndTexture.loadFromFile("Art/bgEnd720a.png", gRenderer)) {							// Background end texture
		printf("Failed to load end background texture!\n");
		success = false;
	}
	if (!gLaserGreenTexture.loadFromFile("Art/LaserGreen.png", gRenderer)) {				// Green Laser Texture
		printf("Failed to load Green Laser texture!\n");
		success = false;
	}
	if (!gLaserOrangeTexture.loadFromFile("Art/LaserOrange.png", gRenderer)) {				// Green Laser Texture
		printf("Failed to load Orange Laser texture!\n");
		success = false;
	}
	if (!gLaserBlueTexture.loadFromFile("Art/LaserBlue.png", gRenderer)) {					// Blue Laser Texture
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}
	if (!gNinjaStarBlueTexture.loadFromFile("Art/NinjaStarBlue.png", gRenderer)) {			// Ninja Star Texture
		printf("Failed to load Blue Ninja Star texture!\n");
		success = false;
	}
	if (!gNinjaStarYellowTexture.loadFromFile("Art/NinjaStarYellow.png", gRenderer)) {		// Ninja Star Texture
		printf("Failed to load Yellow Ninja Star texture!\n");
		success = false;
	}
	if (!gRocketTexture.loadFromFile("Art/Rocket.png", gRenderer)) {		// Ninja Star Texture
		printf("Failed to load Rocket texture!\n");
		success = false;
	}
	if (!gPowerUpRocketTexture.loadFromFile("Art/Rocket.png", gRenderer)) {		// Ninja Star Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}
	if (!gSawTexture.loadFromFile("Art/SawBlue.png", gRenderer)) {							// Ninja Star Texture
		printf("Failed to load Blue Saw texture!\n");
		success = false;
	}
	if (!gGameOverTextTexture.loadFromFile("Art/GameOver1.png", gRenderer)) {				// Game Over Text
		printf("Failed to load Game Over texture!\n");
		success = false;
	}
	if (!gWhiteBloodCellTexture.loadFromFile("Art/WhiteCell.png", gRenderer)) {				// 10/01 Added Blood Cell
		printf("Failed to load White Blood Cell texture!\n");
		success = false;
	}
	if (!gPowerUpHealthTexture.loadFromFile("Art/PowerUpHealthBox.png", gRenderer)) {				// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Health Power Up texture!\n");
		success = false;
	}
	if (!gPowerUpLaserTexture.loadFromFile("Art/PowerUpLaser.png", gRenderer)) {				// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Laser Power Up texture!\n");
		success = false;
	}
	if (!gPowerUpLaserTextureV2.loadFromFile("Art/LaserGunV3.png", gRenderer)) {				// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Laser V2 Power Up texture!\n");
		success = false;
	}
	if (!gLogo1.loadFromFile("Art/Logo1720.png", gRenderer)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Logo 1 texture!\n");
		success = false;
	}
	if (!gLogo2.loadFromFile("Art/Logo2720.png", gRenderer)) {									// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Logo 2 texture!\n");
		success = false;
	}
	if (!gLevel1.loadFromFile("Art/Level1720.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (!gLevel2.loadFromFile("Art/Level2720.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (!gLevel3.loadFromFile("Art/Level3720.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Level 3 texture!\n");
		success = false;
	}

	//Load sprite sheet texture
	if (!gPressEnterSpriteSheetTexture.loadFromFile("Art/PressEnterSpriteSheet2.png", gRenderer)) {	// Sprite sheet for Press Enter Button
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else {
		// Set sprite clips 19/01/2017 Added for loop
		for (unsigned int i = 0; i < 6; ++i) {
			gPressButtonToContinueSpriteClips[i].x = 0;
			if(i < 4)
				gPressButtonToContinueSpriteClips[i].y = i * 50;
			else if (i == 4)
				gPressButtonToContinueSpriteClips[i].y = 100;
			else if (i == 5)
				gPressButtonToContinueSpriteClips[i].y = 50;
			gPressButtonToContinueSpriteClips[i].w = 718;
			gPressButtonToContinueSpriteClips[i].h = 50;
		}
	}

	if (!gEnemySpriteSheetTexture.loadFromFile("Art/EnemySpriteSheet2.png", gRenderer)) {	// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Ship animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (unsigned int i = 0; i < 4; ++i) {
			gEnemySpriteClips[i].x = 0;
			gEnemySpriteClips[i].y = i * 50;
			gEnemySpriteClips[i].w = 120;
			gEnemySpriteClips[i].h = 50;
		}
	}
	if (!gOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange.png", gRenderer)) {	// Sprite sheet for Enemy Ship
		printf("Failed to load Orange Virus animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (unsigned int i = 0; i < 6; ++i) {
			if(i < 4) gOrangeVirusSpriteClips[i].x = i * 75;
			if (i == 5) gOrangeVirusSpriteClips[i].x = 2 * 75;
			if (i == 6) gOrangeVirusSpriteClips[i].x = 1 * 75;
			gOrangeVirusSpriteClips[i].y = 0;
			gOrangeVirusSpriteClips[i].w = 75;
			gOrangeVirusSpriteClips[i].h = 75;
		}
	}

	if (!gExplosionSpriteSheetTexture.loadFromFile("Art/Explosion.png", gRenderer)) {	// Sprite sheet for Explosions
		printf("Failed to load Enemy Ship animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (unsigned int i = 0; i < EXPLOSION_ANIMATION_FRAMES; ++i) {
			gExplosionClips[i].x = i * 96;
			gExplosionClips[i].y = 0;
			gExplosionClips[i].w = 96;
			gExplosionClips[i].h = 96;
		}
	}

	//Load music
	gMusic1 = Mix_LoadMUS("Audio/GameSong1.wav");											// Load music
	if (gMusic1 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gMusic2 = Mix_LoadMUS("Audio/GameSong2.mp3");											// Load music
	if (gMusic2 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gMusic3 = Mix_LoadMUS("Audio/GameSong3.mp3");											// Load music
	if (gMusic3 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gNinjaFX1 = Mix_LoadWAV("Audio/Swoosh1.wav");														// Load sound effects
	if (gNinjaFX1 == NULL) {
		printf("Failed to load P1 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gNinjaFX2 = Mix_LoadWAV("Audio/Swoosh2.wav");														// Load sound effects
	if (gNinjaFX2 == NULL) {
		printf("Failed to load P2 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX1 = Mix_LoadWAV("Audio/Laser1.wav");														// Load sound effects
	if (gLaserFX1 == NULL) {
		printf("Failed to load P1 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserFX2 = Mix_LoadWAV("Audio/Laser2.wav");														// Load sound effects
	if (gLaserFX2 == NULL) {
		printf("Failed to load P2 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gLaserEFX = Mix_LoadWAV("Audio/LaserEnemy.wav");													// Load sound effects
	if (gLaserEFX == NULL) {
		printf("Failed to load enemy laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gExplosionFX = Mix_LoadWAV("Audio/explosion.wav");													// Load sound effects
	if (gExplosionFX == NULL) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gSawFX = Mix_LoadWAV("Audio/Saw.wav");																// Load sound effects
	if (gSawFX == NULL) {
		printf("Failed to load Saw sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Add songs to vector
	listOfMusic.push_back(gMusic1);						// Add tracks to the music array
	listOfMusic.push_back(gMusic2);
	listOfMusic.push_back(gMusic3);

	currentSong = rand() % 3;							// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);		// Play the currently selected song

	return success;
}

void Game::close() {
	// Story
	gStory1.free();
	gStory2.free();
	gStory3.free();
	// Menu
	gMenuTextTexture1.free();
	gMenuTextTexture2.free();
	gMenuTextTexture3.free();
	gMenuTextTexture4.free();
	gMenuTextTexture5.free();

	//Free loaded images
	gButtonSpriteSheetTexture.free();

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
	gEnemyShipTexture.free();
	gEnemyVirusTexture.free();
	gEnemyVirusOrangeTexture.free();
	gVirusFireballTexture.free(); //
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
	gRocketTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();
	gWhiteBloodCellTexture.free();
	gPowerUpHealthTexture.free();
	gPowerUpLaserTexture.free();
	gPowerUpLaserTextureV2.free();
	gPowerUpRocketTexture.free();
	gLogo1.free();
	gLogo2.free();
	gLevel1.free();
	gLevel2.free();
	gLevel3.free();
	// free animations
	gPressEnterSpriteSheetTexture.free();
	gEnemySpriteSheetTexture.free();

	gTimeTextTexture.free();
	gCreatedByTextTexture.free();
	gLevelTextTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();
	gFPSTextTexture.free();
	gFinalScoreTextTexture.free();
	gGameWinnerTextTexture.free();
	gLevelObjectiveTextTexture.free();
	gPlayerMessageTextTexture.free();
	gPointsValueTextMessage1.free();
	gPointsValueTextMessage2.free();

	//Free global font
	TTF_CloseFont(gFontRetro20);
	gFontRetro20 = NULL;
	TTF_CloseFont(gFontRetro40);
	gFontRetro40 = NULL;

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
			if (SDL_PollEvent(&e) != 0) {
				gamepadInfo();							// Display gamepad information
			}
			// MAIN GAME LOOP:  While application is running
			while (!quit) {
				quit = playerInput(quit);				// 2017/01/09 JOE: Handle input from player

				//if (displayIntro) displayGameLogos();	// 2017/01/18 Splash screens at start of game
				//if (getCurrentLevel() == 0 && displayIntro) displaySplashScreens();	// 2017/01/18 Splash screens at start of game
				//if (getCurrentLevel() == MENU) menu();

				if (getCurrentLevel() != 0) playLevel(getCurrentLevel());
				playLevel(1);

				fps.fpsthink();

				//if (player1.getAlive() && player2.getA live()) gameOver = true;

				destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen
			}
		}
	}
}

void Game::menu() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	for (unsigned int i = 0; i < TOTAL_BUTTONS; ++i) {
		gMenuButtons[i].render(gButtonSpriteSheetTexture, gRenderer, &gSpriteClipsMenu[gMenuButtons[i].mCurrentSprite]);
	}

	gMenuTextTexture1.render((SCREEN_WIDTH - gMenuTextTexture1.getWidth()) / 2, (SCREEN_HEIGHT - gMenuTextTexture1.getHeight()) / 12, gRenderer);
	gMenuTextTexture2.render(gMenuTextTexture2.getX(), gMenuTextTexture2.getY(), gRenderer);
	gMenuTextTexture3.render(gMenuTextTexture3.getX(), gMenuTextTexture3.getY(), gRenderer);
	gMenuTextTexture4.render(gMenuTextTexture4.getX(), gMenuTextTexture4.getY(), gRenderer);
	gMenuTextTexture5.render(gMenuTextTexture5.getX(), gMenuTextTexture5.getY(), gRenderer);

	SDL_RenderPresent(gRenderer);			// Update screen
}

void Game::resetGame(int currentLevel) {	// Reset a level or the game
	BloodCellsActive = 0;
	whiteBloodCellsActive = 0;
	smallBloodCellsActive = 0;

	if (currentLevel == MENU) displayIntro = true;
	displayLevelIntro = true;
	backgroundLoopCounter = 0;
	scrollingOffset = 0;
	playerMessage = "";						// Reset the player notification message
	pointsValue = "";						// Reset the points value for destroyed Enemy message

	gamerOverMessageDisplayCounter = 0;

	// Timer
	countdownTimer = GAME_TIMER;			// Reset the countdown timer
	gPlayer1Texture.setFlash(false);
	gPlayer1Texture.setFlash(false);
	gTimeTextTexture.setFlash(false);		// Reset the timer flash
	gGameOverTextTexture.setFlash(true);	// Only ever shown as flashing text

	// Scores
	if (currentLevel <= 1) {				// If the level isn't progressing
		player1.setScore(0);				// Reset player 1 score
		player2.setScore(0);				// Reset player 2 score

		player1.setNumLives(NUM_LIVES);
		player1.setSawActive(false);
		player1.setSpeedBoost(false);

		player2.setNumLives(NUM_LIVES);
		player2.setSawActive(false);
		player2.setSpeedBoost(false);
	}

	// Reset Players
	player1.setAlive(false);
	player1.setHealth(player1.getMaxHealth());
	player2.setAlive(false);
	player2.setHealth(player2.getMaxHealth());

	// Delete all objects on screen
	if (gameOver || levelOver) {
		listOfPowerUps.clear();
		listOfEnemyLaserObjects.clear();
		listOfEnemyShips.clear();
		listOfEnemyVirus.clear();
		listOfPlayerWeapons.clear();
		listOfBloodCells.clear();;
		listOfSawObjects.clear();
		listOfGameObjects.clear();
	}

	levelOver = false;
	gameOver = false;
}

void Game::playLevel(int levelNum) {
	//if (displayLevelIntro && levelNum == LEVEL_1) displayLevelSplashScreen(l1Objective);	// Display splash screens
	//else if (displayLevelIntro && levelNum == LEVEL_2) displayLevelSplashScreen(l2Objective);
	//else if (displayLevelIntro && levelNum == LEVEL_3) displayLevelSplashScreen(l3Objective);
	displayLevelIntro = false;

	if (!gameOver) {
		spawnMovingObjects();		// 2017/01/10 JOE: Spawn enemies and obstacles at random coords and distances apart

		moveGameObjects();			// 2017-01-09 JOE: Move the game objects on the screen

		collisionCheck();
	}

	renderGameObjects();			// 2017-01-09 JOE: Render the game objects to the screen
}

void Game::displaySplashScreens() {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gLogo1.render(0, 0, gRenderer);						// Game Title

		SDL_RenderPresent(gRenderer);						// Update screen
		SDL_Delay(1000);									// Pause with image on screen

	while (scrollingOffsetLogo >= 0) {
		gLogo2.render(0, scrollingOffsetLogo, gRenderer);	// Team Member Names
		scrollingOffsetLogo -= 10;

		SDL_RenderPresent(gRenderer);						// Update screen
	}

	SDL_Delay(1000);										// Pause with image on screen

	displayIntro = false;
}





std::string story1 = "The player must avoid contact with Enemy Viruses\nThe Viruses will move towards the nearest player\n\n\nThe Orange Virus moves towards the nearest player\nAnd explodes when its timer has run out\n\n\nThe Enemy Ship fires lasers\nAs it crosses the screen right to left";
std::string story2 = "Story 2 blah blah \nBrian fill this\nIn Later";
std::string story3 = "Story 3 blah blah blah\nBrian fill this\nIn Later";

void Game::displayLevelSplashScreen(std::string objective) {

	// STORY

	textColour = {255,255,255,255};
	if (!gStory1.loadFromRenderedText(story1, textColour, gFontRetro20, gRenderer, true)) {
		printf("Unable to render level game objective texture!\n");
	}
	if (!gStory2.loadFromRenderedText(story2, textColour, gFontRetro20, gRenderer, true)) {
		printf("Failed to render text texture!\n");
	}
	if (!gStory3.loadFromRenderedText(story3, textColour, gFontRetro20, gRenderer, true)) {
		printf("Failed to render text texture!\n");
	}
	//scrollingOffsetLogo = 600;								// Start at bottom of screen

	//while (scrollingOffsetLogo >= 0) {
		gLevel1.render(0, scrollingOffsetLogo, gRenderer);	// Scroll up Level 1 background
	//	scrollingOffsetLogo -= 5;

	//	SDL_RenderPresent(gRenderer);
	//}

	//SDL_Delay(1000);										// Pause with image on screen

	//scrollingOffsetLogo = -100;
	//textColour = { 0, 255, 0, 255 };						// Green text for level objectives
	scrollingOffsetLogo = 600;								// Texture will start below window

	//if (!gStory1.loadFromRenderedText(objective, textColour, gFontRetro20, gRenderer, true)) {
	//	printf("Failed to render text texture!\n");
	//}
	//if (!gStory1.loadFromRenderedText(story1, { 255, 255, 255, 255 }, gFontRetro20, gRenderer, true)) {
	//	printf("Unable to render level game objective texture!\n");
	//}

	while (scrollingOffsetLogo >= 300) {														// First Part of story
		SDL_RenderClear(gRenderer);																// Clear the screen
		if (getCurrentLevel() == MENU) gLevel1.render(0, 0, gRenderer);							// Static background

		scrollingOffsetLogo -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStory1.render((SCREEN_WIDTH - gStory1.getWidth()) / 2, scrollingOffsetLogo, gRenderer); // FOR TESTING
		gEnemyVirusTexture.render(SCREEN_WIDTH - gEnemyVirusTexture.getWidth() - 100, scrollingOffsetLogo, gRenderer);
		gEnemyVirusOrangeTexture.render(SCREEN_WIDTH - gEnemyVirusOrangeTexture.getWidth() - 100, scrollingOffsetLogo + 100, gRenderer);
		gEnemyShipTexture.render(SCREEN_WIDTH - gEnemyShipTexture.getWidth() - 100, scrollingOffsetLogo + 200, gRenderer);

		SDL_RenderPresent(gRenderer);															// Update screen
	}

	SDL_Delay(2000);																			// Pause with image on screen

	scrollingOffsetLogo = 600;								// Texture will start below window

	while (scrollingOffsetLogo >= 300) {														// Second part of story
		SDL_RenderClear(gRenderer);																// Clear the screen
		if (getCurrentLevel() == MENU) gLevel1.render(0, 0, gRenderer);							// Static background

		scrollingOffsetLogo -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStory2.render((SCREEN_WIDTH - gStory2.getWidth()) / 2, scrollingOffsetLogo, gRenderer); // FOR TESTING

		SDL_RenderPresent(gRenderer);			// Update screen
	}

	SDL_Delay(2000);										// Pause with image on screen																		// Pause with image on screen

	scrollingOffsetLogo = 600;								// Texture will start below window

	while (scrollingOffsetLogo >= 300) {														// Second part of story
		SDL_RenderClear(gRenderer);																// Clear the screen
		if (getCurrentLevel() == MENU) gLevel1.render(0, 0, gRenderer);							// Static background

		scrollingOffsetLogo -= 5;																// Decrement the scrolling offset move the texture up the screen
		gStory3.render((SCREEN_WIDTH - gStory3.getWidth()) / 2, scrollingOffsetLogo, gRenderer); // FOR TESTING

		SDL_RenderPresent(gRenderer);						// Update screen
	}

	SDL_Delay(2000);										// Pause with image on screen

	//*****************************************************

	// OBJECTIVES

	scrollingOffsetLogo = -600;								// Logo will start above window

	while (scrollingOffsetLogo <= 0) {
		gLevel1.render(0, scrollingOffsetLogo, gRenderer);
		scrollingOffsetLogo += 5;							// Decrement scrollling offset to move texture up the screen

		SDL_RenderPresent(gRenderer);						// Update screen for each movement
	}

	scrollingOffsetLogo = 600;								// Texture will start below window

	textColour = { 0, 255, 0, 255 };						// Green text for level objectives

	if (!gLevelObjectiveTextTexture.loadFromRenderedText(objective, textColour, gFontRetro20, gRenderer, true)) {
		printf("Unable to render level game objective texture!\n");
	}

	while (scrollingOffsetLogo >= 300) {
		SDL_RenderClear(gRenderer);																// Clear the screen
		if (getCurrentLevel() == MENU) gLevel1.render(0, 0, gRenderer);							// Static background
		if (getCurrentLevel() == LEVEL_1) gLevel1.render(0, 0, gRenderer);						// Static background
		else if (getCurrentLevel() == LEVEL_2) gLevel2.render(0, 0, gRenderer);					// Static background
		else if (getCurrentLevel() == LEVEL_3) gLevel3.render(0, 0, gRenderer);					// Static background

		scrollingOffsetLogo -= 5;
		gLevelObjectiveTextTexture.render((SCREEN_WIDTH - gLevelObjectiveTextTexture.getWidth()) / 2, scrollingOffsetLogo, gRenderer); // FOR TESTING

		SDL_RenderPresent(gRenderer);			// Update screen
	}

	pressButtonToContinue();
}

void Game::pressButtonToContinue() {
	bool continueGame = false;

	SDL_Rect* currentClip = &gPressButtonToContinueSpriteClips[frame / 6];	// Render current frame
	gPressEnterSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2 + 200, gRenderer, currentClip);

	SDL_RenderPresent(gRenderer);			// Update screen
	++frame;	// Go to next frame

	if (frame / 6 >= ANIMATION_FRAMES) {	// Cycle animation
		frame = 0;
	}

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			std::cout << "test 2" << std::endl;
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
		case SDL_KEYDOWN:
			//printf("Key press detected\n");
			continueGame = true;
			break;
			//if (e.type == SDL_JOYBUTTONDOWN) {
		}

		break;
	}

	if (!continueGame) pressButtonToContinue();
}

void Game::gamepadInfo() {
	if (SDL_NumJoysticks() > 0) {
		if (strcmp(SDL_JoystickName(gController1), "NVIDIA Shield") == 0) {
			std::cout << "nv test" << std::endl;
			// put test here to make NVIDIA Shield controller as 2 controllers
		}

		std::cout << "joystick instance id: " << SDL_JoystickInstanceID(gController1) << std::endl;

		for (unsigned int i = 0; i < SDL_NumJoysticks(); ++i) {
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
	//In memory text stream - string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
	std::stringstream timeText;		// string stream
	std::stringstream score1Text;	// string stream
	std::stringstream score2Text;	// string stream
	std::string finalScores;
	std::string gameWinner;
	std::stringstream framesPerSec;

	timeText.str("");				// Set text to be rendered - string stream - print the time since timer last started - initialise empty
	framesPerSec << "FPS: " << fps.getFPS();
	score1Text << "P1: " << player1.getScore();
	score2Text << "P2: " << player2.getScore();
	finalScores = "Player 1: " + std::to_string(player1.getScore()) + " Player 2: " + std::to_string(player2.getScore());

	// Game Over
	if (levelOver == true) {
		//std::cout << "Level " << currentLevel << " Complete" << std::endl;
		if (getCurrentLevel() == LEVEL_1) textColour = { 0, 255, 0, 255 };
		if (getCurrentLevel() == LEVEL_2) textColour = { 0, 255, 0, 255 };
		if (getCurrentLevel() == LEVEL_3) textColour = { 0, 255, 0, 255 };
		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScores, textColour, gFontRetro40, gRenderer)) {
			printf("Unable to render final scores texture!\n");
		}

		gamerOverMessageDisplayCounter++;

		if (gamerOverMessageDisplayCounter >= 100) {
			gamerOverMessageDisplayCounter = 0;

			if (!(player1.getAlive() && player2.getAlive())) {							// If both players are not alive
				resetGame(MENU);														// Reset the current level	CHANGE TO MENU WHEN MENU READY
				gameOver = true;
			}
			else if(player1.getAlive() || player2.getAlive()){							// If there is a player alive
				setCurrentLevel(getCurrentLevel() + 1);															// go to next level
				if (getCurrentLevel() > MAX_NUM_LEVELS)
					gameOver = true;
				else
					resetGame(getCurrentLevel());												// Increment the level and reset
			}
		}
	}// Levels
	else {
		currentTime = SDL_GetTicks();

		// Countdown Timer
		//if (countdownTimer > GAME_TIMER && countdownTimer < GAME_TIMER + 6) {
		//	timeText << "Game Over";
		//	gameOver = true;
		//} else
		if (countdownTimer > 0 && countdownTimer <= GAME_TIMER) {
			timeText << "Time: " << countdownTimer;
			levelOver = false;
		}
		else if (countdownTimer <= 0 || countdownTimer > GAME_TIMER + 6) {
			timeText << "Game Over";
			levelOver = true;
			if (getCurrentLevel() == MAX_NUM_LEVELS)
				gameOver = true;
		}

		if (currentTime > lastTime + 1000) {
			lastTime = currentTime;
			countdownTimer -= 1;
			//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
		}

		// Time running out change colour to red
		if (countdownTimer >= 0 && countdownTimer <= 5) {
			textColour = { 255, 0, 0, 255 };
			gTimeTextTexture.setFlash(true);
		}
		else {
			textColour = { 0, 255, 0, 255 };			// Green text for timer
			gTimeTextTexture.setFlash(false);
		}
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render time texture!\n");
		}

		//Render text - Get a string from it and use it to render the current time to a texture
		textColour = { 0, 255, 0, 255 }; // Green text for UI elements
		if (!gP1ScoreTextTexture.loadFromRenderedText(score1Text.str().c_str(), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render P1 score texture!\n");
		}
		if (!gP2ScoreTextTexture.loadFromRenderedText(score2Text.str().c_str(), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render P2 score texture!\n");
		}
		if (!gFPSTextTexture.loadFromRenderedText(framesPerSec.str().c_str(), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render FPS texture!\n");
		}
		if (!gLevelTextTexture.loadFromRenderedText("Level " + std::to_string(getCurrentLevel()), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render level text texture!\n");
		}
		if (playerMessage != "") {
			textColour = { 240, 210, 65, 255 };			// Gold colour
			if (!gPlayerMessageTextTexture.loadFromRenderedText(playerMessage, textColour, gFontRetro20, gRenderer)) {
				printf("Unable to render player text texture!\n");
			}
		}
	}

	if (gameOver == true) {
		textColour = { 0, 255, 0, 255 };			// Green text
		if (player1.getScore() > player2.getScore())
			gameWinner = "Player 1 Wins";
		else if (player2.getScore() > player1.getScore())
			gameWinner = "Player 2 Wins";
		else
			gameWinner = "It's a draw";

		if (!gFinalScoreTextTexture.loadFromRenderedText(finalScores, textColour, gFontRetro40, gRenderer)) {
			printf("Unable to render final scores texture!\n");
		}
		if (!gGameWinnerTextTexture.loadFromRenderedText(gameWinner, textColour, gFontRetro40, gRenderer)) {
			printf("Unable to render game winner texture!\n");
		}

		gamerOverMessageDisplayCounter++;
		std::cout << "Game over counter: " << gamerOverMessageDisplayCounter << std::endl;

		if (gamerOverMessageDisplayCounter >= 100) {
			gamerOverMessageDisplayCounter = 0;

			if(!player1.getAlive() && !player2.getAlive())
				resetGame(MENU);							// Reset the current level back to menu
			else {
				setCurrentLevel(getCurrentLevel() + 1);								// If there is a player alive go to next level

				if (getCurrentLevel() > MAX_NUM_LEVELS){			// If current game level goes over 3
					gameOver = true;
					resetGame(1);
				}
				else
					resetGame(getCurrentLevel());				// Increment the level a
			}
		}
	}
}

bool Game::playerInput(bool quit = false) {
//	SDL_Color textColor = { 0, 255, 0, 255 };	//Set text color as green

	// In memory text stream
	// string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory
	while (SDL_PollEvent(&e) != 0) {
		// User requests quit	EXIT - CLOSE WINDOW
		if (e.type == SDL_QUIT) {
			quit = true;
		}// Reset start time on return keypress
		else if (e.type == SDL_KEYDOWN) {
		//else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
			//startTime = SDL_GetTicks();		// time since the program started in milliseconds

			switch (e.key.keysym.sym)
			{
			case SDLK_t:
				//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				if (mapViewport.y == 550) {
					mapViewport.x = (SCREEN_WIDTH - 960) / 2;
					mapViewport.y = 20;
					mapViewport.w = 960;
					mapViewport.h = 700;
				}
				else if (mapViewport.y == 20) {
					mapViewport.x = (SCREEN_WIDTH - 230) / 2;
					mapViewport.y = 550;
					mapViewport.w = 230;	// 192
					mapViewport.h = 168;	// 140
				}
				break;

				//case SDLK_DOWN:
				//	topViewport.w = 10;
				//	break;

			default:
				//	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
				break;
			}

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

		// Handle button events
		for (unsigned int i = 0; i < TOTAL_BUTTONS; ++i) {
			gMenuButtons[i].handleEvent(&e, i);
		}

		player1.handleEvent(e, 1);									// Handle input for Player 1
		player2.handleEvent(e, 2);									// Handle input for Player 2


		for (unsigned int index = 0; index != listOfPlayerWeapons.size(); ++index) {
			if (listOfPlayerWeapons[index]->getType() == ROCKET && listOfPlayerWeapons[index]->getPlayer() == PLAYER_1) {
				listOfPlayerWeapons[index]->handleEvent(e, 1);
			}
			else if (listOfPlayerWeapons[index]->getType() == ROCKET && listOfPlayerWeapons[index]->getPlayer() == PLAYER_2) {
				listOfPlayerWeapons[index]->handleEvent(e, 2);
			}
		}

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

int weaponScrolling = 60;
bool Laser1 = false;
bool Laser2 = false;

void Game::renderGameObjects() {
	// Levels
	//if (getCurrentLevel() != 0) {
		//SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 255);
		//SDL_RenderClear(gRenderer);

	//if (weaponScrolling > 0 - gPowerUpLaserTexture.getWidth())
	if (weaponScrolling > 0)
		weaponScrolling--;

	//else if (weaponScrolling == 0 - gPowerUpHealthTexture.getWidth())
	//else if (weaponScrolling == 0)
		//weaponScrolling = 80;
		//Laser1 = true;

		// Set angle increment for rotating textures
		gNinjaStarBlueTexture.setDegrees(gNinjaStarBlueTexture.getDegrees() + 5);
		gNinjaStarYellowTexture.setDegrees(gNinjaStarYellowTexture.getDegrees() + 5);
		gSawTexture.setDegrees(gSawTexture.getDegrees() + 5);
		gBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 1);
		gBloodCellSmallTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);
		gWhiteBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);

		displayText();										// 2017/01/17: Display the game text

		gPlayer1Texture.flashGameObject(10, 4);				// 2017/01/30 Moved flashGameObject() function into LTexture
		gPlayer2Texture.flashGameObject(10, 4);
		gGameOverTextTexture.setFlash(true);
		gGameOverTextTexture.flashGameObject(5);
		gTimeTextTexture.flashGameObject(8);

		// Clear screen
		//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_SetRenderDrawColor(gRenderer, 0x3C, 0x3C, 0x3C, 0xFF);			// Grey colour --> shows up in UI
		SDL_RenderClear(gRenderer);

		SDL_RenderSetViewport(gRenderer, &gameViewport);

		if (levelOver == false) {
			//fpsthink();										// No need to do this if the game is over

			if (backgroundLoopCounter <= BACKGROUND_SCROLL_TIMES) scrollingOffset -= 5;
			if (scrollingOffset < -gBGTexture.getWidth()) {
				scrollingOffset = 0;							// update the scrolling background

				backgroundLoopCounter++;						// count the number of times the background has looped
				std::cout << "Background has looped " << backgroundLoopCounter << " times" << std::endl;
			}

			int backgroundWidth;

			// Render background
			if (backgroundLoopCounter < 1) {
				gBGStartTexture.render(scrollingOffset, 0, gRenderer);									// 1st
				backgroundWidth = gBGStartTexture.getWidth();
			}
			else if (backgroundLoopCounter > BACKGROUND_SCROLL_TIMES) {
				gBGEndTexture.render(scrollingOffset, 0, gRenderer);									// end background
				backgroundWidth = gBGEndTexture.getWidth();
			}
			else {
				gBGTexture.render(scrollingOffset, 0, gRenderer);										// 3rd and every odd number
				backgroundWidth = gBGTexture.getWidth();
			}

			if (backgroundLoopCounter < BACKGROUND_SCROLL_TIMES) {
				gBGTexture.render(scrollingOffset + backgroundWidth, 0, gRenderer);						// 2nd background (and every even number)
				//gBGTexture.render(scrollingOffset + (backgroundWidth * 2), 0, gRenderer);				// 2nd background (and every even number)
			}
			else
				gBGEndTexture.render(scrollingOffset + gBGEndTexture.getWidth(), 0, gRenderer);			// end background

		//if (gameOver == false) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//SDL_RenderDrawRect(gRenderer, &player1.getCollider());

			// Cycle through list of Blood Cells obstacles and render to screen
			for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
				if ((*iterBC)->getType() == BLOOD_CELL)
					(*iterBC++)->render(gBloodCellTexture, gRenderer, -gBloodCellTexture.getDegrees() * (*iterBC)->getRotationDirection());				// Render the Blood Cell, with random rotation direction
				else if ((*iterBC)->getType() == SMALL_BLOOD_CELL)
					(*iterBC++)->render(gBloodCellSmallTexture, gRenderer, -gBloodCellSmallTexture.getDegrees() * (*iterBC)->getRotationDirection());	// Render the Small Blood Cell, with random rotation direction
				else if ((*iterBC)->getType() == WHITE_BLOOD_CELL)
					(*iterBC++)->render(gWhiteBloodCellTexture, gRenderer, -gWhiteBloodCellTexture.getDegrees() * (*iterBC)->getRotationDirection());	// Render the White Blood Cell, with random rotation direction
			}

			// Cycle through list of Enemy Ships and Virus and render to screen
			for (unsigned int index = 0; index != listOfEnemyShips.size(); ++index) {
				listOfEnemyShips[index]->render(gEnemySpriteSheetTexture, gRenderer, &gEnemySpriteClips[enemyFrame / 10], enemyFrame, 4);				// 4 the number of frames
				//SDL_RenderDrawRect(gRenderer, &listOfEnemyShips[index]->getCollider());
			}
			for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
				if (listOfEnemyVirus[index]->getType() == GREEN) listOfEnemyVirus[index]->render(gEnemyVirusTexture, gRenderer);
				else if (listOfEnemyVirus[index]->getType() == ORANGE) listOfEnemyVirus[index]->render(gOrangeVirusSpriteSheetTexture, gRenderer, &gOrangeVirusSpriteClips[enemyFrame / 10], enemyFrame, 6); // 6 the number of frames
				//SDL_RenderDrawRect(gRenderer, &listOfEnemyVirus[index]->getCollider());
			}

			// Cycle through list of Explosions and render to screen
			for (unsigned int index = 0; index != listOfExplosions.size(); ++index) {
				listOfExplosions[index]->render(gExplosionSpriteSheetTexture, gRenderer, &gExplosionClips[explosionFrame / 8], explosionFrame, 12);
				//SDL_RenderDrawRect(gRenderer, &listOfExplosions[index]->getCollider());
				//std::cout << "ExplosionFrame: " << explosionframe << std::endl;
				if (explosionFrame / 8 >= EXPLOSION_ANIMATION_FRAMES) {
					explosionFrame = 0;
					listOfExplosions[index]->setAlive(false);
				}
			}

			// Cycle through list of power up objects and render them to screen
			for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
				if (listOfPowerUps[index]->getType() == 1)
					listOfPowerUps[index]->render(gPowerUpHealthTexture, gRenderer);
				else
					listOfPowerUps[index]->render(gPowerUpLaserTexture, gRenderer);
				//SDL_RenderDrawRect(gRenderer, &listOfPowerUps[index]->getCollider());
			}

			for (unsigned int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
				std::cout << "Laser " << index << " is of type: " << listOfEnemyLaserObjects[index]->getType() << std::endl;
				if (listOfEnemyLaserObjects[index]->getType() == 1) listOfEnemyLaserObjects[index]->render(gVirusFireballTexture, gRenderer); //
				else listOfEnemyLaserObjects[index]->render(gLaserBlueTexture, gRenderer); // gVirusFireballTexture
				//SDL_RenderDrawRect(gRenderer, &listOfEnemyLaserObjects[index]->getCollider());
			}

			for (unsigned int index = 0; index != listOfPlayerWeapons.size(); ++index) {
				if (listOfPlayerWeapons[index]->getType() == NINJA_STAR_P1)
					listOfPlayerWeapons[index]->render(gNinjaStarYellowTexture, gRenderer, gNinjaStarYellowTexture.getDegrees());	// Yellow ninja star for player 1
				else if (listOfPlayerWeapons[index]->getType() == NINJA_STAR_P2)
					listOfPlayerWeapons[index]->render(gNinjaStarBlueTexture, gRenderer, gNinjaStarBlueTexture.getDegrees());		// Blue ninja star for player 2
				else if (listOfPlayerWeapons[index]->getType() == LASER_P1)
					listOfPlayerWeapons[index]->render(gLaserOrangeTexture, gRenderer);
				else if (listOfPlayerWeapons[index]->getType() == LASER_P2)
					listOfPlayerWeapons[index]->render(gLaserGreenTexture, gRenderer);
				else if (listOfPlayerWeapons[index]->getType() == LASER_V2_P1)
					listOfPlayerWeapons[index]->render(gLaserOrangeTexture, gRenderer);
				else if (listOfPlayerWeapons[index]->getType() == LASER_V2_P2)
					listOfPlayerWeapons[index]->render(gLaserGreenTexture, gRenderer);
				else if (listOfPlayerWeapons[index]->getType() == ROCKET)
					listOfPlayerWeapons[index]->render(gRocketTexture, gRenderer, listOfPlayerWeapons[index]->getAngle());

				//SDL_RenderDrawRect(gRenderer, &listOfPlayerWeapons[index]->getCollider());										// Draw the collider for each Weapon object
			}

			for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {														// Render player scores for killing Enemies
				if (listOfGameObjects[index]->getType() == PLAYER_1) {
					listOfGameObjects[index]->render(gPointsValueTextMessage1, gRenderer);
					//listOfGameObjects[index]->render(listOfGameObjects[index]->getTexture(), gRenderer);
				}
				else if (listOfGameObjects[index]->getType() == PLAYER_2) {
					listOfGameObjects[index]->render(gPointsValueTextMessage2, gRenderer);
					//listOfGameObjects[index]->render(listOfGameObjects[index]->getTexture(), gRenderer);
				}
			}

			for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
				(*iterSaw++)->render(gSawTexture, gRenderer, gSawTexture.getDegrees());												// Render the Saw
			}

			// Render Text
			SDL_RenderSetViewport(gRenderer, &UIViewport);
			gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, 120 - gCreatedByTextTexture.getHeight() - 8, gRenderer);
			SDL_RenderSetViewport(gRenderer, &gameViewport);
			//gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, SCREEN_HEIGHT - gCreatedByTextTexture.getHeight() - 8, gRenderer);
			//gLevelTextTexture.render((SCREEN_WIDTH - gLevelTextTexture.getWidth()) / 1.5, 8, gRenderer);
			gLevelTextTexture.render(10, 8, gRenderer);

			if (playerMessageCounter < MESSAGE_TIME) {
				gPlayerMessageTextTexture.render((SCREEN_WIDTH - gPlayerMessageTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gPlayerMessageTextTexture.getHeight()) / 2, gRenderer);
				playerMessageCounter++;
			}

			gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());	// Flash the timer
			//gTimeTextTexture.render(1150, 8, gRenderer);	// LAZY
			gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8, gRenderer);	// LAZY
			//gP1ScoreTextTexture.render(10, 8, gRenderer);
			//gP2ScoreTextTexture.render(170, 8, gRenderer);
			//gFPSTextTexture.render(350, 8, gRenderer);
			gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8, gRenderer);

			// Health Bars for Players
			SDL_Color fgColour = { 0, 255, 0, 255 };								// Set foreground colour as green
			SDL_Color fgColourBlue = { 0, 200, 255, 255 };							// Set foreground colour as green
			SDL_Color bgColour = { 255, 0, 0, 255 };								// Set background colour as red
			SDL_Color bgColourOrange = { 255, 150, 0, 255 };						// Set background colour as red

			if (player1.getAlive()) {
				renderHealthBar(player1.getX() + (player1.getWidth() / 4), player1.getY() - 10, player1.getWidth() / 2, 5, player1.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);
				gPlayer1Texture.modifyAlpha(gPlayer1Texture.getAlpha());
				player1.render(gPlayer1Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);

				SDL_RenderSetViewport(gRenderer, &UIViewport);
				player1.rendPlayerLives(gP1LivesTexture, 1, gRenderer);												// Player Lives
				gP1ScoreTextTexture.render(10, 50, gRenderer);														// Score for Player 1
				gP2ScoreTextTexture.render(SCREEN_WIDTH - gP2ScoreTextTexture.getWidth() - 10, 50, gRenderer);		// Score for Player 2
				SDL_RenderSetViewport(gRenderer, &gameViewport);
			}// render the ship over the background
			if (player2.getAlive()) {
				renderHealthBar(player2.getX() + (player2.getWidth() / 4), player2.getY() - 10, player2.getWidth() / 2, 5, player2.getHealth() / MAX_HEALTH, fgColour, bgColour, HORIZONTAL);
				gPlayer2Texture.modifyAlpha(gPlayer2Texture.getAlpha());
				player2.render(gPlayer2Texture, gDarkBlueParticleTexture, gMediumBlueParticlTexture, gLightBlueParticleTexture, gShimmerTexture, gRenderer);

				SDL_RenderSetViewport(gRenderer, &UIViewport);
				player2.rendPlayerLives(gP2LivesTexture, 2, gRenderer);												// render the ship over the background
				SDL_RenderSetViewport(gRenderer, &gameViewport);
			}

			// Orange Exploding Virus
			currentTime = SDL_GetTicks();
			if (currentTime > newTime + 500) {
				newTime = currentTime;
				virusBar -= 0.5;					// increment every 1/2 second to decrement countdown timer
				//std::cout << "virus counter " << virusBar;
			}
			for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
				if (listOfEnemyVirus[index]->getType() == ORANGE) {						// 2017/01/25 If the type of virus is an Orange Exploding Virus
					if (listOfEnemyVirus[index]->getX() > SCREEN_WIDTH - listOfEnemyVirus[index]->getWidth()) virusBar = 3.0;	// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
					renderHealthBar(listOfEnemyVirus[index]->getX() + listOfEnemyVirus[index]->getWidth() + 10, listOfEnemyVirus[index]->getY() + (listOfEnemyVirus[index]->getHeight() / 6), 5, (listOfEnemyVirus[index]->getHeight() / 3) * 2, virusBar / listOfEnemyVirus[index]->getTimer(), fgColourBlue, bgColourOrange, VERTICAL); // 2/3s the height of the virus

					if (virusBar <= 0) {																												// If the virusBar is 0 or less
						virusBar = 3.0;																													// Reset to 3
						spawnEnemyLaser(listOfEnemyVirus[index]->getX(), listOfEnemyVirus[index]->getY(), 1);											// x, y, and type
						spawnExplosion(listOfEnemyVirus[index]->getX() - listOfEnemyVirus[index]->getWidth(), listOfEnemyVirus[index]->getY() + 10);	// Create an explosion when it dies
						listOfEnemyVirus[index]->setAlive(false);																						// When timer runs out kill the virus
					}
				}
			}


			/* Professor Mini Map */
			/* Weapon Scrolling will work of trigger buttons, press left and right to select main weapon */

			SDL_RenderSetViewport(gRenderer, &mapViewport);						// UIViewport	// SDL_RenderSetViewport(gRenderer, &gameViewport);  // UIViewport
			if (!levelOver) SDL_RenderCopy(gRenderer, gTest, NULL, NULL);		// Render texture to screen
																				// gCreatedByTextTexture.render(scrollingOffset, 10, gRenderer);
			SDL_RenderSetViewport(gRenderer, &weaponViewport1);  // UIViewport
																 //if (!levelOver) SDL_RenderCopy(gRenderer, gWeapon, NULL, NULL);	// Render texture to screen
			if (Laser1) {
				//gPowerUpLaserTexture.render(0, 0, gRenderer);			// 1st
				gPowerUpLaserTextureV2.render(weaponScrolling, 0, gRenderer);			// 1st
																						//weaponScrolling = 60;
			}
			else
				gPowerUpLaserTexture.render(weaponScrolling, 0, gRenderer);			// 1st
																					//gPowerUpLaserTextureV2.render(weaponScrolling + gPowerUpLaserTexture.getWidth(), 0, gRenderer);			// 1st
																					//gCreatedByTextTexture.render(scrollingOffset, 10, gRenderer);
			SDL_RenderSetViewport(gRenderer, &weaponViewport2);  // UIViewport
			if (Laser2) gPowerUpLaserTextureV2.render(weaponScrolling, 0, gRenderer);			// 1st
			else gPowerUpLaserTexture.render(weaponScrolling, 0, gRenderer);			// 1st
			SDL_RenderSetViewport(gRenderer, NULL);								// Reset Viewport

		}
		else if (levelOver == true) {
			SDL_RenderSetViewport(gRenderer, NULL);  // UIViewport   gameViewport
			if (getCurrentLevel() == LEVEL_1) gLevel1.render(0, 0, gRenderer);						// Static background
			else if (getCurrentLevel() == LEVEL_2) gLevel2.render(0, 0, gRenderer);					// Static background
			else if (getCurrentLevel() == LEVEL_3) gLevel3.render(0, 0, gRenderer);					// Static background
			gFinalScoreTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
			gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2, gRenderer); // FOR TESTING
		}

		if (gameOver == true) {
			SDL_RenderSetViewport(gRenderer, NULL);  // UIViewport   gameViewport
			gGameOverTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
			gGameOverTextTexture.render((SCREEN_WIDTH - gGameOverTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTextTexture.getHeight() - 100) / 2, gRenderer); // FOR TESTING
			gFinalScoreTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
			gFinalScoreTextTexture.render((SCREEN_WIDTH - gFinalScoreTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gFinalScoreTextTexture.getHeight() + 300) / 2, gRenderer); // FOR TESTING
			gGameWinnerTextTexture.modifyAlpha(gGameOverTextTexture.getAlpha());
			gGameWinnerTextTexture.render((SCREEN_WIDTH - gGameWinnerTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameWinnerTextTexture.getHeight() + 450) / 2, gRenderer); // FOR TESTING
		}


	//}

	SDL_RenderPresent(gRenderer);											// Update screen
}

void Game::displayScoreForObject(int Xcoord, int Ycoord, int score, int player) {
	GameObject* p_PointsValue = new GameObject();

	pointsValue = "+" + std::to_string(score);				// Change from single string that alters every time its updated
	//p_PointsValue->setName("+" + std::to_string(score));	// Individual string

	if (pointsValue != "") {
		if (player % 2 == 0) {
			if (!gPointsValueTextMessage1.loadFromRenderedText(pointsValue, { 240, 210, 65, 255 }, gFontRetro20, gRenderer)) {	// Gold Text
				printf("Unable to render player text texture!\n");
				p_PointsValue->setTexture(gPointsValueTextMessage1);
			}
		}
		else if (player % 2 == 1) {
			if (!gPointsValueTextMessage2.loadFromRenderedText(pointsValue, { 0, 0, 255, 255 }, gFontRetro20, gRenderer)) {		// Blue Text
				printf("Unable to render player text texture!\n");
				p_PointsValue->setTexture(gPointsValueTextMessage2);
			}
		}
	}

	p_PointsValue->setX(Xcoord);
	p_PointsValue->setY(Ycoord);
	p_PointsValue->setStartTime(SDL_GetTicks());				// Set time the object was created
	p_PointsValue->setScore(score);
	p_PointsValue->setAlive(true);
	p_PointsValue->setType(player);
	if (player % 2 == 0) p_PointsValue->setType(PLAYER_1);
	else if (player % 2 == 1) p_PointsValue->setType(PLAYER_2);
	//p_PointsValue->setTexture(&gPointsValueTextMessage1);

	/*
	// Move out of this function
	p_PointsValue->setName("+" + std::to_string(score));	// Individual string
	if (p_PointsValue->getName() != "") {
		if (player % 2 == 0) {
			if (!gPointsValueTextMessage1.loadFromRenderedText(p_PointsValue->getName(), { 240, 210, 65, 255 }, gFontRetro20, gRenderer)) {	// Gold Text
				printf("Unable to render player text texture!\n");
				p_PointsValue->setTexture(gPointsValueTextMessage1);
			}
		}
		else if (player % 2 == 1) {
			if (!gPointsValueTextMessage2.loadFromRenderedText(p_PointsValue->getName(), { 0, 0, 255, 255 }, gFontRetro20, gRenderer)) {		// Blue Text
				printf("Unable to render player text texture!\n");
				p_PointsValue->setTexture(gPointsValueTextMessage2);
			}
		}
	}
	*/
	listOfGameObjects.push_back(p_PointsValue);
}

void Game::moveGameObjects() {
	if (player1.getAlive()) player1.movement();						// Update ship movement
	if (player2.getAlive()) player2.movement();

	// Cycle through lists of Enemys and move them
	for (unsigned int index = 0; index != listOfEnemyShips.size(); ++index) {
		listOfEnemyShips[index]->movement();
		spawnEnemyLaser(listOfEnemyShips[index]->getX(), listOfEnemyShips[index]->getY());
	}
	// Cycle through list of Enemy virus and move them
	for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
		if (listOfEnemyVirus[index]->getX() > SCREEN_WIDTH && listOfEnemyVirus[index]->getX() < SCREEN_WIDTH + 10 && listOfEnemyVirus[index]->getType() == 1) {
			playerMessageCounter = 0;
			playerMessage = "Exploding Orange Virus Approaching";
		}
		if(abs(listOfEnemyVirus[index]->getX() - player1.getX()) < abs(listOfEnemyVirus[index]->getX() - player2.getX()))	// absolute values to see which is closer on x axis, player1 or 2, and move towards that player
			listOfEnemyVirus[index]->movement(player1.getX(), player1.getY());
		else
			listOfEnemyVirus[index]->movement(player2.getX(), player2.getY());
	}

	// Cycle through list of Blood Cells and move them
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		(*iterBC++)->movement();	// 2017/01/10 JOE: Move the blood cells in a wavey line
	}

	// Cycle through list of Power Ups and move them
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		listOfPowerUps[index]->movement();
	}
	for (unsigned int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
		listOfEnemyLaserObjects[index]->movement();
	}
	for (unsigned int index = 0; index != listOfPlayerWeapons.size(); ++index) {
		listOfPlayerWeapons[index]->movement();
		//SDL_RenderDrawRect(gRenderer, &listOfPlayerWeapons[index]->getCollider());
	}
	for (iterSaw = listOfSawObjects.begin(); iterSaw != listOfSawObjects.end();) {
		if ((*iterSaw)->getPlayer() == PLAYER_1)
			(*iterSaw++)->movement(player1.getX(), player1.getY());	// Move the saw
		else if ((*iterSaw)->getPlayer() == PLAYER_2)
			(*iterSaw++)->movement(player2.getX(), player2.getY());	// Move the saw
	}
}

// Destroy Game Objects
void Game::destroyGameObjects() {
	for (unsigned int index = 0; index != listOfExplosions.size(); ++index) {
		if (!listOfExplosions[index]->getAlive()) {
			listOfExplosions.erase(listOfExplosions.begin() + index);
			//std::cout << "Explosion Destroyed." << std::endl;
			index--;
		}
	}// end for

	for (unsigned int index = 0; index != listOfEnemyShips.size(); ++index) {
		if (!listOfEnemyShips[index]->getAlive()) {
			listOfEnemyShips.erase(listOfEnemyShips.begin() + index);
			//std::cout << "Enemy Ship Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (unsigned int index = 0; index != listOfEnemyVirus.size(); ++index) {
		if (!listOfEnemyVirus[index]->getAlive()) {
			listOfEnemyVirus.erase(listOfEnemyVirus.begin() + index);
			//std::cout << "Enemy Virus Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (iterBC = listOfBloodCells.begin(); iterBC != listOfBloodCells.end();) {
		if (!(*iterBC)->getAlive()) {
			if ((*iterBC)->getType() == BLOOD_CELL) BloodCellsActive--;					// Decrement active blood cells when one is deleted
			else if ((*iterBC)->getType() == SMALL_BLOOD_CELL) smallBloodCellsActive--; // Decrement active small blood cells when one is deleted
			else if ((*iterBC)->getType() == WHITE_BLOOD_CELL) whiteBloodCellsActive--; // Decrement active white blood cells when one is deleted
			iterBC = listOfBloodCells.erase(iterBC);
			//std::cout << "destroy blood cell" << std::endl;
		}
		else {
			iterBC++;
		}
	}

	for (unsigned int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
		if (!listOfEnemyLaserObjects[index]->getAlive()) {
			listOfEnemyLaserObjects.erase(listOfEnemyLaserObjects.begin() + index);
			//std::cout << "Enemy Laser Destroyed." << std::endl;
			index--;
		}
	}// end for

	for (unsigned int index = 0; index != listOfPlayerWeapons.size(); index++) {
		if (!listOfPlayerWeapons[index]->getAlive()) {
			if (listOfPlayerWeapons[index]->getType() == NINJA_STAR_P1) std::cout << "P1 Ninja Star Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == NINJA_STAR_P2) std::cout << "P2 Ninja Star Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == LASER_P1) std::cout << "P1 Laser Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == LASER_P2) std::cout << "P2 Laser Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == LASER_V2_P1) std::cout << "P1 Angle Laser Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == LASER_V2_P2) std::cout << "P2 Angle Laser Destroyed." << std::endl;
			else if (listOfPlayerWeapons[index]->getType() == ROCKET) {
				if (listOfPlayerWeapons[index]->getPlayer() == PLAYER_1) {
					std::cout << "P1 ROCKET Destroyed." << std::endl;
					p1RocketActive = false;
				}
				else if (listOfPlayerWeapons[index]->getPlayer() == PLAYER_2) {
					std::cout << "P2 ROCKET Destroyed." << std::endl;
					p2RocketActive = false;
				}
			}

			listOfPlayerWeapons.erase(listOfPlayerWeapons.begin() + index);
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
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		if (!listOfPowerUps[index]->getAlive()) {
			listOfPowerUps.erase(listOfPowerUps.begin() + index);
			//std::cout << "Power Up Destroyed." << std::endl;
			index--;
		}
	}// end for
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {			// Erase Game Objects
		if (SDL_GetTicks() > listOfGameObjects[index]->getStartTime() + 1000)	// if the current time is more than the start time + 100
			listOfGameObjects[index]->setAlive(false);							// Kill the object

		if (!listOfGameObjects[index]->getAlive()) {
			listOfGameObjects.erase(listOfGameObjects.begin() + index);
			index--;
		}
	}// end for
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
	if (BloodCellsActive < SPAWN_NUM_BLOOD_CELL) {
		BloodCellsActive++;									// increment Blood cell counter
		spawnBloodCell();
	}
	if (smallBloodCellsActive < SPAWN_NUM_BLOOD_CELL_S) {
		smallBloodCellsActive++;							// increment Small blood cell counter
		spawnBloodCell(SMALL_BLOOD_CELL);
	}
	if(whiteBloodCellsActive < SPAWN_NUM_BLOOD_CELL_WHITE){
		whiteBloodCellsActive++;							// increment white blood cell counter
		spawnBloodCell(WHITE_BLOOD_CELL);
	}

	if (listOfPowerUps.size() < SPAWN_NUM_POWER_UPS) {
		spawnPowerUp();
	}
}
void Game::spawnPlayer(int player) {
	int randomYCoord = rand() % 5 + 1;

	if (player == PLAYER_1) {
		player1.spawn(0, (randomYCoord * 110) - 50);						// 2017/01/20: Spawn Player 1 at random Y coord
		player1.setAlive(true);
	}
	else if (player == PLAYER_2) {
		player2.spawn(0, (randomYCoord * 110) - 50);
		if (player2.getY() == player1.getY()) spawnPlayer(2);	// 2017/01/20: Spawn Player 2 at random Y coord + different to Player 1
		player2.setAlive(true);
		//std::cout << "player1.getY() " << player1.getY() << " player2.getY() " << player2.getY() << std::endl;
	}
}

void Game::spawnExplosion(int x, int y) {
	Explosion* p_Explosion = new Explosion(x, y);
	p_Explosion->setAlive(true);
	p_Explosion->spawn(x, y - 30);
	//p_Explosion->spawn(100, 100);
	listOfExplosions.push_back(p_Explosion);
}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomSpeed;

	EnemyShip* p_Enemy = new EnemyShip();
	spawnRandom(x, y, randomSpeed, 50, p_Enemy->getHeight());
	p_Enemy->spawn(x, y, -randomSpeed, p_Enemy->getCollider());
	listOfEnemyShips.push_back(p_Enemy);
}
void Game::spawnEnemyVirus() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 150);
	//int randomExplodingVirus = rand() % 4 + 1;							// 1 in 4 chance of Orange Exploding Virus
	int randomExplodingVirus = 1;										// TEST Orange Virus

	if (randomExplodingVirus == 1) {
		EnemyVirus* p_OrangeVirus = new EnemyVirus(ORANGE, 3.0);		// Orange type = 1
		p_OrangeVirus->spawn(x, y, -4, -2, p_OrangeVirus->getCollider(), ORANGE);
		listOfEnemyVirus.push_back(p_OrangeVirus);
	}
	else {
		EnemyVirus* p_GreenVirus = new EnemyVirus(GREEN, 0);			// Green type = 0
		p_GreenVirus->spawn(x, y, -4, -2, p_GreenVirus->getCollider());
		listOfEnemyVirus.push_back(p_GreenVirus);
	}
}
void Game::spawnBloodCell(int type) {
	int x, y, randomSpeed;
	BloodCell* p_BloodCell = new BloodCell();

	p_BloodCell->setType(type);	// Set the type of Blood Cell

	spawnRandom(x, y, randomSpeed, 200, p_BloodCell->getHeight());
	p_BloodCell->spawn(x, y, -randomSpeed, p_BloodCell->getDistanceBetween());	// 2017/01/24 Added Y padding to keep objects with the game screen boundary
	listOfBloodCells.push_back(p_BloodCell);
}

void Game::spawnPowerUp() {

	int randomPowerup = rand() % 2 + 1;

	int x, y, randomSpeed;

	PowerUp* p_PowerUp = new PowerUp(randomPowerup, 50);						// Type and score
	spawnRandom(x, y, randomSpeed, 200, p_PowerUp->getHeight());				// Spawn with random X and Y coord, and speed between 1 and 3
	p_PowerUp->spawn(x, y, -randomSpeed);										// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	//p_PowerUp->setType(randomPowerup);
	listOfPowerUps.push_back(p_PowerUp);
}

void Game::spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier, int yPadding, int speed) {	// 2017-01-20 Separate out common randomness
	int randomX = rand() % 5 + 1;
	int randomY = rand() % 8 + 1;			// A number between 1 and 8
	randomSpeed = rand() % 3 + speed;

	x = SCREEN_WIDTH + (randomX * xMuliplier);
	y = 40 + (randomY * ((SCREEN_HEIGHT_GAME - yPadding - 80) / 8)); // 40 top and bottom, yPadding, object height
}

// Spawn Weapon at ships location
void Game::spawnLaser(int x, int y, int player, int velocity, int grade) {
	Laser* p_Laser1 = new Laser();
	p_Laser1->setAlive(true);

	if (player == PLAYER_1) {
		p_Laser1->spawn(x + 65, y + 25, velocity, LASER_P1);
		grade = player1.getLaserGrade();
		p_Laser1->setType(LASER_P1);
		p_Laser1->setPlayer(PLAYER_1);
		p_Laser1->setCollider((*p_Laser1->getCollider()));
	}
	else if (player == PLAYER_2) {
		p_Laser1->spawn(x + 65, y + 25, velocity, LASER_P2);
		grade = player2.getLaserGrade();
		p_Laser1->setType(LASER_P2);
		p_Laser1->setPlayer(PLAYER_2);
	}

	listOfPlayerWeapons.push_back(p_Laser1);

	if (grade == 1) {		// FIRE 2 MORE LASERS AT ANGLES
		Laser* p_Laser2 = new Laser(1, 1);
		Laser* p_Laser3 = new Laser(2, 1);;

		if (player == PLAYER_1) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_1, LASER_P1);
			p_Laser3->spawn(x + 65, y + 35, velocity, PLAYER_1, LASER_P1);
		}
		else if (player == PLAYER_2) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_2, LASER_P2);
			p_Laser3->spawn(x + 65, y + 35, velocity, PLAYER_2, LASER_P2);
		}

		listOfPlayerWeapons.push_back(p_Laser2);
		listOfPlayerWeapons.push_back(p_Laser3);
	}

	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gLaserFX2, 0);
	}
}
void Game::spawnEnemyLaser(int xCoord, int yCoord, int type) {
	if (type == 0 && xCoord < SCREEN_WIDTH) {											// first type and visible on screen, start shooting
		LaserEnemy* p_LaserE = new LaserEnemy();
		int randomLaser = rand() % 3 + 1;
		int distanceBetweenShots = (50 * randomLaser) + 50;								// 2017/01/20 More random shooting from enemies
		//if (shipX % 100 == 0) {
		if (xCoord % distanceBetweenShots < 5) {										// 2017-01-20 Not all ships were firing
			p_LaserE->spawn(xCoord, yCoord, p_LaserE->getCollider());
			listOfEnemyLaserObjects.push_back(p_LaserE);
			Mix_PlayChannel(-1, gLaserEFX, 0);
		}
	}
	else if(type == 1){
		for (unsigned int i = 1; i < 9; i++) {
			//std::cout << "Laser " << i << " created" << std::endl;
			LaserEnemy* p_Laser = new LaserEnemy(1);					// Create an Enemy Laser of type 1 (Orange Virus)
			p_Laser->spawn(xCoord, yCoord, p_Laser->getCollider());		// Spawn the laser from the Virus Coordinates

			if(i == 1) p_Laser->setVelX(p_Laser->getVelocity());		// Set the direction for the 8 Orange Virus Lasers
			else if(i == 2) p_Laser->setVelX(-p_Laser->getVelocity());
			else if (i == 3) {
				p_Laser->setVelX(0);
				p_Laser->setVelY(p_Laser->getVelocity());
			}
			else if (i == 4) {
				p_Laser->setVelX(0);
				p_Laser->setVelY(-p_Laser->getVelocity());
			}
			else if (i == 5) {
				p_Laser->setVelX(p_Laser->getVelocity() / sqrt(2));
				p_Laser->setVelY(-p_Laser->getVelocity() / sqrt(2));
			}
			else if (i == 6) {
				p_Laser->setVelX(p_Laser->getVelocity() / sqrt(2));
				p_Laser->setVelY(p_Laser->getVelocity() / sqrt(2));
			}
			else if (i == 7) {
				p_Laser->setVelX(-(p_Laser->getVelocity() / sqrt(2)));
				p_Laser->setVelY(-(p_Laser->getVelocity() / sqrt(2)));
			}
			else if (i == 8) {
				p_Laser->setVelX(-(p_Laser->getVelocity() / sqrt(2)));
				p_Laser->setVelY(p_Laser->getVelocity() / sqrt(2));
			}

			listOfEnemyLaserObjects.push_back(p_Laser);					// Add the Enemy Lasers to a list to move and render
		}
	}
}
void Game::spawnNinjaStar(int x, int y, int player) {					// player to spawn for and their coords
	NinjaStar* p_NinjaStar = new NinjaStar();
	p_NinjaStar->spawn(x, y, p_NinjaStar->getCollider());
	p_NinjaStar->setPlayer(player);										// 2017/01/17 Set the player the laser belongs too

	std::cout << "Ninja Star Spawned " << player << "p1 " << PLAYER_1 << " p2 " << PLAYER_2 << std::endl;

	if (player == PLAYER_1) p_NinjaStar->setType(NINJA_STAR_P1);
	else if (player == PLAYER_2) p_NinjaStar->setType(NINJA_STAR_P2);

	listOfPlayerWeapons.push_back(p_NinjaStar);
	if (!gameOver) {
		if (player == 1) Mix_PlayChannel(-1, gNinjaFX1, 0);
		if (player == 2) Mix_PlayChannel(-1, gNinjaFX2, 0);
	}
}

void Game::spawnRocket(int x, int y, int player, int type) {
	if (player == PLAYER_1 && !p1RocketActive) {
		Rocket* p_Rocket = new Rocket();
		p_Rocket->spawn(x, y, p_Rocket->getCollider(), player, type);
		p_Rocket->setType(ROCKET);
		std::cout << "Rocket Spawned" << std::endl;
		listOfPlayerWeapons.push_back(p_Rocket);
		p1RocketActive = true;
	}
	else if (player == PLAYER_2 && !p2RocketActive) {
		Rocket* p_Rocket = new Rocket();
		p_Rocket->spawn(x, y, p_Rocket->getCollider(), player, type);
		p_Rocket->setType(ROCKET);
		std::cout << "Rocket Spawned" << std::endl;
		listOfPlayerWeapons.push_back(p_Rocket);
		p2RocketActive = true;
	}

}

void Game::spawnSaw(int x, int y, int player) {				// player to spawn for and their coords, turn on if inacive, off if active
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

//bool Game::checkCollision(SDL_Rect *a, SDL_Rect *b) {
bool checkCollision(SDL_Rect *a, SDL_Rect *b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = (*a).x;
	rightA = (*a).x + (*a).w;
	topA = (*a).y;
	bottomA = (*a).y + (*a).h;

	//Calculate the sides of rect B
	leftB = (*b).x;
	rightB = (*b).x + (*b).w;
	topB = (*b).y;
	bottomB = (*b).y + (*b).h;

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

void Game::collisionCheck() {
	// Check if Player 1  or 2 has collided with an enemy virus
	for (unsigned int index1 = 0; index1 != listOfEnemyVirus.size(); ++index1) {
		if (checkCollision(player1.getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
			if (player1.getSawActive() && listOfEnemyVirus[index1]->getType() == GREEN) {
				listOfEnemyVirus[index1]->setAlive(false);						// If saw is active kill that enemy
			}
			else if (listOfEnemyVirus[index1]->getType() == ORANGE) {
				virusBar = 0;
			}
			else
				if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfEnemyVirus[index1]->getScore() / 3, "Enemy Virus");	// If player 1 isn't flashing, Take off 5 health
		}
		else if (checkCollision(player2.getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
			if (player2.getSawActive() && listOfEnemyVirus[index1]->getType() == GREEN) {
				listOfEnemyVirus[index1]->setAlive(false);						// If saw is active kill that enemy
			}
			else if (listOfEnemyVirus[index1]->getType() == ORANGE) {
				virusBar = 0;
			}
			else
				if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfEnemyVirus[index1]->getScore() / 3, "Enemy Virus");	//  If player 2 isn't flashing, Take off 5 health
		}
	}

	// Check if Player has colided with Enemy Ship
	for (unsigned int index2 = 0; index2 != listOfEnemyShips.size(); ++index2) {
		if (checkCollision(player1.getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
			if (player1.getSawActive()) {
				listOfEnemyShips[index2]->setAlive(false);										// If saw is active kill that enemy
			}
			else
				if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfEnemyShips[index2]->getScore() / 5, "Enemy Ship");	// Take off 5 health
		}
		else if (checkCollision(player2.getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
			if (player2.getSawActive()) {
				listOfEnemyShips[index2]->setAlive(false);										// If saw is active kill that enemy
			}
			else
				if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfEnemyShips[index2]->getScore() / 5, "Enemy Ship");	// Take off 5 health
		}
	}

	// Check if Player 1 or 2 has picked up a power up
	for (unsigned int index = 0; index != listOfPowerUps.size(); ++index) {
		if (checkCollision(player1.getCollider(), listOfPowerUps[index]->getCollider()) == true) {
			player1.setScore(player1.getScore() + listOfPowerUps[index]->getScore());
			//player1.setHealth(player1.getHealth() + listOfPowerUps[index]->getScore());

			if (listOfPowerUps[index]->getType() == HEALTH) {
				managePlayerHealth(PLAYER_1, -listOfPowerUps[index]->getScore());
				playerMessageCounter = 0;
				playerMessage = "Player 1 has increased their health!!!";
			}
			else if (listOfPowerUps[index]->getType() == LASER) {
				player1.setScore(player1.getScore() + listOfPowerUps[index]->getScore());
				player1.setLaserGrade(1);
				Laser1 = true;
				std::cout << "Player 1 has picked up a laser power up" << std::endl;
				playerMessageCounter = 0;
				playerMessage = "Player 1 has upgraded their laser!!!";
			}

			listOfPowerUps[index]->setAlive(false);
		}
		else if (checkCollision(player2.getCollider(), listOfPowerUps[index]->getCollider()) == true) {
			player2.setScore(player2.getScore() + listOfPowerUps[index]->getScore());
			//player2.setHealth(player2.getHealth() + listOfPowerUps[index]->getScore());

			if (listOfPowerUps[index]->getType() == HEALTH) {
				managePlayerHealth(PLAYER_2, -listOfPowerUps[index]->getScore());
				playerMessageCounter = 0;
				playerMessage = "Player 2 has increased their health!!!";
			}
			else if (listOfPowerUps[index]->getType() == LASER) {
				player2.setScore(player2.getScore() + listOfPowerUps[index]->getScore());
				player2.setLaserGrade(1);
				Laser2 = true;
				std::cout << "Player 2 has picked up a laser power up" << std::endl;
				playerMessageCounter = 0;
				playerMessage = "Player 2 has upgraded their laser!!!";
			}

			listOfPowerUps[index]->setAlive(false);
			//std::cout << "Power Up Picked Up by " << player2.getName() << "!\n";
		}
	}

	// Cycle through Ninja Stars and Lasers, and check collision with Enemy Ships and Virus
	for (unsigned int index = 0; index != listOfPlayerWeapons.size(); index++) {
		for (unsigned int index1 = 0; index1 != listOfEnemyVirus.size(); index1++) {
			if (checkCollision(listOfPlayerWeapons[index]->getCollider(), listOfEnemyVirus[index1]->getCollider()) == true) {
				managePlayerScores(listOfEnemyVirus[index1]->getScore(), listOfPlayerWeapons[index]->getPlayer());		// 2017-02-06 Add to players score

				pointsValueCounter = 0;
				displayScoreForObject(listOfEnemyVirus[index1]->getX(), listOfEnemyVirus[index1]->getY(), listOfEnemyVirus[index1]->getScore(), listOfPlayerWeapons[index]->getType());	// Display Score

				spawnExplosion(listOfPlayerWeapons[index]->getX(), listOfPlayerWeapons[index]->getY());
				score(listOfPlayerWeapons[index]->getType());

				listOfEnemyVirus[index1]->setAlive(false);
				listOfPlayerWeapons[index]->setAlive(false);	// DESTROY
			}
		}
		for (unsigned int index2 = 0; index2 != listOfEnemyShips.size(); index2++) {
			if (checkCollision(listOfPlayerWeapons[index]->getCollider(), listOfEnemyShips[index2]->getCollider()) == true) {
				managePlayerScores(listOfEnemyShips[index2]->getScore(), listOfPlayerWeapons[index]->getPlayer());		// 2017-02-06 Add to players score

				pointsValueCounter = 0;
				//pointsValue = "Score + " + std::to_string(listOfEnemyShips[index2]->getScore());
				displayScoreForObject(listOfEnemyShips[index2]->getX(), listOfEnemyShips[index2]->getY(), listOfEnemyShips[index2]->getScore(), listOfPlayerWeapons[index]->getType());  // Display Score

				spawnExplosion(listOfPlayerWeapons[index]->getX(), listOfPlayerWeapons[index]->getY());
				score(listOfPlayerWeapons[index]->getType());

				listOfEnemyShips[index2]->setAlive(false);
				listOfPlayerWeapons[index]->setAlive(false);
			}
		}
	}

	// Check if Enemy Laser has collided with Player 1 or 2
	for (unsigned int index = 0; index != listOfEnemyLaserObjects.size(); ++index) {
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

void Game::managePlayerScores(int score, int player) {
	if (player == PLAYER_1) player1.setScore(player1.getScore() + score);
	else if (player == PLAYER_2) player2.setScore(player2.getScore() + score);
}

void Game::score(int type) {
	if (type == NINJA_STAR_P1) std::cout << "Enemy Ship Killed by Player 1 Ninja Star!\n";
	else if (type == NINJA_STAR_P2) std::cout << "Enemy Ship Killed by Player 2 Ninja Star!\n";
	else if (type == LASER_P1) std::cout << "Enemy Ship Killed by Player 1 Laser!\n";
	else if (type == LASER_P2) std::cout << "Enemy Ship Killed by Player 2 Laser!\n";
	else if (type == SAW_P1) std::cout << "Enemy Ship Killed by Player 1 Saw!\n";
	else if (type == SAW_P2) std::cout << "Enemy Ship Killed by Player 2 Saw!\n";
	else if (type == LASER_V2_P1) std::cout << "Enemy Ship Killed by Player 1 Upgraded Laser!\n";
	else if (type == LASER_V2_P2) std::cout << "Enemy Ship Killed by Player 2 Upgraded Laser!\n";
	else if (type == ROCKET) std::cout << "Enemy Ship Killed by Player Rocket!\n";

	Mix_PlayChannel(-1, gExplosionFX, 0);
}

void Game::managePlayerHealth(int player, int score, std::string name) {
	if (player == PLAYER_1) {
		gPlayer1Texture.setFlash(true);								// Flash on collision with Game Object
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
		gPlayer2Texture.setFlash(true);								// Flash on collision with Game Object
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
		if (player == PLAYER_1) std::cout << "Player 1 has collided with " << name << "! Health: " << player1.getHealth() << std::endl;
		if (player == PLAYER_2) std::cout << "Player 2 has collided with " << name << "! Health: " << player2.getHealth() << std::endl;
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
int Game::getCurrentLevel() {
	return mCurrentLevel;
}
void Game::setCurrentLevel(int l) {
	mCurrentLevel = l;
}

/* 2017/01/25	Added explosions when lasers collide with Enemy Ships and Virus
//				Fixed error for Player Message Text
//				Fixed Ninja Star scoring for Player 2
// 2017/01/24	Changed fonts and graphics at start of level, and start and end of scrolling background
//				Added Menu to main code
//				Changed to 1280 x 720 from 800 x 600
// 2017/01/23	Set up levels and background
// 2017/01/09	Edited background to be 800 x 600 instead of 600 x 480
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"					// Game header file, with functions and variabls
#include <sstream>					// For timer
#include <SDL_mixer.h>				// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include "Texture.h"				// Game textures
#include "Player.h"					// Player class
#include "EnemyShip.h"				// Enemy ship class
#include "EnemyVirus.h"				// 2017/01/10 JOE: Added Seans virus enemy
#include "WeaponEnLaser.h"			// The laser the enemy firesF
#include "WeaponPlLaser.h"			// Player Laser weapon
#include "WeaponPlNinjaStar.h"		// Player Ninja Star weapon
#include "WeaponPlRocket.h"			// 2017-02-06
#include "WeaponPlSaw.h"			// 2017/01/17 Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell obstacle
#include "PowerUp.h"				// 2017/01/10 SEAN: Added Power Up
//#include "Particle.h"				// Particles for the ship engine
#include "Menu.h"					// 2017/02/14 Includes button.h
//#include "Button.h"
#include "Explosion.h"				// 2017/01/25 Added explosions for Player Laser colliding with Enemy Ships and Virus
#include "FPS.h"
#include "SplashScreen.h"			// 2017/02/08
#include "ScoreValueText.h"			// 2017-02-09
#include "StatusBar.h"				// 2017/02/09
#include "_TestData.h"				// 2017/02/09
#include "CollisionStuff.h"			// 2017/02/09
#include "Gamepad.h"				// 2017/02/09
#include "Audio.h"					// 2017/02/09
#include <math.h>


/***************************************************************************************************************************/
/******************************************** TURN STUFF ON AND OFF FOR TESTING ********************************************/

// Game & Level Testing
bool quit = false;					// Main loop flag
bool testMode = true;				// Game is in testing
bool displayGameIntro;				// False means off - set in _TestData.h
bool displayLevelIntro;				// Display the information splash screen at the start of a level - set in _TestData.h

/***************************************************************************************************************************/

// Weapons
int rocket1BonusScore;
int rocket2BonusScore;
bool killRocket1 = false;
bool killRocket2 = false;
bool Laser1 = false;
bool Laser2 = false;

void setViewport(SDL_Rect &rect, int x, int y, int w, int h);	// These classes are giving errors when they are moved to the header file
bool checkCollision(SDL_Rect *a, SDL_Rect *b);

// Classes
//Particle particle;
Texture texture;
GameObject loadGameObjects;
Menu menu1;
Audio audio;
StatusBar bar;
SplashScreen splash;
FPS fps;							// 2017/02/01 Moved FPS functionality to it's own class

// Viewports
SDL_Rect gameViewport;				// Main game screen view port
SDL_Rect UIViewport;				// Menu below main game screen view port
SDL_Rect mapViewport;				// Map indicating the ships current location in the professors body
SDL_Rect weaponViewport1;			// Indicates the currently selected main weapon
SDL_Rect weaponViewport2;			// Indicates the currently selected main weapon
Texture gProfessorMapTexture;		// Map texture to show the players current position inside the professor
//Texture gWeapon;					// Background texture

// Animation
int frame = 0;											// Current animation frame
const int ANIMATION_FRAMES = 4;							// Number of frames of animation for Enemy Ship
const int EXPLOSION_ANIMATION_FRAMES = 12;				// Number of frames of animation for Explosions
SDL_Rect gEnemySpriteClips[ANIMATION_FRAMES];			// Sprite frames for Enemy Ship animation
SDL_Rect gOrangeVirusSpriteClips[6];					// Sprite frames for Orange Virus animation
SDL_Rect gBlueVirusSpriteClips[6];						// Sprite frames for Blue Virus animation
SDL_Rect gExplosionClips[EXPLOSION_ANIMATION_FRAMES];	// Sprite frames for Explosion animation

Texture gEnemySpriteSheetTexture;		// Enemy sprite sheet
Texture gExplosionSpriteSheetTexture;	// explosion sprite sheet
Texture gOrangeVirusSpriteSheetTexture;	// Orange Virus sprite sheet
Texture gBlueVirusSpriteSheetTexture;	// Orange Virus sprite sheet
int animationFrames = 0;				// Frame count for speed of Enemy animation

SDL_Event e;							// Event handler

// Joystick
SDL_Joystick* gController1 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Joystick* gController2 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Haptic*	gControllerHaptic = NULL;	// 2017/01/18 Haptic (Force Feedback) added

SDL_Window* gWindow = NULL;				// The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;			// The window renderer

// Text
SDL_Color textColour;					// Set the text colour
TTF_Font *gFontRetro20;					// Globally used font 2017-01-25 Changed to Retro font which is more readable
int gamerOverMessageDisplayCounter = 0;	// Length of time to display game over message

// Scene textures
Texture gBGTexture;					// Background
Texture gBGStartTexture;			// Start of background
Texture gBGEndTexture;				// End of background scrolling
// Objects and weapons
Texture gPlayer1Texture;			// Player 1 ship
Texture gP1LivesTexture;			// Player 1 Small ship for number of lives
Texture gPlayer2Texture;			// Player 2 ship
Texture gP2LivesTexture;			// Player 2 Small Ship for number of lives
Texture gEnemyShipTexture;			// Enemy Ship for info screen
Texture gEnemyVirusTexture;			// Enemy Virus
Texture gEnemyVirusOrangeTexture;	// Enemy Virus Orange
Texture gVirusFireballTexture;		// Enemy Virus Fireball
Texture gEnemyVirusBlueTexture;		// Enemy Virus Blue
Texture gVirusShield;				// Enemy Virus Rotating Shield
Texture gLaserGreenTexture;			// Texture for Player 1 Laser weapon
Texture gLaserOrangeTexture;		// Texture for Player 2 Laser weapon
Texture gLaserBlueTexture;			// Texture for Enemy Laser weapon
Texture gPowerUpHealthTexture;		// Texture for Health Box Power Up
Texture gPowerUpLaserTexture;		// Texture for Laser Power Up
Texture gPowerUpLaserTextureV2;		// Texture for Health Box Power Up
Texture gRocketTexture;				// Texture for Rocket weapon
Texture gPowerUpRocketTexture;		// Texture for Rocket power up
Texture gPowerUpCheckpointTexture;	// Texture for Checkpoint power up
// Rotating Objects and Weapons (degrees to rotate in brackets)
Texture gNinjaStarBlueTexture(5);	// Texture for Ninja Star weapon
Texture gNinjaStarYellowTexture(5);	// Texture for Ninja Star weapon // 2017-01-30 with rotation angle of 5 degrees
Texture gSawTexture(5);				// Texture for Ninja Star weapon
Texture gBloodCellTexture(1);		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
Texture gBloodCellSmallTexture(2);	// Texture for Smaller Blood Cell
Texture gWhiteBloodCellTexture(2);	// Texture for White Blood Cell
// UI
Texture gTimeTextTexture;			// Countdown time displayed in game screen
Texture gCreatedByTextTexture;		// Created by message at bottom of screen for demo
Texture gLevelTextTexture;			// Current level displayed at top of game screen
Texture gP1ScoreTextTexture;		// Player 1 current score
Texture gP2ScoreTextTexture;		// Player 2 current score
Texture gFPSTextTexture;			// Frames Per Second displayed at top of screen
Texture gInfoMessageP1TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageP2TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageTextTexture;	// Player notification messages for picking up objects etc.
Texture gPointsValueTextMessage1;	// Points value for a destroyed enemy Virus or Ship
Texture gPointsValueTextMessage2;	// Points value for a destroyed enemy Virus or Ship

// Vectors for objects that have collisions - These 2 lists are the only 2 we need
std::vector<Texture*> listOfScoreTextures;		// The score for any object a player Kills
std::vector<GameObject*> listOfGameObjects;		// 2017/01/31 Using to display the scores for each object killed, 2017/02/15 added Power Ups, Explosions

GameObject* player1 = new Player();
GameObject* player2 = new Player();

bool Game::init() {
	listOfGameObjects.push_back(player1);
	listOfGameObjects.push_back(player2);

	resetGame(getCurrentLevel());										// Initialise variables depending on level

	// View ports
	setViewport(gameViewport, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// Main Game Screen
	setViewport(UIViewport, 0, 600, SCREEN_WIDTH, 120);					// Bottom of screen UI / Info
	setViewport(weaponViewport1, 10, 600, 60, 60);						// Current Main Weapon Selected
	setViewport(weaponViewport2, SCREEN_WIDTH - 60 - 10, 600, 60, 60);	// Current Main Weapon Selected

	// Game Console Title
	std::cout << "16//02/2017 - Fixed Player Movement, edited rockets, added info message function, fixed Map size & alpha\n" << std::endl;
	std::cout << "Player 1 Health: " << player1->getHealth() << " " << "Player 2 Health: " << player2->getHealth() << std::endl;		// Player health at start of game
	std::cout << "Player 1 Lives: " << player1->getNumLives() << " " << "Player 2 Lives: " << player2->getNumLives() << std::endl;
	player1->setName("Player 1");	// Names for players
	player1->setSubType(PLAYER_1);
	player2->setName("Player 2");
	player2->setSubType(PLAYER_2);

	if (testMode) player1->setNumLives(NUM_LIVES);
	if (testMode) player2->setNumLives(NUM_LIVES);

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

			printf("Joystick connected\n");					// DETECTS JOYSTICK
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

	menu1.loadMediaMenu(gRenderer);						// Load buttons etc
	//success = player1->loadMediaPlayer(gRenderer);		// Load particles for each player
	//success = player2->loadMediaPlayer(gRenderer);		// Load particles for each player
	success = audio.loadMediaAudio();
	//success = particle.loadMediaParticles(gRenderer);		// 2017-02-18 Moved particle textures to Particles class
	success = loadGameObjects.loadMediaPlayer(gRenderer);		// 2017-02-18 Moved particle textures to Particles class

	if (!gProfessorMapTexture.loadFromFile("Art/Prof.png", gRenderer)) {			// Load Dark Particle texture
		printf("Failed to load Professor texture image!\n");
		success = false;
	}
//	if (!gWeapon.loadFromFile("Art/LaserGun2.png", gRenderer)) {	// Load Dark Particle texture
//		printf("Failed to load LaserGun texture image!\n");
//		success = false;
//	}

	// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };													// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);										// Use bold font

		if (!gCreatedByTextTexture.loadFromRenderedText("A Game By Sean Horgan and Joe O'Regan", textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render prompt text texture!\n");
			success = false;
		}
	}

	// Load Textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png", gRenderer)) {					// Player 1 Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
//	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.png", gRenderer)) {					// Player 2 Ship Texture
	if (!gPlayer2Texture.loadFromFile("Art/Player2ShipOld.png", gRenderer)) {					// Player 2 Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gP1LivesTexture.loadFromFile("Art/Player1ShipSmall.png", gRenderer)) {				// Player 1 Lives Texture
		printf("Failed to load Player 1 Small Ship texture!\n");
		success = false;
	}
//	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmall.png", gRenderer)) {				// Player 2 Lives Texture
	if (!gP2LivesTexture.loadFromFile("Art/Player2ShipSmallOld.png", gRenderer)) {				// Player 2 Lives Texture
		printf("Failed to load Player 2 Small Ship texture!\n");
		success = false;
	}
	if (!gVirusFireballTexture.loadFromFile("Art/VirusFireball.png", gRenderer)) {			// Enemy Virus Texture - Orange Fireball
		printf("Failed to load Enemy Virus Orange Fireball texture!\n");
		success = false;
	}
	if (!gVirusShield.loadFromFile("Art/EnemyVirusSatellite.png", gRenderer)) {				// Enemy Virus Texture - Blue Fireball
		printf("Failed to load Enemy Virus Orange Fireball texture!\n");
		success = false;
	}
	if (!gEnemyShipTexture.loadFromFile("Art/EnemyShip.png", gRenderer)) {					// Enemy Ship Texture
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
//	if (!gEnemyVirusTexture.loadFromFile("Art/EnemyVirus.png", gRenderer)) {				// Enemy Virus Texture - Green
	if (!gEnemyVirusTexture.loadFromFile("Art/VirusGreen.png", gRenderer)) {				// Enemy Virus Texture - Green
		printf("Failed to load Enemy Virus texture!\n");
		success = false;
	}
//	if (!gEnemyVirusOrangeTexture.loadFromFile("Art/EnemyVirusOrange.png", gRenderer)) {	// Enemy Virus Texture - Orange
	if (!gEnemyVirusOrangeTexture.loadFromFile("Art/VirusOrange.png", gRenderer)) {	// Enemy Virus Texture - Orange
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
	if (!gWhiteBloodCellTexture.loadFromFile("Art/WhiteCell.png", gRenderer)) {				// 10/01 White Blood Cell
		printf("Failed to load White Blood Cell texture!\n");
		success = false;
	}
	if (!gBGTexture.loadFromFile("Art/Background720.png", gRenderer)) {						// 09/01 Edited background to be 800 x 600 instead of 600 * 480
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gBGStartTexture.loadFromFile("Art/bgBegin720a.png", gRenderer)) {					// Background start texture
		printf("Failed to load start background texture!\n");
		success = false;
	}
	if (!gBGEndTexture.loadFromFile("Art/bgEnd720a.png", gRenderer)) {						// Background end texture
		printf("Failed to load end background texture!\n");
		success = false;
	}
	// Weapons
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
	if (!gSawTexture.loadFromFile("Art/SawBlue.png", gRenderer)) {							// Saw Texture
		printf("Failed to load Blue Saw texture!\n");
		success = false;
	}
	if (!gRocketTexture.loadFromFile("Art/Rocket.png", gRenderer)) {						// Rocket Texture
		printf("Failed to load Rocket texture!\n");
		success = false;
	}
	// Power Ups
//	if (!gPowerUpCheckpointTexture.loadFromFile("Art/Clock.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
	if (!gPowerUpCheckpointTexture.loadFromFile("Art/PowerUpClockOld.png", gRenderer)) {								// 10/01 Added Power Up - Load Power Up texture
		printf("Failed to load Checkpoint texture!\n");
		success = false;
	}
//	if (!gPowerUpRocketTexture.loadFromFile("Art/RocketPowerUp.png", gRenderer)) {			// Rocket Power Up Texture
	if (!gPowerUpRocketTexture.loadFromFile("Art/PowerUpRocket.png", gRenderer)) {			// Rocket Power Up Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}
//	if (!gPowerUpHealthTexture.loadFromFile("Art/HealthBox.png", gRenderer)) {				// 10/01 Added Power Up - Health Power Up texture
	if (!gPowerUpHealthTexture.loadFromFile("Art/PowerUpHealthBox.png", gRenderer)) {				// 10/01 Added Power Up - Health Power Up texture
		printf("Failed to load Health Power Up texture!\n");
		success = false;
	}
//	if (!gPowerUpLaserTexture.loadFromFile("Art/LaserGun2.png", gRenderer)) {				// 10/01 Added Power Up - Laser Power Up texture
	if (!gPowerUpLaserTexture.loadFromFile("Art/PowerUpLaser.png", gRenderer)) {				// 10/01 Added Power Up - Laser Power Up texture
		printf("Failed to load Laser Power Up texture!\n");
		success = false;
	}
//	if (!gPowerUpLaserTextureV2.loadFromFile("Art/LaserGunV2.png", gRenderer)) {			// 10/01 Added Power Up - Laser V2 Power Up texture
	if (!gPowerUpLaserTextureV2.loadFromFile("Art/LaserGunV3.png", gRenderer)) {			// 10/01 Added Power Up - Laser V2 Power Up texture
		printf("Failed to load Laser V2 Power Up texture!\n");
		success = false;
	}

	success = splash.initSplashScreens(gRenderer);											// Initialise the splash screens

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

//	if (!gOrangeVirusSpriteSheetTexture.loadFromFile("Art/OrangeVirusSpriteSheet.png", gRenderer)) {	// Sprite sheet for Enemy Orange Virus
	if (!gOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange.png", gRenderer)) {	// Sprite sheet for Enemy Orange Virus
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

//	if (!gBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirusBlue_SpriteSheet.png", gRenderer)) {	// Sprite sheet for Enemy Blue Virus
	if (!gBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Blue.png", gRenderer)) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Blue Virus animation texture!\n");
		success = false;
	}
	else {
		//Set sprite clips
		for (unsigned int i = 0; i < 6; ++i) {
			if (i < 4) gBlueVirusSpriteClips[i].x = i * 75;
			if (i == 5) gBlueVirusSpriteClips[i].x = 2 * 75;
			if (i == 6) gBlueVirusSpriteClips[i].x = 1 * 75;
			gBlueVirusSpriteClips[i].y = 0;
			gBlueVirusSpriteClips[i].w = 75;
			gBlueVirusSpriteClips[i].h = 75;
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

	if (MUSIC_ON) audio.music();		// EDIT IN _TestData.h

	return success;
}

void Game::close() {
	// Free loaded images
	gPlayer1Texture.free();
	gPlayer2Texture.free();
	gP1LivesTexture.free();
	gP2LivesTexture.free();
	gEnemyShipTexture.free();
	gEnemyVirusTexture.free();
	gEnemyVirusOrangeTexture.free();
	gVirusFireballTexture.free(); //
	gVirusShield.free();
	gBGTexture.free();
	gBGStartTexture.free();
	gBGEndTexture.free();

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
	gPowerUpCheckpointTexture.free();
	// free animations
	gEnemySpriteSheetTexture.free();

	gTimeTextTexture.free();
	gCreatedByTextTexture.free();
	gLevelTextTexture.free();
	gP1ScoreTextTexture.free();
	gP2ScoreTextTexture.free();
	gFPSTextTexture.free();
	gInfoMessageP1TextTexture.free();
	gInfoMessageP2TextTexture.free();
	gInfoMessageTextTexture.free();
	gPointsValueTextMessage1.free();
	gPointsValueTextMessage2.free();

	//Free global font
	TTF_CloseFont(gFontRetro20);
	gFontRetro20 = NULL;

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

	splash.closeSplashScreens();	// Close splash screen stuff
	menu1.closeMenu();				// Close menu stuff
	//player1->closePlayer();
	//player2->closePlayer();
	audio.destroy();				// Close audio files
	//particle.closeParticle();		// Close textures for particles
	loadGameObjects.closePlayer();

	// Quit SDL subsystems
	IMG_Quit();
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
				gamepadInfo(gController1, gController2, e);					// 2017/02/09 Display gamepad information, moved to separate header file
			}
			// MAIN GAME LOOP:  While application is running
			while (!quit) {
				quit = playerInput(quit);									// 2017/01/09 JOE: Handle input from player

				//particle.createParticle(player1->getX(), player1->getY());

				if (getCurrentLevel() == 0 && displayGameIntro) displayGameIntro = splash.displayGameIntroSplashScreens(gRenderer);	// 2017/01/18 Splash screens at start of game, Game Title & Game Creators

				if (getCurrentLevel() == MENU) menu1.draw(gRenderer);		// New

				if (getCurrentLevel() != 0) playLevel(getCurrentLevel());
				//playLevel(1);	// Test start at level 2

				if (getCurrentLevel() > 0) fps.fpsthink();					// Update the FPS

				destroyGameObjects();										// 2017-01-09 JOE: Destroy the game objects when finished on the screen
			}
		}
	}
}

void Game::playLevel(int levelNum) {
	if (displayLevelIntro) displayLevelIntroScreens(levelNum);	// Set true or false in _test.cpp

	if (!gameOver) {
		spawnMovingObjects();	// 2017/01/10 JOE: Spawn enemies and obstacles at random coords & distances apart
		moveGameObjects();		// 2017-01-09 JOE: Move the game objects on the screen
		collisionCheck();		// Check collisions between 2 objects
	}

	renderGameObjects();		// 2017-01-09 JOE: Render the game objects to the screen
}

void Game::displayLevelIntroScreens(int level) {
	// STORY - INSTRUCTIONS - OBJECTIVES - INFORMATION screens, pass in all the textures to give information about for each level
	if (level == 1) displayLevelIntro = splash.level1IntroScreens(gRenderer, gEnemyVirusTexture, gEnemyVirusOrangeTexture, gEnemyShipTexture, gPowerUpHealthTexture, gPowerUpLaserTexture, gPowerUpRocketTexture);		// Display level story and info screens
	if (level == 2) displayLevelIntro = splash.level2IntroScreens(gRenderer, gEnemyVirusTexture, gEnemyVirusOrangeTexture, gEnemyShipTexture);
	if (level == 3) displayLevelIntro = splash.level3IntroScreens(gRenderer, gEnemyVirusTexture, gEnemyVirusOrangeTexture, gEnemyShipTexture);

	if (level <= MAX_NUM_LEVELS) splash.pressButtonToContinue(gRenderer, e);
}

void Game::displayText() {
	std::stringstream timeText, score1Text, score2Text, framesPerSec;	// In memory text stream - string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory

	timeText.str("");													// Set text to be rendered - string stream - print the time since timer last started - initialise empty
	framesPerSec << "FPS: " << fps.getFPS();							// FPS the game is running at
	score1Text << "P1: " << player1->getScore();						// Player 1 score
	score2Text << "P2: " << player2->getScore();						// Player 2 score
	finalScores = "Player 1: " + std::to_string(player1->getScore()) + " Player 2: " + std::to_string(player2->getScore());	// End of game Player 1 and Player 2 scores

	if (!levelOver) {
		if (countdownTimer > 0 && countdownTimer <= GAME_TIMER) {
			timeText << "Time: " << countdownTimer;						// Set the game timer
			levelOver = false;											// Level is not over
		}
		else if (countdownTimer <= 0 || countdownTimer > GAME_TIMER + 6) {
			levelOver = true;											// Level is over
			if (getCurrentLevel() == MAX_NUM_LEVELS) gameOver = true;
		}

		gameTimer();													// Set the count down timer

		gTimeTextTexture.UITextTimer(timeText.str().c_str(), gRenderer, countdownTimer);	// Render Text - Use a string to render the current Game Time to a Texture

		gP1ScoreTextTexture.UIText(score1Text.str().c_str(), gRenderer);					// Render text - Use a string to render the current P1 Score to a texture
		gP2ScoreTextTexture.UIText(score2Text.str().c_str(), gRenderer);					// Render text - Use a string to render the current P2 Score to a texture
		gFPSTextTexture.UIText(framesPerSec.str().c_str(), gRenderer);						// Render text - Use a string to render the current FPS to a texture
		gLevelTextTexture.UIText("Level " + std::to_string(getCurrentLevel()), gRenderer);	// Render text - Use a string to render the current Level to a texture

		if (infoMessageP1 != "") gInfoMessageP1TextTexture.UITextPlayerMessage(infoMessageP1, gRenderer, PLAYER_1);	// Render Text - Use a string to render Player 1 notifications
		if (infoMessageP2 != "") gInfoMessageP2TextTexture.UITextPlayerMessage(infoMessageP2, gRenderer, PLAYER_2);	// Render Text - Use a string to render Player 2 notifications
		if (infoMessageGeneral != "") gInfoMessageTextTexture.UITextPlayerMessage(infoMessageGeneral, gRenderer);					// Render Text - Use a string to render General notifications
	}

	if (levelOver == true) {
		//std::cout << "Level " << getCurrentLevel() << " Complete" << std::endl;
		//gamerOverMessageDisplayCounter = 0;
		gameProgress();
	}// Levels

	if (gameOver == true) {
		if (player1->getScore() > player2->getScore())
			gameWinners = "Player 1 Wins";
		else if (player2->getScore() > player1->getScore())
			gameWinners = "Player 2 Wins";
		else
			gameWinners = "It's a draw";

		gameProgress();
	}
}

void Game::gameProgress() {
	gamerOverMessageDisplayCounter++;
	//std::cout << "Game over counter: " << gamerOverMessageDisplayCounter << std::endl;

	if (gamerOverMessageDisplayCounter >= 300) {
		gamerOverMessageDisplayCounter = 0;

		if (!player1->getAlive() && !player2->getAlive()) {
			resetGame(MENU);								// Reset the current level back to menu
			gameOver = true;
		}
		else {
			setCurrentLevel(getCurrentLevel() + 1);			// If there is a player alive go to next level

			if (getCurrentLevel() > MAX_NUM_LEVELS) {		// If current game level goes over 3
				gameOver = true;
				resetGame(1);
			}
			else
				resetGame(getCurrentLevel());				// Increment the level a
		}
	}
}

bool Game::playerInput(bool quit = false) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {	// User requests quit	EXIT - CLOSE WINDOW
			quit = true;
		}							// Reset start time on return keypress
		else if (e.type == SDL_KEYDOWN) {
		//else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {

			switch (e.key.keysym.sym) {
			// Play/Pause music on a m key press, stop music on 0
			case SDLK_m:
				if (Mix_PlayingMusic() == 0) {							// If there is no music playing
					int song = audio.playMusic();
					identifyTrack(song);
					infoMessage("Music Play");
				}
				else {													// If music is being played
					if (Mix_PausedMusic() == 1) {						// Check if the music is paused
						Mix_ResumeMusic();								// Resume music
						infoMessage("Music Play");
					}
					else {												// If the music is playing
						Mix_PauseMusic();								// Pause the music
						infoMessage("Music Paused");
					}
				}
				break;
			case SDLK_l:
				musicTrackForward(); break;								// Skip track forwards
			case SDLK_k:
				musicTrackBackward(); break;							// Skip track backwards
			case SDLK_0:
				Mix_HaltMusic(); infoMessage("Music Stopped"); break;	// Stop Music

			// Map
			case SDLK_t:
				//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				if (mapViewport.y == 600) {
					setViewport(mapViewport, (SCREEN_WIDTH - 780) / 2, 40, 900, 657);
					infoMessage("View Map");
					gProfessorMapTexture.setAlpha(50);
				}
				else if (mapViewport.y == 40) {
					setViewport(mapViewport, (SCREEN_WIDTH - 120) / 2, 600, 120, 88); // 230 was 192, 168 was 140
					infoMessage("Hide Map");
					gProfessorMapTexture.setAlpha(255);
				}
				gProfessorMapTexture.modifyAlpha(gProfessorMapTexture.getAlpha());
				break;

			default:
				//	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
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

		menu1.handleMenuEvents(e);
		if (getCurrentLevel() != 0) {									// If not in menu state
			//player1->handleEvent(e, PLAYER_1);							// Handle input for Player 1
			//player2->handleEvent(e, PLAYER_2);							// Handle input for Player 2

			for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
				if (listOfGameObjects[index]->getType() == PLAYER_1) listOfGameObjects[index]->handleEvent(e, PLAYER_1);
				else if (listOfGameObjects[index]->getType() == PLAYER_2) listOfGameObjects[index]->handleEvent(e, PLAYER_2);
				if (listOfGameObjects[index]->getSubType() == ROCKET_P1 && listOfGameObjects[index]->getPlayer() == PLAYER_1) listOfGameObjects[index]->handleEvent(e, PLAYER_1);
				else if (listOfGameObjects[index]->getSubType() == ROCKET_P2 && listOfGameObjects[index]->getPlayer() == PLAYER_2) listOfGameObjects[index]->handleEvent(e, PLAYER_2);
			}
		}
	}

	return quit;
}

void Game::musicTrackForward() {
	int songName = audio.musicForwardSongName();
	identifyTrack(songName);
	infoMessage("Music Track Skip Forwards");
}
void Game::musicTrackBackward() {
	int songName = audio.musicBackSongName();
	identifyTrack(songName);
	infoMessage("Music Track Skip Backwards");
}
void Game::identifyTrack(int songName) {
	if (songName == 0) {
		infoMessage("Artist: Unknown", 1);
		infoMessage("Track: Unknown", 2);
	}
	else if (songName == 1) {
		infoMessage("Artist: Unknown", 1);
		infoMessage("Track: Unknown", 2);
	}
	else if (songName == 2) {
		infoMessage("Artist: Unknown", 1);
		infoMessage("Track: Unknown", 2);
	}
	else if (songName == 3) {
		infoMessage("Artist: Jim O'Regan", 1);
		infoMessage("Song Title: The Last Step", 2);
	}
}

void Game::renderGameObjects() {
	// Levels
	//if (getCurrentLevel() != 0) {
		//SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 255); SDL_RenderClear(gRenderer);

	//if (weaponScrolling > 0 - gPowerUpLaserTexture.getWidth())
	if (weaponScrolling > 0)
		weaponScrolling--;

	//else if (weaponScrolling == 0 - gPowerUpHealthTexture.getWidth())
	//else if (weaponScrolling == 0)
		//weaponScrolling = 80;
		//Laser1 = true;

		// ROTATE GAME OBJECTS - Set angle increment for rotating textures
		gNinjaStarBlueTexture.setDegrees(gNinjaStarBlueTexture.getDegrees() + 5);
		gNinjaStarYellowTexture.setDegrees(gNinjaStarYellowTexture.getDegrees() + 5);
		gSawTexture.setDegrees(gSawTexture.getDegrees() + 5);
		gBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 1);
		gBloodCellSmallTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);
		gWhiteBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);

		displayText();										// 2017/01/17: Display the game text

		gPlayer1Texture.flashGameObject(10, 4);				// 2017/01/30 Moved flashGameObject() function into LTexture
		gPlayer2Texture.flashGameObject(10, 4);
		gTimeTextTexture.flashGameObject(8);

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x3C, 0x3C, 0x3C, 0xFF);		// Grey colour --> shows up in UI
		SDL_RenderClear(gRenderer);

		SDL_RenderSetViewport(gRenderer, &gameViewport);

		if (levelOver == false) {
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

			for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
				// Player 1
				if (listOfGameObjects[index]->getSubType() == PLAYER_1) {
					gPlayer1Texture.modifyAlpha(gPlayer1Texture.getAlpha());
					player1->renderPlayer(gPlayer1Texture, gRenderer);
				}
				// Render Saws
				if (listOfGameObjects[index]->getSubType() == SAW1) listOfGameObjects[index]->render(gSawTexture, gRenderer, gSawTexture.getDegrees());
				else if (listOfGameObjects[index]->getSubType() == SAW2) listOfGameObjects[index]->render(gSawTexture, gRenderer, gSawTexture.getDegrees());

				// Render Power Ups
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) listOfGameObjects[index]->render(gPowerUpHealthTexture, gRenderer);			// Health Texture
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) listOfGameObjects[index]->render(gPowerUpLaserTexture, gRenderer);				// Laser Texture
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) listOfGameObjects[index]->render(gPowerUpRocketTexture, gRenderer);			// Rocket Texture
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) listOfGameObjects[index]->render(gPowerUpCheckpointTexture, gRenderer);	// Checkpoint Texture

				// Render Explosions
				else if (listOfGameObjects[index]->getSubType() == EXPLOSION) {
					animationFrames = listOfGameObjects[index]->getFrames();		// 2017/02/09 Fixed the explosion animations, they are now assigned to indiviual objects with the game object frame attribute
					listOfGameObjects[index]->render(gExplosionSpriteSheetTexture, gRenderer, &gExplosionClips[animationFrames / 12], animationFrames, 12);
					listOfGameObjects[index]->setFrames(animationFrames);
					if (animationFrames / 8 >= EXPLOSION_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
						animationFrames = 0;										// reset animation frames
						listOfGameObjects[index]->setAlive(false);
					}
				}

				// Render player scores for killing Enemies
				else if (listOfGameObjects[index]->getSubType() == PLAYER1_SCORE) {
					listOfGameObjects[index]->m_Texture.setAlpha(120);																// Set scores slightly transparent
					listOfGameObjects[index]->render(listOfGameObjects[index]->m_Texture, gRenderer);								// works for m_Texture but not getTexture
				}
				else if (listOfGameObjects[index]->getSubType() == PLAYER2_SCORE) {
					listOfGameObjects[index]->m_Texture.setAlpha(100);																// Set scores slightly transparent
					listOfGameObjects[index]->render(listOfGameObjects[index]->m_Texture, gRenderer);
				}

				// Render Enemy Lasers
				else if (listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) listOfGameObjects[index]->render(gVirusFireballTexture, gRenderer); //
				else if (listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET) listOfGameObjects[index]->render(gVirusShield, gRenderer); //
				else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER) listOfGameObjects[index]->render(gLaserBlueTexture, gRenderer);

				// Render Blood Cells
				else if (listOfGameObjects[index]->getSubType() == BLOOD_CELL) listOfGameObjects[index]->render(gBloodCellTexture, gRenderer, -gBloodCellTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());				// Render the Blood Cell, with random rotation direction
				else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL) listOfGameObjects[index]->render(gBloodCellSmallTexture, gRenderer, -gBloodCellSmallTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());	// Render the Small Blood Cell, with random rotation direction
				else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL) listOfGameObjects[index]->render(gWhiteBloodCellTexture, gRenderer, -gWhiteBloodCellTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());

				// Render Enemies
				else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
					animationFrames = listOfGameObjects[index]->getFrames();																										// 2017/02/09 Fixed the Enemy Ship animations, they are now assigned to indiviual objects with the game object frame attribute
					listOfGameObjects[index]->render(gEnemySpriteSheetTexture, gRenderer, &gEnemySpriteClips[animationFrames / 10], animationFrames, 4);							// 4 the number of frames
					listOfGameObjects[index]->setFrames(animationFrames);
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) listOfGameObjects[index]->render(gEnemyVirusTexture, gRenderer);
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) listOfGameObjects[index]->render(gOrangeVirusSpriteSheetTexture, gRenderer, &gOrangeVirusSpriteClips[animationFrames / 10], animationFrames, 6);	// 6 the number of frames
				else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) listOfGameObjects[index]->render(gBlueVirusSpriteSheetTexture, gRenderer, &gBlueVirusSpriteClips[animationFrames / 10], animationFrames, 6);		// 6 the number of frames

				// Weapons
				else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P1) listOfGameObjects[index]->render(gNinjaStarYellowTexture, gRenderer, gNinjaStarYellowTexture.getDegrees());	// Yellow ninja star for player 1
				else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P2) listOfGameObjects[index]->render(gNinjaStarBlueTexture, gRenderer, gNinjaStarBlueTexture.getDegrees());		// Blue ninja star for player 2
				else if (listOfGameObjects[index]->getSubType() == LASER_P1) listOfGameObjects[index]->render(gLaserOrangeTexture, gRenderer);
				else if (listOfGameObjects[index]->getSubType() == LASER_P2) listOfGameObjects[index]->render(gLaserGreenTexture, gRenderer);
				else if (listOfGameObjects[index]->getSubType() == LASER_V2_P1) listOfGameObjects[index]->render(gLaserOrangeTexture, gRenderer);
				else if (listOfGameObjects[index]->getSubType() == LASER_V2_P2) listOfGameObjects[index]->render(gLaserGreenTexture, gRenderer);
				else if (listOfGameObjects[index]->getSubType() == ROCKET_P1) listOfGameObjects[index]->render(gRocketTexture, gRenderer, listOfGameObjects[index]->getAngle());
				else if (listOfGameObjects[index]->getSubType() == ROCKET_P2) listOfGameObjects[index]->render(gRocketTexture, gRenderer, listOfGameObjects[index]->getAngle());
				// Set the object alpha value

				listOfGameObjects[index]->m_Texture.modifyAlpha(listOfGameObjects[index]->m_Texture.getAlpha());
			}

			// Render Text
			SDL_RenderSetViewport(gRenderer, &UIViewport);
			gCreatedByTextTexture.render((SCREEN_WIDTH - gCreatedByTextTexture.getWidth()) / 2, 120 - gCreatedByTextTexture.getHeight() - 8, gRenderer);
			SDL_RenderSetViewport(gRenderer, &gameViewport);
			gLevelTextTexture.render(10, 8, gRenderer);

			if (infoMessageP1Counter < MESSAGE_TIME) {
				gInfoMessageP1TextTexture.render((SCREEN_WIDTH - gInfoMessageP1TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP1TextTexture.getHeight()) / 2) - 20, gRenderer); // Top message P1
				infoMessageP1Counter++;
			}
			if (infoMessageP2Counter < MESSAGE_TIME) {
				gInfoMessageP2TextTexture.render((SCREEN_WIDTH - gInfoMessageP2TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP2TextTexture.getHeight()) / 2) + 20, gRenderer);	// Bottom message P2
				infoMessageP2Counter++;
			}
			if (infoMessageCounter < MESSAGE_TIME) {
				gInfoMessageTextTexture.render((SCREEN_WIDTH - gInfoMessageTextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageTextTexture.getHeight()) / 2), gRenderer);	// Middle message General
				infoMessageCounter++;
			}

			gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());								// Flash the timer
			gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8, gRenderer);	// LAZY
			gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8, gRenderer);

			// Render Player 1
			if (player1->getAlive()) {
				bar.playerHealthBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getHealth(), gRenderer);

				if (killRocket1) {
					for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
						if (listOfGameObjects[index]->getSubType() == ROCKET_P1) listOfGameObjects[index]->setAlive(false);		// Kill the rocket
					}
				}

				if (player1->getRocketBarActive()) {
					rocket1BonusScore = 50;									// RESET ROCKET BONUS SCORE
					killRocket1 = false;										// Reset Kill rocket
					if (SDL_GetTicks() >= player1->getTimerTracker() + 200) {
						player1->setTimerTracker(SDL_GetTicks());				// start the timer
						player1->setTimer(player1->getTimer() - 0.2);
					}

					rocket1BonusScore -= rocket1BonusScore * (player1->getTimer() / ROCKET_TIMER);
					bar.rocketPowerBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getTimer(), gRenderer);

					if (player1->getTimer() <= 0) {
						spawnExplosion(player1->getX(), player1->getY());
						player1->setRocketActive(false);
						player1->setRocketBarActive(false);
						killRocket1 = true;
					}
				}

				gPlayer1Texture.modifyAlpha(gPlayer1Texture.getAlpha());
				player1->renderPlayer(gPlayer1Texture, gRenderer);

				SDL_RenderSetViewport(gRenderer, &UIViewport);
				texture.rendPlayerLives(player1->getNumLives(), gP1LivesTexture, 1, gRenderer);											// Player Lives
				gP1ScoreTextTexture.render(10, 50, gRenderer);														// Score for Player 1
				SDL_RenderSetViewport(gRenderer, &gameViewport);
			}// render the ship over the background

			// Render Player 2
			if (player2->getAlive()) {
				bar.playerHealthBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getHealth(), gRenderer);

				if (killRocket2) {
					for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
						if (listOfGameObjects[index]->getSubType() == ROCKET_P2) listOfGameObjects[index]->setAlive(false);		// Kill the rocket
					}
				}

				if (player2->getRocketBarActive()) {
					rocket2BonusScore = 50;										// RESET ROCKET BONUS SCORE
					killRocket2 = false;										// Reset Kill rocket
					if (SDL_GetTicks() >= player2->getTimerTracker() + 200) {
						player2->setTimerTracker(SDL_GetTicks());				// start the timer
						player2->setTimer(player2->getTimer() - 0.2);
					}

					rocket2BonusScore -= rocket2BonusScore * (player2->getTimer() / ROCKET_TIMER);
					bar.rocketPowerBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getTimer(), gRenderer);

					if (player2->getTimer() <= 0) {
						spawnExplosion(player2->getX(), player2->getY());
						player2->setRocketActive(false);
						player2->setRocketBarActive(false);
						killRocket2 = true;
					}
				}

				gPlayer2Texture.modifyAlpha(gPlayer2Texture.getAlpha());
				player2->render(gPlayer2Texture, gRenderer);

				SDL_RenderSetViewport(gRenderer, &UIViewport);
				texture.rendPlayerLives(player1->getNumLives(), gP2LivesTexture, 2, gRenderer);											// render the ship over the background
				gP2ScoreTextTexture.render(SCREEN_WIDTH - gP2ScoreTextTexture.getWidth() - 10, 50, gRenderer);		// Score for Player 2
				SDL_RenderSetViewport(gRenderer, &gameViewport);
			}

			for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
				if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {													// 2017/01/25 If the type of virus is an Orange Exploding Virus

					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {						// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());									// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);				// Decrement the timer
					}

					// Start the timer
					if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50) {
						listOfGameObjects[index]->setTimer(VIRUS_TIMER);	// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
					}

					// Draw the healthbar
					bar.virusTimer(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer(), gRenderer);

					// Explode!!!
					if (listOfGameObjects[index]->getTimer() <= 0) {
						spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_FIREBALL);										// x, y, and type
						spawnExplosion(listOfGameObjects[index]->getX() - listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getY() + 10);// Create an explosion when it dies
						listOfGameObjects[index]->setAlive(false);																					// When timer runs out kill the virus
					}
				}
				if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {													// 2017/01/25 If the type of virus is an Orange Exploding Virus

					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {						// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());									// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);				// Decrement the timer				// Decrement the timer
					}

					// Start the timer
					if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50) {
						listOfGameObjects[index]->setTimer(VIRUS_TIMER);	// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
					}

					// Draw the healthbar
					bar.virusTimerBlue(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer(), gRenderer);

					// Explode Orange Virus!!!
					if (listOfGameObjects[index]->getTimer() <= 0) {
						spawnExplosion(listOfGameObjects[index]->getX() - listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getY() + 10);// Create an explosion when it dies
						listOfGameObjects[index]->setAlive(false);																					// When timer runs out kill the virus
					}

					// Spawn the virus satellite object
					if (listOfGameObjects[index]->satelliteObjectAlive == false && listOfGameObjects[index]->getX() < SCREEN_WIDTH - 10) {
						spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLUE_VIRUS_BULLET, index);// x, y, and type
						listOfGameObjects[index]->satelliteObjectAlive = true;
					}

					// Set the Virus Satellite center point
					for (unsigned int index1 = 0; index1 != listOfGameObjects.size(); ++index1) {
						if (listOfGameObjects[index1]->getSubType() == BLUE_VIRUS_BULLET) {
							if (index == listOfGameObjects[index1]->whichVirusAssignedTo && listOfGameObjects[index]->getAlive()) {
								listOfGameObjects[index1]->movement(listOfGameObjects[index]->getX() + (listOfGameObjects[index]->getHeight() / 2), listOfGameObjects[index]->getY() + (listOfGameObjects[index]->getWidth() / 2), listOfGameObjects[index]->getTimer());	// Set center point when moving
							}
							else {
								listOfGameObjects[index1]->movement();
							}
						}
					}
				}
			}

			/* Professor Mini Map */
			/* Weapon Scrolling will work of trigger buttons, press left and right to select main weapon */
			SDL_RenderSetViewport(gRenderer, &mapViewport);								// UIViewport	// SDL_RenderSetViewport(gRenderer, &gameViewport);  // UIViewport
			//if (!levelOver) SDL_RenderCopy(gRenderer, gTest, NULL, NULL);				// Render texture to screen
			if (!levelOver) gProfessorMapTexture.renderMap(gRenderer);
			//if (!levelOver) gTest.render(NULL, NULL, gRenderer);
																						// gCreatedByTextTexture.render(scrollingOffset, 10, gRenderer);
			SDL_RenderSetViewport(gRenderer, &weaponViewport1);							// UIViewport
																						//if (!levelOver) SDL_RenderCopy(gRenderer, gWeapon, NULL, NULL);	// Render texture to screen
			if (Laser1) {
				//gPowerUpLaserTexture.render(0, 0, gRenderer);							// 1st
				gPowerUpLaserTextureV2.render(weaponScrolling, 0, gRenderer);			// 1st //weaponScrolling = 60;
			}
			else
				gPowerUpLaserTexture.render(weaponScrolling, 0, gRenderer);				// 1st

			SDL_RenderSetViewport(gRenderer, &weaponViewport2);  // UIViewport
			if (Laser2) gPowerUpLaserTextureV2.render(weaponScrolling, 0, gRenderer);	// 1st
			else gPowerUpLaserTexture.render(weaponScrolling, 0, gRenderer);			// 1st
			SDL_RenderSetViewport(gRenderer, NULL);										// Reset Viewport

		}
		else if (levelOver == true) {
			SDL_RenderSetViewport(gRenderer, NULL);										// UIViewport   gameViewport

			splash.endOfGame(gRenderer, getCurrentLevel(), finalScores);

			resetGame(getCurrentLevel() + 1);
			if (getCurrentLevel() >	MAX_NUM_LEVELS) gameOver = true;
		}

		if (gameOver == true) {
			SDL_RenderSetViewport(gRenderer, NULL);  // UIViewport   gameViewport
			splash.endOfGame(gRenderer, getCurrentLevel(), finalScores, gameWinners);
		}
	//}

	SDL_RenderPresent(gRenderer);					// Update screen
}

void Game::displayScoreForObject(int Xcoord, int Ycoord, int score, int player) {
	GameObject* p_PointsValue = new ScoreValueText(Xcoord, Ycoord, score, player);

	if (player % 2 == 0) {
		p_PointsValue->setSubType(PLAYER1_SCORE);
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 240, 210, 65, 255 }, gFontRetro20, gRenderer)) {	// Gold Text
			printf("Unable to render player text texture!\n");
		}
	}
	else if (player % 2 == 1) {
		p_PointsValue->setSubType(PLAYER2_SCORE);
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 0, 0, 255, 255 }, gFontRetro20, gRenderer)) {		// Blue Text
			printf("Unable to render player text texture!\n");
		}
	}

	listOfGameObjects.push_back(p_PointsValue);
}

void Game::moveGameObjects() {
	if (player1->getAlive()) player1->movement();										// Update ship movement
	if (player2->getAlive()) player2->movement();

	// Cycle through list of Game Objects and move them, Player scores, and Power Ups so far
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getSubType() == PLAYER1_SCORE) {
			listOfGameObjects[index]->movement(player1->getX(), player1->getY());		// Move the score to Player 1 ship
		}
		else if (listOfGameObjects[index]->getSubType() == PLAYER2_SCORE) {				// Move the score to Player 2 ship
			listOfGameObjects[index]->movement(player2->getX(), player2->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == SAW1) {							// Move Player 1 saw
			listOfGameObjects[index]->movement(player1->getX(), player1->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == SAW2) {							// Move Player 2 saw
				listOfGameObjects[index]->movement(player2->getX(), player2->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {					// Move Enemy ships + Fire enemy lasers
			listOfGameObjects[index]->movement();
			spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), ENEMY_SHIP_LASER);
		}
		else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {					// Move Enemy Virus, tracking the player movement
			if (listOfGameObjects[index]->getX() > SCREEN_WIDTH && listOfGameObjects[index]->getX() < SCREEN_WIDTH + 10 && listOfGameObjects[index]->getSubType() == 1) {
				infoMessage("Exploding Orange Virus Approaching");
			}

			if ((abs(player1->getX() - listOfGameObjects[index]->getX()) * abs(player1->getX() - listOfGameObjects[index]->getX())) +			// Distance on X axis between player 1 and virus squared
				(abs(player1->getY() - listOfGameObjects[index]->getY()) * abs(player1->getY() - listOfGameObjects[index]->getY())) <			// Distance on Y axis between player 1 and virus squared
				(abs(player2->getX() - listOfGameObjects[index]->getX()) * abs(abs(player2->getX() - listOfGameObjects[index]->getX())) + 		// Distance on X axis between player 2 and virus squared
				(abs(player2->getY() - listOfGameObjects[index]->getY()) * abs(abs(player2->getY() - listOfGameObjects[index]->getY())))))		// Distance on Y axis between player 2 and virus squared
			{
				listOfGameObjects[index]->movement(player1->getX(), player1->getY());
			}
			else {
				listOfGameObjects[index]->movement(player2->getX(), player2->getY());
			}
		}
		else listOfGameObjects[index]->movement();
	}
}

// 2017-02-16 Display player messages for player events, added to a function
void Game::infoMessage(std::string message, int type, int timer) {
	if (type == 0) {
		infoMessageCounter = 0;
		infoMessageGeneral = message;
	}
	else if (type == PLAYER_1) {
		infoMessageP1Counter = 0;
		infoMessageP1 = message;
	}
	else if (type == PLAYER_2) {
		infoMessageP2Counter = 0;
		infoMessageP2 = message;
	}
	std::cout << message << std::endl;
}

// Destroy Game Objects
void Game::destroyGameObjects() {
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {								// Erase Game Objects
		if ((listOfGameObjects[index]->getSubType() == PLAYER1_SCORE || listOfGameObjects[index]->getSubType() == PLAYER2_SCORE) && SDL_GetTicks() > listOfGameObjects[index]->getTimerTracker() + 2500)	// if the current time is more than the start time + 100
			listOfGameObjects[index]->setAlive(false);													// Kill the object

		if (!listOfGameObjects[index]->getAlive()) {
			// Decrement the number active on screen
			if (listOfGameObjects[index]->getSubType() == BLOOD_CELL) activeBloodCells--;					// Decrement active blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL) activeSmallBloodCells--;	// Decrement active small blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL) activeWhiteBloodCells--;	// Decrement active white blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) activeEnemyShips--;				// Decrement active enemy ships when one is deleted
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) activeEnemyVirus--;			// Decrement active enemy Virus when one is deleted
			else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) activeEnemyVirus--;			// Decrement active enemy Virus when one is deleted
			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) activeEnemyVirus--;				// Decrement active enemy Virus when one is deleted
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P1) {
				player1->setRocketActive(false);
			}
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P2) {
				player2->setRocketActive(false);
			}

			if (listOfGameObjects[index]->getType() == PLAYER_WEAPON) {
				spawnExplosion(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());		// Expode Player Weapon when it is destroyed
			}

			// Erase The Object From The List
			if (!listOfGameObjects[index]->getAlive()) {
				listOfGameObjects.erase(listOfGameObjects.begin() + index);
				index--;
			}
		}
	}// end for
}

// Decide how many of each enemy / obstacle on screen at a given time
void Game::spawnMovingObjects() {
	if(player1->getAlive() == false && player1->getNumLives() > 0) spawnPlayer(PLAYER_1);
	if(player2->getAlive() == false && player2->getNumLives() > 0) spawnPlayer(PLAYER_2);

	if (!player1->getAlive() && !player2->getAlive()) gameOver = true;

	if (activeBloodCells < SPAWN_NUM_BLOOD_CELL) {
		activeBloodCells++;									// increment Blood cell counter
		spawnBloodCell(BLOOD_CELL);
	}
	if (activeSmallBloodCells < SPAWN_NUM_BLOOD_CELL_S) {
		activeSmallBloodCells++;							// increment Small blood cell counter
		spawnBloodCell(SMALL_BLOOD_CELL);
	}
	if(activeWhiteBloodCells < SPAWN_NUM_BLOOD_CELL_WHITE){
		activeWhiteBloodCells++;							// increment white blood cell counter
		spawnBloodCell(WHITE_BLOOD_CELL);
	}

	// Check how many of each game object are in the list
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getType() == POWER_UP) activePowerUps++;
		else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP)	activeEnemyShips++;
		else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) activeEnemyVirus++;
	}// end for

	if (activePowerUps < SPAWN_NUM_POWER_UPS) { spawnPowerUp(); }
	if (activeEnemyShips < SPAWN_NUM_ENEMY_SHIPS) { spawnEnemyShip(); }
	if (activeEnemyVirus < SPAWN_NUM_ENEMY_VIRUS) { spawnEnemyVirus(); }
}
void Game::spawnPlayer(int player) {
	int randomYCoord = rand() % 9; // a number 0 to 8

	if (player == PLAYER_1) {
		player1->spawn(0, (randomYCoord * 58) + 50);						// 2017/01/20: Spawn Player 1 at random Y coord
		player1->setAlive(true);
		gPlayer1Texture.setFlash(true);
		gPlayer1Texture.flashGameObject(10, 4);								// 2017/01/30 Moved flashGameObject() function into LTexture
		listOfGameObjects.push_back(player1);
	}
	else if (player == PLAYER_2) {
		player2->spawn(0, (randomYCoord * 58) + 50);
		if (player2->getY() == player1->getY()) spawnPlayer(PLAYER_2);				// 2017/01/20: Spawn Player 2 at random Y coord + different to Player 1
		player2->setAlive(true);
		gPlayer2Texture.setFlash(true);
		gPlayer2Texture.flashGameObject(10, 4);
		listOfGameObjects.push_back(player2);
		//std::cout << "player1.getY() " << player1.getY() << " player2.getY() " << player2.getY() << std::endl;
	}

}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomSpeed;

	GameObject* p_Enemy = new EnemyShip();
	spawnRandom(x, y, randomSpeed, 50, p_Enemy->getHeight());
	p_Enemy->spawn(x, y, -randomSpeed, p_Enemy->getCollider());
	listOfGameObjects.push_back(p_Enemy);
}
void Game::spawnEnemyVirus() {
	int x, y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 150);
	int randomExplodingVirus = rand() % 4 + 1;								// 1 in 4 chance of Orange Exploding Virus
	///int randomExplodingVirus = 1;										// TEST Orange Virus

	if (randomExplodingVirus == 2) {
		GameObject* p_OrangeVirus = new EnemyVirus(VIRUS_ORANGE, 3.0);		// Orange type = 1
		p_OrangeVirus->setTimer(3.0);
		//std::cout << "Enemy Virus Spawned. Timer: " << p_OrangeVirus->getTimer() << std::endl;
		p_OrangeVirus->spawn(x, y, -4, -2, p_OrangeVirus->getCollider(), VIRUS_ORANGE);
		listOfGameObjects.push_back(p_OrangeVirus);
		//std::cout << "distance to virus p1: " << abs(((player1.getX() * player1.getX()) + (player1.getY() * player1.getY()))) << " p2: " << abs((player2.getX() * player2.getX()) + (player2.getY() * player2.getY())) << std::endl;
	}
	else if (randomExplodingVirus == 1) {
		GameObject* p_BlueVirus = new EnemyVirus(VIRUS_BLUE, 3.0);			// BLUE type = 2
		//std::cout << "Enemy Virus Spawned. Timer: " << p_BlueVirus->getTimer() << std::endl;
		p_BlueVirus->spawn(x, y, -4, -2, p_BlueVirus->getCollider(), VIRUS_BLUE);
		listOfGameObjects.push_back(p_BlueVirus);
	}
	else {
		GameObject* p_GreenVirus = new EnemyVirus(VIRUS_GREEN, 0);			// Green type = 0
		p_GreenVirus->spawn(x, y, -4, -2, p_GreenVirus->getCollider(), VIRUS_GREEN);
		listOfGameObjects.push_back(p_GreenVirus);
	}
}
void Game::spawnBloodCell(int type) {
	int x, y, randomSpeed;
	GameObject* p_BloodCell = new BloodCell();

	p_BloodCell->setSubType(type);	// Set the type of Blood Cell

	spawnRandom(x, y, randomSpeed, 200, p_BloodCell->getHeight());
	//p_BloodCell->spawn(x, y, -randomSpeed, p_BloodCell->getDistanceBetween());	// 2017/01/24 Added Y padding to keep objects with the game screen boundary
	p_BloodCell->spawn(x, y, -randomSpeed);	// 2017/01/24 Added Y padding to keep objects with the game screen boundary
	listOfGameObjects.push_back(p_BloodCell);
}
void Game::spawnPowerUp() {
	int x, y, randomSpeed, powerUpType = 0;
	int randomPowerup = rand() % 4 + 1;											// Number between 1 and 3

	if (countdownTimer <= 10) {
		powerUpType = POWER_UP_CHECKPOINT;										// if the timer is less than or equal 10, spawn the Checkpoint power up
	}
	else {
		if (randomPowerup == 1) powerUpType = POWER_UP_HEALTH;
		else if (randomPowerup == 2) powerUpType = POWER_UP_LASER;
		else if (randomPowerup == 3) powerUpType = POWER_UP_ROCKET;
	}

	GameObject* p_PowerUp = new PowerUp(powerUpType, 50);						// Type and score
	spawnRandom(x, y, randomSpeed, 200, p_PowerUp->getHeight());				// Spawn with random X and Y coord, and speed between 1 and 3
	p_PowerUp->spawn(x, y, -randomSpeed);										// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	listOfGameObjects.push_back(p_PowerUp);
}

void Game::spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier, int yPadding, int speed) {	// 2017-01-20 Separate out common randomness
	int randomX = rand() % 5 + 1;
	int randomY = rand() % 8 + 1;												// A number between 1 and 8
	randomSpeed = rand() % 3 + speed;

	x = SCREEN_WIDTH + (randomX * xMuliplier);
	y = 40 + (randomY * ((SCREEN_HEIGHT_GAME - yPadding - 80) / 8));			// 40 top and bottom, yPadding, object height
}

// Spawn Weapon at ships location
void Game::spawnExplosion(int x, int y) {
	GameObject* p_Explosion = new Explosion(x, y);
	p_Explosion->setAlive(true);
	p_Explosion->spawn(x, y - 30);
	//p_Explosion->spawn(100, 100);
	listOfGameObjects.push_back(p_Explosion);

	audio.explosionFX();
}
void Game::spawnLaser(int x, int y, int player, int velocity, int grade) {
	GameObject* p_Laser1 = new WeaponPlLaser();
	p_Laser1->setAlive(true);

	if (player == PLAYER_1) {
		p_Laser1->spawn(x + 65, y + 25, velocity, PLAYER_1, LASER_P1);
		grade = player1->getLaserGrade();
		p_Laser1->setSubType(LASER_P1);
		p_Laser1->setPlayer(PLAYER_1);
		p_Laser1->setCollider((*p_Laser1->getCollider()));
	}
	else if (player == PLAYER_2) {
		p_Laser1->spawn(x + 65, y + 25, velocity, PLAYER_2, LASER_P2);
		grade = player2->getLaserGrade();
		p_Laser1->setSubType(LASER_P2);
		p_Laser1->setPlayer(PLAYER_2);
	}

	listOfGameObjects.push_back(p_Laser1);

	if (grade == 1) {		// FIRE 2 MORE LASERS AT ANGLES
		GameObject* p_Laser2 = new WeaponPlLaser(1, 1);
		GameObject* p_Laser3 = new WeaponPlLaser(2, 1);;

		if (player == PLAYER_1) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_1, LASER_P1);
			p_Laser3->spawn(x + 65, y + 35, velocity, PLAYER_1, LASER_P1);
		}
		else if (player == PLAYER_2) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_2, LASER_P2);
			p_Laser3->spawn(x + 65, y + 35, velocity, PLAYER_2, LASER_P2);
		}

		listOfGameObjects.push_back(p_Laser2);
		listOfGameObjects.push_back(p_Laser3);
	}

	if (!gameOver) {
		if (player == 1) audio.laserFX_P1();
		else if (player == 2) audio.laserFX_P2();
	}
}
void Game::spawnEnemyLaser(int xCoord, int yCoord, int type, int whichVirus) {
	if (type == ENEMY_SHIP_LASER && xCoord < SCREEN_WIDTH) {							// first type and visible on screen, start shooting
		int distanceBetweenShots = ((rand() % 3 + 1) * 50) + 60;						// 2017/01/20 More random shooting from enemies
																						// if (shipX % 100 == 0) {
		if (xCoord % distanceBetweenShots < 3) {										// 2017-01-20 Not all ships were firing
			GameObject* p_LaserE = new WeaponEnLaser(ENEMY_SHIP_LASER);
			p_LaserE->spawn(xCoord - 20, yCoord + 30, p_LaserE->getVelocity());
			listOfGameObjects.push_back(p_LaserE);

			audio.laserFX_Enemy();
		}
	}
	else if(type == VIRUS_FIREBALL){
		for (unsigned int i = 1; i < 9; i++) {
			//std::cout << "Laser " << i << " created" << std::endl;
			GameObject* p_Laser = new WeaponEnLaser(VIRUS_FIREBALL);	// Create an Enemy Laser of type 1 (Orange Virus)
			p_Laser->spawn(xCoord, yCoord);								// Spawn the laser from the Virus Coordinates

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

			listOfGameObjects.push_back(p_Laser);					// Add the Enemy Lasers to a list to move and render
		}
	}
	else if (type == BLUE_VIRUS_BULLET) {
		GameObject* p_Laser = new WeaponEnLaser(BLUE_VIRUS_BULLET);
		p_Laser->spawn(xCoord, yCoord);								// Spawn the laser from the Virus Coordinates
		p_Laser->setVelX(-5);
		p_Laser->whichVirusAssignedTo = whichVirus;

		listOfGameObjects.push_back(p_Laser);						// Add the Enemy Lasers to a list to move and render
	}
}
void Game::spawnNinjaStar(int x, int y, int player) {					// player to spawn for and their coords
	GameObject* p_NinjaStar = new WeaponPlNinjaStar();
	p_NinjaStar->spawn(x + 65, y + 25);
	p_NinjaStar->setPlayer(player);										// 2017/01/17 Set the player the laser belongs too
	p_NinjaStar->setAlive(true);
	p_NinjaStar->setVelX(10);

	std::cout << "Ninja Star Spawned " << player << "p1 " << PLAYER_1 << " p2 " << PLAYER_2 << std::endl;

	if (player == PLAYER_1) p_NinjaStar->setSubType(NINJA_STAR_P1);
	else if (player == PLAYER_2) p_NinjaStar->setSubType(NINJA_STAR_P2);

	listOfGameObjects.push_back(p_NinjaStar);
	if (!gameOver) {
		if (player == 1) audio.ninjaFX_P1();
		else if (player == 2) audio.ninjaFX_P2();
	}
}
void Game::spawnRocket(int x, int y, int player, int type, bool launch) {
	if (launch == false && player == PLAYER_1 && player1->getNumRockets() > 0) player1->setRocketBarActive(true);			// if not ready to fire, player is player 1, and player 1 has rockets
	else if (launch == false && player == PLAYER_2 && player2->getNumRockets() > 0) player2->setRocketBarActive(true);
	else {
		bool createRocket = false;
		if (player == PLAYER_1 && !player1->getRocketActive() && player1->getNumRockets() > 0) {
			player1->setRocketActive(true);							// Player 1 rocket is active (only 1 rocket can be active at a time)
			player1->setRocketBarActive(false);
			player1->setTimer(ROCKET_TIMER);
			player1->setNumRockets(player1->getNumRockets() - 1);	// decrement the number of rockets
			createRocket = true;									// Launch the rocket
		}
		else if (player == PLAYER_2 && !player2->getRocketActive() && player2->getNumRockets() > 0) {
			player2->setRocketActive(true);
			player2->setRocketBarActive(false);
			player2->setTimer(ROCKET_TIMER);
			player2->setNumRockets(player2->getNumRockets() - 1);	// decrement the number of rockets
			createRocket = true;
		}
		if (createRocket) {
			GameObject* p_Rocket = new WeaponPlRocket();				// Create a rocket
			//p_Rocket->setVelX(0);
			p_Rocket->spawn(x, y, p_Rocket->getCollider(), player, type);	// spawn for the player
			p_Rocket->setAngle(0);	// Fire straight
			if (player == PLAYER_1) p_Rocket->setSubType(ROCKET_P1);
			else if (player == PLAYER_2) p_Rocket->setSubType(ROCKET_P2);
			std::cout << "Rocket Spawned" << std::endl;
			listOfGameObjects.push_back(p_Rocket);
		}
	}
}
void Game::spawnSaw(int x, int y, int type) {			// player to spawn for and their coords, turn on if inacive, off if active	// 2017-02-08 Updated and working OK
	bool createSaw = false;

	// Check which player to create a saw for
	if (type == SAW1 && !player1->getSawActive()) {
		createSaw = true;
		player1->setSawActive(true);					// show saw
	}
	else if (type == SAW2 && !player2->getSawActive()) {
		createSaw = true;
		player2->setSawActive(true);					// show saw
	}

	if (createSaw) {
		GameObject* p_Saw = new WeaponPlSaw(type);		// Create new saw
		p_Saw->spawn(x + 65, y + 25);					// spawn the saw
		listOfGameObjects.push_back(p_Saw);				// add to list of saws
		p_Saw->setSubType(type);
		if (!gameOver) audio.sawFX();
	}
	else if (!createSaw) {
		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			if (listOfGameObjects[index]->getSubType() == type) {			// if saw is the right type
				if (listOfGameObjects[index]->getAlive() == true) {			// if saw is active

					if (listOfGameObjects[index]->getSubType() == SAW1) player1->setSawActive(false);						// hide saw
					else if (listOfGameObjects[index]->getSubType() == SAW2) player2->setSawActive(false);					// hide saw

					listOfGameObjects[index]->setAlive(false);
				}
			}
		}// end for
	}
}

void Game::collisionCheck() {
	// Check if Player 1 or 2 has collided with another game object
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (checkCollision(player1->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());

			if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
				managePlayerHealth(PLAYER_1, -listOfGameObjects[index]->getScore());
				infoMessage("Player 1 has increased their health!!!", PLAYER_1);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
				player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());
				player1->setLaserGrade(1);
				Laser1 = true;
				infoMessage("Player 1 has upgraded their laser!!!", PLAYER_1);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) {
				player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());
				player1->setNumRockets(player1->getNumRockets() + 1);
				infoMessage("Player 1 has collected a Rocket!!! Rockets: " + std::to_string(player1->getNumRockets()), PLAYER_1);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) {
				player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());
				infoMessage("Checkpoint Reached!!!");
				std::cout << "Checkpoint reached!\n";
				countdownTimer += 20;
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getScore());															// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player1->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getScore() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (player1->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (player1->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					//virusBar = 0;
					listOfGameObjects[index]->setTimer(0);
				}
				else
					if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getScore() / 3, "Enemy Virus");	// If player 1 isn't flashing, Take off 5 health
			}

			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON) listOfGameObjects[index]->setAlive(false);
		}
		else if (checkCollision(player2->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());

			if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
				managePlayerHealth(PLAYER_2, -listOfGameObjects[index]->getScore());
				infoMessageP2Counter = 0;
				infoMessage("Player 2 has increased their health!!!", PLAYER_2);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
				player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
				player2->setLaserGrade(1);
				Laser2 = true;
				infoMessage("Player 2 has upgraded their laser!!!", PLAYER_2);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) {
				player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
				player2->setNumRockets(player2->getNumRockets() + 1);
				infoMessage("Player 2 has collected a Rocket!!! Rockets: " + std::to_string(player2->getNumRockets()), PLAYER_2);
			}
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) {
				player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
				infoMessage("Checkpoint Reached!!!");
				std::cout << "Checkpoint reached!\n";
				countdownTimer += 20;
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getScore());	// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player2->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getScore() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					//virusBar = 0;
					listOfGameObjects[index]->setTimer(0);
				}
				else
					if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getScore() / 3, "Enemy Virus");	// If player 2 isn't flashing, Take off 5 health
			}

			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON) listOfGameObjects[index]->setAlive(false);
			//std::cout << "Power Up Picked Up by " << player2.getName() << "!\n";
		}
	}

	// Check Weapons Sub-Type For Collisions With Enemy Sub-Type
	for (unsigned int weaponIndex = 0; weaponIndex != listOfGameObjects.size(); weaponIndex++) {
		for (unsigned int enemyIndex = 0; enemyIndex != listOfGameObjects.size(); enemyIndex++) {
			if (listOfGameObjects[weaponIndex]->getType() == PLAYER_WEAPON && listOfGameObjects[enemyIndex]->getType() == ENEMY_OBJECT) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P1) {
						infoMessage("Impact!!! Missile has taken out an Enemy Virus! Score +" + std::to_string(rocket1BonusScore), PLAYER_1);
						managePlayerScores(rocket1BonusScore, PLAYER_1, listOfGameObjects[weaponIndex]->getSubType());
					}
					else if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P2) {
						infoMessage("Impact!!! Missile has taken out an Enemy Virus! Score +" + std::to_string(rocket2BonusScore), PLAYER_2);
						managePlayerScores(rocket2BonusScore, PLAYER_2, listOfGameObjects[weaponIndex]->getSubType());
					}

					managePlayerScores(listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getPlayer(), listOfGameObjects[weaponIndex]->getSubType());		// 2017-02-06 Add to players score

					pointsValueCounter = 0;
					displayScoreForObject(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getSubType());	// Display Score

					listOfGameObjects[enemyIndex]->setAlive(false);
					listOfGameObjects[weaponIndex]->setAlive(false);	// DESTROY
				}
			}
		}
	}
}

void Game::managePlayerScores(int score, int player, int type) {				// add get name
	if (player == PLAYER_1) player1->setScore(player1->getScore() + score);
	else if (player == PLAYER_2) player2->setScore(player2->getScore() + score);

	if (type == PLAYER_WEAPON) std::cout << "Enemy Ship Killed by Player " << player << std::endl;
	else if (type == SAW1) std::cout << "Enemy Ship Killed by Player 1 Saw!\n";
	else if (type == SAW2) std::cout << "Enemy Ship Killed by Player 2 Saw!\n";
}
void Game::managePlayerHealth(int player, int score, std::string name) {
	if (player == PLAYER_1) {
		gPlayer1Texture.setFlash(true);								// Flash on collision with Game Object
		player1->setHealth(player1->getHealth() - score);

		if (player1->getNumLives() <= 0) {
			player1->setSawActive(false);
			player1->setAlive(false);
		}
		else if (player1->getHealth() <= 0 && player1->getAlive()){
			player1->setNumLives(player1->getNumLives() - 1);
			if(player1->getNumLives() > 0) spawnPlayer(PLAYER_1);
			player1->setHealth(100);
		}
	}
	else if (player == PLAYER_2) {
		gPlayer2Texture.setFlash(true);								// Flash on collision with Game Object
		player2->setHealth(player2->getHealth() - score);

		if (player2->getNumLives() <= 0) {
			player2->setSawActive(false);
			player2->setAlive(false);
		}
		else if (player2->getHealth() <= 0 && player2->getAlive()) {
			player2->setNumLives(player2->getNumLives() - 1);
			if(player2->getNumLives() > 0) spawnPlayer(PLAYER_2);
			player2->setHealth(100);
		}

		if (player2->getAlive() && SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds 2017/01/20 Moved to player 2, was rumbling for both players
			printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
		}
	}

	if (score > 0) {
		audio.explosionFX();
		if (player == PLAYER_1) std::cout << "Player 1 has collided with " << name << "! Health: " << player1->getHealth() << std::endl;
		if (player == PLAYER_2) std::cout << "Player 2 has collided with " << name << "! Health: " << player2->getHealth() << std::endl;
	}
	else if (score < 0) std::cout << "Player" << player << " has received a power up of " << -score << " health";

	//if (SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds
	//	printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
	//}
}

//void Game::setViewport(SDL_Rect &rect, int x, int y, int w, int h) {
void setViewport(SDL_Rect &rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Game::gameTimer() {
	currentTime = SDL_GetTicks();
	if (currentTime > lastTime + 1000) {								// Decrement countdown timer
		lastTime = currentTime;
		countdownTimer--;
		//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
	}
}

void Game::resetGame(int currentLevel) {								// Reset a level or the game
	rocket1BonusScore = 50;												// The score that is generated for a successful strike by a player rocket
	rocket2BonusScore = 50;

	// Reset the map of the professor
	setViewport(mapViewport, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// Reset the map to small size
	gProfessorMapTexture.modifyAlpha(255);								// Reset the alpha value for the map texture

	std::string finalScores = "";										// Reset the final scores message
	std::string gameWinners = "";										// Reset the game winner message

	setCurrentLevel(currentLevel);										// Set the current level

	// Reset the number of objects on screen
	activeBloodCells = 0;
	activeWhiteBloodCells = 0;
	activeSmallBloodCells = 0;
	activePowerUps = 0;
	activeEnemyShips = 0;

	if (currentLevel == MENU) displayGameIntro = DISPLAY_GAME_INTRO_SCREENS;
	displayLevelIntro = DISPLAY_LEVEL_INTRO_SCREENS;
	backgroundLoopCounter = 0;
	scrollingOffset = 0;
	weaponScrolling = 60;

	// Information Messages
	infoMessageP1Counter = MESSAGE_TIME;	// Time to display player 1 notification messages
	infoMessageP2Counter = MESSAGE_TIME;	// Time to display player 2 notification messages
	infoMessageCounter = MESSAGE_TIME;		// Time to display player 2 notification messages
	pointsValueCounter = MESSAGE_TIME;		// Time to display score for killing Enemy message
	infoMessageP1 = "";						// Reset the player 1 notification message
	infoMessageP2 = "";						// Reset the player 2 notification message
	infoMessageGeneral = "";				// Reset the General notification message
	pointsValue = "";						// Reset the points value for destroyed Enemy message


	gamerOverMessageDisplayCounter = 0;

	// Timer
	lastTime = 0;
	currentTime = SDL_GetTicks();
	countdownTimer = GAME_TIMER;			// Reset the countdown timer
	gPlayer1Texture.setFlash(false);
	gPlayer2Texture.setFlash(false);
	gTimeTextTexture.setFlash(false);		// Reset the timer flash

											// Scores
	if (currentLevel <= 1) {				// If the level isn't progressing
		player1->setScore(0);				// Reset player 1 score
		player2->setScore(0);				// Reset player 2 score

		player1->setNumLives(NUM_LIVES);
		player2->setNumLives(NUM_LIVES);
	}

	// Reset Players
	player1->setSawActive(false);
	player1->setSpeedBoost(false);
	player2->setSawActive(false);
	player2->setSpeedBoost(false);

	player1->setAlive(false);
	player1->setHealth(player1->getMaxHealth());
	player2->setAlive(false);
	player2->setHealth(player2->getMaxHealth());

	player1->setVelX(0);
	player1->setVelY(0);
	player2->setVelX(0);
	player2->setVelY(0);
	player1->setTimer(ROCKET_TIMER);
	player2->setTimer(ROCKET_TIMER);

	// Delete all objects on screen
	if (gameOver || levelOver) {
		listOfGameObjects.clear();		// Scores, Power Ups, Explosions
		listOfScoreTextures.clear();
	}

	levelOver = false;
	gameOver = false;
}

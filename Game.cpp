/*
	2017/03/01 Added double laser for player
	2017/02/28 Fixed entry point not defined error with #define SDL_MAIN_HANDLED
				Moved background texture loading to texture map
	2017/02/27 Made the Constructor private for use as a singleton
				Removed unnecessary header files
				Fixed player lives not rendering for 1 Player mode
	2017/02/26 GAME: Added singletons for Texture class
	2017/02/23 PLAYER: Added option to play as 1 or 2 players
				GAME: Added singleton for Game class
				Added full screen option, removed as flickers when intro backgrounds are scrolling
	2017/02/22 PLAYER: Added check to make sure player is alive to dislay speed boost indicator on heads up display
	2017/02/21 HUD: Separated heads up display object initialisation to the class for loading textures for player lives etc
				HUD: Added Heads up display class HUD.h for handling displaying objects on the heads up display / User interface
	2017/02/19 EXPLOSIONS: Added separate explosions for blood cells to look more like a blood splatter
				ROCKET: Added functionality to initialise the rocket, then create and launch the rocket after returning true from function in spawnRocket() function
				PLAYER: Added check to player movement for speed boost
	2017/02/18 CHECKPOINT: Added checkpoint power, enemy laser, blood cells up to game objects list
				Set types and sub-types for objects on game objects list
				Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen
	2017/02/17 AUDIO: Added identifyTrack() function to dentify the song current playing and display the name on screen
				AUDIO: Started adding original music tracks to the game
	2017/02/16 MESSAGES: Added infoMessage() function to display player messages for player events
	2017/02/15 GAME OBJECT: Started converting all game objects to be moved to one game object list, instead of separate lists for each object type
				LEVEL: Added reset function for completing a level, or resetting the game
				MESSAGES: Added independent information messages for player 1 and 2
				SAW: Fixed saw not spawning ...again!
				MAP: Fixed dimensions of map, and set transparent when enlarged
				POWER UPS: Added Power Ups, Explosions to list of game objects
	2017/02/14 MENU: Added menu handling class
	2017/02/10 SCORES: Added functionality so the scores displayed on screen move to player who scored them (Changed from moving to players score)
				MAP: Tried using some of the algorithms from graphics last sememster to see could they be used to move a player ship on the game map, to indicate it's position with no luck
	2017/02/09 GAMEPAD: Display gamepad information, moved to separate header file
				EXPLOSION: Fixed the explosion animations, they are now assigned to indiviual objects with the game object frame attribute
				Fixed the Enemy Ship animations, they are now assigned to indiviual objects with the game object frame attribute
				Added audio class Audio.h for handling music and sound effects
				Added gamepad class Gamepad.h for handling gamepad functionality
				Added collision class CollisionStuff.h for handling collisions between objects
				Added status bar class StatusBar.h for creating status bars, such as health bar
				Added score class ScoreValueText.h for displaying values of scores for destroying objects
				Added separate function for text and logos to Game class
	2017/02/08 Added separate splash screen class SplashScreen.h for displaying splash screens
				Added check so rocket explodes on collision with the game boundary
				Added press enter to continue for splash screens instead of delay before progressing to level
	2017/02/06 Added managePlayerScores() function to handle players score
				Added spawnRocket() function to create rockets for players, rocket movement can be controlled by player
				Added class for rockets Rocket.h (Renamed WeaponPlRocket.h)
				Added functionality so only 1 rocket can be active at a time for players
	2017/02/02 Completely separated FPS to its own class
				Added storyline at intro to game
	2017/02/01 Started to move FPS functionality to it's own class
				Added frames for second class FPS.h
	2017/01/31 Added vector list of game objects to display the scores for each object killed
				Added timer for player information messages
				Added points value messages for each player
	2017/01/30 Added rotation angle to constructors for Textures that rotate
				Moved flashGameObject() functionality into Texture class
				Added particle texture alpha modify functionality
				Combined player weapons to one list instead of lists for each type
	2017/01/29 Added mini map to game, map increases/decreases size by pressing button using viewports
	2017/01/25 Added spawnExplosion() function for creating explosions when lasers collide with Enemy Ships and Virus
				Added explosion handling class Explosion.h
				Fixed error for Player Message Text
				Fixed Ninja Star scoring for Player 2
				Added check for if the type of virus is newer Orange Exploding Virus or older Green Virus
				Added alert message to notify player Exploding Orange Virus is approaching
				Added functionality so Orange Virus explodes after colliding with player
	2017/01/24 Changed fonts and graphics at start of level, and start and end of scrolling background
				Added Menu to main code
				Changed screen size from 1280 x 720 from 800 x 600
				Added Y padding to keep objects within the game screen boundary
	2017/01/23 Set up level progression and background
				Added laser power up, player can increase the laser weapons grade to fire 3 beams instead of just 1
				Fixed saw spawning, now appearing/disappearing
	2017/01/22 Added forwards/backwards rotation for blood cells
				Moved render functions out of Game.cpp
	2017/01/20 Spawn Player 1 at random Y coord added to spawnPlayer() function
				Added more random shooting from enemy ships
				Fixed problem where not all ships are firing
				Fixed problem for ninja stars only scoring for Player 1
				Added spawnSaw() function to create Saw Weapon for player
				Added spawnExplosion() functions for creating explosions when objects collide
				Added particle handling class Particle.h for player ship engine particles
				Added game over message
				Added player lives indicators for players
	2017/01/19 Started to add game main menu
				Added for loops for separating sprite sheets
				Added 3 beam laser weapon
	2017/01/18 Added splash screens at start of game, Game Title & Game Creators
				Added pressButtonToContinue() function for splash screens at start of game, so player can read writing at own pace
				Added spawnRandom() function to separate out common randomness of game object spawning
				Added collision handling functions
				Fixed animations for game objects, with independent frame handling
				Added health bars for players
				Added force feedback (haptic) support for controller button press and collisions
				Added player speedboost
				Fixed virus movement to move towards the nearest player not just player 1
	2017/01/17 Added displayText() function to render text used in the game
				Added gamepadInfo() function to separate gamepad information into its own function
				Added player decision to spawnNinjaStar() function - determines player to spawn for and their coords
				Added class for saw weapon Saw.h (renamed WeaponPlSaw.h)
				Added collision detection for Ninja Stars
				Separated Player 1 and 2 scores
				Added check for number of gamepads connected to system
				Added wrapped text to add new line character for level intro splash screens
				Added scrolling text to intro screen
	2017/01/16 Added spawnLaser() function to spawn a laser at coords, with velocitys
				Added second player to game
	2017/01/15 Added support for game controller (sticks not working correctly)
				Added gameTimer() function, to ouput the current seconds remaining in the game
	2017/01/13 Fixed problem with rendering text -> true type fonts not initialised in init()
	2017/01/12 Added check so scrolling background stops at end, so end of level boss can be inserted
	2017/01/11 Added checks for collisions by lasers
				Added flash on collision for player
				Started work on true type font support for game text (and timer) adding SDL_ttf
				Added flashing game over texture
				Added flashing to timer for when there is 5 seconds or less on the clock, also changes colour to red, to warn player
				Alter function for alpha values to handle any object and not just Players
	2017/01/10 Added Large Blood Cell object
				Added class for handling blood cells including Small Blood Cell, and White Blood Cells, BloodCell.h
				Added spawn functions to spawn enemies and obstacles at random coords & distances apart
				Added class for handling powerups PowerUp.h
	2017/01/09 Added music and sound effects to game, needs to be initialised with video in init()
				Added spawnNinjaStar() function to create ninja star weapon
				Edited background to be 800 x 600 instead of 600 x 480
				Added playerInput() function to handle input from player
				Added destroyGameObjects() function to destroy the game objects when finished using
				Added moveGameObjects() funtction to move the game objects on the screen
				Added spawnEnemyShip() function to create enemy ships at random times and random y coord
	2017/01/06 Added player lasers
				Enemy movement from right to left towards player adapted from laser spawning
	2016/10/17 First prototype of game
*/
/*
	GAME:

	The game class controls the initialisation, updating, and cleaning of the game. Object movement, rendering and functionality
	is handled within this class. Level progression and game over conditions are handles. A simple state machine controls
	progression from menu, and then through the levels, and back to the menu on game over.
*/

#include "_TestData.h"				// 2017/02/09
#include "Game.h"					// Game header file, with functions and variabls
#include <sstream>					// For timer
#include "EnemyShip.h"				// Enemy ship class
#include "EnemyVirus.h"				// 2017/01/10 JOE: Added Seans virus enemy
#include "WeaponPlLaser.h"			// Player Laser weapon
#include "WeaponPlNinjaStar.h"		// 2017/01/09 Player Ninja Star weapon
#include "WeaponPlRocket.h"			// 2017/02/06 Class for creating rockets
#include "WeaponPlSaw.h"			// 2017/01/17 Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell obstacle
#include "PowerUp.h"				// 2017/01/10 SEAN: Added Power Up
#include "Menu.h"					// 2017/02/14 Class for handling menus. Includes button.h
#include "Explosion.h"				// 2017/01/25 Added explosions for Player Laser colliding with Enemy Ships and Virus
#include "FPS.h"					// 2017/02/01 Class for handling frames for second
#include "SplashScreen.h"			// 2017/02/08 Class for displaying splash screens
#include "ScoreValueText.h"			// 2017-02-09 Class for displaying values of scores for destroying objects
#include "StatusBar.h"				// 2017/02/09 Class for creating status bars, such as health bar
#include "CollisionStuff.h"			// 2017/02/09 Class for handling collisions between objects
#include "Gamepad.h"				// 2017/02/09 Class for handling gamepad functionality
#include "Audio.h"					// 2017/02/09 Class for handling music and sound effects
#include "HUD.h"					// 2017/02/21 Class for handling displaying objects on heads up display
#include <math.h>

Game* Game::s_pInstance = 0;

Texture gLevel;

int ninjaStarP1Counter, ninjaStarP2Counter, laserCounter, rocketCounter;
int ninjaStarP1Missed, ninjaStarP2Missed, ninjaStarP1Streak, ninjaStarP2Streak;
int scoreTextP1counter, scoreTextP2counter;
int bloodCellCounterP1, bloodCellcounterP2;

/***************************************************************************************************************************/
/******************************************** TURN STUFF ON AND OFF FOR TESTING ********************************************/

// Game & Level Testing
bool quit = false;					// Main loop flag
bool testMode = true;				// Game is in testing

/***************************************************************************************************************************/

// Weapons
bool killRocket1 = false;
bool killRocket2 = false;
bool Laser1 = false;
bool Laser2 = false;

void setViewport(SDL_Rect &rect, int x, int y, int w, int h);	// These classes are giving errors when they are moved to the header file
void setupAnimationClip(SDL_Rect rect[], int frames, int amount, bool type2 = false);

// Classes
Menu menu1;
HUD headsUpDisplay;
StatusBar bar;
SplashScreen splash;
FPS fps1;							// 2017/02/01 Moved FPS functionality to it's own class
Particle particle;

// Viewports
SDL_Rect gameViewport;				// Main game screen view port
SDL_Rect UIViewport;				// Menu below main game screen view port
SDL_Rect mapViewport;				// Map indicating the ships current location in the professors body
SDL_Rect weaponViewport1;			// Indicates the currently selected main weapon
SDL_Rect weaponViewport2;			// Indicates the currently selected main weapon
SDL_Rect rocketViewport1;			// Indicates the currently selected main weapon
SDL_Rect rocketViewport2;			// Indicates the currently selected main weapon
SDL_Rect boostViewport1;			// Indicates the currently selected main weapon
SDL_Rect boostViewport2;			// Indicates the currently selected main weapon
// Animation frames
SDL_Rect gEnemySpriteClips[ANIMATION_FRAMES];				// Sprite frames for Enemy Ship animation
SDL_Rect gGreenVirusSpriteClips[6];							// Sprite frames for Orange Virus animation
SDL_Rect gOrangeVirusSpriteClips[6];						// Sprite frames for Orange Virus animation
SDL_Rect gBlueVirusSpriteClips[6];							// Sprite frames for Blue Virus animation
SDL_Rect gSmallGreenVirusSpriteClips[6];					// Sprite frames for Small Green Virus animation
SDL_Rect gSmallOrangeVirusSpriteClips[6];					// Sprite frames for Small Orange Virus animation
SDL_Rect gSmallBlueVirusSpriteClips[6];						// Sprite frames for Small Blue Virus animation
// Explosion Animations
SDL_Rect gExplosionClips[EXPLOSION_ANIMATION_FRAMES];				// Sprite frames for Explosion animation
SDL_Rect gBloodExplosionClips[BLOOD_EXP_ANIMATION_FRAMES];			// Sprite frames for Blood Explosion animation
SDL_Rect gVirusGreenExplosionClips[BLOOD_EXP_ANIMATION_FRAMES];		// Sprite frames for Green Virus Explosion animation
SDL_Rect gVirusOrangeExplosionClips[BLOOD_EXP_ANIMATION_FRAMES];	// Sprite frames for Orange Virus Explosion animation
SDL_Rect gVirusBlueExplosionClips[BLOOD_EXP_ANIMATION_FRAMES];		// Sprite frames for Blue Virus Explosion animation

Texture gProfessorMapTexture;						// Map texture to show the players current position inside the professor
Texture gEnemySpriteSheetTexture;					// Enemy sprite sheet
Texture gExplosionSpriteSheetTexture;				// Explosion sprite sheet
Texture gBloodExplosionSpriteSheetTexture;			// Blood explosion sprite sheet
Texture gVirusGreenExplosionSpriteSheetTexture;		// Green Virus explosion sprite sheet
Texture gVirusOrangeExplosionSpriteSheetTexture;	// Orange Virus explosion sprite sheet
Texture gVirusBlueExplosionSpriteSheetTexture;		// Blue Virus explosion sprite sheet

Texture gGreenVirusSpriteSheetTexture;		// Green Virus sprite sheet
Texture gOrangeVirusSpriteSheetTexture;		// Orange Virus sprite sheet
Texture gBlueVirusSpriteSheetTexture;		// Blue Virus sprite sheet

Texture gSmallGreenVirusSpriteSheetTexture;	// Small Green Virus sprite sheet
Texture gSmallOrangeVirusSpriteSheetTexture;// Small Orange Virus sprite sheet
Texture gSmallBlueVirusSpriteSheetTexture;	// Small Blue Virus sprite sheet

SDL_Event e;							// Event handler

// Joystick
SDL_Joystick* gController1 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Joystick* gController2 = NULL;		// Game Controller 1 handler - Data type for a game controller is SDL_Joystick
SDL_Haptic*	gControllerHaptic = NULL;	// 2017/01/18 Haptic (Force Feedback) added

// Text
SDL_Color textColour;					// Set the text colour
TTF_Font *gFontRetro20;				// Globally used font 2017-01-25 Changed to Retro font which is more readable

// Objects and weapons
Texture gPlayer1Texture;			// Player 1 ship
Texture gPlayer2Texture;			// Player 2 ship

Texture gPowerUpRocketTexture;		// Texture for Rocket power up
Texture gRocketTexture;				// Texture for Rocket weapon
Texture gNinjaStarBlueTexture(5);	// Texture for Ninja Star weapon
Texture gNinjaStarYellowTexture(5);	// Texture for Ninja Star weapon // 2017-01-30 with rotation angle of 5 degrees
Texture gSawTexture(5);				// Texture for Ninja Star weapon
Texture gBloodCellTexture(1);		// Texture for Blood Cell obstacle (classed as enemy as it causes damage on impact)
Texture gBloodCellSmallTexture(2);	// Texture for Smaller Blood Cell
Texture gWhiteBloodCellTexture(2);	// Texture for White Blood Cell
// UI
Texture gTimeTextTexture;			// Countdown time displayed in game screen
Texture gFPSTextTexture;			// Frames Per Second displayed at top of screen

Texture gInfoMessageP1TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageP2TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageTextTexture;	// Player notification messages for picking up objects etc.

// Vectors for objects that have collisions - These 2 lists are the only 2 we need
//std::vector<Texture*> listOfScoreTextures;	// The score for any object a player Kills
std::vector<GameObject*> listOfGameObjects;		// 2017/01/31 Using to display the scores for each object killed, 2017/02/15 added Power Ups, Explosions

Player* player1 = new Player();
Player* player2 = new Player();

bool Game::init() {
	nameEntered = false;

	//twoPlayer = true;

	resetGame(getCurrentLevel());										// Initialise variables depending on level

	// View ports
	setViewport(gameViewport, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// Main Game Screen
	setViewport(UIViewport, 0, 600, SCREEN_WIDTH, 120);					// Bottom of screen UI / Info
	setViewport(weaponViewport1, 10, 600, 60, 60);						// Current Main Weapon Selected
	setViewport(rocketViewport1, 70, 600, 60, 60);						// Current Main Weapon Selected
	setViewport(boostViewport1, 130, 600, 60, 60);						// Current Main Weapon Selected
	setViewport(weaponViewport2, SCREEN_WIDTH - 70, 600, 60, 60);		// Current Main Weapon Selected
	setViewport(rocketViewport2, SCREEN_WIDTH - 130, 600, 60, 60);		// Current Main Weapon Selected
	setViewport(boostViewport2, SCREEN_WIDTH - 190, 600, 60, 60);		// Current Main Weapon Selected

	// Game Console Title
	std::cout << "23//02/2017 - Selectable 1 or 2 Player" << std::endl;

	std::cout << "Player 1 Health: " << player1->getHealth() << " Lives: " << player1->getNumLives() << std::endl;		// Player 1 health & Lives at start of game
	player1->setName("Player 1");	// Names for players
	//if (testMode) player1->setNumLives(MAX_NUM_LIVES);

	if (twoPlayer) {
		std::cout << "Player 2 Health: " << player2->getHealth() << " Lives: " << player2->getNumLives() << std::endl;	// Player 1 health & Lives at start of game
		player2->setName("Player 2");
		//if (testMode) player2->setNumLives(MAX_NUM_LIVES);
	}

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
		int windowFlag;		// Show the game in full screen or windowed
		if (FULL_SCREEN)
			windowFlag = SDL_WINDOW_FULLSCREEN;
		else
			windowFlag = SDL_WINDOW_SHOWN;

		gWindow = SDL_CreateWindow("Antibody", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlag);	/* Window name */

		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// Create vsynced renderer for window

			if (getRenderer() == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);										// Initialize renderer color

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

	//gLevel.loadFromRenderedText("Level " + std::to_string(getCurrentLevel()), { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	//gLevel.loadFromRenderedTextID("Level " + std::to_string(getCurrentLevel()), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	Texture::Instance()->loadFromRenderedTextID("Level " + std::to_string(getCurrentLevel()), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	bool success = true;			// Loading success flag

	Texture::Instance()->loadTextureMedia();

	menu1.loadMediaMenu();						// Load buttons etc

	//success = player1->loadMediaPlayer();		// Load particles for each player
	//success = player2->loadMediaPlayer();		// Load particles for each player
	//if (twoPlayer) success = player2->loadMediaPlayer();		// Load particles for each player

	success = Audio::Instance()->loadMediaAudio();
	success = headsUpDisplay.loadLevelStuff();			// 2017/02/21 Separated heads up display object initialisation to the class for loading textures for player lives etc
	success = particle.initParticle();

	if (!gProfessorMapTexture.loadFromFile("Art/Prof.png")) {			// Load Dark Particle texture
		printf("Failed to load Professor texture image!\n");
		success = false;
	}

	// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };										// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);							// Use bold font
	}

	// Load Textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png")) {					// Player 1 Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
//	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.png")) {					// Player 2 Ship Texture
	if (!gPlayer2Texture.loadFromFile("Art/Player2ShipOld.png")) {					// Player 2 Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gBloodCellTexture.loadFromFile("Art/BloodCell.png")) {					// 10/01 Added Large Blood Cell
		printf("Failed to load Blood Cell texture!\n");
		success = false;
	}
	if (!gBloodCellSmallTexture.loadFromFile("Art/BloodCellSmall.png")) {		// 10/01 Added Small Blood Cell
		printf("Failed to load Small Blood Cell texture!\n");
		success = false;
	}
	if (!gWhiteBloodCellTexture.loadFromFile("Art/WhiteCell.png")) {			// 10/01 White Blood Cell
		printf("Failed to load White Blood Cell texture!\n");
		success = false;
	}
	// Weapons
	if (!gNinjaStarBlueTexture.loadFromFile("Art/NinjaStarBlue.png")) {			// Ninja Star Texture
		printf("Failed to load Blue Ninja Star texture!\n");
		success = false;
	}
	if (!gNinjaStarYellowTexture.loadFromFile("Art/NinjaStarYellow.png")) {		// Ninja Star Texture
		printf("Failed to load Yellow Ninja Star texture!\n");
		success = false;
	}
	if (!gSawTexture.loadFromFile("Art/SawBlue.png")) {							// Saw Texture
		printf("Failed to load Blue Saw texture!\n");
		success = false;
	}
	if (!gRocketTexture.loadFromFile("Art/Rocket.png")) {						// Rocket Texture
		printf("Failed to load Rocket texture!\n");
		success = false;
	}
	// Power Ups
	if (!gPowerUpRocketTexture.loadFromFile("Art/PowerUpRocket.png")) {			// Rocket Power Up Texture
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}

	success = splash.initSplashScreens();										// Initialise the splash screens

	if (!gEnemySpriteSheetTexture.loadFromFile("Art/EnemySpriteSheet2.png")) {	// Sprite sheet for Enemy Ship
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

	if (!gGreenVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Green.png")) {	// Sprite sheet for Enemy Orange Virus
		printf("Failed to load Green Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gGreenVirusSpriteClips, 6, 75, true);	// Set sprite clips
	}
	if (!gOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange.png")) {// Sprite sheet for Enemy Orange Virus
		printf("Failed to load Orange Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gOrangeVirusSpriteClips, 6, 75, true);	// Set sprite clips
	}

	if (!gBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Blue.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gBlueVirusSpriteClips, 6, 75, true);	// Set sprite clips
	}
	if (!gSmallGreenVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Green_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallGreenVirusSpriteClips, 6, 40, true);	// Set sprite clips
	}
	if (!gSmallOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallOrangeVirusSpriteClips, 6, 40, true);	// Set sprite clips
	}
	if (!gSmallBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Blue_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallBlueVirusSpriteClips, 6, 40, true);	// Set sprite clips
	}

	if (!gExplosionSpriteSheetTexture.loadFromFile("Art/Explosion.png")) {	// Sprite sheet for Explosions
		printf("Failed to load Explosion animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gExplosionClips, EXPLOSION_ANIMATION_FRAMES, 96);	// Set sprite clips
	}
	if (!gBloodExplosionSpriteSheetTexture.loadFromFile("Art/ExplosionBlood.png")) {	// Sprite sheet for Explosions
		printf("Failed to load Blood Explosion animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gBloodExplosionClips, BLOOD_EXP_ANIMATION_FRAMES, 128);	// Set sprite clips
	}
	if (!gVirusGreenExplosionSpriteSheetTexture.loadFromFile("Art/ExplosionVirusGreen.png")) {	// Sprite sheet for Explosions
		printf("Failed to load Green Virus Explosion animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gVirusGreenExplosionClips, BLOOD_EXP_ANIMATION_FRAMES, 128);	// Set sprite clips
	}
	if (!gVirusOrangeExplosionSpriteSheetTexture.loadFromFile("Art/ExplosionVirusOrange.png")) {	// Sprite sheet for Explosions
		printf("Failed to load Orange Virus Explosion animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gVirusOrangeExplosionClips, BLOOD_EXP_ANIMATION_FRAMES, 128);	// Set sprite clips
	}
	if (!gVirusBlueExplosionSpriteSheetTexture.loadFromFile("Art/ExplosionVirusBlue.png")) {	// Sprite sheet for Explosions
		printf("Failed to load Blue Virus Explosion animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gVirusBlueExplosionClips, BLOOD_EXP_ANIMATION_FRAMES, 128);	// Set sprite clips
	}

	//if (MUSIC_ON) audio.music();		// EDIT IN _TestData.h
	Audio::Instance()->music();

	return success;
}

void setupAnimationClip(SDL_Rect rect[], int frames, int amount, bool type2) {
	if (!type2) {
		for (unsigned int i = 0; i < frames; ++i) {
			rect[i].x = i * amount;
			rect[i].y = 0;
			rect[i].w = amount;
			rect[i].h = amount;
		}
	}
	else {
		for (unsigned int i = 0; i < 6; ++i) {
			if (i < 4) rect[i].x = i * amount;
			else if (i == 5) rect[i].x = 2 * amount;
			else if (i == 6) rect[i].x = 1 * amount;
			rect[i].y = 0;
			rect[i].w = amount;
			rect[i].h = amount;
		}
	}
}

void Game::close() {
	gProfessorMapTexture.free();

	// Free loaded images
	gPlayer1Texture.free();
	gPlayer2Texture.free();

	gNinjaStarBlueTexture.free();
	gNinjaStarYellowTexture.free();
	gSawTexture.free();
	gRocketTexture.free();
	gBloodCellTexture.free();
	gBloodCellSmallTexture.free();
	gWhiteBloodCellTexture.free();
	gPowerUpRocketTexture.free();

	// free animations
	gEnemySpriteSheetTexture.free();
	gExplosionSpriteSheetTexture.free();
	gBloodExplosionSpriteSheetTexture.free();
	gVirusGreenExplosionSpriteSheetTexture.free();
	gVirusOrangeExplosionSpriteSheetTexture.free();
	gVirusBlueExplosionSpriteSheetTexture.free();

	gGreenVirusSpriteSheetTexture.free();
	gOrangeVirusSpriteSheetTexture.free();
	gBlueVirusSpriteSheetTexture.free();

	gSmallGreenVirusSpriteSheetTexture.free();
	gSmallOrangeVirusSpriteSheetTexture.free();
	gSmallBlueVirusSpriteSheetTexture.free();

	gTimeTextTexture.free();
	gFPSTextTexture.free();
	gInfoMessageP1TextTexture.free();
	gInfoMessageP2TextTexture.free();
	gInfoMessageTextTexture.free();

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
	//SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//gRenderer = NULL;

	//fps.fpsclose();
	splash.closeSplashScreens();	// Close splash screen stuff
	menu1.closeMenu();				// Close menu stuff
	Audio::Instance()->destroy();
	headsUpDisplay.closeLevelStuff();
	particle.closeParticle();

	// Empty Lists
	listOfGameObjects.clear();		// Scores, Power Ups, Explosions
	//listOfScoreTextures.clear();

	Texture::Instance()->clearTextureMap();

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
				if (!twoPlayer) player2->setAlive(false);

				quit = playerInput(quit);									// 2017/01/09 JOE: Handle input from player

				if (getCurrentLevel() == 0 && displayGameIntro) displayGameIntro = splash.displayGameIntroSplashScreens();	// 2017/01/18 Splash screens at start of game, Game Title & Game Creators

				if (getCurrentLevel() == MENU) menu1.draw();		// New

				//if (!nameEntered) enterName();

				//if(getCurrentLevel() == 1) enterName();
				//else {

					if (getCurrentLevel() != 0) playLevel(getCurrentLevel());
					//playLevel(1);	// Test start at level 2

					if (getCurrentLevel() > 0) fps1.fpsthink();					// Update the FPS

					destroyGameObjects();										// 2017-01-09 JOE: Destroy the game objects when finished on the screen
				//}
			}
		}
	}
}


bool renderText;
std::string inputText = "Name";
/*
//bool Game::enterName() {
bool Game::enterName() {
	SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);	// Clear background
	Texture::Instance()->draw("enterNameID", 50, 100, 400, 20);		// Display enter name message
	Texture::Instance()->loadInputText(inputText);
	//Texture::Instance()->drawText("inputTextID", 50, 150);
	Texture::Instance()->renderMap("inputTextID", 50, 150, 100, 100);

	renderText = false;		// flag that keeps track of whether we need to update the texture

	while (SDL_PollEvent(&e) != 0) {
		//User requests quit
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		//Special key input
		else if (e.type == SDL_KEYDOWN) {
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {	// backspace -> remove the last character from the string
				//lop off character
				inputText.pop_back();
				renderText = true;		// Set the text update flag
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + c -> copy the text to the clip board
				SDL_SetClipboardText(inputText.c_str());
			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {	// Ctrl + v -> get the text from the clipboard
				inputText = SDL_GetClipboardText();
				renderText = true;		// Set the text update flag
			}
			else if (e.key.keysym.sym == SDLK_RETURN) {
				player1->setName(inputText);
				//Game::Instance()->setName(inputText);
				nameEntered = true;
			}
		}
		//Special text input event
		else if (e.type == SDL_TEXTINPUT) {
			//Not copy or pasting
			if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
				//Append character
				inputText += e.text.text;
				renderText = true;
			}
		}
	}


	//Rerender text if needed
	if (renderText) {
		//Text is not empty
		if (inputText != "") {
			Texture::Instance()->loadInputText(inputText);
		}
		//Text is empty
		else {
			Texture::Instance()->loadInputText(" ");
		}
	}

	return nameEntered;
}
*/

void Game::playLevel(int levelNum) {
	//if (!nameEntered)
		//nameEntered = enterName();
	//else
	if (displayLevelIntro)displayLevelIntroScreens(levelNum);	// Set true or false in _test.cpp
	{
		if (!gameOver) {
			spawnMovingObjects();	// 2017/01/10 JOE: Spawn enemies and obstacles at random coords & distances apart
			moveGameObjects();		// 2017-01-09 JOE: Move the game objects on the screen
			collisionCheck();		// Check collisions between 2 objects
		}

		renderGameObjects();		// 2017-01-09 JOE: Render the game objects to the screen
	}
}

void Game::displayLevelIntroScreens(int level) {
	// STORY - INSTRUCTIONS - OBJECTIVES - INFORMATION screens, pass in all the textures to give information about for each level
	//if (level == 1)
		displayLevelIntro = splash.level1IntroScreens(getCurrentLevel());		// Display level story and info screens
	//if (level == 2) displayLevelIntro = splash.level2IntroScreens();
	//if (level == 3) displayLevelIntro = splash.level3IntroScreens();

	if (level <= MAX_NUM_LEVELS) splash.pressButtonToContinue(e);
}

void Game::displayText() {
	if (player1->getAlive()) player1Score = player1->getScore();
	if (twoPlayer && player2->getAlive()) player2Score = player2->getScore();

	std::stringstream framesPerSec;	// In memory text stream - string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory

	framesPerSec << "FPS: " << fps1.getFPS();													// FPS the game is running at

	if(!twoPlayer)
		finalScores = "Player 1: " + std::to_string(player1Score);								// End of game Player 1 and Player 2 scores
	else if(twoPlayer)
		finalScores = "Player 1: " + std::to_string(player1Score) + " Player 2: " + std::to_string(player2Score);	// End of game Player 1 and Player 2 scores

	std::stringstream timeText;
	timeText.str("");																			// Set text to be rendered - string stream - print the time since timer last started - initialise empty

	if (!levelOver && !gameOver) {
		if (countdownTimer > 0 && countdownTimer <= GAME_TIMER) {
			timeText << "Time: " << countdownTimer;												// Set the game timer

			gTimeTextTexture.UITextTimer(timeText.str().c_str(), countdownTimer);	// Render Text - Use a string to render the current Game Time to a Texture

			gFPSTextTexture.UIText(framesPerSec.str().c_str());						// Render text - Use a string to render the current FPS to a texture

			levelOver = false;
		} else
			if (countdownTimer <= 0 || countdownTimer > GAME_TIMER + 6) {
				levelOver = true;													// Level is over
			if (getCurrentLevel() == MAX_NUM_LEVELS) gameOver = true;
		}

		gameTimer();																// Set the count down timer - decrement by 1 second

		//headsUpDisplay.gameTime(countdownTimer);	// NOT WORKING

		//gTimeTextTexture.UITextTimer(timeText.str().c_str(), countdownTimer);	// Render Text - Use a string to render the current Game Time to a Texture

		//gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8);
		fps1.rendFPS(framesPerSec.str().c_str());
		/*
		if (!gFPSTextTexture.loadFromRenderedText(framesPerSec.str().c_str(), textColour, gFontRetro20, gRenderer)) {
			printf("Unable to render FPS texture!\n");
		}
		*/
		if (infoMessageP1 != "") gInfoMessageP1TextTexture.UITextPlayerMessage(infoMessageP1, PLAYER_1);	// Render Text - Use a string to render Player 1 notifications
		if (infoMessageP2 != "") gInfoMessageP2TextTexture.UITextPlayerMessage(infoMessageP2, PLAYER_2);	// Render Text - Use a string to render Player 2 notifications
		if (infoMessageGeneral != "") gInfoMessageTextTexture.UITextPlayerMessage(infoMessageGeneral);		// Render Text - Use a string to render General notifications
	}
	else if (levelOver == true) {
		//std::cout << "Level " << getCurrentLevel() << " Complete" << std::endl;
		//gamerOverMessageDisplayCounter = 0;
		gameProgress();
	}// Levels
	else if (gameOver == true) {
		if (!twoPlayer)
			gameWinners = "Player has completed the course";
		else if (twoPlayer) {
			if (player1Score > player2Score)
				gameWinners = "Player 1 Wins";
			else if (player2Score > player1Score)
				gameWinners = "Player 2 Wins";
			else
				gameWinners = "It's a draw";
		}

		gameProgress();
	}
}

void Game::gameProgress() {
	gamerOverMessageDisplayCounter++;
	//std::cout << "Game over counter: " << gamerOverMessageDisplayCounter << std::endl;

	if (gamerOverMessageDisplayCounter >= 300) {
		gamerOverMessageDisplayCounter = 0;

		//if (player1->getAlive() == false) {
		if (!player1->getAlive() || !player2->getAlive()) {
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
					int song = Audio::Instance()->playMusic();
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
				// case SDLK_DOWN:
				//	topViewport.w = 10;
				//	break;

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
		if (getCurrentLevel() != 0) {												// If not in menu state
			if(player1->getAlive()) player1->handleEvent(e, 1);						// Handle input for Player 1
			if (player2->getAlive()) player2->handleEvent(e, 2);					// Handle input for Player 2

			for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
				if (listOfGameObjects[index]->getSubType() == ROCKET_P1 && listOfGameObjects[index]->getPlayer() == PLAYER_1) {
					listOfGameObjects[index]->handleEvent(e, PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == ROCKET_P2 && listOfGameObjects[index]->getPlayer() == PLAYER_2) {
					listOfGameObjects[index]->handleEvent(e, PLAYER_2);
				}
			}
		}
	}

	return quit;
}

void Game::musicTrackForward() {
	int songName = Audio::Instance()->musicForwardSongName();
	identifyTrack(songName);
	infoMessage("Music Track Skip Forwards");
}
void Game::musicTrackBackward() {	;
	int songName = Audio::Instance()->musicBackSongName();
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
		infoMessage("Song Title: The First Step", 2);
	}
	else if (songName == 4) {
		infoMessage("Artist: Joe O'Regan", 1);
		infoMessage("Song Title: Virus", 2);
	}
}

void Game::setRotatingAngle() {
	// ROTATE GAME OBJECTS - Set angle increment for rotating textures
	gNinjaStarBlueTexture.setDegrees(gNinjaStarBlueTexture.getDegrees() + 5);
	gNinjaStarYellowTexture.setDegrees(gNinjaStarYellowTexture.getDegrees() + 5);
	gSawTexture.setDegrees(gSawTexture.getDegrees() + 5);
	gBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 1);
	gBloodCellSmallTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);
	gWhiteBloodCellTexture.setDegrees(gBloodCellTexture.getDegrees() + 2);
}

void Game::scrollBackground() {
	if (backgroundLoopCounter <= BACKGROUND_SCROLL_TIMES) scrollingOffset -= 5;	// Scroll for a fixed number of times
	if (scrollingOffset < -SCREEN_WIDTH) {
		scrollingOffset = 0;													// update the scrolling background

		backgroundLoopCounter++;												// count the number of times the background has looped
		std::cout << "Background has looped " << backgroundLoopCounter << " times" << std::endl;
	}

	// Render background
	if (backgroundLoopCounter < 1) Texture::Instance()->renderMap("startBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);											// 1st background (and every odd number)
	else if (backgroundLoopCounter > BACKGROUND_SCROLL_TIMES) Texture::Instance()->renderMap("endBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);
	else Texture::Instance()->renderMap("middleBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);

	if (backgroundLoopCounter < BACKGROUND_SCROLL_TIMES) Texture::Instance()->renderMap("middleBG", scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// 2nd background (and every even number)
	else Texture::Instance()->renderMap("endBG", scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);														// end background
}

void Game::renderGameObjects() {
	// Levels
	if (weaponScrolling > 0) weaponScrolling--;
	setRotatingAngle();	// 2017/02/22: Angle needs to be updated each time a rotating object is drawn to screen
	displayText();		// 2017/01/17: Display the game text

	if (player1->getAlive()) gPlayer1Texture.flashGameObject(10, 4);				// 2017/01/30 Moved flashGameObject() function into LTexture
	if (player2->getAlive()) gPlayer2Texture.flashGameObject(10, 4);
	gTimeTextTexture.flashGameObject(8);

		// Clear screen
	SDL_SetRenderDrawColor(getRenderer(), 0x3C, 0x3C, 0x3C, 0xFF);		// Grey colour --> shows up in UI
	SDL_RenderClear(getRenderer());

	SDL_RenderSetViewport(getRenderer(), &gameViewport);				// Set the viewport

	if (levelOver == false && gameOver == false) {
		scrollBackground();

		//if (gameOver == false) {
		SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		gPowerUpRocketTexture.modifyAlpha(255);							// Keep alpha values independent

		//if (player1->getAlive()) SDL_RenderDrawRect(getRenderer(), &player1->getCollider());
		//if (twoPlayer && player2->getAlive()) SDL_RenderDrawRect(getRenderer(), &player2->getCollider());

		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			//SDL_RenderDrawRect(getRenderer(), &listOfGameObjects[index]->getCollider());
			frames = listOfGameObjects[index]->getFrames();		// 2017/02/09 Fixed the explosion animations, they are now assigned to indiviual objects with the game object frame attribute

			// Render Saws
			if (listOfGameObjects[index]->getSubType() == SAW1) listOfGameObjects[index]->render(gSawTexture, gSawTexture.getDegrees());
			else if (listOfGameObjects[index]->getSubType() == SAW2) listOfGameObjects[index]->render(gSawTexture, gSawTexture.getDegrees());
			// Render Power Ups
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH)		// Health Texture
				Texture::Instance()->renderMap("healthPowerUpID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER)		// Laser Texture
				Texture::Instance()->renderMap("laserPowerUpID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) listOfGameObjects[index]->render(gPowerUpRocketTexture);			// Rocket Texture
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) // Checkpoint Texture
				Texture::Instance()->renderMap("checkpointPowerUpID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());

			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES)		// Checkpoint Texture
				Texture::Instance()->renderMap("lifePowerUpID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			// Render Explosions
			else if (listOfGameObjects[index]->getSubType() == EXPLOSION) {
				listOfGameObjects[index]->render(gExplosionSpriteSheetTexture, &gExplosionClips[frames / EXPLOSION_ANIMATION_FRAMES], frames, EXPLOSION_ANIMATION_FRAMES);
				if (frames / 8 >= EXPLOSION_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
					frames = 0;										// reset animation frames
					listOfGameObjects[index]->setAlive(false);
				}
			}
			// Render Blood Explosion
			else if (listOfGameObjects[index]->getSubType() == BLOOD_EXPLOSION) {
				gBloodExplosionSpriteSheetTexture.setAlpha(100);
				gBloodExplosionSpriteSheetTexture.modifyAlpha(gBloodExplosionSpriteSheetTexture.getAlpha());
				listOfGameObjects[index]->render(gBloodExplosionSpriteSheetTexture, &gBloodExplosionClips[frames / 5], frames, BLOOD_EXP_ANIMATION_FRAMES);
				if (frames / 5 >= BLOOD_EXP_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
					frames = 0;										// reset animation frames
					listOfGameObjects[index]->setAlive(false);
				}
			}
			else if (listOfGameObjects[index]->getSubType() == GREEN_VIRUS_EXPLOSION) {
				gVirusGreenExplosionSpriteSheetTexture.setAlpha(125);
				gVirusGreenExplosionSpriteSheetTexture.modifyAlpha(gVirusGreenExplosionSpriteSheetTexture.getAlpha());
				listOfGameObjects[index]->render(gVirusGreenExplosionSpriteSheetTexture, &gVirusGreenExplosionClips[frames / 5], frames, BLOOD_EXP_ANIMATION_FRAMES);
				if (frames / 5 >= BLOOD_EXP_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
					frames = 0;										// reset animation frames
					listOfGameObjects[index]->setAlive(false);
				}
			}
			else if (listOfGameObjects[index]->getSubType() == ORANGE_VIRUS_EXPLOSION) {
				gVirusOrangeExplosionSpriteSheetTexture.setAlpha(125);
				gVirusOrangeExplosionSpriteSheetTexture.modifyAlpha(gVirusOrangeExplosionSpriteSheetTexture.getAlpha());
				listOfGameObjects[index]->render(gVirusOrangeExplosionSpriteSheetTexture, &gVirusOrangeExplosionClips[frames / 5], frames, BLOOD_EXP_ANIMATION_FRAMES);
				if (frames / 5 >= BLOOD_EXP_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
					frames = 0;										// reset animation frames
					listOfGameObjects[index]->setAlive(false);
				}
			}
			else if (listOfGameObjects[index]->getSubType() == BLUE_VIRUS_EXPLOSION) {
				gVirusBlueExplosionSpriteSheetTexture.setAlpha(125);
				gVirusBlueExplosionSpriteSheetTexture.modifyAlpha(gVirusBlueExplosionSpriteSheetTexture.getAlpha());
				listOfGameObjects[index]->render(gVirusBlueExplosionSpriteSheetTexture, &gVirusBlueExplosionClips[frames / 5], frames, BLOOD_EXP_ANIMATION_FRAMES);
				if (frames / 5 >= BLOOD_EXP_ANIMATION_FRAMES) {		// If the explosion reaches the last frame
					frames = 0;										// reset animation frames
					listOfGameObjects[index]->setAlive(false);
				}
			}
			// Render player scores for killing Enemies
			else if (listOfGameObjects[index]->getSubType() == PLAYER1_SCORE) {
				if (player1->getAlive()) {
					listOfGameObjects[index]->m_Texture.setAlpha(120);													// Set scores slightly transparent
					listOfGameObjects[index]->render(listOfGameObjects[index]->m_Texture);								// works for m_Texture but not getTexture
				}
				else listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getSubType() == PLAYER2_SCORE) {
				if (player2->getAlive()) {
					listOfGameObjects[index]->m_Texture.setAlpha(100);													// Set scores slightly transparent
					listOfGameObjects[index]->render(listOfGameObjects[index]->m_Texture);
				}
				else listOfGameObjects[index]->setAlive(false);
			}
			// Render Enemy Lasers
			else if (listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) Texture::Instance()->renderMap("fireballID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight()); //
			else if (listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET) Texture::Instance()->renderMap("satelliteID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER) Texture::Instance()->renderMap("blueLaserID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			// Render Blood Cells
			else if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL)
				listOfGameObjects[index]->render(gBloodCellTexture, -gBloodCellTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());			// Render the Blood Cell, with random rotation direction
			else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL)
				listOfGameObjects[index]->render(gBloodCellSmallTexture, -gBloodCellSmallTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());	// Render the Small Blood Cell, with random rotation direction
			else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL)
				listOfGameObjects[index]->render(gWhiteBloodCellTexture, -gWhiteBloodCellTexture.getDegrees() * listOfGameObjects[index]->getRotationDirection());

			// Render Enemies
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {																						// 2017/02/09 Fixed the Enemy Ship animations, they are now assigned to indiviual objects with the game object frame attribute
				listOfGameObjects[index]->render(gEnemySpriteSheetTexture, &gEnemySpriteClips[frames / 10], frames, 4);												// 4 the number of frames
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) listOfGameObjects[index]->render(gGreenVirusSpriteSheetTexture, &gGreenVirusSpriteClips[frames / 10], frames, 6);
			else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) listOfGameObjects[index]->render(gOrangeVirusSpriteSheetTexture, &gOrangeVirusSpriteClips[frames / 10], frames, 6);				// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) listOfGameObjects[index]->render(gBlueVirusSpriteSheetTexture, &gBlueVirusSpriteClips[frames / 10], frames, 6);						// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_GREEN) listOfGameObjects[index]->render(gSmallGreenVirusSpriteSheetTexture, &gSmallGreenVirusSpriteClips[frames / 10], frames, 6);	// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_ORANGE) listOfGameObjects[index]->render(gSmallOrangeVirusSpriteSheetTexture, &gSmallOrangeVirusSpriteClips[frames / 10], frames, 6);// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_BLUE) listOfGameObjects[index]->render(gSmallBlueVirusSpriteSheetTexture, &gSmallBlueVirusSpriteClips[frames / 10], frames, 6);		// 6 the number of frames

			// Weapons
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P1)
				listOfGameObjects[index]->render(gNinjaStarYellowTexture, gNinjaStarYellowTexture.getDegrees());	// Yellow ninja star for player 1
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P2)
				listOfGameObjects[index]->render(gNinjaStarBlueTexture, gNinjaStarBlueTexture.getDegrees());		// Blue ninja star for player 2
			else if (listOfGameObjects[index]->getSubType() == LASER_P1) Texture::Instance()->renderMap("orangeLaserID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == LASER_P2) Texture::Instance()->renderMap("greenLaserID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == LASER_V2_P1) Texture::Instance()->renderMap("orangeLaserID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == LASER_V2_P2) Texture::Instance()->renderMap("greenLaserID", listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P1)
				listOfGameObjects[index]->render(gRocketTexture, listOfGameObjects[index]->getAngle());
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P2)
				listOfGameObjects[index]->render(gRocketTexture, listOfGameObjects[index]->getAngle());

			// Set the object alpha value

			listOfGameObjects[index]->setFrames(frames);	// increment the frames

			listOfGameObjects[index]->m_Texture.modifyAlpha(listOfGameObjects[index]->m_Texture.getAlpha());
		}

		// Render Text
		SDL_RenderSetViewport(getRenderer(), &gameViewport);

		//headsUpDisplay.displayLevelNum(getCurrentLevel());
		//gLevel.free();

		Texture::Instance()->render("levelID", 10, 8);
		//Texture::Instance()->render("levelID", 10, 8);
		//gLevel.render(10, 8);

		if (infoMessageP1Counter < MESSAGE_TIME) {
			gInfoMessageP1TextTexture.render((SCREEN_WIDTH - gInfoMessageP1TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP1TextTexture.getHeight()) / 2) - 20); // Top message P1
			infoMessageP1Counter++;
		}
		if (infoMessageP2Counter < MESSAGE_TIME) {
			gInfoMessageP2TextTexture.render((SCREEN_WIDTH - gInfoMessageP2TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP2TextTexture.getHeight()) / 2) + 20);// Bottom message P2
			infoMessageP2Counter++;
		}
		if (infoMessageCounter < MESSAGE_TIME) {
			gInfoMessageTextTexture.render((SCREEN_WIDTH - gInfoMessageTextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageTextTexture.getHeight()) / 2));			// Middle message General
			infoMessageCounter++;
		}

		gTimeTextTexture.flashGameObject(8);
		gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());						// Flash the timer
		gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8);	// LAZY

		gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8);

		if (player1->getAlive()) {
			bar.playerHealthBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getHealth());

			if (player1->getRocketBarActive()) {
				player1->rocketScore();				// Set the score for the rocket

				bar.rocketPowerBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getTimer());

				if (player1->getTimer() <= 0) {
					spawnExplosion(player1->getX(), player1->getY(), EXPLOSION);
					player1->resetRocket();			// reset the rocket, returns boolean value
				}
			}

			gPlayer1Texture.modifyAlpha(gPlayer1Texture.getAlpha());
			//player1->render(gPlayer1Texture);
			player1->render(gPlayer1Texture);
		}// render the ship over the background
		if (twoPlayer && player2->getAlive()) {
			bar.playerHealthBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getHealth());

			if (player2->getRocketBarActive()) {
				player2->rocketScore();	// return true

				bar.rocketPowerBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getTimer());

				if (player2->getTimer() <= 0) {
					spawnExplosion(player2->getX(), player2->getY(), EXPLOSION);
					player2->resetRocket();
				}
			}

			gPlayer2Texture.modifyAlpha(gPlayer2Texture.getAlpha());
			//player2->render(gPlayer2Texture);
			player2->render(gPlayer2Texture);
		}
		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {								// 2017/01/25 If the type of virus is an Orange Exploding Virus
				// Start the timer
				if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50)
					listOfGameObjects[index]->setTimer(VIRUS_TIMER);	// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
				else{
					// Start counting down
					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {				// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());							// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);		// Decrement the timer
					}
				}

				// Draw the healthbar
				bar.virusTimer(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer());

				// Explode!!!
				if (listOfGameObjects[index]->getTimer() <= 0) {
					spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_FIREBALL);	// x, y, and type
					listOfGameObjects[index]->setAlive(false);																// When timer runs out kill the virus
				}
			}

			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {									// 2017/01/25 If the type of virus is an Orange Exploding Virus
				// Start the timer
				if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50) {
					listOfGameObjects[index]->setTimer(VIRUS_TIMER);									// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
				}
				else{
					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {			// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());						// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);	// Decrement the timer
					}
				}

				// Draw the healthbar
				bar.virusTimerBlue(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer());

				// Spawn the virus satellite object
				if (listOfGameObjects[index]->satelliteObjectOrbiting == false && listOfGameObjects[index]->getX() < SCREEN_WIDTH - 10) {
					spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLUE_VIRUS_BULLET, index);// x, y, and type
					listOfGameObjects[index]->satelliteObjectOrbiting = true;
				}

				// Set the Virus Satellite center point
				for (unsigned int index1 = 0; index1 != listOfGameObjects.size(); ++index1) {
					if (listOfGameObjects[index1]->getSubType() == BLUE_VIRUS_BULLET) {

						// Timer For Blue Virus!!!
						if (listOfGameObjects[index]->getTimer() < 0) {
							//listOfGameObjects[index]->setAlive(false);				// When timer runs out kill the virus

							listOfGameObjects[index]->setTimer(VIRUS_TIMER);			// Reset the timer
							// spawn another object
							spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLUE_VIRUS_BULLET, index);// x, y, and type
							listOfGameObjects[index]->satelliteObjectOrbiting = true;	// Reset satellite orbiting

							// Fire satellite object when timer runs out
							listOfGameObjects[index]->satelliteObjectOrbiting = false;	// Reset satellite orbiting
							listOfGameObjects[index1]->setProjectileActive(true);		// Set the SATELLITE to firing
						}


						// If it's a blue virus bullet and the virus it is attached to is alive
						//if (index == listOfGameObjects[index1]->whichVirusAssignedTo && listOfGameObjects[index]->getAlive()) { // Spawn if alive

						// If it's a blue virus bullet and the virus it's attached to has a timer above 0

						if (index == listOfGameObjects[index1]->whichVirusAssignedTo			// currently assigned virus
							&& listOfGameObjects[index]->getTimer() > 0							// timer > 0
							&& listOfGameObjects[index1]->getProjectileActive() == false) {		// projectile active false
																								// Set the satellite to move around the blue virus
							listOfGameObjects[index1]->movement(listOfGameObjects[index]->getX() + (listOfGameObjects[index]->getHeight() / 2), listOfGameObjects[index]->getY() + (listOfGameObjects[index]->getWidth() / 2), listOfGameObjects[index]->getTimer());	// Set center point when moving
						}
						else if (index == listOfGameObjects[index1]->whichVirusAssignedTo
							&& listOfGameObjects[index]->getTimer() < 0
							&& listOfGameObjects[index1]->getProjectileActive() == true){

							listOfGameObjects[index1]->movement();								// Projectile movement
						}
					}
				}
			}
		}

		// User Interface / Player Information Panel

		SDL_RenderSetViewport(getRenderer(), &UIViewport);

		headsUpDisplay.playerScore(twoPlayer, player1Score, player2Score);
		headsUpDisplay.percentageNinjaStarKills(twoPlayer, ninjaStarP1Counter, ninjaStarP2Counter);
		headsUpDisplay.playerScoresCounter(twoPlayer, scoreTextP1counter, scoreTextP2counter);

		// 2017/02/22 Add check for player being alive
		if (twoPlayer && player1->getAlive() && player2->getAlive())
			headsUpDisplay.rendPlayerLives(player1->getNumLives(), player2->getNumLives());
		else if (player1->getAlive() == false && player2->getAlive())
			headsUpDisplay.rendPlayerLives(0, player2->getNumLives());
		else if (player1->getAlive() && (player2->getAlive() == false && !twoPlayer))
			headsUpDisplay.rendPlayerLives(player1->getNumLives());

		if (player1->getAlive())
			headsUpDisplay.rendPlayerLives(player1->getNumLives());

		headsUpDisplay.createdByText();

		/* Professor Mini Map */
		/* Weapon Scrolling will work of trigger buttons, press left and right to select main weapon */
		SDL_RenderSetViewport(getRenderer(), &mapViewport);									// UIViewport	// SDL_RenderSetViewport(getRenderer(), &gameViewport);  // UIViewport
		if (!levelOver) gProfessorMapTexture.renderMap();

		SDL_RenderSetViewport(getRenderer(), &weaponViewport1);								// UIViewport
		//if (player1->getLaserGrade() == LASER_SINGLE) gPowerUpLaserTexture.render(weaponScrolling, 5);			// 1st
		if (player1->getLaserGrade() == LASER_SINGLE) Texture::Instance()->weaponIndicator("laserPowerUpID", weaponScrolling);
		//else if (player1->getLaserGrade() == LASER_TRIPLE) gPowerUpLaserTextureV2.render(weaponScrolling, 5);	// 1st //weaponScrolling = 60;
		else if (player1->getLaserGrade() == LASER_TRIPLE) Texture::Instance()->weaponIndicator("laserV2PowerUpID", weaponScrolling);

		SDL_RenderSetViewport(getRenderer(), &rocketViewport1);								// UIViewport

		if (player1->getAlive()) {
			headsUpDisplay.rocketIndicator(player1->getNumRockets(), player1->getAlive(), PLAYER_1);	// Number of rockets for Player 1
		}
		else headsUpDisplay.rocketIndicator(0, false, PLAYER_1);

		SDL_RenderSetViewport(getRenderer(), &boostViewport1);								// UIViewport
		if (player1->getAlive()) headsUpDisplay.speedBoostIndicator(player1->getSpeedBoost());	// 2017/02/22 Added check to make sure player is alive
		else headsUpDisplay.speedBoostIndicator(false);

		bar.speedBoostBar(player1->boostTimer());

		SDL_RenderSetViewport(getRenderer(), &weaponViewport2);  // UIViewport
		//if (twoPlayer && player2->getLaserGrade() == LASER_SINGLE) gPowerUpLaserTexture.render(weaponScrolling, 5);			// 1st
		if (twoPlayer && player2->getLaserGrade() == LASER_SINGLE) Texture::Instance()->weaponIndicator("laserPowerUpID", weaponScrolling);
		else if (twoPlayer && player2->getLaserGrade() == LASER_DOUBLE) Texture::Instance()->weaponIndicator("laserPowerUpV2ID", weaponScrolling);
		else if (twoPlayer && player2->getLaserGrade() == LASER_TRIPLE) Texture::Instance()->weaponIndicator("laserPowerUpV3ID", weaponScrolling);

		SDL_RenderSetViewport(getRenderer(), &rocketViewport2);								// UIViewport

		if (twoPlayer && player2->getAlive()) {
			headsUpDisplay.rocketIndicator(player2->getNumRockets(), player2->getAlive(), PLAYER_2);				// Number of rockets for Player 1
		}
		else if (twoPlayer && player2->getAlive() == false )
			headsUpDisplay.rocketIndicator(0, false, PLAYER_2);


		SDL_RenderSetViewport(getRenderer(), &boostViewport2);
		if (twoPlayer && player2->getAlive()) headsUpDisplay.speedBoostIndicator(player2->getSpeedBoost());
		else if (twoPlayer && player2->getAlive() == false) headsUpDisplay.speedBoostIndicator(false);

		if (twoPlayer) bar.speedBoostBar(player2->boostTimer(), START_RIGHT);

		SDL_RenderSetViewport(getRenderer(), NULL);											// Reset Viewport

		if(player1->getAlive())
		SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);								// Set Colour for squares around viewports to green
		else if(twoPlayer && player1->getAlive() == false)
			SDL_SetRenderDrawColor(getRenderer(), 125, 125, 125, 255);
		SDL_RenderDrawRect(getRenderer(), &weaponViewport1);								// Draw squares around the viewports
		SDL_RenderDrawRect(getRenderer(), &rocketViewport1);
		SDL_RenderDrawRect(getRenderer(), &boostViewport1);

		if(!twoPlayer || player2->getAlive() == false)
			SDL_SetRenderDrawColor(getRenderer(), 125, 125, 125, 255);
		SDL_RenderDrawRect(getRenderer(), &weaponViewport2);
		SDL_RenderDrawRect(getRenderer(), &rocketViewport2);
		SDL_RenderDrawRect(getRenderer(), &boostViewport2);
	}
	else if (levelOver == true) {
		SDL_RenderSetViewport(getRenderer(), NULL);											// UIViewport   gameViewport

		splash.endOfGame(getCurrentLevel(), finalScores);

		resetGame(getCurrentLevel() + 1);
		if (getCurrentLevel() >	MAX_NUM_LEVELS) gameOver = true;
	}
	else if (gameOver == true) {
		SDL_RenderSetViewport(getRenderer(), NULL);  // UIViewport   gameViewport
		splash.endOfGame(getCurrentLevel(), finalScores, gameWinners);
	}

	SDL_RenderPresent(getRenderer());					// Update screen
}

// 2017/02/22 Check player is alive
void Game::displayScoreForObject(int Xcoord, int Ycoord, int score, int player) {
	if (player == PLAYER_1 && player1->getAlive()) {
		GameObject* p_PointsValue = new ScoreValueText(Xcoord, Ycoord, score, player);
		//p_PointsValue->setSubType(PLAYER1_SCORE);
		scoreTextP1counter++;
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 240, 210, 65, 255 }, gFontRetro20)) {	// Gold Text
			printf("Unable to render player text texture!\n");
		}
		listOfGameObjects.push_back(p_PointsValue);
	}
	else if (player == PLAYER_2 && player2->getAlive()) {
		GameObject* p_PointsValue = new ScoreValueText(Xcoord, Ycoord, score, player);
		//p_PointsValue->setSubType(PLAYER2_SCORE);
		scoreTextP2counter++;
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 0, 0, 255, 255 }, gFontRetro20)) {		// Blue Text
			printf("Unable to render player text texture!\n");
		}
		listOfGameObjects.push_back(p_PointsValue);
	}
}

void Game::moveGameObjects() {
	if (player1->getAlive()) player1->movement();											// Update ship movement
	if (player2->getAlive()) player2->movement();

	// Cycle through list of Game Objects and move them, Player scores, and Power Ups so far
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getSubType() == PLAYER1_SCORE) {
			listOfGameObjects[index]->movement(player1->getX(), player1->getY());			// Move the score to Player 1 ship
		}
		else if (listOfGameObjects[index]->getSubType() == SAW1) {							// Move Player 1 saw
			listOfGameObjects[index]->movement(player1->getX(), player1->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == PLAYER2_SCORE) {					// Move the score to Player 2 ship
				listOfGameObjects[index]->movement(player2->getX(), player2->getY());
			}
		else if (listOfGameObjects[index]->getSubType() == SAW2) {							// Move Player 2 saw
			listOfGameObjects[index]->movement(player2->getX(), player2->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {					// Move Enemy ships + Fire enemy lasers
			listOfGameObjects[index]->movement();
			spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), ENEMY_SHIP_LASER);
		}
		else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {	// Move Enemy Virus, tracking the player movement
			if (listOfGameObjects[index]->getX() > SCREEN_WIDTH && listOfGameObjects[index]->getX() < SCREEN_WIDTH + 10) {	// When a virus is within 10 pixels of appearing on screen
					infoMessage(listOfGameObjects[index]->getName() + " Approaching");	// 2017/02/19 Added information message indicates virus is approaching
			}
			if (player2->getAlive() && (abs(player1->getX() - listOfGameObjects[index]->getX()) * abs(player1->getX() - listOfGameObjects[index]->getX())) +	// Distance on X axis between player 1 and virus squared
				(abs(player1->getY() - listOfGameObjects[index]->getY()) * abs(player1->getY() - listOfGameObjects[index]->getY())) >			// Distance on Y axis between player 1 and virus squared
				(abs(player2->getX() - listOfGameObjects[index]->getX()) * abs(abs(player2->getX() - listOfGameObjects[index]->getX())) + 		// Distance on X axis between player 2 and virus squared
				(abs(player2->getY() - listOfGameObjects[index]->getY()) * abs(abs(player2->getY() - listOfGameObjects[index]->getY())))))		// Distance on Y axis between player 2 and virus squared
			{
				listOfGameObjects[index]->movement(player2->getX(), player2->getY());
			}
			else {
				listOfGameObjects[index]->movement(player1->getX(), player1->getY());
			}
		}
		else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL && activeEnemyVirusSmall > 0) {
			//infoMessage("Number of small blue viruses: " + std::to_string(activeEnemyVirusSmall));

			int nearestSmallBlueVirus = 1280 * 1280 + 600 * 600;	// Furthest distance objects can be apart on screen

			// The White blood cell can attack smaller sized virus objects
			for (unsigned int smallVirusIndex = 0; smallVirusIndex != listOfGameObjects.size(); ++smallVirusIndex) {
				if (listOfGameObjects[smallVirusIndex]->getType() == SMALL_VIRUS) {
					if (abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) * abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) +
						abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) * abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) < nearestSmallBlueVirus)
						nearestSmallBlueVirus = abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) * abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) +
						abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) * abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) < nearestSmallBlueVirus;

					listOfGameObjects[index]->movement(listOfGameObjects[smallVirusIndex]->getX(), listOfGameObjects[smallVirusIndex]->getY());	// move towards nearest small virus
				}
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
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getX() <= 200 - listOfGameObjects[index]->getWidth()) {
			listOfGameObjects[index]->setAlive(false);
		}
	}

	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {	// Erase Game Objects
		if ((listOfGameObjects[index]->getSubType() == PLAYER1_SCORE)) {
			if (SDL_GetTicks() > listOfGameObjects[index]->getTimerTracker() + 2500) listOfGameObjects[index]->setAlive(false); // if the current time is more than the start time + 100
			if (listOfGameObjects[index]->getAlive() == false) scoreTextP1counter--;											// Decrement the player 1 score text counter
		}
		else if ((listOfGameObjects[index]->getSubType() == PLAYER2_SCORE)) {
			if (SDL_GetTicks() > listOfGameObjects[index]->getTimerTracker() + 2500) listOfGameObjects[index]->setAlive(false); // if the current time is more than the start time + 100
			if (listOfGameObjects[index]->getAlive() == false) scoreTextP2counter--;											// Decrement the player 2 score text counter
		}

		if (!listOfGameObjects[index]->getAlive()) {
			// Decrement the number active on screen
			if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) {
				activeBloodCells--;																						// Decrement active blood cells when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLOOD_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL) activeSmallBloodCells--;				// Decrement active small blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL) activeWhiteBloodCells--;				// Decrement active white blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				activeEnemyShips--;																						// Decrement active enemy ships when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), EXPLOSION);			// Expode Player Weapon when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
				activeEnemyVirus--;																						// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), GREEN_VIRUS_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
				activeEnemyVirus--;																						// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), ORANGE_VIRUS_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				activeEnemyVirus--;																						// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), BLUE_VIRUS_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P1) {
				player1->setProjectileActive(false);
				if (player1->getKillRocket()) listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P2) {
				player2->setProjectileActive(false);
				if (player2->getKillRocket()) listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getType() == SMALL_VIRUS) activeEnemyVirusSmall--;
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P1) {
				ninjaStarP1Missed++;
				ninjaStarP1Counter--;
			}
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P2) {
				ninjaStarP2Missed++;
				ninjaStarP2Counter--;
			}

			// Erase The Object From The List
			if (!listOfGameObjects[index]->getAlive()) {
				std::cout << "kill " << listOfGameObjects[index]->getName() << std::endl;
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
		spawnBloodCell(LARGE_BLOOD_CELL);					// Spawn a large blood cell
	}

	if (activeSmallBloodCells < SPAWN_NUM_BLOOD_CELL_S) {
		activeSmallBloodCells++;							// increment Small blood cell counter
		spawnBloodCell(SMALL_BLOOD_CELL);					// Spawn a small blood cell
	}
	if(activeWhiteBloodCells < SPAWN_NUM_BLOOD_CELL_WHITE){
		activeWhiteBloodCells++;							// increment white blood cell counter
		spawnBloodCell(WHITE_BLOOD_CELL);					// spawn a white blood cell
	}

	activePowerUps = 0;		// Number of active onscreen Power Ups
	activeEnemyShips = 0;	// Number of active onscreen Enemy Ships
	activeEnemyVirus = 0;	// Number of active onscreen Enemy Virus

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
		gPlayer1Texture.flashGameObject(10, 4);							// 2017/01/30 Moved flashGameObject() function into LTexture
	}
	else if (player == PLAYER_2) {
		player2->spawn(0, (randomYCoord * 58) + 50);
		if (player2->getY() == player1->getY()) spawnPlayer(2);			// 2017/01/20: Spawn Player 2 at random Y coord + different to Player 1
		player2->setAlive(true);
		gPlayer2Texture.setFlash(true);
		gPlayer2Texture.flashGameObject(10, 4);
		//std::cout << "player1.getY() " << player1.getY() << " player2.getY() " << player2.getY() << std::endl;
	}
}

// List of enemy ships to spawn at random times and positions
void Game::spawnEnemyShip() {
	int x, y, randomSpeed;

	GameObject* p_Enemy = new EnemyShip();
	spawnRandom(x, y, randomSpeed, 50, p_Enemy->getHeight(), 1);
	p_Enemy->spawn(x, y, -randomSpeed, p_Enemy->getCollider());
	listOfGameObjects.push_back(p_Enemy);
}
void Game::spawnEnemyVirus(int x, int y, int subType) {
	int smallX = x, smallY = y, randomSpeed;
	spawnRandom(x, y, randomSpeed, 150);

	// Spawn the small virus at a random position close to the original virus position
	if (subType == VIRUS_SMALL_GREEN || subType == VIRUS_SMALL_ORANGE || subType == VIRUS_SMALL_BLUE) {
		int randomX = rand() % 60 + smallX - 15;	// Somewhere between - 15 and 45 of original position
		int randomY = rand() % 60 + smallY - 15;
		int randomSpeed = rand() % 4 + 1;

		GameObject* p_SmallVirus = new EnemyVirus(subType);
		p_SmallVirus->spawn(randomX, randomY, -randomSpeed, -1, p_SmallVirus->getCollider(), subType);
		p_SmallVirus->setType(SMALL_VIRUS);
		p_SmallVirus->setColliderHeight(40);
		p_SmallVirus->setColliderWidth(40);
		listOfGameObjects.push_back(p_SmallVirus);
	}
	else {
		int randomExplodingVirus = rand() % 4 + 1;								// 1 in 4 chance of Orange Exploding Virus
		//randomExplodingVirus = 2; // Test blue virus
		if (randomExplodingVirus == 1) subType = VIRUS_ORANGE;
		else if (randomExplodingVirus == 2) subType = VIRUS_BLUE;
		else subType = VIRUS_GREEN;

		GameObject* p_Virus = new EnemyVirus(subType, 3.0);		// Orange type = 1
		p_Virus->setTimer(VIRUS_TIMER);
		p_Virus->spawn(x, y, -randomSpeed, -randomSpeed, p_Virus->getCollider(), subType);
		listOfGameObjects.push_back(p_Virus);
		//std::cout << "distance to virus p1: " << abs(((player1.getX() * player1.getX()) + (player1.getY() * player1.getY()))) << " p2: " << abs((player2.getX() * player2.getX()) + (player2.getY() * player2.getY())) << std::endl;
	}
}
void Game::spawnBloodCell(int subType) {
	int x, y, randomSpeed;
	GameObject* p_BloodCell = new BloodCell(subType);

	spawnRandom(x, y, randomSpeed, 200, p_BloodCell->getHeight());
	//p_BloodCell->spawn(x, y, -randomSpeed, p_BloodCell->getDistanceBetween());	// 2017/01/24 Added Y padding to keep objects within the game screen boundary
	p_BloodCell->spawn(x, y, -randomSpeed);											// 2017/01/24 Added Y padding to keep objects within the game screen boundary
	listOfGameObjects.push_back(p_BloodCell);

	bloodCellCounterP1++;
}
void Game::spawnPowerUp() {
	int x, y, randomSpeed, powerUpType = 0;
	int randomPowerup = rand() % 5 + 1;												// Number between 1 and 4
	//randomPowerup = 4;

	if (countdownTimer <= 10) {
		powerUpType = POWER_UP_CHECKPOINT;											// if the timer is less than or equal 10, spawn the Checkpoint power up
	}
	else {
		if (randomPowerup == 1) powerUpType = POWER_UP_HEALTH;
		else if (randomPowerup == 2) powerUpType = POWER_UP_LASER;
		else if (randomPowerup == 3) powerUpType = POWER_UP_ROCKET;
		else if (randomPowerup == 4) powerUpType = POWER_UP_LIVES;
	}

	GameObject* p_PowerUp = new PowerUp(powerUpType, 50);						// Type and score
	spawnRandom(x, y, randomSpeed, 200, p_PowerUp->getHeight());				// Spawn with random X and Y coord, and speed between 1 and 3
	p_PowerUp->spawn(x, y, -randomSpeed);										// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	listOfGameObjects.push_back(p_PowerUp);
}

void Game::spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier, int yPadding, int speed) {	// 2017-01-20 Separate out common randomness of game object spawning
	int randomX = rand() % 5 + 1;
	int randomY = rand() % 8 + 1;												// A number between 1 and 8
	randomSpeed = rand() % 4 + speed;

	x = SCREEN_WIDTH + (randomX * xMuliplier);
	y = 40 + (randomY * ((SCREEN_HEIGHT_GAME - yPadding - 80) / 8));			// 40 top and bottom, yPadding, object height
}

// Spawn Weapon at ships location
void Game::spawnExplosion(int x, int y, int subType) {
	GameObject* p_Explosion = new Explosion(x, y, subType);		// Create an explosion at x and y, with given type
	p_Explosion->spawn(x, y - 30);								// Spawn the explosion at the given x & y coords
	listOfGameObjects.push_back(p_Explosion);					// Add explosion to list of game objects

	if (subType == EXPLOSION) Audio::Instance()->explosionFX();				// Play explosion sound effectmusicBackSongName
}

void Game::spawnLaser(int x, int y, int player, int grade, int velocity) {

	std::cout << "Laser Grade: " << grade << std::endl;

	GameObject* p_Laser1 = new WeaponPlLaser(player);

	if (player == PLAYER_1) {
		p_Laser1->spawn(x + 65, y + 25, velocity, PLAYER_1, LASER_P1);	// Spawn laser at front of ship, with set veloicty, for player 1, setting sub-type of laser
		grade = player1->getLaserGrade();								// Decide if it is a single laser, or triple laser beam
	}
	else if (player == PLAYER_2) {
		p_Laser1->spawn(x + 65, y + 25, velocity, PLAYER_2, LASER_P2);
		grade = player2->getLaserGrade();
	}

	if (grade == LASER_DOUBLE) {
		p_Laser1->setAngle(LASER2_TOP);

		GameObject* p_Laser2 = new WeaponPlLaser(player, LASER2_BOTTOM, LASER_DOUBLE);

		if (player == PLAYER_1) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_1, LASER_P1);
		}
		else if (player == PLAYER_2) {
			p_Laser2->spawn(x + 65, y + 30, velocity, PLAYER_2, LASER_P2);
		}

		listOfGameObjects.push_back(p_Laser2);
	}

	listOfGameObjects.push_back(p_Laser1);

	if (grade == LASER_TRIPLE) {		// FIRE 2 MORE LASERS AT ANGLES
		GameObject* p_Laser2 = new WeaponPlLaser(player, LASER3_TOP, LASER_TRIPLE);	// Angled laser
		GameObject* p_Laser3 = new WeaponPlLaser(player, LASER3_BOTTOM, LASER_TRIPLE);

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
		if (player == 1) Audio::Instance()->laserFX_P1();
		else if (player == 2) Audio::Instance()->laserFX_P2();
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

			Audio::Instance()->laserFX_Enemy();
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

			listOfGameObjects.push_back(p_Laser);						// Add the Enemy Lasers to a list to move and render
		}
	}
	else if (type == BLUE_VIRUS_BULLET) {
		GameObject* p_Laser = new WeaponEnLaser(BLUE_VIRUS_BULLET);
		p_Laser->spawn(xCoord, yCoord, -10);							// Spawn the laser from the Virus Coordinates
		p_Laser->whichVirusAssignedTo = whichVirus;

		listOfGameObjects.push_back(p_Laser);							// Add the Enemy Lasers to a list to move and render
	}
}
void Game::spawnNinjaStar(int x, int y, int player) {					// player to spawn for and their coords
	//std::cout << "Ninja Star Spawned " << player << "p1 " << PLAYER_1 << " p2 " << PLAYER_2 << std::endl;
	GameObject* p_NinjaStar = new WeaponPlNinjaStar(player);
	p_NinjaStar->spawn(x + 65, y + 25, 10);								// Spawn the weapon at the x & y coords given, with a velocity of 10

	listOfGameObjects.push_back(p_NinjaStar);							// Add to game objects list
	if (!gameOver) {
		if (player == PLAYER_1) {
			ninjaStarP1Counter++;
			Audio::Instance()->ninjaFX_P1();										// Play a different sound effect depending on the player
		}
		else if (player == PLAYER_2) {
			ninjaStarP2Counter++;
			Audio::Instance()->ninjaFX_P2();
		}
	}
}
void Game::spawnRocket(int x, int y, int player, int type, bool launch) {
	if (launch == false && player == PLAYER_1 && player1->getNumRockets() > 0) player1->setRocketBarActive(true);			// if not ready to fire, player is player 1, and player 1 has rockets
	else if (twoPlayer && launch == false && player == PLAYER_2 && player2->getNumRockets() > 0) player2->setRocketBarActive(true);
	else {
		bool createRocket = false;

		if (player == PLAYER_1 && !player1->getProjectileActive() && player1->getNumRockets() > 0) {
			createRocket = player1->initialiseRocket();						// 2017/02/19 initialise the rocket, then create and launch the rocket after returning true from function
		}
		else if (player == PLAYER_2 && !player2->getProjectileActive() && player2->getNumRockets() > 0) {
			createRocket = player2->initialiseRocket();
		}
		if (createRocket) {
			GameObject* p_Rocket = new WeaponPlRocket(player);				// Create a rocket
			p_Rocket->spawn(x, y, p_Rocket->getCollider(), player, type);	// spawn for the player

			//std::cout << "Rocket Spawned" << std::endl;
			listOfGameObjects.push_back(p_Rocket);							// Add rocket to game object list
		}
	}
}

void Game::spawnSaw(int x, int y, int subType) {		// player to spawn for and their coords, turn on if inacive, off if active	// 2017-02-08 Updated and working OK
	bool createSaw = false;								// Used to decide which player to create the saw for, so code doesn't need to be repeated

	// Check which player to create a saw for
	if (subType == SAW1 && !player1->getSawActive()) {
		createSaw =  player1->setSawActive(true);		// Show saw, set saw active function returns true value
	}
	else if (subType == SAW2 && !player2->getSawActive()) {
		createSaw =  player2->setSawActive(true);
	}
	if (createSaw) {
		GameObject* p_Saw = new WeaponPlSaw(subType);	// Create new saw
		p_Saw->spawn(x + 65, y + 25);					// Spawn the saw at the given x & y coords
		listOfGameObjects.push_back(p_Saw);				// Add the saw to the game object listg
		if (!gameOver) Audio::Instance()->sawFX();					// Play the sound effect for the saw starting
	}
	else if (!createSaw) {
		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			if (listOfGameObjects[index]->getSubType() == subType) {										// if saw is the right sub-type
				if (listOfGameObjects[index]->getAlive() == true) {											// if saw is active
					if (listOfGameObjects[index]->getSubType() == SAW1) player1->setSawActive(false);		// If the say is the right sub-type hide saw for Player 1
					else if (listOfGameObjects[index]->getSubType() == SAW2) player2->setSawActive(false);	// Hide saw for Player 2

					listOfGameObjects[index]->setAlive(false);
				}
			}
		}// end for
	}
}

/*
	2017/02/06 Added function to handle player scoring, setting the scores for Players 1 and 2
*/
void Game::managePlayerScores(int score, int player, int type) {				// add get name
	if (player == PLAYER_1) player1->setScore(player1->getScore() + score);
	else if (player == PLAYER_2) player2->setScore(player2->getScore() + score);

	if (type == PLAYER_WEAPON) std::cout << "Enemy Ship Killed by Player " << player << std::endl;
	else if (type == SAW1) std::cout << "Enemy Ship Killed by Player 1 Saw!\n";
	else if (twoPlayer && type == SAW2) std::cout << "Enemy Ship Killed by Player 2 Saw!\n";
}
void Game::managePlayerHealth(int player, int score, std::string name) {
	if (player == PLAYER_1) {
		gPlayer1Texture.setFlash(true);								// Flash on collision with Game Object
		player1->setHealth(player1->getHealth() - score);

		if (player1->getNumLives() <= 0) {							// if the number of lives 0 or less
			player1->setSawActive(false);							// kill the active saw
			player1->setAlive(false);								// kill the player
		}
		//else if (player1->getHealth() <= 0 && player1->getAlive()) {	// if player health is 0 or less AND player is alive
		else if (player1->getHealth() <= 0) {	// if player health is 0 or less AND player is alive
			player1->setNumLives(player1->getNumLives() - 1);
			if (player1->getNumLives() > 0) {
				spawnPlayer(PLAYER_1);
				player1->setHealth(100);
			}
		}
	}
	else if (twoPlayer && player == PLAYER_2) {
		gPlayer2Texture.setFlash(true);								// Flash on collision with Game Object
		player2->setHealth(player2->getHealth() - score);

		if (player2->getNumLives() <= 0) {
			player2->setSawActive(false);
			player2->setAlive(false);
		}
		//else if (player2->getHealth() <= 0 && player2->getAlive()) {
		else if (player2->getHealth() <= 0) {
			player2->setNumLives(player2->getNumLives() - 1);
			if (player2->getNumLives() > 0) {
				spawnPlayer(PLAYER_2);
				player2->setHealth(100);
			}
		}
		if (SDL_NumJoysticks() > 0) {
			if (player2->getAlive() && SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds 2017/01/20 Moved to player 2, was rumbling for both players
				printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
			}
		}
	}

	if (score > 0) {
		Audio::Instance()->explosionFX();
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

// Reset a level or the game
void Game::resetGame(int currentLevel) {
	frames = 0;					// Animation Frames

	//gLevel.free();

	// Reset the map of the professor
	setViewport(mapViewport, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// Reset the map to small size
	gProfessorMapTexture.modifyAlpha(255);								// Reset the alpha value for the map texture

	std::string finalScores = "";										// Reset the final scores message
	std::string gameWinners = "";										// Reset the game winner message

	setCurrentLevel(currentLevel);										// Set the current level
	//gLevel.loadFromRenderedText("Level " + std::to_string(getCurrentLevel()), { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	//gLevel.loadFromRenderedTextID("Level " + std::to_string(getCurrentLevel()), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	Texture::Instance()->loadFromRenderedTextID("Level " + std::to_string(getCurrentLevel()), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	// Reset the number of objects on screen
	activeBloodCells = 0;
	activeWhiteBloodCells = 0;
	activeSmallBloodCells = 0;
	activePowerUps = 0;
	activeEnemyShips = 0;
	activeEnemyVirusSmall = 0;

	//if (currentLevel == MENU)
		displayGameIntro = DISPLAY_GAME_INTRO_SCREENS;
	//displayLevelIntro = DISPLAY_LEVEL_INTRO_SCREENS;
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
	gTimeTextTexture.setFlash(false);		// Reset the timer flash
	headsUpDisplay.resetHUD();

	// Reset Players
	if (currentLevel <= 1) {				// If the level isn't progressing
		player1->setScore(0);				// Reset player 1 score
		player1->setNumLives(MAX_NUM_LIVES);
		nameEntered = false;
	}

	player1->setSawActive(false);
	player1->setSpeedBoost(false);
	player1->setAlive(false);
	player1->setHealth(player1->getMaxHealth());
	player1->setVelX(0);
	player1->setVelY(0);
	player1->setTimer(ROCKET_TIMER);

	if (twoPlayer) {
		if (currentLevel <= 1) {
			player2->setScore(0);				// Reset player 2 score
			player2->setNumLives(MAX_NUM_LIVES);
		}
		gPlayer2Texture.setFlash(false);

		player2->setSawActive(false);
		player2->setSpeedBoost(false);

		player2->setAlive(false);
		player2->setHealth(player2->getMaxHealth());

		player2->setVelX(0);
		player2->setVelY(0);
		player2->setTimer(ROCKET_TIMER);
	}

	// Delete all objects on screen
	if (gameOver || levelOver) {
		listOfGameObjects.clear();		// Scores, Power Ups, Explosions
		//listOfScoreTextures.clear();
	}

	levelOver = false;
	gameOver = false;
}

void Game::collisionCheck() {
	// Check if Player 1 or 2 has collided with another game object
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (checkCollision(player1->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());

			// Power Ups
			if (listOfGameObjects[index]->getType() == POWER_UP) {
				if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
					managePlayerHealth(PLAYER_1, -listOfGameObjects[index]->getDamage());
					infoMessage("Player 1 has increased their health!!!", PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
					player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());
					player1->setLaserGrade(player1->getLaserGrade() + 1);
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
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) {
					player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());
					if (player1->getNumLives() < MAX_NUM_LIVES) {
						player1->setNumLives(player1->getNumLives() + 1);
						infoMessage("Player 1 has increased their number of lives!!!", PLAYER_1);
					}
					else
						infoMessage("Player 1 has already has the max number of lives!!!", PLAYER_1);
				}

				listOfGameObjects[index]->setAlive(false);
			}
			// Enemies
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage());															// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player1->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				//if (player1->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
				if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_GREEN);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_GREEN);
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				//else if (player1->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_ORANGE);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_ORANGE);
					listOfGameObjects[index]->setTimer(0);
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_BLUE);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_BLUE);
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 3, "Enemy Virus");	// If player 1 isn't flashing, Take off 5 health
			}

			// Make sure the player isn't colliding with it's own weapon or a blood cell
			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON && listOfGameObjects[index]->getType() != BLOOD_CELL)
				listOfGameObjects[index]->setAlive(false);	// If it's not a collision between a player and a player weapon or a blood cell

			if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL && player1->getSawActive())
				listOfGameObjects[index]->setAlive(false);	// If the players saw is active and it collides with a large blood cell, the blood cell is destroyed
		}
		else if (twoPlayer && checkCollision(player2->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());

			if (listOfGameObjects[index]->getType() == POWER_UP) {
				if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
					managePlayerHealth(PLAYER_2, -listOfGameObjects[index]->getDamage());
					infoMessageP2Counter = 0;
					infoMessage("Player 2 has increased their health!!!", PLAYER_2);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
					player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
					player2->setLaserGrade(player2->getLaserGrade() + 1);
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
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) {
					player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
					if (player2->getNumLives() < MAX_NUM_LIVES) {
						player2->setNumLives(player2->getNumLives() + 1);
						infoMessage("Player 2 has increased their number of lives!!!", PLAYER_2);
					}
					else
						infoMessage("Player 2 has already has the max number of lives!!!", PLAYER_2);
				}

				listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage());	// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player2->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_GREEN);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_GREEN);
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				//else if (player1->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				else if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_ORANGE);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_ORANGE);
					listOfGameObjects[index]->setTimer(0);
				}
				else if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_BLUE);
					spawnEnemyVirus(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_SMALL_BLUE);
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage() / 3, "Enemy Virus");	// If player 2 isn't flashing, Take off 5 health
			}

			if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL && player2->getSawActive())	// If the player collides with a large blood cell and the player saw is active
				listOfGameObjects[index]->setAlive(false);

			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON && listOfGameObjects[index]->getType() != BLOOD_CELL)
				listOfGameObjects[index]->setAlive(false);
		}
	}

	// Check Weapons Sub-Type For Collisions With Enemy Sub-Type
	for (unsigned int weaponIndex = 0; weaponIndex != listOfGameObjects.size(); weaponIndex++) {
		for (unsigned int enemyIndex = 0; enemyIndex != listOfGameObjects.size(); enemyIndex++) {
			// If a white blood cell collides with a small virus, the small virus is destroyed
			if (listOfGameObjects[weaponIndex]->getSubType() == WHITE_BLOOD_CELL && listOfGameObjects[enemyIndex]->getType() == SMALL_VIRUS) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					listOfGameObjects[enemyIndex]->setAlive(false);	// Destroy the small virus
																	//infoMessage("DESTROY BLUE VIRUS");
				}
			}

			// 2017/02/19 If there is a collison between ninja stars and large blood cells
			if ((listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P1 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P2) && listOfGameObjects[enemyIndex]->getSubType() == LARGE_BLOOD_CELL) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					listOfGameObjects[enemyIndex]->setAlive(false);
					listOfGameObjects[weaponIndex]->setAlive(false);	// DESTROY
				}
			}

			if (listOfGameObjects[weaponIndex]->getType() == PLAYER_WEAPON && listOfGameObjects[enemyIndex]->getType() == ENEMY_OBJECT) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					// 2017/02/22 Updated messages to include name
					if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P1) {
						infoMessage("Impact!!! Missile has taken out " + listOfGameObjects[enemyIndex]->getName() + "! Score +" + std::to_string(player1->getBonusScore()), PLAYER_1);
						managePlayerScores(player1->getBonusScore(), PLAYER_1, listOfGameObjects[weaponIndex]->getSubType());
					}
					else if (twoPlayer && listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P2) {
						infoMessage("Impact!!! Missile has taken out" + listOfGameObjects[enemyIndex]->getName() + "! Score +" + std::to_string(player2->getBonusScore()), PLAYER_2);
						managePlayerScores(player2->getBonusScore(), PLAYER_2, listOfGameObjects[weaponIndex]->getSubType());
					}
					// If a virus is cut in half, spawn 2 smaller virus
					else if (listOfGameObjects[weaponIndex]->getSubType() == SAW1 || listOfGameObjects[weaponIndex]->getSubType() == SAW2 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P1 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P2) {

						if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_GREEN) {
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_GREEN);
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_GREEN);
							activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
						}
						else if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_ORANGE) {
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_ORANGE);
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_ORANGE);
							activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
						}
						else if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_BLUE) {
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_BLUE);
							spawnEnemyVirus(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), VIRUS_SMALL_BLUE);
							activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
						}
					}

					managePlayerScores(listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getPlayer(), listOfGameObjects[weaponIndex]->getSubType());		// 2017-02-06 Add to players score

					pointsValueCounter = 0;
					displayScoreForObject(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getPlayer());	// Display Score

					listOfGameObjects[enemyIndex]->setAlive(false);
					listOfGameObjects[weaponIndex]->setAlive(false);	// DESTROY
				}
			}
		}
	}
}

/*
	2017/03/22 Moved animations for Explosions to the Explosion class
				Added alpha value to Game Object class
				Added separate render function for animations using a Texture ID to Game Object class
				Removed degrees from Texture constructor as this is now handled from within the class of each rotating object
				Seperate function added for Virus to decide which Player to move towards
				Players and Scrolling Background added to Game Object list
	2017/03/21 Added ScrollingBackground class to handle background scrolling and rendering
	2017/03/20 Moved additional render functionality from Game class
				Fixed memory leak after moving level number rendering to HUD class
	2017/03/19 Added ship start and end point positions to mini map
				Added separate function to count timers for how long messages appear on screen, checkMessageTimes()
	2017/03/18 Added the Ninja Stars and Saw texture to the texture map in Texture class
				Ninja Star and Saw rotations are updated in the move() function in their own Classes instead of setRotatingAngle() in Game class
				Added checks to make sure objects are being delted
				Fixed Saws not being deleted from game object list
				Cut 2 mb/sec memory leak by loading createdByTextTexture text in 3 separate textures only once in the game in Texture class
				Added new Boss Enemy with lasers spawning from eyes, and Virus spawning from mouth in level 1
				Boss has random movement
	2017/03/17 Combined music loading with effects loading, as only one function is necessary
				Added array for music information including path, id, and error message to display
				Changed playMusic() to playPauseMusic() and changed type to void from int as identifyTrack() is now in Audio class not Game
				Moved play / pause functionality to playMusic() function in Audio class
				Changed musicForwardSongName() and musicBackSongName() type to void from int, as tracks are identified with identifyTrack() in Audio and not Game class
				Moved enemy laser spawning from Game class to Enemy Ship move function
				Created a unique render function for Blood Cells that uses the stored texture ID to load the texture image
				it also rotates the blood cells in a random direction
	2017/03/13 Added full screen toggle setting by pressing F11 and in settings menu
				Tidied up the pause menu, so it can only be accessed from within the game
				Added bubble image to represent player shield shieldP1ID, shieldP2ID
				Added splash effect for destroying blood cells and rip effect for Virus enemies ripping in 2
				Added sound fx to a map
				Added effect for large blood cells being destroyed
				Added effect for Virus enemies ripping in 2
				Added seperate effects for players collecting power ups
	2017/03/08 Added full screen
	2017/03/07 Added additional original song Blood Level
	2017/03/06 Moved texture information to array for loading
	2017/03/04 Moved smaller class files functionality into their headers
				Set a game object texture ID variable, Player and Enemy lasers now render based on their unique texture ID
				Added a function to display a random message at the start of each level
	2017/03/03 Fixed memory leak in game, where text is rendered to a texture when it doesn't need to be
				Shortened some functions like player spawnlaser() function
				Started work on pause menu (press 'Esc')
				Changed movement for chasing objects to stalker movement (moveStalker())
				Only 1 spawn function is needed, the object constructors do the rest of the work
				FPS is now activated by holding the F1 key, to view the current FPS
	2017/03/02 Added abstract base class for game objects
				Added boss enemy, needs work on movement
				Changed movement() name to move()
				Pressing "Esc" now sets the currentLevel to 0 bringing us back to the menu
				Reset number of rockets at end of game, when resetting back to menu
	2017/03/01 Added double laser for player
				Press esc to return to main menu
				Fixed delete ninja stars - checking for type not subtype
				Fixed story formatting, adding bigger text to fill the screen space
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

#include "_TestData.h"				// JOE: 2017/02/09 Keeps testing functionality in one place
#include "Game.h"					// Game header file, with functions and variabls
#include <sstream>					// For timer
#include "EnemyShip.h"				// SEAN/JOE: Enemy ship class
#include "EnemyVirus.h"				// 2017/01/10 SEAN/JOE: Added virus enemy
#include "WeaponPlLaser.h"			// SEAN: Player Laser weapon
#include "WeaponPlNinjaStar.h"		// 2017/01/09 JOE: Player Ninja Star weapon
#include "WeaponPlRocket.h"			// 2017/02/06 JOE: Class for creating rockets
#include "WeaponPlSaw.h"			// 2017/01/17 JOE: Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell obstacle
#include "PowerUp.h"				// 2017/01/10 SEAN/JOE: Added Power Up
#include "Menu.h"					// 2017/02/14 BRIAN/JOE: Class for handling menus. Includes button.h
#include "Explosion.h"				// 2017/01/25 JOE: Added explosions for Player Laser colliding with Enemy Ships and Virus
//#include "FPS.h"					// 2017/02/01 SEAN/JOE: Class for handling frames for second
#include "SplashScreen.h"			// 2017/02/08 JOE: Class for displaying splash screens
#include "ScoreValueText.h"			// 2017-02-09 JOE: Class for displaying values of scores for destroying objects
//#include "StatusBar.h"				// 2017/02/09 JOE: Class for creating status bars, such as health bar
#include "CollisionStuff.h"			// 2017/02/09 JOE: Class for handling collisions between objects
#include "Gamepad.h"				// 2017/02/09 JOE: Class for handling gamepad functionality
#include "Audio.h"					// 2017/02/09 JOE: Class for handling music and sound effects
//#include "HUD.h"					// 2017/02/21 JOE: Class for handling displaying objects on heads up display
#include "EnemyBoss.h"				// 2017/02/03 JOE: Class for handling Enemy Boss objects
#include "GameStateMachine.h"		// 2017/02/03 JOE: Class for handling Game State Machine (Finite State Machine)
#include "StateMainMenu.h"			// 2017/02/03 JOE: Class for handling the main menu state
#include "Blockage.h"
#include "randomMessageGenerator.h"	// 2017/02/04 JOE: Class for randomising messages
#include "SettingsMenu.h"
#include "HighScores.h"
#include "EnterName.h"
//#include "ScrollingBackground.h"	// 2017/03/21 JOE: Class for scrolling background

Game* Game::s_pInstance = 0;
//GameStateMachine* m_pGameStateMachine;	// P109 Add GameStateMachine as a member of the Game class

// Game & Level Testing
bool quit = false;					// Main loop flag
bool testMode = true;				// Game is in testing

// Classes
Menu menu1;
//StatusBar bar;
SplashScreen splash;
//FPS fps1;							// 2017/02/01 Moved FPS functionality to it's own class
//Particle particle;
SettingsMenu settings;
HighScores highScore;
EnterName enterName1;

// Text
SDL_Color textColour;				// Set the text colour
TTF_Font *gFontRetro20;				// Globally used font 2017-01-25 Changed to Retro font which is more readable

bool Game::init() {
	// Add objects to Game Objects list
	//listOfGameObjects.push_back(player1);					// 2017/03/22 Add Player 1 to Game Objects list
	//if (twoPlayer) listOfGameObjects.push_back(player2);	// 2017/03/22 Add Player 2 to Game Objects list
	//listOfGameObjects.push_back(scrollBG);					// 2017/03/22 Add Scrolling Background to Game Objects list;

	//m_pGameStateMachine = new GameStateMachine();			// Create the state machine
	//m_pGameStateMachine->changeState(new StateMainMenu());	// Add a state
	nameEntered = false;

	//resetGame(getCurrentLevel());										// Initialise variables depending on level

	// View ports
	//setViewport(gameViewport, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// Main Game Screen

	// Game Console Title
	std::cout << "22//03/2017 - Antibody Final Version" << std::endl;

	//std::cout << player1->getName() << " Health: " << player1->getHealth() << " Lives: " << player1->getNumLives() << std::endl;		// Player 1 health & Lives at start of game
	//if (testMode) player1->setNumLives(MAX_NUM_LIVES);
	/*
	if (twoPlayer) {
		std::cout << "Player 2 Health: " << player2->getHealth() << " Lives: " << player2->getNumLives() << std::endl;					// Player 1 health & Lives at start of game
		//if (testMode) player2->setNumLives(MAX_NUM_LIVES);
	}
	*/
	bool success = true;						// Initialization flag

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0) {											// 2017/01/09 JOE: SOUND - Neet do initialise audio with video
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
		if (FULL_SCREEN)
			windowFlag = SDL_WINDOW_FULLSCREEN;
		else
			windowFlag = SDL_WINDOW_SHOWN;

		//gWindow = SDL_CreateWindow("Antibody", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);	/* Window name */
		//gWindow = SDL_CreateWindow("Antibody", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	/* Window name */
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
				SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);									// Initialize renderer color

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
	bool success = true;														// Loading success flag

	Texture::Instance()->loadTextureMedia();
	success = menu1.loadMenuMedia();											// Load buttons etc
	success = Audio::Instance()->loadMediaAudio();								// 2017/03/17 Combined music loading with effects loading, as only one function is necessary
	//success = headsUpDisplay.loadLevelStuff();									// 2017/02/21 Separated heads up display object initialisation to the class for loading textures for player lives etc
	//success = particle.initParticle();
	success = splash.initSplashScreens();										// Initialise the splash screens

	// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };																	// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);														// Use bold font
	}
	/*
	//gEnemyBossStatusBarTextTexture.loadFromRenderedText("The Gaddinator", { 100, 240, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	gEnemyBossStatusBarTextTexture.loadFromRenderedText("Lorctron", { 180, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	// Load Textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png")) {												// Player 1 Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.png")) {												// Player 2 Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gEnemyBossEyesSpriteSheetTexture.loadFromFile("Art/eyeLaserSpriteSheet.png")) {					// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Boss animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gEnemyBossEyes, 25, 25, 16);
	}

	if (!gEnemyBossSpriteSheetTexture.loadFromFile("Art/lorcanSpriteSheet.png")) {							// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Boss animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gEnemyBossSpriteClips, 300, 460, 4);											// Set sprite clips
	}

	if (!gSmallGreenVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Green_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallGreenVirusSpriteClips, 40, 40, 4);										// Set sprite clips
	}
	if (!gSmallOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallOrangeVirusSpriteClips, 40, 40, 4);									// Set sprite clips
	}
	if (!gSmallBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Blue_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallBlueVirusSpriteClips, 40, 40, 4);									// Set sprite clips
	}
	*/
	int PLAYER_INDEX;

	if (twoPlayer) PLAYER_INDEX = 2;
	else PLAYER_INDEX = 1;

	return success;
}

void Game::close() {
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
	//gRenderer = NULL;

	//fps.fpsclose();
	splash.closeSplashScreens();	// Close splash screen stuff
	menu1.closeMenuMedia();				// Close menu stuff
	Audio::Instance()->destroy();
	//headsUpDisplay.closeLevelStuff();
	//particle.closeParticle();

	// Empty Lists
	//listOfGameObjects.clear();		// Scores, Power Ups, Explosions
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
				//if (!twoPlayer) player2->setAlive(false);

				quit = playerInput(quit);									// 2017/01/09 JOE: Handle input from player

				if (getCurrentLevel() == MENU) menu1.draw();				// New
				else if (getCurrentLevel() == PAUSE) menu1.drawPause();		// New
				else if (getCurrentLevel() != MENU && getCurrentLevel() != PAUSE && getCurrentLevel() != SETTINGS && getCurrentLevel() != HIGH_SCORES && getCurrentLevel() != ENTER_NAME) playLevel(getCurrentLevel());
				else if (getCurrentLevel() == SETTINGS && settingsMenuLoaded == false) {
					settingsMenuLoaded = settings.loadSettingsMedia();
					settings.draw();
				}
				else if (getCurrentLevel() == HIGH_SCORES && highScoresLoaded == false) {
					highScoresLoaded = highScore.loadHighScoresMedia();
					highScore.draw();
				}
				else if (getCurrentLevel() == ENTER_NAME && enterNameLoaded == false) {
				//else if (getCurrentLevel() == HIGH_SCORES && enterNameLoaded == false) {
					enterNameLoaded = enterName1.loadNameMedia();
					enterName1.draw();
				}
				//if (!nameEntered) enterName();

				//if(getCurrentLevel() == 1) enterName();
				//else {
				//if (getCurrentLevel() == PAUSE)
					//fps1.fpsthink();			// Update the FPS

				//destroyGameObjects();										// 2017-01-09 JOE: Destroy the game objects when finished on the screen
				//}
			}
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
				Audio::Instance()->playPauseMusic(); break;				// 2017/03/17 Altered function to play / pause the music in Audio class
			case SDLK_l:
				Audio::Instance()->musicForwardSongName(); break;		// Skip track forwards, identifying the name of the new song playing
			case SDLK_k:
				Audio::Instance()->musicBackSongName(); break;			// Skip track backwards, identifying the name of the new song playing
			case SDLK_0:
				Audio::Instance()->stopMusic();
			case SDLK_ESCAPE:
				if (getCurrentLevel() == LEVEL_1 || getCurrentLevel() == LEVEL_2 || getCurrentLevel() == LEVEL_3) {
					levelToPause = getCurrentLevel();	// Store the existing level number
					setCurrentLevel(PAUSE);				// 2017-03-13 Add if statement for esc press
				}
				else setCurrentLevel(MENU);
				break;

			case SDLK_F11:
				fullScreenOrWindowed();	// Alter between full screen and windowed display
				break;

			// Map
			case SDLK_t:
				//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				// Go From mini map to large transparent map
				//if (mapViewport.y == 600) {
				if (headsUpDisplay.miniMap) {
					//setViewport(mapViewport, (SCREEN_WIDTH - 780) / 2, 40, 900, 657);
					setViewport(headsUpDisplay.mapVP, (SCREEN_WIDTH - 780) / 2, 40, 900, 657);
					infoMessage("View Map");
					Texture::Instance()->modifyAlpha(50, "profID");
					headsUpDisplay.miniMap = false;													// 2017/03/19 Show big map ship position
				}
				// Go from large map to mini map
				//else if (mapViewport.y == 40) {
				else {
					//setViewport(mapViewport, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// 230 was 192, 168 was 140
					setViewport(headsUpDisplay.mapVP, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// 230 was 192, 168 was 140
					infoMessage("Hide Map");
					Texture::Instance()->modifyAlpha(255, "profID");
					headsUpDisplay.miniMap = true;														// 2017/03/19 Show big map ship position
				}
				break;
				// case SDLK_DOWN:
				//	topViewport.w = 10;
				//	break;
			case SDLK_F1:
				framesPerSec.str("");
				framesPerSec << "FPS: " << fps1.getFPS();								// FPS the game is running at
				gFPSTextTexture.UIText(framesPerSec.str().c_str());						// Render text - Use a string to render the current FPS to a texture
				fps1.rendFPS(framesPerSec.str().c_str());
				break;

			default:
				//	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
				break;
			}
		}

		else if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_F1:
				gFPSTextTexture.free();
				framesPerSec.str("");
				break;
			default:
				break;
			}
		}
		//Joystick button press
		else if (e.type == SDL_JOYBUTTONDOWN) {
			//Play rumble at 75% strenght for 500 milliseconds
			if (SDL_HapticRumblePlay(gControllerHaptic, 0.5, 50) != 0) {
				printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
			}
		}
		// Menu events
		menu1.handleMenuEvents(e);
		if (getCurrentLevel() != 0) {												// If not in menu state
			if(player1->getAlive()) player1->handleEvent(e, PLAYER_1);						// Handle input for Player 1
			if (player2->getAlive()) player2->handleEvent(e, PLAYER_2);					// Handle input for Player 2

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

void Game::fullScreenOrWindowed() {
	if (windowFlag == SDL_WINDOW_FULLSCREEN)
		windowFlag = SDL_WINDOW_SHOWN;
	else
		windowFlag = SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(gWindow, windowFlag);
}


void Game::renderGameOver() {
	// Decide the winner of the game
	if (!Game::Instance()->twoPlayer)
		gameWinners = "Player has completed the course";
	else if (twoPlayer) {
		if (player1Score > player2Score) gameWinners = "Player 1 Wins";
		else if (player2Score > player1Score) gameWinners = "Player 2 Wins";
		else gameWinners = "It's a draw";
	}

	//gameProgress();													// Times the end of game message

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);						// Clear the current viewport to render to full window / screen
	splash.endOfGame(Game::Instance()->getCurrentLevel(), finalScores, gameWinners);	// Call end of game splash screens
	//renderTimer(gameOverTimer);										// Render returning to menu timer
	SDL_RenderPresent(Game::Instance()->getRenderer());								// Update screen
}

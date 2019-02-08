/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Game.h
	- Description:			Header file for the game class.		
	- Log:
		2017/02/28		Fixed entry point not defined error with #define SDL_MAIN_HANDLED
		2017/02/27		Made the Constructor private for use as a singleton
						Moved setRotatingAngle() functions here. Sets the angle for rotating objects
						Moved scrollBackground() function here. Scolls the background image
		2017/02/23		Added singleton for Game class
		2017/02/19		Added blood explosions to spawnExplosion() function
		2017/02/17		Added identifyTrack() function to dentify the song current playing and display the name on screen
		2017/02/16		Added infoMessage() function to display player messages for player events
		2017/02/15		Added gameTimer() function, to ouput the current seconds remaining in the game
		2017/02/06		Added spawnRocket() function to create rockets for players
						Added managePlayerScores() function to handle players score
		2017/01/25		Added spawnExplosion() functions for creating explosions when objects collide
		2017/01/20		Added spawnSaw() function to create Saw Weapon for player
						Added Weapons grade for spawnLaser() function to distinguish between upgrades in weapons
		2017/01/18		Added pressButtonToContinue() function for splash screens at start of game, so player can read writing at own pace
						Added spawnRandom() function to separate out common randomness of game object spawning
		2017/01/17		Added displayText() function to render text used in the game
						Added gamepadInfo() function to separate gamepad information into its own function
						Added player decision to spawnNinjaStar() function - determines player to spawn for and their coords
		2017/01/16		Added spawnLaser() function to spawn a laser at coords, with velocitys 
		2017/01/10		Added spawnEnemyVirus() function to create enemy virus at random times and random y coord
						Added spawnEnemyLaser() function, to spawn bullet objects for enemy ships
						Added spawnBloodCell() function to create blood cells
						Added spawnMovingObjects() function to spawn enemies and obstacles at random coords & distances apart
		2017/01/09		Added spawnNinjaStar() function to create ninja star weapons
						Added playerInput() function to handle input from player
						Added renderGameObjects() function to render the game objects to the screen
						Added moveGameObjects() function to move the game objects on the screen
						Added destroyGameObjects() function to destroy the game objects when finished using
						Added spawnEnemyShip() function to create enemy ships at random times and random y coord
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef GAME_H
#define GAME_H


#define SDL_MAIN_HANDLED	// Handling SDL main definition ourselves
#include <SDL.h>
#include "GameStateMachine.h"
#include <cstdlib>			// For Random Numbers
#include <ctime>			// For Random Numbers
#include <list>

// Other Symbolic Constants
#define PLAYER_1 1
#define PLAYER_2 2

// Animation
const int ANIMATION_FRAMES = 4;				// Number of frames of animation for Enemy Ship
const int EXPLOSION_ANIMATION_FRAMES = 16;	// Number of frames of animation for Explosions
const int BLOOD_EXP_ANIMATION_FRAMES = 16;

enum gameStates {  MENU, LEVEL_1, LEVEL_2, LEVEL_3, PAUSE, SETTINGS, HIGH_SCORES, GAME_INTRO, LEVEL_INFO, ENTER_NAME };

class Game {
public:
	// 27/02/2017 Game Singleton
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	/* MAIN GAME FUNCTIONS */

	bool init();							// Starts up SDL and creates window -- ERROR window won't close
	bool loadMedia();						// Loads media for the game
	void update();							// Update the game. This is the main loop for the game
	bool playerInput(bool quit);			// 2017/01/09 JOE: Handle input from player
	void moveGameObjects();					// 2017-01-09 JOE: Move the game objects on the screen
	void render();							// Render the game to screen
	void destroyGameObjects();				// 2017-01-09 JOE: Destroy the game objects when finished on the screen
	void close();							// Frees media and shuts down SDL
	void resetGame(int level);				// Reset game to this level

	/* VARIABLES */

	// Game States
	bool settingsMenuLoaded = false;		// Determines if the Settings Menu is loaded or not
	bool highScoresLoaded = false;			// Determines if the High Scores Table is loaded or not
	bool enterNameLoaded = false;			// Determines if the Enter Name state is loaded or not
	bool displayGameIntro;					// False means off - set in _TestData.h
	bool displayLevelIntro;					// Display the information splash screen at the start of a level - set in _TestData.h

	// Game Window
	SDL_Window* gWindow = NULL;				// The window we'll be rendering to
	int windowFlag;							// Show the game in full screen or windowed	

	// Viewports
	SDL_Rect gameViewport;					// Main game screen view port, this is the section of the window where the game is rendered

	// Player
	int player1Score, player2Score;			// Need variables to store score in case player dies	
	bool nameEntered;						// Has a name been entered for the Player
	bool renderText;						// Render game text to screen
	std::string inputText = "Name";			// Text to be input for Players name
	int checkpointsSpawned = 0;				// Number of checkpoints that are spawned
	bool twoPlayer;							// Decides if game is 2 player or 1 player
	
	int frames;								// Frame count for speed of Enemy animation

	// Time
	unsigned int lastTime, currentTime, countdownTimer, gameOverTimer;	// TEST TIMING
	
	// Background
	int backgroundLoopCounter;							// Number of times the background image has looped

	// Level
	int levelToPause;									// Store Current Level to return to from pause
	bool gameOver = false;								// Decide if game is over
	bool levelOver = false;								// Decide if level is over
	bool noTime = false;								// Decide if time has run out for the level
	
	// Game Messages
	int infoMessageP1Counter, infoMessageP2Counter;		// Time to display notification messages
	int infoMessageCounter, infoMessageMapCounter;		// Centre message, not specific to players
	std::string infoMessageP1, infoMessageP2; 			// Player notification messages. Different colour for each player appearing in the middle of the game screen
	std::string infoMessageGeneral, infoMessageMap;		// Additional game messages
	int gamerOverMessageCounter;						// Length of time to display game over message
	std::string finalScores, gameWinners;				// Game Over Messages	
	
	/* FUNCTIONS */

	// States
	int getCurrentLevel() { return mCurrentLevel; }		// Get the current level
	void setCurrentLevel(int l) { mCurrentLevel = l; }	// Set the current level
	void displayLevelIntros(int level);				// Display the intro / objective screens at the start of each level
	bool enterName();									// Enter the name for the player before beginning the game
	void playLevel(int levelNum);						// Play each level

	// Rendering
	void fullScreenOrWindowed();										// Decide if the game is in full screen or windowed mode
	SDL_Renderer* getRenderer() const { return gRenderer; }				// The renderer for the game
	void displayScoreForObject(int x, int y, int score, int player);	// Display the score the player receives for destroying an Enemy object
	void displayText();													// 2017/01/17: Display game text
	void infoMessage(std::string message, int type = 0, int timer = 0);	// Display an information message on screen
	void checkMessageTimes();											// 2017/03/19 Check how long a message has been on screen
	void renderGamePlay();												// 2017-01-09 Render the game objects to the screen
	void renderGameOver();												// 2017/03/02 Render the game objects for Game Over state
	void renderTimer(unsigned int &timer);								// 2017/03/02 Separate the game timer to its own function

	// Spawn Game Objects
	void spawnMovingObjects();												// Decide the amount of each object to spawn
	void spawnRandomAttributes(int &x, int &y, int &randomSpeed, int xMuliplier = 0, int yPad = 80, int speed = 1);	// Spawn random attributes for game objects, such as speed, and distance between objects when spawning
	void spawnPlayer(int player);											// Spawn / Respawn player at start of game, or when a life is lost
	void spawnEnemyBoss();													// 2017/03/02 Added function to create Enemy Boss objects at random times and coords
	void spawnEnemyShip();													// 2017/01/09 Added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus(int type = 0, int x = 0, int y = 0);				// 2017/01/10 Added function to create enemy virus at random times and random y coord
	void spawnBloodCell(int type = 0);										// 2017/01/10 Add function to create blood cells
	void spawnLaser(int x, int y, int player, int grade = 0, int v = 20);	// 2017/01/16 spawn a laser at coords, with velocitys 2017/01/20 added Weapons grade
	void spawnEnemyLaser(int x, int y, int type = 0, int whichVirus = 0);	// 2017/01/10 Spawn an Enemy Laser, fireball, or projectile
	void spawnNinjaStar(int x, int y, int player);							// 2017/01/09 Added function to create ninja star weapons - 2017/01/17 added player decision - player to spawn for and their coords
	void spawnSaw(int x, int y, int player);								// 2017/01/20: Saw Weapon for player
	void spawnPowerUp();													// Spawn a power up for the player to collect
	void spawnRocket(int x, int y, int player, int type, bool launch);		// 2017-02-06 Spawn a player Rocket weapon
	void spawnBlockage();													// Spawn a blockage obstacle
	void spawnExplosion(int x, int y, int subType);							// 2017/01/25 Added explosions // 2017/02/19 Added blood explosions

	// Movement and Updating
	bool moveToPlayer1(int x, int y);										// 2017/03/22 Separate which Player the virus chooses to move towards to function	
	void gameProgress();													// Decide if the game is over or not
	
	// Collisions
	bool checkCollision(SDL_Rect *a, SDL_Rect *b);							// Check collision between game objects
	void collisionCheck();													// Check collisions between game objects on the Game Objects list, and decide what happens
	
	int getNumPlayers() { return mNumPlayers; }								// Get the number of players in the game
	void setNumPlayers(int n) { mNumPlayers = n; }							// Set the number of players in the game
	void managePlayerHealth(int player, int score, std::string name = "Game Object");	// Set the health for the player if it has collided with an object, increasing if it picks up a health power up
	void managePlayerScores(int score, int player, int type);							// Manage scores for the player destroying enemy objects
	
private:

	Game() {};								// 2017/02/27 Constructor private for singleton

	SDL_Renderer* gRenderer;				// P65 2017/02/27 Renderer
	
	int mNumPlayers;						// The number of players in the game

	int mCurrentLevel =	MENU;				// The current level of the game, 0 = menu, 1 = level 1 etc.

	static Game* s_pInstance;				// One instance of Game to be used throughout the project
};

#endif

// Old public stuff

//int pointsValueCounter;								// Time to display score for killing Enemy message
//std::string pointsValue;							// Player notification messages, Yellow writing appearing in the middle of the game screen
//std::string levelObjective;				// The objective for the start of each level
//GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
//SDL_Renderer* getRenderer() const { return m_pRenderer; }
//void enterName();
	//int scrollingOffset;								// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function) // Moved to ScrollingBackground class
	//int weaponScrolling;								// Scroll the image for current default laser weapon // 2017/03/20 Moved to HUD class
	//void scrollBackground();							// 2017/02/22 Moved here. Scoll the background // 2017/03/21 Moved to ScrollingBackground class
	//void setRotatingAngle();							// 2017/02/22 Moved here. Set the angle for rotating objects // No longer needed angle set in move() function for rotating objects

//int counter = 0;		// counter for changing alpha for flashing
//void displayLevelSplashScreen(std::string objective);
	//void gameTimer(unsigned int &timer);					// 2017-03-02
	//void gameTimer();										// 2017-02-15

	//void gamepadInfo();									// 2017/01/17: Separate gamepad information

	//void pressButtonToContinue();							// 2017/01/18
	//void renderTimer();									// 2017/03/02 JOE: Separate the game timer to its own function

//void setViewport(SDL_Rect &rect, int x, int y, int w, int h);
//void setupAnimationClip(SDL_Rect &rect, int frames, int amount, bool type2 = false);
// Music
//void musicTrackForward();								// FOR SOME REASON, CONTROLLER DOESNT LIKE THE AUDIO CLASS -> SO PLAYING THROUGH GAME
//void musicTrackBackward();
//void identifyTrack(int songName);						// 2017/02/17 Identify the song playing

// Old Private stuff

//GameStateMachine* m_pGameStateMachine;	// Instance of the game state machine
//int mCurrentLevel = GAME_INTRO;		// 2017/03/18 The current level of the game, 0 = menu, 1 = level 1 etc.
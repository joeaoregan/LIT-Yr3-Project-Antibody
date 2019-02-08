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
	bool settingsMenuLoaded = false;
	bool highScoresLoaded = false;
	bool enterNameLoaded = false;

	SDL_Window* gWindow = NULL;				// The window we'll be rendering to
	int windowFlag;							// Show the game in full screen or windowed
	void fullScreenOrWindowed();

	// 27/02/2017 Game Singleton
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	// Viewports
	SDL_Rect gameViewport;		// Main game screen view port

	bool checkCollision(SDL_Rect *a, SDL_Rect *b);
	
	//SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Renderer* getRenderer() const { return gRenderer; }

	int player1Score, player2Score;		// need variables to store score in case player dies

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
	
	bool nameEntered;
	bool enterName();
	//void enterName();
	bool renderText;
	std::string inputText = "Name";

	bool twoPlayer;
	bool displayGameIntro;				// False means off - set in _TestData.h
	bool displayLevelIntro;				// Display the information splash screen at the start of a level - set in _TestData.h


	int gamerOverMessageDisplayCounter;	// Length of time to display game over message
	int frames;							// Frame count for speed of Enemy animation

	// Time
	unsigned int lastTime, currentTime, countdownTimer, gameOverTimer, lastTime2;	// TEST TIMING

	// Game Over Messages
	std::string finalScores, gameWinners;

	// Scrolling
	int backgroundLoopCounter;							// Number of times the background image has looped
	//int scrollingOffset;								// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function) // Moved to ScrollingBackground class
	//int weaponScrolling;								// Scroll the image for current default laser weapon // 2017/03/20 Moved to HUD class
	//void scrollBackground();							// 2017/02/22 Moved here. Scoll the background // 2017/03/21 Moved to ScrollingBackground class
	//void setRotatingAngle();							// 2017/02/22 Moved here. Set the angle for rotating objects // No longer needed angle set in move() function for rotating objects

	// Game Messages
	int pointsValueCounter;								// Time to display score for killing Enemy message
	std::string pointsValue;							// Player notification messages, Yellow writing appearing in the middle of the game screen
	int infoMessageP1Counter, infoMessageP2Counter;		// Time to display notification messages
	int infoMessageCounter, infoMessageMapCounter;
	std::string infoMessageP1, infoMessageP2; 			// Player notification messages, Yellow writing appearing in the middle of the game screen
	std::string infoMessageGeneral, infoMessageMap;
	
	void checkMessageTimes();							// 2017/03/19 Check how long a message has been on screen

	// Number of Game Objects currently on the screen
	int activeBloodCells;
	int activeWhiteBloodCells;
	int activeSmallBloodCells;
	int activePowerUps;
	int activeEnemyShips;
	int activeEnemyVirus;
	int activeEnemyVirusSmall;
	int activeEnemyBoss;


	int getCurrentLevel() { return mCurrentLevel; }
	void setCurrentLevel(int l) { mCurrentLevel = l; }
	int levelToPause;										// Store Current Level to return to from pause

	//int counter = 0;		// counter for changing alpha for flashing
	bool gameOver = false;
	bool levelOver = false;
	bool noTime = false;

	int checkpointsSpawned = 0;
	
	bool init();								// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();								// Frees media and shuts down SDL

	//void displayLevelSplashScreen(std::string objective);
	void displayLevelIntroScreens(int level);
	std::string levelObjective;

	void playLevel(int levelNum);

	void displayScoreForObject(int x, int y, int score, int player);

	void resetGame(int level);								// Reset game to this level

	void spawnExplosion(int x, int y, int subType);			// 2017/01/25 Added explosions // 2017/02/19 Added blood explosions

	void spawnMovingObjects();
	void spawnPlayer(int player);
	void spawnEnemyBoss();													// 2017/03/02 JOE: Added function to create Enemy Boss objects at random times and coords
	void spawnEnemyShip();													// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus(int type = 0, int x = 0, int y = 0);				// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell(int type = 0);										// 2017/01/10 JOE: add function to create blood cells
	void spawnLaser(int x, int y, int player, int grade = 0, int v = 20);	// 2017/01/16 spawn a laser at coords, with velocitys 2017/01/20 added Weapons grade
	void spawnEnemyLaser(int x, int y, int type = 0, int whichVirus = 0);	// 2017/01/10
	void spawnNinjaStar(int x, int y, int player);							// 2017/01/09 JOE: added function to create ninja star weapons - 2017/01/17 added player decision - player to spawn for and their coords
	void spawnSaw(int x, int y, int player);								// 2017/01/20: Saw Weapon for player
	void spawnPowerUp();
	void spawnRocket(int x, int y, int player, int type, bool launch);		// 2017-02-06
	void spawnBlockage();


	void gameProgress();
	//void gameTimer(unsigned int &timer);					// 2017-03-02
	//void gameTimer();										// 2017-02-15

	//void gamepadInfo();									// 2017/01/17: Separate gamepad information

	void displayText();										// 2017/01/17: Display game text
	//void pressButtonToContinue();							// 2017/01/18

	void infoMessage(std::string message, int type = 0, int timer = 0);

	void collisionCheck();

	bool playerInput(bool quit);							// 2017/01/09 JOE: Handle input from player
	void render();
	void renderGamePlay();									// 2017-01-09 JOE: Render the game objects to the screen
	void renderGameOver();									// 2017/03/02 JOE: Render the game objects for Game Over state
	void renderTimer(unsigned int &timer);					// 2017/03/02 JOE: Separate the game timer to its own function
	//void renderTimer();									// 2017/03/02 JOE: Separate the game timer to its own function
	void moveGameObjects();									// 2017-01-09 JOE: Move the game objects on the screen

	bool moveToPlayer1(int x, int y);						// 2017/03/22 Separate which Player the virus chooses to move towards to function

	void destroyGameObjects();								// 2017-01-09 JOE: Destroy the game objects when finished on the screen

	bool loadMedia();										// Loads media

	// Music
	//void musicTrackForward();								// FOR SOME REASON, CONTROLLER DOESNT LIKE THE AUDIO CLASS -> SO PLAYING THROUGH GAME
	//void musicTrackBackward();
	//void identifyTrack(int songName);						// 2017/02/17 Identify the song playing

	void spawnRandomAttributes(int &x, int &y, int &randomSpeed, int xMuliplier = 0, int yPadding = 80, int speed = 1);

	int getNumPlayers() { return mNumPlayers; }
	void setNumPlayers(int n) { mNumPlayers = n; }
	void managePlayerHealth(int player, int score, std::string name = "Game Object");
	void managePlayerScores(int score, int player, int type);

	//void setViewport(SDL_Rect &rect, int x, int y, int w, int h);
	//void setupAnimationClip(SDL_Rect &rect, int frames, int amount, bool type2 = false);


private:
	GameStateMachine* m_pGameStateMachine;

	SDL_Renderer* gRenderer;		// P65 2017/02/27 Renderer

	Game() {};						// 2017/02/27 Constructor private for singleton
	
	int mNumPlayers;
	//int mCurrentLevel = GAME_INTRO;		// 2017/03/18 The current level of the game, 0 = menu, 1 = level 1 etc.
	int mCurrentLevel =	MENU;		// The current level of the game, 0 = menu, 1 = level 1 etc.

	static Game* s_pInstance;
};

#endif
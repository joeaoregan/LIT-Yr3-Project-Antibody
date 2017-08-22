#ifndef LEVEL_H
#define LEVEL_H

#include "Game.h"

class Level {
public:
	// Constructor - Initializes the variables
	Level(int level = LEVEL_1) {
		Game::Instance()->setCurrentLevel(level);					// Set the current level
	}

	// Destructor
	~Level() {};

	int backgroundLoopCounter;							// Number of times the background image has looped

	bool noTime = false;
	//int counter = 0;		// counter for changing alpha for flashing
	bool gameOver = false;
	bool levelOver = false;

	int checkpointsSpawned = 0;

	// Viewports
	SDL_Rect gameViewport;		// Main game screen view port

	bool loadMedia();
	void update();
	void render();
	void clearMedia();
	void destroyGameObjects();

	bool checkCollision(SDL_Rect *a, SDL_Rect *b);

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

	int gamerOverMessageDisplayCounter;	// Length of time to display game over message
	int frames;							// Frame count for speed of Enemy animation

	// Time
	unsigned int lastTime, currentTime, countdownTimer, gameOverTimer, lastTime2;	// TEST TIMING

	void renderGamePlay();									// 2017-01-09 JOE: Render the game objects to the screen

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


	//void displayLevelSplashScreen(std::string objective);
	void displayLevelIntroScreens(int level);
	std::string levelObjective;

	void playLevel(int levelNum);

	void displayScoreForObject(int x, int y, int score, int player);

	void resetGame(int level);								// Reset game to this level

	void gameProgress();

	void displayText();										// 2017/01/17: Display game text

	void infoMessage(std::string message, int type = 0, int timer = 0);

	void collisionCheck();

	void renderTimer(unsigned int &timer);					// 2017/03/02 JOE: Separate the game timer to its own function
															//void renderTimer();									// 2017/03/02 JOE: Separate the game timer to its own function
	void moveGameObjects();									// 2017-01-09 JOE: Move the game objects on the screen

	bool moveToPlayer1(int x, int y);						// 2017/03/22 Separate which Player the virus chooses to move towards to function

//	void destroyGameObjects();								// 2017-01-09 JOE: Destroy the game objects when finished on the screen

	void spawnRandomAttributes(int &x, int &y, int &randomSpeed, int xMuliplier = 0, int yPadding = 80, int speed = 1);

	void managePlayerHealth(int player, int score, std::string name = "Game Object");
	void managePlayerScores(int score, int player, int type);
};

#endif

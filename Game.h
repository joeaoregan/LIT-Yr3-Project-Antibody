/*
*-------------------------------------------------
*		Game.h
*		Sean Horgan - K00196030
*		Date Started - 06/01/2017 - 18:13pm
*		Date Complete - 06/01/2017 - 19:47pm
*-------------------------------------------------
*/

#ifndef GAME_H
#define GAME_H

#include <cstdlib>		// For Random Numbers
#include <ctime>		// For Random Numbers
#include <list>
#include <vector>
#include <string>

// Other Symbolic Constants
#define PLAYER_1 1
#define PLAYER_2 2
#define NUMBER_OF_SONGS = 3;			// Total number of songs in the playlist

class Game {
public:
	// Time
	unsigned int lastTime, currentTime, countdownTimer;	// TEST TIMING

	// Game Over Messages
	std::string finalScores, gameWinners;

	// Scrolling
	int backgroundLoopCounter;							// Number of times the background image has looped
	int scrollingOffset;								// 2017/01/10 JOE: Declare the background scrolling offset (Moved as stops background scrolling when in the render function)
	int weaponScrolling;								// Scroll the image for current default laser weapon

	// Game Messages
	int pointsValueCounter;								// Time to display score for killing Enemy message
	std::string pointsValue;							// Player notification messages, Yellow writing appearing in the middle of the game screen
	int infoMessageP1Counter, infoMessageP2Counter, infoMessageCounter;		// Time to display notification messages
	std::string infoMessageP1, infoMessageP2, infoMessageGeneral;			// Player notification messages, Yellow writing appearing in the middle of the game screen

	// Number of Blood Cells currently on the screen
	int BloodCellsActive;
	int whiteBloodCellsActive;
	int smallBloodCellsActive;

	enum levels { MENU, LEVEL_1, LEVEL_2, LEVEL_3 };
	enum playerWeapons {NINJA_STAR_P1, NINJA_STAR_P2, LASER_P1, LASER_P2, SAW_P1, SAW_P2, LASER_V2_P1, LASER_V2_P2, ROCKET_P1, ROCKET_P2};

	int getCurrentLevel() { return mCurrentLevel; }
	void setCurrentLevel(int l) { mCurrentLevel = l; }

	//int counter = 0;		// counter for changing alpha for flashing
	bool gameOver = false;
	bool levelOver = false;

	bool init();								// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();								// Frees media and shuts down SDL

	//void displayLevelSplashScreen(std::string objective);
	void displayLevelIntroScreens(int level);
	std::string levelObjective;

	void playLevel(int levelNum);

	void displayScoreForObject(int x, int y, int score, int player);

	void resetGame(int level);								// Reset game to this level

	void spawnExplosion(int x, int y);						// 2017/01/25 Added explosions

	void spawnMovingObjects();
	void spawnPlayer(int player);
	void spawnEnemyShip();									// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus();									// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell(int type = 0);						// 2017/01/10 JOE: add function to create blood cells
	void spawnLaser(int x, int y, int player, int v = 20, int grade = 0);	// 2017/01/16 spawn a laser at coords, with velocitys 2017/01/20 added Weapons grade
	void spawnEnemyLaser(int x, int y, int type = 0, int whichVirus = 0);						// 2017/01/10
	void spawnNinjaStar(int x, int y, int player);			// 2017/01/09 JOE: added function to create ninja star weapons - 2017/01/17 added player decision - player to spawn for and their coords
	void spawnSaw(int x, int y, int player);				// 2017/01/20: Saw Weapon for player
	void spawnPowerUp();
	void spawnRocket(int x, int y, int player, int type);				// 2017-02-06

	void gameProgress();
	void gameTimer();										// 2017-02-15

	//void gamepadInfo();									// 2017/01/17: Separate gamepad information

	void displayText();										// 2017/01/17: Display game text
	//void pressButtonToContinue();							// 2017/01/18

	void infoMessage(std::string message, int type = 0, int timer = 0);

	void collisionCheck();
	//bool checkCollision(SDL_Rect *a, SDL_Rect *b);

	bool playerInput(bool quit);							// 2017/01/09 JOE: Handle input from player
	void renderGameObjects();								// 2017-01-09 JOE: Render the game objects to the screen
	void moveGameObjects();									// 2017-01-09 JOE: Move the game objects on the screen
	void destroyGameObjects();								// 2017-01-09 JOE: Destroy the game objects when finished on the screen

	bool loadMedia();										// Loads media

	// Music
	void musicTrackForward();								// FOR SOME REASON, CONTROLLER DOESNT LIKE THE AUDIO CLASS -> SO PLAYING THROUGH GAME
	void musicTrackBackward();

	void spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier = 0, int yPadding = 80, int speed = 1);

	int getNumPlayers() { return mNumPlayers; }
	void setNumPlayers(int n) { mNumPlayers = n; }
	void managePlayerHealth(int player, int score, std::string name = "Game Object");
	void managePlayerScores(int score, int player, int type);

	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//void setViewport(SDL_Rect &rect, int x, int y, int w, int h);

private:
	int mNumPlayers;
	int mCurrentLevel = MENU;							// The current level of the game, 0 = menu, 1 = level 1 etc.
	//int mCurrentLevel = LEVEL_1;						// The current level of the game, 0 = menu, 1 = level 1 etc.

	static Game* s_pInstance;
};

#endif

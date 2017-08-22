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

//#include <SDL.h>
//#include <SDL_image.h>
//#include "LTexture.h"
#include <cstdlib>		// For Random Numbers
#include <ctime>		// For Random Numbers
#include <list>
#include <vector>
#include <string>

// Number of enemies to be displayed on screen
#define SPAWN_NUM_ENEMY_SHIPS 1			// WAS 2 The number of enemy ships that can appear on screen at a time
#define SPAWN_NUM_ENEMY_VIRUS 1			// WAS 2 The number of enemy virus that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL 4			// WAS 6 The number of large blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_S 5		// WAS 9 The number of small blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_WHITE 2	// WAS 3 The number of white blood cells that can appear on screen at a time
#define SPAWN_NUM_POWER_UPS 1			// The number of power ups that can appear on screen at a time

// Other Symbolic Constants
#define PLAYER_1 1
#define PLAYER_2 2
#define NUM_PLAYERS 2					// The number of players
#define BACKGROUND_SCROLL_TIMES 5		// The number of times the main background scrolls
#define MAX_HEALTH 100.0				// The max health for a player
#define GAME_TIMER 30					// Time to start counting down from, in seconds
#define NUMBER_OF_SONGS = 3;			// Total number of songs in the playlist

// Game Levels and Testing
#define NUM_LIVES 3						// Number of lives each player starts with
#define MAX_NUM_LEVELS 3				// The maximum number of levels to progress through

// Player Message
#define MESSAGE_TIME 100				// Player Information Message, Stays on screen for a couple of seconds

class Game {
public:
	// Number of Blood Cells currently on the screen
	int BloodCellsActive;
	int whiteBloodCellsActive;
	int smallBloodCellsActive;

	void score(int type);		// calc the scores

	enum levels { MENU, LEVEL_1, LEVEL_2, LEVEL_3 };
	enum powerUpTypes { HEALTH = 1, LASER };
	enum virusType { GREEN, ORANGE };
	enum playerWeapons {NINJA_STAR_P1, NINJA_STAR_P2, LASER_P1, LASER_P2, SAW_P1, SAW_P2, LASER_V2_P1, LASER_V2_P2};

	int getCurrentLevel();
	void setCurrentLevel(int l);

	//int counter = 0;		// counter for changing alpha for flashing
	bool gameOver = false;
	bool levelOver = false;

	// Render Healthbars
	//enum healthBarOrientation { VERTICAL, HORIZONTAL };
	//void renderHealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, int orientation);	// 2017/01/20 Added orientation

	bool init();								// Starts up SDL and creates window -- ERROR window won't close
	void update();
	void close();								// Frees media and shuts down SDL

	void displaySplashScreens();					// Display Logos at start of game
	void displayLevelSplashScreen(std::string objective);

	void menu();
	void playLevel(int levelNum);
	//void level2();
	//void level3();

	//void renderMenu();

	void resetGame(int level);					// Reset game to this level

	void spawnExplosion(int x, int y);			// 2017/01/25 Added explosions

	void spawnMovingObjects();
	void spawnPlayer(int player);
	void spawnEnemyShip();						// 2017/01/09 JOE: added function to create enemy ships at random times and random y coord
	void spawnEnemyVirus();						// 2017/01/10 JOE: added function to create enemy virus at random times and random y coord
	void spawnBloodCell(int type = 0);						// 2017/01/10 JOE: add function to create blood cells
	void spawnLaser(int x, int y, int player, int v = 20, int grade = 0);	// 2017/01/16 spawn a laser at coords, with velocitys 2017/01/20 added Weapons grade
	void spawnEnemyLaser(int x, int y, int type = 0);						// 2017/01/10
	void spawnNinjaStar(int x, int y, int player);			// 2017/01/09 JOE: added function to create ninja star weapons - 2017/01/17 added player decision - player to spawn for and their coords
	void spawnSaw(int x, int y, int player);				// 2017/01/20: Saw Weapon for player
	void spawnPowerUp();

	void gamepadInfo();							// 2017/01/17: Separate gamepad information
	void displayText();							// 2017/01/17: Display game text
	void pressButtonToContinue();				// 2017/01/18

	void collisionCheck();

	bool playerInput(bool quit);				// 2017/01/09 JOE: Handle input from player
	void renderGameObjects();					// 2017-01-09 JOE: Render the game objects to the screen
	void moveGameObjects();						// 2017-01-09 JOE: Move the game objects on the screen
	void destroyGameObjects();					// 2017-01-09 JOE: Destroy the game objects when finished on the screen
	//void flashGameObject(int &alpha, bool &flash, int rate = 10, int times = 0);

	//bool checkCollision(SDL_Rect *a, SDL_Rect *b);
	bool loadMedia();					// Loads media

	// Music
	void musicForward();
	void musicBack();

	void spawnRandom(int &x, int &y, int &randomSpeed, int xMuliplier = 0, int yPadding = 80, int speed = 1);

	int getNumPlayers();
	void setNumPlayers(int n);
	void managePlayerHealth(int player, int score, std::string name = "Game Object");

	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
private:
	int mNumPlayers;
	int mCurrentLevel = MENU;						// The current level of the game, 0 = menu, 1 = level 1 etc.
	//int mCurrentLevel = LEVEL_1;						// The current level of the game, 0 = menu, 1 = level 1 etc.

	static Game* s_pInstance;
};

#endif

/*	----------------------------------------------------------------------------------------------------------------------
	- Name:					_TestData.h
	- Description:			This header files contains game settings which can be adjusted as needed 
							to balance and test the game.
	- Information:			Contains all functions for calculating and displaying FPS
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef TEST_DATA_H
#define TEST_DATA_H

#define GAME_TIMER 30						// Time to start counting down from, in seconds

#define NUM_PLAYERS 2						// The number of players

#define BACKGROUND_SCROLL_TIMES 15			// The number of times the main background scrolls
#define BACKGROUND_SCROLL_SPEED 5


// Game Levels and Testing
#define MAX_NUM_LIVES 3						// Number of lives each player starts with
#define MAX_NUM_LEVELS 3					// The maximum number of levels to progress through

// Player Message
#define MESSAGE_TIME 150					// Player Information Message, Stays on screen for a couple of seconds
#define MESSAGE_TIME_MAP 200				// Player Information Message, Stays on screen for a couple of seconds

// Display the game splash screens
#define DISPLAY_GAME_INTRO_SCREENS false	// needs to be true when game is complete
#define DISPLAY_LEVEL_INTRO_SCREENS false	// needs to be true when game is complete

#define MUSIC_ON false

#define FULL_SCREEN false

//#define TWO_PLAYER false


/* Number of enemies and power ups to be displayed on screen */
#define SPAWN_NUM_ENEMY_SHIPS 3				// WAS 2 The number of enemy ships that can appear on screen at a time
#define SPAWN_NUM_ENEMY_VIRUS_LVL1 3		// WAS 2 The number of enemy virus that can appear on screen at a time
#define SPAWN_NUM_ENEMY_VIRUS_LVL4 5
#define SPAWN_NUM_ENEMY_VIRUS_LVL3 6

//#define SPAWN_NUM_BLOOD_CELL 4			// WAS 6 The number of large blood cells that can appear on screen at a time
//#define SPAWN_NUM_BLOOD_CELL_S 5			// WAS 9 The number of small blood cells that can appear on screen at a time
//#define SPAWN_NUM_BLOOD_CELL_WHITE 2		// WAS 3 The number of white blood cells that can appear on screen at a time
#define SPAWN_NUM_POWER_UPS 2				// The number of power ups that can appear on screen at a time

// Seans Game Balancing Stuff
// Number of enemies to be displayed on screen
#define SPAWN_NUM_ENEMY_SHIPS_LVL1 3		// WAS 2 The number of enemy ships that can appear on screen at a time
#define SPAWN_NUM_ENEMY_SHIPS_LVL2 3
#define SPAWN_NUM_ENEMY_SHIPS_LVL3 4

#define SPAWN_NUM_BLOOD_CELL 4				// WAS 6 The number of large blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_S 5			// WAS 9 The number of small blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_WHITE 2		// WAS 3 The number of white blood cells that can appear on screen at a time
#define SPAWN_NUM_POWER_UPS 1				// The number of power ups that can appear on screen at a time
#define SPAWN_NUM_BLOCKAGES 4				// Max number of blockage enemies to spawn

// Max number of checkpoints to spawn in any one level
#define SPAWN_NUM_CHECKPOINTS  1			// Number of checkpoints to be spawned
#define MAX_NUM_CHECKPOINTS 2				// The maximum number of checkpoints to be on screen at any time

#endif
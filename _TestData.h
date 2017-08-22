#ifndef TEST_DATA_H
#define TEST_DATA_H

#define GAME_TIMER 5					// Time to start counting down from, in seconds

#define NUM_PLAYERS 2					// The number of players

#define BACKGROUND_SCROLL_TIMES 5		// The number of times the main background scrolls

// Number of enemies to be displayed on screen
#define SPAWN_NUM_ENEMY_SHIPS 3			// WAS 2 The number of enemy ships that can appear on screen at a time
#define SPAWN_NUM_ENEMY_VIRUS 3			// WAS 2 The number of enemy virus that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL 4			// WAS 6 The number of large blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_S 5		// WAS 9 The number of small blood cells that can appear on screen at a time
#define SPAWN_NUM_BLOOD_CELL_WHITE 2	// WAS 3 The number of white blood cells that can appear on screen at a time
#define SPAWN_NUM_POWER_UPS 1			// The number of power ups that can appear on screen at a time

// Game Levels and Testing
#define NUM_LIVES 3						// Number of lives each player starts with
#define MAX_NUM_LEVELS 3				// The maximum number of levels to progress through

// Player Message
#define MESSAGE_TIME 100				// Player Information Message, Stays on screen for a couple of seconds

class _TestData {
public:

};

#endif
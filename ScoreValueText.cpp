// 2017/02/09
// This class generates the scores that appear when an enemy is shot, 
// using a different colour to indicate which player will recive the points

#include "ScoreValueText.h"

ScoreValueText::ScoreValueText(int x, int y, int score, int player) {
	setName("+" + std::to_string(score));		// Individual string
	setX(x);
	setY(y);
	setTimerTracker(SDL_GetTicks());				// Set time the object was created
	setScore(score);							// the value of the object
	setAlive(true);								// set it active on the screen
	//setType(player);							// Is it a score for player 1 or player 2

	if (player % 2 == 0) setType(1);
	else if (player % 2 == 1) setType(2);		// NEEDS TO BE ADJUSTED FOR ROCKETS
}

ScoreValueText::~ScoreValueText() {}
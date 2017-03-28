/*
	2017/02/10 Added functionality so the scores displayed on screen move to player who scored them (Changed from moving to players score)
	2017/02/09 Added score class ScoreValueText.h for displaying values of scores for destroying objects
	2017/02/06 Added managePlayerScores() function to handle players score to Game class
	2017/01/31 Added points value messages for each player
				Added vector list of game objects to display the scores for each object killed
*/

#ifndef SCORE_VALUE_H
#define SCORE_VALUE_H

#include "GameObject.h"

class ScoreValueText : public GameObject {
public:
	ScoreValueText(int x, int y, int score, int player);
	~ScoreValueText();

	virtual void move() {};
	void move(int x, int y);	// Tracker movement, scores move towards players who earned the points

	Texture m_Texture;
};

#endif
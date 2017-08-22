#ifndef SCORE_VALUE_H
#define SCORE_VALUE_H

#include "GameObject.h"

class ScoreValueText : public GameObject {
public:
	ScoreValueText(int x, int y, int score, int player);
	~ScoreValueText();
};

#endif
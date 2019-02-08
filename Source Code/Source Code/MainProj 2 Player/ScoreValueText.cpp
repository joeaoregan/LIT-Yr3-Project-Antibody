/*
	2017/02/10 Added functionality so the scores displayed on screen move to player who scored them (Changed from moving to players score)
				Set score text transparency to 100, as it draw too much attention from the game action
	2017/02/09 Added score class ScoreValueText.h for displaying values of scores for destroying objects
	2017/02/06 Added managePlayerScores() function to handle players score to Game class
	2017/01/31 Added points value messages for each player
				Added vector list of game objects to display the scores for each object killed
*/
/*
	SCORE VALUE TEXT:

	This class generates the scores that appear when an enemy is shot, 
	using a different colour to indicate which player will recive the points
*/

#include "ScoreValueText.h"
#include "Texture.h"

ScoreValueText::ScoreValueText(int x, int y, int score, int player) {
	setType(SCORE_TEXT);
	setName("+" + std::to_string(score));		// Individual string
	setX(x);
	setY(y);
	setTimerTracker(SDL_GetTicks());			// Set time the object was created
	setScore(score);							// the value of the object
	setAlive(true);								// set it active on the screen
	setVelocity(8);
	//setType(player);							// Is it a score for player 1 or player 2
	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	if (player == PLAYER1) setSubType(PLAYER1_SCORE);
	else if (player == PLAYER2) setSubType(PLAYER2_SCORE);	// NEEDS TO BE ADJUSTED FOR ROCKETS

	//if (!m_Texture.loadFromRenderedText("+" + std::to_string(score), { 240, 210, 65, 255 }, gFontRetro20)) {	// Gold Text
	//	printf("Unable to render player text texture!\n");
	//}

	setLineAlgCalculated(false);
}

ScoreValueText::~ScoreValueText() {}
int i = 0;
void ScoreValueText::move(int x, int y) {
	
	float dx = x - getX();
	float dy = y - getY();
	float goal_dist = sqrt((dx * dx) + (dy * dy));

	if (goal_dist > getVelocity()) {
		float ratio = getVelocity() / goal_dist;
		float x_move = ratio * dx;
		float y_move = ratio * dy;
		setX(getX() + (int) x_move);
		setY(getY() + (int) y_move);

		//if (getType() == 1 && getY() >= 600 && getX() >= 50) setAlive(false);
		//else if (getType() == 2 && getY() >= 600 && getX() >= 1230) setAlive(false);
		if (getX() >= x - 5 && getX() <= x + 105 && getY() >= y - 5 && getY() >= y + 52) setAlive(false);	// kill if within player coords
	} else {
		setX(x);
		setY(y);
		setAlive(false);
	}
	/*
	
	float percent;
	float moveX = abs(getX() - x1);
	float moveY = abs(getY() - y1);

	if (moveY / moveX <= 1) {
		if (moveX / moveY <= 0) setY(getY());
		if (moveX / moveY < 0.25) setY(getY() + 1);
		if (moveX / moveY < 0.5) setY(getY() + 2);
		if (moveX / moveY < 0.75) setY(getY() + 3);
		if (moveX / moveY <= 1.0) setY(getY() + 4);

		if (moveY / moveX <= 0) setY(getY());
		if (moveY / moveX < 0.25) setY(getY() + 1);
		if (moveY / moveX < 0.5) setY(getY() + 2);
		if (moveY / moveX < 0.75) setY(getY() + 3);
		if (moveY / moveX <= 1.0) setY(getY() + 4);
	}
	
	
	// Using the midpoint line scan-conversion algorithm from graphics last year
	if (!getLineAlgCalculated()) {
		dx = x1 - getX();
		dy = y1 - getY();

		std::cout << "x0: " << getX() << " y0: " << getY() << " x1: " << x1 << " y1: " << y1 << std::endl;
		setLineAlgCalculated(true);
	}
	int d = 2 * dy - dx;
	int incrE = 2 * dy;
	int incrNE = 2 * (dy - dx);

	if (dx / dy <= 1) {
		if (getX() < x1) {
			if (d <= 0) {
				d += incrE;
				//std::cout << "incrE" << std::endl;
				setX(getX() + 5);
			}
			else {
				d += incrNE;
				//std::cout << "incrNE " << i << std::endl; i++;
				setX(getX() + 5);
				setY(getY() + 5);
			}
		}
	}
	





	else {
		if (getY() < y1) {
			if (d <= 0) {
				d += incrE;
				setY(getY() + 5);
			}
			else {
				d += incrNE;
				setY(getY() + 5);
				setX(getX() + 5);
			}
		}
	}
	*/
}
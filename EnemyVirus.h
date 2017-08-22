#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"

class EnemyVirus : public Enemy {
public:
	float bombTimer;

	EnemyVirus();							// Initializes the variables
	EnemyVirus(int type, float time);							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);
	//void render();							// Shows the Enemy on the screen
	void render(LTexture &texture, SDL_Renderer *rend);							// Shows the Enemy on the screen
	void render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &enemyframe);

	float getTimer();
	void setTimer(int t);
};

#endif
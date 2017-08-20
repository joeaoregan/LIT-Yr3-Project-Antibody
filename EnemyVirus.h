#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"

class EnemyVirus : public Enemy {
public:
	EnemyVirus();							// Initializes the variables
	~EnemyVirus();							// Destructor

	virtual void movement(int playerX, int playerY);
	//void render(LTexture &texture, SDL_Renderer *rend);							// Shows the Enemy on the screen
};

#endif
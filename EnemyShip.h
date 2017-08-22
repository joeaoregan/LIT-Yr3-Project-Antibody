#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Enemy.h"

class EnemyShip : public Enemy {
public:
	EnemyShip();							// Initializes the variables
	~EnemyShip();

	const int ANIMATION_FRAMES = 4;

	virtual void movement();
	//void render();							// Shows the Enemy on the screen
	void render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &enemyframey);							// Shows the Enemy on the screen
};

#endif
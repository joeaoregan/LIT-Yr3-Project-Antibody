#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

#include "Enemy.h"

class EnemyShip : public Enemy {
public:
	EnemyShip();							// Initializes the variables
	~EnemyShip();

	//SDL_Rect gEnemySpriteClips[ANIMATION_FRAMES];
	int enemyframe = 0;

	const int ANIMATION_FRAMES = 4;

	virtual void movement();
	void render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &enemyframey);							// Shows the Enemy on the screen
};

#endif
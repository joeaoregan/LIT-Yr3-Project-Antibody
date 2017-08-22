
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class LaserEnemy : public Weapon {
public:
	LaserEnemy(int type = 0);						// Initializes the variables
	~LaserEnemy();						// Destructor

	virtual void movement();			// Moves the laser
	//void render();						// Shows the laser on the screen
	void render(LTexture &texture, SDL_Renderer *rend);						// Shows the laser on the screen 2017/01/22 Added Texture and renderer
	virtual void spawn(int x, int y, SDL_Rect collider);	// Spawn the object at the dimensions provided
};

#endif

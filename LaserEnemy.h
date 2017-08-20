
/* 2017/01/09:
JOE: Added Laser For Enemy ship
*/
#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H
#include "Weapon.h"

class LaserEnemy : public Weapon {
public:
	LaserEnemy();						// Initializes the variables
	~LaserEnemy();						// Destructor

	virtual void movement();			// Moves the laser
	void render();						// Shows the laser on the screen
	virtual void spawn(int x, int y, SDL_Rect collider);	// Spawn the object at the dimensions provided
	SDL_Rect getELaserCollider();

    virtual void spawn(int x, int y) {
        setX(x - 20);
        setY(y + 30);
        setVelX(-getVelocity());	// Minus value as travelling right to left
        setVelY(0);
    }

private:
	SDL_Rect mELaserCollider;
};

#endif

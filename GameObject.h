/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include <iostream>

class GameObject {
public:
	GameObject();
	~GameObject();				// Deconstructor

	virtual void spawn();
	virtual void spawn(int x, int y);
	void spawn(int x, int y, int vx);								// spawn with coords & velocity
	void spawn(int x, int y, int vx, int vy);
	void spawn(int x, int y, int vx, SDL_Rect collider);
	void spawn(int x, int y, int vx, int vy, SDL_Rect collider);
	virtual void movement();

	int getX();					// Get GameObject X coord
	int getY();					// Get GameObject Y coord
	int getVelX();
	int getVelY();
	int getVelocity();
	bool getAlive();
	int getScore();
	int getWidth();
	int getHeight();

	void setX(int x);			// Set GameObject X coord
	void setY(int y);			// Set GameObject Y coord
	void setVelX(int x);
	void setVelY(int y);
	void setVelocity(int v);
	void setAlive(bool alive);
	void setWidth(int w);		// set the objects width
	void setHeight(int h);		// set the objects height
	void setScore(int s);

	SDL_Rect getCollider();
	void setColliderWidth(int w);
	void setColliderHeight(int h);
	void setColliderX(int x);
	void setColliderY(int y);

private:
	// GameObject Variables
	int m_health;					// Value between 0 and 160
	int m_speed;					// Value between 1 and 4
	int m_x, m_y;					// GameObject coords
	int m_xVel, m_yVel, m_Velocity;	// Velocity
	int m_Width, m_Height;			// Dimensions
	bool m_Alive;					// Is the weapon active on screen
	SDL_Rect mCollider;
	int m_Score;					// Score value for killing or collecting an object
};

#endif
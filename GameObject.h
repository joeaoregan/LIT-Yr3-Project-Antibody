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
	~GameObject();												// Deconstructor

	// Spawn
	virtual void spawn();
	virtual void spawn(int x, int y);
	void spawn(int x, int y, int vx);							// spawn with coords & velocity
	void spawn(int x, int y, int vx, int vy);
	void spawn(int x, int y, int vx, SDL_Rect collider);
	void spawn(int x, int y, int vx, int vy, SDL_Rect collider);

	// Movement
	virtual void movement();

	// Get Variables
	int getX();					// Get GameObject X coord
	int getY();					// Get GameObject Y coord
	int getVelX();
	int getVelY();
	int getVelocity();
	bool getAlive();
	int getScore();
	int getWidth();
	int getHeight();
	std::string getName();
	int getHealth();
	int getMaxHealth();
	int getNumLives();

	// Set Variables
	void setX(int x);			// Set GameObject X coord
	void setY(int y);			// Set GameObject Y coord
	void setVelX(int x);
	void setVelY(int y);
	void setVelocity(int v);
	void setAlive(bool alive);
	void setWidth(int w);		// set the objects width
	void setHeight(int h);		// set the objects height
	void setScore(int s);
	void setName(std::string name);
	void setHealth(int health);			// set the health
	void setNumLives(int n);

	// Collider
	SDL_Rect getCollider();
	void setCollider(SDL_Rect collider);	// 2017/01/19 Added as Sean keeps doing dumb things with the colliders
	void setColliderWidth(int w);
	void setColliderHeight(int h);
	void setColliderX(int x);
	void setColliderY(int y);

	// Texture
	LTexture getTexture();
	void setTexture(LTexture *texture);
	void render(LTexture &texture, SDL_Renderer *rend, int degrees = 0);						// Shows the laser on the screen 2017/01/22 Added Texture and renderer

private:
	// GameObject Variables
	std::string m_Name;				// Name of the object
	int m_Health;					// Value between 0 and 100
	int m_x, m_y;					// GameObject coords
	int m_xVel, m_yVel, m_Velocity;	// Velocity
	int m_Width, m_Height;			// Dimensions
	bool m_Alive;					// Is the GameObject active on screen, return true if its health is greater than 0
	SDL_Rect mCollider;
	int m_Score;					// Score value for killing or collecting an object
	int m_NumLives;

	LTexture *mTexture;				// Texture to be used for game object
};

#endif



//int m_Speed;					// Value between 1 and 4


// global functions friends of the GameObjects class
//friend std::ostream& operator<<(std::ostream& os, const GameObject& aGameObject);

//GameObject(int damage = 3);			// Constructor with default value of 3 for damage

//std::string m_typeID;				// GameObject name
//int m_Damage;						// Damage to reduce health after an object moves
//int m_direction;					// CA2 - set the objects direction

//void draw();						// print to the screen the typeID and its x and y coords
//virtual void update();				// virtual function
//void info();						// print all info relating to the object


// Indicate where the border has been impacted
//int reboundX = 0, reboundY = 0;		// Store impact point, to highlight
//int getImpactX() const;				// Get the x coord of impact object
//int getImpactY() const;				// Get the y coord of impact object
//void setImpactX(int x);				// Set and reset objects impact x coord
//void setImpactY(int y);				// Set and reset objects impact y coord

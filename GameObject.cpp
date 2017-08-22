#include "GameObject.h"

#define MAX_HEALTH 100

// Constructor
//GameObject::GameObject(int damage) :	// Constructor has default value for damage of 3
//	m_Damage(damage)
//{}
GameObject::GameObject() {
	m_x = 0;
	m_y = 0;
	m_xVel = 0;
	m_yVel = 0;
}
// Deconstructors
GameObject::~GameObject() {
	//std::cout << "GameObject deconstructor" << std::endl;
}

// Render the Game Objects to the screen
void GameObject::render(LTexture &texture, SDL_Renderer *rend, int degrees) {
	texture.render(getX(), getY(), rend, NULL, degrees, NULL, SDL_FLIP_NONE);
}

void GameObject::render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &currentframe, int frames) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend, currentClip);

	++currentframe;								// Go to next frame

	if (currentframe >= frames * 10) {	// Cycle animation
		currentframe = 0;
	}
}

int GameObject::getStartTime() { return m_StartTime; }
int GameObject::getEndTime() { return m_EndTime; }
void GameObject::setStartTime(int t) { m_StartTime = t; }
void GameObject::setEndTime(int t) { m_EndTime = t; }

LTexture GameObject::getTexture() {
	return m_Texture;
}
void GameObject::setTexture(LTexture texture) {
	m_Texture = texture;
}

void GameObject::spawn(int x, int y, int vx, int vy) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
	setAlive(true);
}

void GameObject::spawn(int x, int y, int vx, SDL_Rect collider) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vx;	// 2017-01-10 JOE: use same velocity for x and y
	m_Collider = collider;
}

void GameObject::spawn(int x, int y, int vx, int vy, SDL_Rect collider, int type) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
	m_Collider = collider;
	m_Type = type;
	setAlive(true);
}

void GameObject::movement() {
	m_x += m_xVel;
	//m_y += m_yVel;

	setColliderX(getX());
	setColliderY(getY());

	// Destroy Game Object moving off screen on Y axis
	if (getY() < 40) setAlive(false);								// Once it reaches the pink border
	else if (getY() > (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	else setAlive(true);

	// Destroy Game Object moving off screen on X axis
	if ((getX() > SCREEN_WIDTH && getVelX() > 0)) setAlive(false);	// 2017/02/08 Need to check if velocity is negative, or power ups & blood cells don't appear on screen
	else if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}

// Getter and Setter methods
int GameObject::getMaxHealth() {
	return MAX_HEALTH;
}

void GameObject::setHealth(int h) {
	if (h < 0) {
		m_Health = 0;				// If health is less than 0 set 0
		setAlive(false);			// set the Game object as not alive
	}
	else if (h > 100)
		m_Health = 100;
	else
		m_Health = h;
}
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

void GameObject::spawn() {
	m_x = 0;
	m_y = 0;
	m_xVel = 0;
	m_yVel = 0;
}
void GameObject::spawn(int x, int y) {
	m_x = x;
	m_y = y;
	m_xVel = 0;
	m_yVel = 0;
}
void GameObject::spawn(int x, int y, int vx) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vx;	// 2017-01-10 JOE: use same velocity for x and y
}

void GameObject::spawn(int x, int y, int vx, int vy) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
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
}

void GameObject::movement() {
	m_x += m_xVel;
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
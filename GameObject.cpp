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

// Getter and Setter methods
int GameObject::getX() {
	return m_x;
}
int GameObject::getY() {
	return m_y;
}

int GameObject::getVelX() {
	return m_xVel;
}
int GameObject::getVelY() {
	return m_yVel;
}
int GameObject::getVelocity() {
	return m_Velocity;
}

bool GameObject::getAlive() {
	return m_Alive;
}
int GameObject::getScore() {
	return m_Score;
}
int GameObject::getWidth() {
	return m_Width;					// return the objects width
}
int GameObject::getHeight() {
	return m_Height;				// return the objects height
}
std::string GameObject::getName() {
	return m_Name;
}
int GameObject::getHealth() {
	return m_Health;
}
int GameObject::getMaxHealth() {
	return MAX_HEALTH;
}
int GameObject::getNumLives() {
	return m_NumLives;
}

void GameObject::setX(int x) {
	m_x = x;
}

void GameObject::setY(int y) {
	m_y = y;
}

void GameObject::setVelX(int x) {
	m_xVel = x;
}
void GameObject::setVelY(int y) {
	m_yVel = y;
}
void GameObject::setVelocity(int v) {
	m_Velocity = v;
}
void GameObject::setAlive(bool alive) {
	m_Alive = alive;
}
void GameObject::setScore(int score) {
	m_Score = score;
}
void GameObject::setWidth(int w) {
	m_Width = w;					// set the objects width
}
void GameObject::setHeight(int h) {
	m_Height = h;					// set the objects width
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
void GameObject::setNumLives(int n) {
	m_NumLives = n;
}

//SDL_Rect GameObject::getCollider(){
//	return m_Collider;
//}
void GameObject::setCollider(SDL_Rect collider) {
	m_Collider = collider;
}

void GameObject::setColliderWidth(int w){
	m_Collider.w = w;
}

void GameObject::setColliderHeight(int h){
	m_Collider.h = h;
}

void GameObject::setColliderX(int x){
	m_Collider.x = x;
}

void GameObject::setColliderY(int y){
	m_Collider.y = y;
}

void GameObject::setName(std::string name) {
	m_Name = name;
}



// 2017/01/25
int GameObject::getType() {
	return m_Type;
}

void GameObject::setType(int t) {
	m_Type = t;
}

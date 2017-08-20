#include "GameObject.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

void GameObject::movement() {
	m_x += m_xVel;
}

//void GameObject::render() {

//}

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
int GameObject::getWidth() {
	return m_Width;					// return the objects width
}
int GameObject::getHeight() {
	return m_Height;				// return the objects height
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
void GameObject::setWidth(int w) {
	m_Width = w;					// set the objects width
}
void GameObject::setHeight(int h) {
	m_Height = h;					// set the objects width
}

void GameObject::movement(SDL_Rect& square, Circle& circle) {
	m_x += m_xVel;
	shiftColliders();

	//If the dot collided or went too far to the left or right
	//if ((m_x - mCollider.r < 0) || (m_x + mCollider.r > SCREEN_WIDTH) || checkCollision(mCollider, square) || checkCollision(mCollider, circle)) {
	if (checkCollision(mColliderCirc, square) || checkCollision(mColliderCirc, circle)) {
		m_x -= m_xVel;	//Move back
						//std::cout << "collision left / right" << std::endl;
		shiftColliders();
	}

	//Move the dot up or down
	m_y += m_yVel;
	shiftColliders();

	//If the dot collided or went too far up or down
	if ((m_y - mColliderCirc.r < 40) || (m_y + mColliderCirc.r > SCREEN_HEIGHT - 40) || checkCollision(mColliderCirc, square) || checkCollision(mColliderCirc, circle)) {
		//if ((m_y - mCollider.r < 0) || (m_y + mCollider.r > SCREEN_HEIGHT) || checkCollision(mCollider, square) || checkCollision(mCollider, circle)) {
		//if (checkCollision(mCollider, square) || checkCollision(mCollider, circle)) {		
		m_y -= m_yVel;	//Move back
						//std::cout << "collision up / down" << std::endl;
		shiftColliders();
	}
}

bool GameObject::checkCollision(Circle& a, Circle& b) {
int totalRadiusSquared = a.r + b.r;
totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

//If the distance between the centers of the circles is less than the sum of their radii
if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) {
std::cout << "Collision with circle" << std::endl;
return true;	//The circles have collided
}

//If not
return false;
}

bool GameObject::checkCollision(Circle& a, SDL_Rect& b) {
int cX, cY; // Closest point on collision box

//Find closest x offset
if (a.x < b.x){
cX = b.x;
}
else if (a.x > b.x + b.w) {
cX = b.x + b.w;
}
else {
cX = a.x;
}

//Find closest y offset
if (a.y < b.y) {
cY = b.y;
}
else if (a.y > b.y + b.h) {
cY = b.y + b.h;
}
else {
cY = a.y;
}

//If the closest point is inside the circle
if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)	{// distance calculation without the square root
std::cout << "Collision with box" << std::endl;
return true;	// This box and the circle have collided
}

return false;		// If the shapes have not collided
}

double GameObject::distanceSquared(int x1, int y1, int x2, int y2) {
int deltaX = x2 - x1;
int deltaY = y2 - y1;
return deltaX*deltaX + deltaY*deltaY;
}

GameObject::Circle GameObject::getCircleCollider() {
return mColliderCirc;
}

void GameObject::shiftColliders() {
//Align collider to center of dot
mColliderCirc.x = getX();
mColliderCirc.y = getY();
}

void GameObject::setCollider(Circle c) {
mColliderCirc = c;
}

void GameObject::setColliderR(int r) {
mColliderCirc.r = r;
}



SDL_Rect GameObject::getCollider() {
	return mCollider;
}
void GameObject::setColliderX(int x) {
	mCollider.x = x;
}// end setX

 // set Y
void GameObject::setColliderY(int y) {
	mCollider.y = y;
}// end setY


void GameObject::setColliderWidth(int w) {
	mCollider.w = w;
}
void GameObject::setColliderHeight(int h) {
	mCollider.h = h;
}
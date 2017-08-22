#include "EnemyVirus.h"

EnemyVirus::EnemyVirus() {
	setScore(15);						// Value for killing object

	setWidth(75);
	setHeight(75);

	setVelocity(3);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}
EnemyVirus::EnemyVirus(int type, float time) {
	if(type == 0)
		setScore(10);						// Value for killing object
	else if (type == 1)
		setScore(15);

	setWidth(75);
	setHeight(75);

	setVelocity(3);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setType(type);						// 2017-01-25 type of game object
	setTimer(time);
}

EnemyVirus::~EnemyVirus() {

}

void EnemyVirus::movement(int shipX, int shipY) {
	GameObject::movement();

	if (getX() > shipX) {
		if (getY() - shipY >= 0) {
			if (getY() - shipY >= getVelocity())
				setY(getY() - getVelocity());			// No need to make smaller movements at the moment, as velocity is v.low anyway
		}
		else if (getY() - shipY < 0) {
			setY(getY() + getVelocity());
		}
	}

	setColliderX(getX());
	setColliderY(getY());

	// destroy enemy ship once it is offscreen
	if (getX() < -getWidth()) setAlive(false);
	else setAlive(true);
}

void EnemyVirus::render(LTexture &texture, SDL_Renderer *rend) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend);
}


// Enemies render function with sprite animation
void EnemyVirus::render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &frame) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend, currentClip);

	++frame;								// Go to next frame

	if (frame >= 6 * 10) {	// Cycle animation
		frame = 0;
	}
}

float EnemyVirus::getTimer() {
	return bombTimer;
}

void EnemyVirus::setTimer(int t) {
	bombTimer = t;
}
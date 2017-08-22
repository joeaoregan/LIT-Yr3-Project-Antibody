#include "EnemyVirus.h"

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

	if (getX() < SCREEN_WIDTH - getWidth()) {				// If the object is on the screen
		if (getX() > shipX) {
			if (getY() - shipY >= 0) {
				if (getY() - shipY >= getVelocity())
					setY(getY() - getVelocity());			// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getY() - shipY < 0) {
				setY(getY() + getVelocity());
			}
		}
	}
}
#include "EnemyVirus.h"

EnemyVirus::EnemyVirus(int type, float time) {
	setType(ENEMY_OBJECT);
	setDamage(20);

	setWidth(60);
	setHeight(60);

	setVelocity(3);

	if (type == VIRUS_GREEN) {
		setScore(10);						// Value for killing object
		setName("Green Virus");
	}
	else if (type == VIRUS_ORANGE) {
		setScore(15);
		setName("Exploding Orange Virus");
	}
	else if (type == VIRUS_BLUE) {
		setScore(20);
		setName("Blue Virus");
	}
	else if (getType() == SMALL_VIRUS) {
		setScore(5);
		setWidth(45);
		setHeight(45);
		setVelocity(1);
		if (type == VIRUS_SMALL_GREEN) setName("Small Green Virus");
		else if (type == VIRUS_SMALL_ORANGE) setName("Small Orange Virus");
		else if (type == VIRUS_SMALL_BLUE) setName("Small Blue Virus");
	}

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setSubType(type);						// 2017-01-25 type of game object
	setTimer(time);

	setTimerTracker(0.0);

	setFrames(0);
}

EnemyVirus::~EnemyVirus() {

}

void EnemyVirus::movement(int shipX, int shipY) {
	if (getType() != SMALL_VIRUS && getX() < SCREEN_WIDTH - getWidth() && getX() > shipX) {
			if (getY() - shipY >= 0) {
				if (getY() - shipY >= getVelocity())
					setY(getY() - getVelocity());							// No need to make smaller movements at the moment, as velocity is v.low anyway
			}
			else if (getY() - shipY < 0) {
				setY(getY() + getVelocity());
			}

			setColliderX(getX() + 6);
			setColliderY(getY() + 10);

			setX(getX() + getVelX());
			GameObject::destroy();		// Destroy the object when it moves off screen
		}	
	else
		GameObject::movement();			// Normal right to left movement
}
/*
	2017/02/19 Added random speed for Enemy Virus objects
				Changed information message to warn player when all types of virus are approaching
				Changed white blood cell movement to to destroy blue virus objects when they're split in two
				Added different coloured explosions for Enemy Virus
				Virus can now be cut with saw, splitting in two
	2017/02/10 Started work on blue virus, with rotating satellite object ...I hate trigonometry!!
				Satellite weapon fires with .5 seconds left on timer
				Fixed score for blue virus
	2017/02/09 Fixed virus moving towards nearest player
				Made virus animations independent, so they don't all render same frame at the same time
	2017/01/25 Added check for if the type of virus is newer Orange Exploding Virus or older Green Virus
				Added alert message to notify player Exploding Orange Virus is approaching 
				Added functionality so Orange Virus explodes after colliding with player
	2017/01/18 Fixed virus movement to move towards the nearest player not just player 1
	2017/01/10 updated movement() function so Virus moves towards player on Y coord
				Added spawn functions to spawn enemies and obstacles at random coords & distances apart
*/
/* 
	ENEMY VIRUS:

	There are three types of virus Green, Orange, and Blue. The Green Virus can move towards the players 
	Y position on the screen, while the player is in front of them as they move right to left. The other 
	two virus types have the same movement. Orange Viruses have a countdown timer, and explode sending 
	8 fireballs in 8 different directions. The Blue Virus type has a satellite object that fires when its
	timer runs out, and can spawn another virus when the timer resets. Virus objects can be split in two
	by the players Saw and Ninja Star weapons. When they are split into a smaller size, the viruses can 
	by terminated by the White Blood Cells which quickly move towards them to clean them up.
*/
#include "EnemyVirus.h"

EnemyVirus::EnemyVirus(int subType, float time) {
	setType(ENEMY_OBJECT);
	setDamage(20);

	setWidth(60);
	setHeight(60);

	setVelocity(3);

	if (subType == VIRUS_GREEN) {
		setScore(10);						// Value for killing object
		setName("Green Virus");
	}
	else if (subType == VIRUS_ORANGE) {
		setScore(15);
		setName("Exploding Orange Virus");
	}
	else if (subType == VIRUS_BLUE) {
		setScore(20);
		setName("Blue Virus");
	}
	else if (getType() == SMALL_VIRUS) {
		setScore(5);
		setWidth(45);
		setHeight(45);
		setVelocity(1);
		if (subType == VIRUS_SMALL_GREEN) setName("Small Green Virus");
		else if (subType == VIRUS_SMALL_ORANGE) setName("Small Orange Virus");
		else if (subType == VIRUS_SMALL_BLUE) setName("Small Blue Virus");
	}

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setSubType(subType);						// 2017-01-25 type of game object
	setTimer(time);

	setTimerTracker(0.0);

	setFrames(0);
}

EnemyVirus::~EnemyVirus() {

}

// 2017/03/03 Stalker movement, for moving towards player
void EnemyVirus::moveStalker(int shipX, int shipY) {
	if (getType() != SMALL_VIRUS &&  getX() > shipX) {					// 2017/03/22 Moved from Game class
		if (getX() > SCREEN_WIDTH && getX() < SCREEN_WIDTH + 10) {		// When a virus is within 10 pixels of appearing on screen
			Game::Instance()->infoMessage(getName() + " Approaching");	// 2017/02/19 Added information message indicates virus is approaching
		}

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
		GameObject::move();			// Normal right to left movement
}
/*	---------------------------------------------------------------------------------------------------------------------
		- Name:					EnemyVirus.cpp
		- Description:			cpp file for the EnemyVirus object, containing creation and movement functionality
		- Information:			There are three types of virus Green, Orange, and Blue. The Green Virus can move towards the players
								Y position on the screen, while the player is in front of them as they move right to left. The other
								two virus types have the same movement. Orange Viruses have a countdown timer, and explode sending
								8 fireballs in 8 different directions. The Blue Virus type has a satellite object that fires when its
								timer runs out, and can spawn another virus when the timer resets. Virus objects can be split in two
								by the players Saw and Ninja Star weapons. When they are split into a smaller size, the viruses can
								by terminated by the White Blood Cells which quickly move towards them to clean them up.

		- Log:
			2017/03/22			Added animation sprite sheets for viruses to Texture map
			2017/02/19			Added random speed for Enemy Virus objects
								Changed information message to warn player when all types of virus are approaching
								Changed white blood cell movement to to destroy blue virus objects when they're split in two
								Added different coloured explosions for Enemy Virus
								Virus can now be cut with saw, splitting in two
			2017/02/10			Started work on blue virus, with rotating satellite object ...I hate trigonometry!!
								Satellite weapon fires with .5 seconds left on timer
								Fixed score for blue virus
			2017/02/09			Fixed virus moving towards nearest player
								Made virus animations independent, so they don't all render same frame at the same time
			2017/01/25			Added check for if the type of virus is newer Orange Exploding Virus or older Green Virus
								Added alert message to notify player Exploding Orange Virus is approaching
								Added functionality so Orange Virus explodes after colliding with player
			2017/01/18			Fixed virus movement to move towards the nearest player not just player 1
			2017/01/10			updated movement() function so Virus moves towards player on Y coord
								Added spawn functions to spawn enemies and obstacles at random coords & distances apart
----------------------------------------------------------------------------------------------------------------------*/
#include "EnemyVirus.h"

// Name: EnemyVirus()
// Role: Contructor for EnemyVirus Objects, initializes variables and assigns a score & name depending on type.
EnemyVirus::EnemyVirus(int subType, float time) {
	setType(ENEMY_OBJECT);
	setDamage(20);

	setWidth(75);
	setHeight(75);

	setColliderWidth(60);
	setColliderHeight(60);

	setVelocity(3);

	if (subType == VIRUS_GREEN) {
		setScore(10);								// Value for killing object
		setName("Green Virus");
		setTextureID("greenVirusID");				// 2017/03/22 Move texture to Texture Map
	}
	else if (subType == VIRUS_ORANGE) {
		setScore(15);
		setName("Exploding Orange Virus");
		setTextureID("orangeVirusID");				// 2017/03/22 Move texture to Texture Map
	}
	else if (subType == VIRUS_BLUE) {
		setScore(20);
		setName("Blue Virus");
		setTextureID("blueVirusID");				// 2017/03/22 Move texture to Texture Map
	}
	else if (getType() == SMALL_VIRUS) {
		setScore(5);
		setWidth(45);
		setHeight(45);
		setVelocity(1);

		if (subType == VIRUS_SMALL_GREEN) {
			setName("Small Green Virus");
			setTextureID("greenVirusSmallID");		// 2017/03/22 Move texture to Texture Map
		}
		else if (subType == VIRUS_SMALL_ORANGE) {
			setName("Small Orange Virus");
			setTextureID("orangeVirusSmallID");		// 2017/03/22 Move texture to Texture Map
		}
		else if (subType == VIRUS_SMALL_BLUE) {
			setName("Small Blue Virus");
			setTextureID("blueVirusSmallID");		// 2017/03/22 Move texture to Texture Map
		}
	}

	setSubType(subType);						// 2017-01-25 type of game object
	setTimer(time);

	setTimerTracker(0.0);

	// Animation Stuff
	setFrames(4);					// Frames needed for animation
	setAnimCount(0);
	setCurrentFrame(0);				// Start at 1st frame of animation
	setAlpha(255);
}

// Name: ~EnemyVirus()
// Role: Destructor for enemy virus objects, removing them from memory
EnemyVirus::~EnemyVirus() {

}

// Name: moveStalker()
// Role: Move the virus towards the player, tracks player movement and moves towards the player while in front of them.
// 2017/03/03 Stalker movement, for moving towards player
void EnemyVirus::move(int shipX, int shipY) {
	if (getType() != SMALL_VIRUS &&  getX() > shipX) {
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
		GameObject::destroy();											// Destroy the object when it moves off screen
	}
	else
		GameObject::move();													// Normal right to left movement

	// Increment Animation Frame
	setAnimCount(getAnimCount() + 1);
	setCurrentFrame((getAnimCount() / 10) % 4);
	if (getCurrentFrame() == getNumFrames()) setAnimCount(0);
}
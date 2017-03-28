/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					EnemyVirus.h
	- Description:			Header file for the EnemyVirus object which is a sub-type of Enemy
	- Information:			Declares functions and variables for creating and updating the EnemyVirus Object

	- Log:
		2017/01/25		Added check for if the type of virus is newer Orange Exploding Virus or older Green Virus
						Added alert message to notify player Exploding Orange Virus is approaching to Game class
						Added functionality so Orange Virus explodes after colliding with player to Game class
						Added higher score for Orange Virus
		2017/02/21		Added check so only Ninja Stars and Saaws split viruses
		2017/01/10		updated movement() function so Virus moves towards player on Y coord
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"
#include "WeaponEnLaser.h"

class EnemyVirus : public Enemy {
public:
	float bombTimer;										// Timer for exploding viruses

	EnemyVirus(int type = VIRUS_GREEN, float time = 0);		// Initializes the variables
	~EnemyVirus();											// Destructor
	
	virtual void move(int playerX, int playerY);			// Tracker movement for Virus, moving towards the nearest player
	virtual void destroy() {};
	virtual void render() {
		GameObject::renderAnimation();
	};
};

#endif
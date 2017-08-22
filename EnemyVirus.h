/*
	2017/01/25 Added check for if the type of virus is newer Orange Exploding Virus or older Green Virus
				Added alert message to notify player Exploding Orange Virus is approaching to Game class
				Added functionality so Orange Virus explodes after colliding with player to Game class
				Added higher score for Orange Virus
	2017/02/21 Added check so only Ninja Stars and Saaws split viruses
	2017/01/10 updated movement() function so Virus moves towards player on Y coord
*/

#ifndef ENEMY_VIRUS_H
#define ENEMY_VIRUS_H

#include "Enemy.h"
#include "Player.h"
#include "WeaponEnLaser.h"

//enum virusType { VIRUS_GREEN, VIRUS_ORANGE, VIRUS_BLUE };

class EnemyVirus : public Enemy {
public:
	float bombTimer;

	EnemyVirus(int type = VIRUS_GREEN, float time = 0);							// Initializes the variables
	~EnemyVirus();							// Destructor
	
	virtual void movement(int playerX, int playerY);
};

#endif
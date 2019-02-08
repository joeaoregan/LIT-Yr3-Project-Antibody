/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponEnLaser.h
	- Description:			Header file for the Weapon Enemy Laser class.
	- Information:			Contains all function definitions and variables for the Enemy Weapon Laser class.
							This class handles enemy weapon objects, first starting with Enemy Ship lasers, then adding Orange Virus projectiles,
							and then adding the satellite projectile for the Blue Virus.

							WeaponEnLaser (LaserEnemy.cpp) is where all the implementations of the function definitions in LaserEnemy.h reside.
	- Log:
		2017/03/04		Moved smaller class files functionality into their headers
						Set a game object texture ID variable, Player and Enemy lasers now render based on their unique texture ID
		2017/02/18		Added enemy laser to game objects list
						Set types and sub-types for objects on game objects list
		2017/01/10		Added enemy laser projectile, velocity is a minus value as it is travelling right to left
		2017/01/09		Added Laser For Enemy ship basd on Seans Player Laser functionality
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef LASER_ENEMY_H
#define LASER_ENEMY_H

#include "Weapon.h"

//enum EnemyLaserTypes { ENEMY_SHIP_LASER, VIRUS_FIREBALL, BLUE_VIRUS_BULLET };

class WeaponEnLaser : public Weapon {
public:
	// Enemy Laser Constructor - Initializes the variables
	WeaponEnLaser(int subType = ENEMY_SHIP_LASER, int rotateCenter = 0) {
		//std::cout << "Enemy Laser constuctor called.\n";
		setVelocity(-15);
		setVelX(-15);
		//setVelY(0);
		setAlive(true);

		setType(ENEMY_WEAPON);					// Type of object (enemy weapon)
		setSubType(subType);					// Subtype of weapon

		// Set the name, damage and dimensions, depending on the sub-type of Enemy
		if (subType == ENEMY_SHIP_LASER) {
			setName("Enemy Laser");
			setDamage(5);						// 2017/02/21 Player health is decreased by 5 health points
			setWidth(50);
			setHeight(5);
			setTextureID("blueLaserID");
		}
		else if (subType == VIRUS_FIREBALL) {
			setName("Virus Fireball");
			setDamage(10);						// 2017/02/21 Player health is decreased by 5 health points
			setWidth(25);
			setHeight(25);
			setTextureID("fireballID");
		}
		else if (subType == BLUE_VIRUS_BULLET) {
			setProjectileActive(false);
			setName("Blue Virus Bullet");
			setDamage(15);						// 2017/02/21 Player health is decreased by 5 health points
			setWidth(25);
			setHeight(25);
			setTextureID("satelliteID");
			//std::cout << "BLUE VIRUS BULLET CONSTRUCTOR" << std::endl;
		}

		if (getSubType() == ENEMY_SHIP_LASER) {
			setColliderWidth(getWidth());
			setColliderHeight(getHeight());
		}
		// Type 1 = orange fireball
		else {								
			setColliderWidth(25);
			setColliderHeight(25);
		}

		setScore(0);						// 2017/01/20 Points to deduct from player after collision with this object

		rotateCounter = 0;
		satelliteObjectOrbiting = false;	// Blue virus projectile is orbiting or not
	};

	// Enemy laser Destructor
	~WeaponEnLaser() {
		std::cout << "Enemy Laser destructor called.\n";
	};			
	
	// Moves the Enemy laser
	virtual void move() {
		GameObject::move();
	};

	virtual void destroy() {};

	/*
		2017/03/18 Render function
	*/
	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen

		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
	};

	int centerX, centerY;		// center for rotation
};

#endif#pragma once

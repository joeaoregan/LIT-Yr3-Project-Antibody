/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Name:					Explosion.h
	- Description:			This class handles explosions for collisions between objects
	- Information:			Different explosions are rendered for blood cells, the different types of objects, and player and enemy ship collisions
							Explosions are independently animated, so they don't show the same frame for every explosion appearing on screen.
	- Log:

	2017/03/04				Moved smaller class files functionality into their headers
	2017/02/19				Added separate explosions for blood cells to look more like a blood splatter
	2017/02/18				Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen
	2017/02/15				Added Explosions to list of game objects
	2017/02/09				Made Explosion animations independent, so they don't all render same frame at the same time
	2017/01/25				Added spawnExplosion() function for creating explosions when lasers collide with Enemy Ships and Virus
							Added explosion handling class Explosion.h
	2017/01/20				Added spawnExplosion() functions for creating explosions when objects collide

------------------------------------------------------------------------------------------------------------------------------------------------------- */
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"

class Explosion : public GameObject {
public:
	// Constructor - Initializes the variables
	Explosion(int x, int y, int subType = 0) {
		setType(EXPLOSION);
		setSubType(subType);

		setDamage(5);

		setX(x);
		setY(y);

		setAlive(true);
		
		// 2017/03/22 Move Alpha Value settings from Game class
		if (subType == FIRE_EXPLOSION) {
			setAlpha(200);
			setTextureID("explosionID");
			setWidth(96);
			setHeight(96);
			setFrames(12);
		}
		else if (subType == BLOOD_EXPLOSION) {
			setAlpha(100);
			setWidth(128);
			setHeight(128);
			setTextureID("eplosionBloodID");
			setFrames(16);
		}
		else if (subType == GREEN_VIRUS_EXPLOSION) {
			setAlpha(125);
			setWidth(128);
			setHeight(128);
			setTextureID("explosionGreenID");
			setFrames(16);
		}
		else if (subType == ORANGE_VIRUS_EXPLOSION) {
			setAlpha(125);
			setWidth(128);
			setHeight(128);
			setTextureID("explosionOrangeID");
			setFrames(16);
		}
		else if (subType == BLUE_VIRUS_EXPLOSION) {
			setAlpha(125);
			setWidth(128);
			setHeight(128);
			setTextureID("explosionBlueID");
			setFrames(16);
		}

		// Animation Stuff
		setAnimCount(0);
		setCurrentFrame(0);								// Start at 1st frame of animation
		setAnimRow(0);									// Current row in the sprite sheet
	};							

	// Destructor
	~Explosion() {};

	//int frameCount;

	// Inherited Movement function (Enemy ships only move right to left)
	virtual void move(int x, int y) {
		//GameObject::move();											// 2017/03/24 Explosions do not need to move

		setAnimCount(getAnimCount() + 1);								// Counter used to set the frames
		setCurrentFrame(getCurrentFrame() + (getAnimCount() / 20));		// Set the current animation frame, base on the counter value
		if (getCurrentFrame() == getNumFrames()) setAlive(false);		// End the animation once it has rendered all the frames

		destroy();														// 2017/03/24 Destroy the exlposion if off screen
		/*
		setCurrentFrame(int(SDL_GetTicks() / (1000 / 3) % getFrames()));	// Set the current animation frame
		if(SDL_GetTicks() / 1000
		setCurrentFrame(getCurrentFrame() + 1);	// Set the current animation frame
		frameCount++;
		setCurrentFrame(getCurrentFrame() + int(frameCount / 100));
		*/
	};

	virtual void destroy() {
		GameObject::destroy();											// Use Game Objects destroy function
	};

	virtual void render() {
		GameObject::renderAnimation();									// Use Game Objects render function
	};	
};

#endif
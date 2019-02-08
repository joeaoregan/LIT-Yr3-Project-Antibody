/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					ScrollingBackground.h
		- Description:			This class renders and scrolls the background images
		- Information:			The background is treated as a game object, and can be moved and rendered with the 
								rest of the objects in the game

		- Log:
			2017/03/21			Added ScrollingBackground class to handle background scrolling and rendering
------------------------------------------------------------------------------------------------------------------------------------------------------- */

#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "GameObject.h"
#include "Game.h"		// Game Instance
#include "_TestData.h"	// BACKGROUND_SCROLL_TIMES + BACKGROUND_SCROLL_SPEED

class ScrollingBackground : public GameObject {
public:
	ScrollingBackground() {
		setType(BACKGROUND);
		setName("Scrolling Background");
		setWidth(1280);
		setHeight(600);
		setX(0);
		setY(0);
		setTextureID("startBG");		// 2017/03/18 Added saw texture to texture map

		std::cout << "Background Constructor Called" << std::endl;
		setAlive(true);
	};
	~ScrollingBackground() {};

	int scrollingOffset = 0;
	//int backgroundLoopCounter;

	void loadBackgroundStuff() {};

	/*
		Move the Background image depending on the scroll speed set in _TestData.h BACKGROUND_SCROLL_SPEED
		and also the number of times the image is to scroll BACKGROUND_SCROLL_TIMES
		The number of times the background is looped is also counted
		The Enemy boss spawns once the background (or distance on map) has looped the required times
	*/
	virtual void move(int x = 0, int y = 0) {
		int bgCounter = Game::Instance()->backgroundLoopCounter;

		if (Game::Instance()->backgroundLoopCounter <= BACKGROUND_SCROLL_TIMES) scrollingOffset -= BACKGROUND_SCROLL_SPEED;	// Scroll for a fixed number of times
		if (scrollingOffset < -SCREEN_WIDTH) {
			scrollingOffset = 0;													// update the scrolling background

			Game::Instance()->backgroundLoopCounter++;								// count the number of times the background has looped
			std::cout << "Background has looped " << Game::Instance()->backgroundLoopCounter << " times" << std::endl;
		}

	};

	/*
		Clear media for ScrollingBackground from memory
	*/
	virtual void destroy() {
		scrollingOffset = 0;	// Reset scrollingOffset

		// Background images to free when not in level state

		//{ "Art/bgBegin720a.png", "startBG", "Starting Background" },
		//{ "Art/Background720.png", "middleBG", "Middle Background" },
		//{ "Art/bgEnd720a.png", "endBG", "End Background" },
		Texture::Instance()->clearFromTextureMap("startBG");	// Clear start background
		Texture::Instance()->clearFromTextureMap("middleBG");	// Clear middle background
		Texture::Instance()->clearFromTextureMap("endBG");		// Clear end background
	};

	/*
		Background scrolling has it's own rendering conditions
		Rendering a one frame to begin the loop, another as the main central loop
		Then it stops on the end background frame, where the player will take on the enemy boss
	*/
	virtual void render() {
		//GameObject::render();
		std::cout << "background render " << std::endl;

		// Render background	
		if (Game::Instance()->backgroundLoopCounter < 1) Texture::Instance()->renderMap("startBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);											// 1st background (and every odd number)
		else if (Game::Instance()->backgroundLoopCounter > BACKGROUND_SCROLL_TIMES) Texture::Instance()->renderMap("endBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);
		else Texture::Instance()->renderMap("middleBG", scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);

		if (Game::Instance()->backgroundLoopCounter < BACKGROUND_SCROLL_TIMES) Texture::Instance()->renderMap("middleBG", scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// 2nd background (and every even number)
		else Texture::Instance()->renderMap("endBG", scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);
	};
};

#endif
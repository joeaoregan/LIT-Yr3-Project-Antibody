/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					FPS.cpp
	- Description:			cpp file for Frames Per Second calculations
	- Information:
		How it works:		Contains all functions for calculating and displaying FPS
							Measure how long each frame takes to render by using SDL_GetTicks()
							Averages out the last couple of values by putting all values in an array
							and working out the average frame rendering time.

	- Link to tutorial:		http://sdl.beuc.net/sdl.wiki/SDL_Average_FPS_Measurement - Ctrl + Click to view page

	- Log:

		2017/01/18			Implemented FPS class and functions to get an accurate measurement of the FPS.
		2017/02/01			Separated FPS to its own class
							Added frames for second class FPS.h
		2017/02/02			Completely separated FPS to its own class
		2017/03/03			FPS is now activated by holding the "F1" key
----------------------------------------------------------------------------------------------------------------------*/

#include <SDL.h>
#include "FPS.h"
#include <string.h>
#include "Game.h"
/*
	This function gets called once on startup.
*/
void FPS::initFPS() {
	// Set all frame times to 0ms.
	memset(frameTimes, 0, sizeof(frameTimes));
	frameCount = 0;
	framesPerSecond = 0;
	frameTimeLast = SDL_GetTicks();
}

/*
	Free the media associated with the FPS class
*/
void FPS::closeFPS() {
	gFPSTextTexture.free();		// Free the frames per second texture
}

/*
	Render the frames per second count to screen
*/
void FPS::renderFPS(std::string fpsText) {
//void FPS::rendFPS(std::string fpsText, SDL_Renderer *rend) {
	gFPSTextTexture.UIText(fpsText);						// Render text - Use a string to render the current FPS to a texture
	gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8);
}

void FPS::updateFPS() {
	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;
	Uint32 i;

	// frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
	// This value rotates back to 0 after it hits FRAME_VALUES.
	frametimesindex = frameCount % FRAME_VALUES;

	getticks = SDL_GetTicks();								// store the current time

	frameTimes[frametimesindex] = getticks - frameTimeLast;	// save the frame time value

	frameTimeLast = getticks;								// save the last frame time for the next fpsthink

	frameCount++;											// increment the frame count

	// Work out the current framerate
	// The code below could be moved into another function if you don't need the value every frame.
	// I've included a test to see if the whole array has been written to or not. This will stop
	// strange values on the first few (FRAME_VALUES) frames.
	if (frameCount < FRAME_VALUES) {
		count = frameCount;
	}
	else {
		count = FRAME_VALUES;
	}

	framesPerSecond = 0;									// add up all the values and divide to get the average frame time.
	for (i = 0; i < count; i++) {
		framesPerSecond += frameTimes[i];
	}

	framesPerSecond /= count;

	framesPerSecond = 1000.f / framesPerSecond;				// now to make it an actual frames per second value...
}
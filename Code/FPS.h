/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					FPS.H
	- Description:			Header for Frames Per Second calculations
	- Information:
		How it works:		Class to declare functions and variables for calculating and displaying FPS
	
	- Link to tutorial:		http://sdl.beuc.net/sdl.wiki/SDL_Average_FPS_Measurement - Ctrl + Click to view page

	- Log:

		2017/01/18			Implemented FPS class and functions to get an accurate measurement of the FPS. 

----------------------------------------------------------------------------------------------------------------------*/

#ifndef FPS_H
#define FPS_H

#include "Texture.h"

#define FRAME_VALUES 10

class FPS {
public:
	Texture gFPSTextTexture;							// Frames Per Second displayed at top of screen

	Uint32 frameTimes[FRAME_VALUES];					// An array to store frame times
	Uint32 frameTimeLast;								// Last calculated SDL_GetTicks
	Uint32 frameCount;									// Total frames rendered

	float framesPerSecond;								// The value that will display the FPS the game is running at

	void initFPS();										// Sets all frame times to 0ms
	void updateFPS();									// Update the frames per second
	void closeFPS();									// Free the media associated with the FPS class

	float getFPS() { return framesPerSecond; }			// Get the frames per second
	void setFPS(float fps) { framesPerSecond = fps; }	// Set the frames per second

	void renderFPS(std::string fpsText);				// Render the frames per second to screen
	//void rendFPS(std::string fpsText, SDL_Renderer *rend);
};

#endif
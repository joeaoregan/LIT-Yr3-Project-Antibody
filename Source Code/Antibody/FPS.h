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
	Texture gFPSTextTexture;			// Frames Per Second displayed at top of screen

	Uint32 frametimes[FRAME_VALUES];	// An array to store frame times
	Uint32 frametimelast;				// Last calculated SDL_GetTicks
	Uint32 framecount;					// Total frames rendered

	float framespersecond;				// The value that will display the FPS the game is running at

	void fpsinit();						// Sets all frame times to 0ms
	void fpsthink();				
	void fpsclose();

	float getFPS();
	void setFPS(float fps);

	void rendFPS(std::string fpsText);
	//void rendFPS(std::string fpsText, SDL_Renderer *rend);
};

#endif
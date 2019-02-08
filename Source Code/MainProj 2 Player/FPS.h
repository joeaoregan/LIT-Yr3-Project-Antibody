/*
	2017/02/27:	User game singleton to access renderer
*/

#ifndef FPS_H
#define FPS_H

#include "Texture.h"

#define FRAME_VALUES 10

class FPS {
public:
	Texture gFPSTextTexture;			// Frames Per Second displayed at top of screen

	// FPS
	Uint32 frametimes[FRAME_VALUES];	// An array to store frame times:
	Uint32 frametimelast;				// Last calculated SDL_GetTicks
	Uint32 framecount;					// total frames rendered

	// FPS
	float framespersecond;				// the value you want

	void fpsinit();
	void fpsthink();
	void fpsclose();

	float getFPS();
	void setFPS(float fps);

	void rendFPS(std::string fpsText);
	//void rendFPS(std::string fpsText, SDL_Renderer *rend);
};

#endif
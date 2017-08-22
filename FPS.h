#ifndef FPS_H
#define FPS_H

#include "FPS.h"
#define FRAME_VALUES 10

class FPS {
public:
	// FPS
	Uint32 frametimes[FRAME_VALUES];	// An array to store frame times:
	Uint32 frametimelast;				// Last calculated SDL_GetTicks
	Uint32 framecount;					// total frames rendered

	void fpsinit();
	void fpsthink();
};

#endif
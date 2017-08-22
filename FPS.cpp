#include <SDL.h>
#include "FPS.h"
#include <string.h>

// 2017/02/01 Separated to its own class

// This function gets called once on startup.
void FPS::fpsinit() {
	// Set all frame times to 0ms.
	memset(frametimes, 0, sizeof(frametimes));
	framecount = 0;
	framespersecond = 0;
	frametimelast = SDL_GetTicks();
}


float FPS::getFPS() { return framespersecond; }
void FPS::setFPS(float fps) { framespersecond = fps; }


void FPS::fpsthink() {
	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;
	Uint32 i;

	// frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
	// This value rotates back to 0 after it hits FRAME_VALUES.
	frametimesindex = framecount % FRAME_VALUES;

	getticks = SDL_GetTicks();	// store the current time

	frametimes[frametimesindex] = getticks - frametimelast;	// save the frame time value

	frametimelast = getticks;	// save the last frame time for the next fpsthink

	framecount++;	// increment the frame count

					// Work out the current framerate

					// The code below could be moved into another function if you don't need the value every frame.

					// I've included a test to see if the whole array has been written to or not. This will stop
					// strange values on the first few (FRAME_VALUES) frames.
	if (framecount < FRAME_VALUES) {
		count = framecount;
	}
	else {
		count = FRAME_VALUES;
	}

	framespersecond = 0;	// add up all the values and divide to get the average frame time.
	for (i = 0; i < count; i++) {
		framespersecond += frametimes[i];
	}

	framespersecond /= count;

	framespersecond = 1000.f / framespersecond;	// now to make it an actual frames per second value...
}
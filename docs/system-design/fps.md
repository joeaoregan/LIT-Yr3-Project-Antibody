# FPS

## Overview (`FPS.h`, `FPS.cpp`)

```text
┌---------------------------┐
|            FPS            |
├---------------------------┤
| +gFPSTextTexture: Texture | - Frames/second texture
| +frameTimes: Uint32       | - Array to store frame times
| +frameTimeLast: Uint32    | - Last calculated SDL_GetTicks
| +frameCount: Uint32       | - Total frames rendered
| +framesPerSecond: float   | - Value displaying FPS game runs at
├---------------------------┤
| +initFPS() : void         | - Sets all frame times to 0ms
| +updateFPS() : void       | - Update the frames per second
| +closeFPS() : void        | - Free media for FPS class
| +getFPS() : float         | - Get the frames per second
| +setFPS() : void          | - Set the frames per second
| +renderFPS() : void       | - Render FPS texture to screen
└---------------------------┘
```

The `FPS` class calculates and displays the real-time frame rate, toggled on and off using the **F1** key.

## Calculation Logic

Instead of relying on single-frame measurements from `SDL_GetTicks()` (which can fluctuate wildly), the class averages frame times over a circular buffer array (`frameTimes[FRAME_VALUES]`):

1. `SDL_GetTicks()` records the time elapsed since SDL initialisation.
2. Frame delta time is added to the circular array and the count index increments.
3. The sum of all stored frame times is divided to compute an average, then converted to seconds (`/ 1000.f`) to yield a stable Frames Per Second figure.
4. `renderFPS()` draws the formatted string to a fixed UI viewport.

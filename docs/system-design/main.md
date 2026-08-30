# Main

## Overview (`Main.cpp`)

The main program entry point.

* Seeds the pseudo-random number generator (`srand(time(NULL))`).
* Calls `Game::Instance()->init()` to initialise engine subsystems.
* Initiates the primary execution loop via `Game::Instance()->update()`.
* Invokes `Game::Instance()->close()` upon termination to clean up resources.

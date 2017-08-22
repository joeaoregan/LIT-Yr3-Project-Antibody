#ifndef GAMEPAD_H
#define GAMEPAD_H
#include <string.h>

#include <SDL.h>
#include <iostream>

void gamepadInfo(SDL_Joystick* gController1, SDL_Joystick* gController2, SDL_Event e) {
	if (SDL_NumJoysticks() > 0) {
		if (strcmp(SDL_JoystickName(gController1), "NVIDIA Shield") == 0) {
			std::cout << "nv test" << std::endl;
			// put test here to make NVIDIA Shield controller as 2 controllers
		}

		std::cout << "joystick instance id: " << SDL_JoystickInstanceID(gController1) << std::endl;

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			const char *name = SDL_GameControllerNameForIndex(i);
			if (name) {
				printf("Joystick %i has game controller name '%s'\n", i, name);
			}
			else {
				printf("Joystick %i has no game controller name.\n", i);
			}
		}

		printf("Joystick connected %d\n", e.jaxis.which);												// DETECTS JOYSTICK
		std::cout << "Number of joystics: " << SDL_NumJoysticks() << std::endl;

		std::cout << "Controller Name: " << SDL_JoystickName(gController1) << std::endl;				// Name of joystick
		std::cout << "Number of buttons: " << SDL_JoystickNumButtons(gController1) << std::endl;		// Number of useable buttons
		std::cout << "Number of axes: " << SDL_JoystickNumAxes(gController1) << std::endl;				// Number of axes on the controller, includes sticks and triggers.
		std::cout << "Number of trackballs: " << SDL_JoystickNumBalls(gController1) << std::endl;		// No trackballs on NVidia Shield Controller
		std::cout << "Number of hats: " << SDL_JoystickNumHats(gController1) << std::endl << std::endl;	// Hats = d-pad on NVidia Shield Controller

		if (SDL_NumJoysticks() > 2) {
			std::cout << "Controller Name: " << SDL_JoystickName(gController2) << std::endl;				// Name of joystick
			std::cout << "Number of buttons: " << SDL_JoystickNumButtons(gController2) << std::endl;		// Number of useable buttons
			std::cout << "Number of axes: " << SDL_JoystickNumAxes(gController2) << std::endl;				// Number of axes on the controller, includes sticks and triggers.
			std::cout << "Number of trackballs: " << SDL_JoystickNumBalls(gController2) << std::endl;		// No trackballs on NVidia Shield Controller
			std::cout << "Number of hats: " << SDL_JoystickNumHats(gController2) << std::endl << std::endl;	// Hats = d-pad on NVidia Shield Controller
		}
	}
}

#endif

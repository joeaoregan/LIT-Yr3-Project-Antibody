/* 2017-01-09:
Weapons will inherit from weapon
*/
#include "Weapon.h"

#define JOYSTICK_DEAD_ZONE 10000

// Constructor
Weapon::Weapon() { }

// Deconstructors
Weapon::~Weapon() { }

void Weapon::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:													// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS: setVelY(getVelY() - getVelocity()); setAngle(-10); break;	// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS: setVelY(getVelY() + getVelocity()); setAngle(10); break;		// Down
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:													// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS: setVelY(getVelY() + getVelocity()); setAngle(0); break;	// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS: setVelY(getVelY() - getVelocity()); setAngle(0); break;		// undo move down 
			}
		}

		// Move rocket for Player 2 with gamepad
	}
	else if (player == 2) {
		if (e.type == SDL_JOYAXISMOTION) {	// Set movement for D-Pad
			if (e.jaxis.axis == 4) {
				if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
					//m_joystickValues[whichOne].second->setY(1);
					setVelY(getVelY() + 1);
					setAngle(10);
				}
				else if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
					//m_joystickValues[whichOne].second->setY(-1);
					setVelY(getVelY() - 1);
					setAngle(-10);
				}
				else {
					//m_joystickValues[whichOne].second->setY(0);
					setVelY(0);
					setAngle(0);
				}
			}
			std::cout << "Thubstick" << std::endl;
		}
	}
}
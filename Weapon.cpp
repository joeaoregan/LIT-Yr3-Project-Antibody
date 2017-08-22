/* 2017-01-09:
Weapons will inherit from weapon
*/
#include "Weapon.h"

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
	}
}
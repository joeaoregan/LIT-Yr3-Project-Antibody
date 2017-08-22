/* 2017-01-09:
Weapons will inherit from weapon
*/

#include "Weapon.h"

// Constructor
Weapon::Weapon() {

}

// Deconstructors
Weapon::~Weapon() {

}

int Weapon::getPlayer() {
	return mPlayer;
}

void Weapon::setPlayer(int p) {
	mPlayer = p;
}

int Weapon::getAngle() {
	return mAngle;
}
void Weapon::setAngle(int a) {
	mAngle = a;
}

int Weapon::getGrade() {
	return mGrade;
}
void Weapon::setGrade(int g) {
	mGrade = g;
}



// Render the Ninja Star objects to the screen
void Weapon::render(LTexture &texture, SDL_Renderer *rend, int degrees) {
	texture.render(getX(), getY(), rend, NULL, degrees, NULL, SDL_FLIP_NONE);
}

void Weapon::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:													// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS: setVelY(getVelY() - getVelocity()); break;	// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS: setVelY(getVelY() + getVelocity()); break;		// Down
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:													// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS: setVelY(getVelY() + getVelocity()); break;	// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS: setVelY(getVelY() - getVelocity()); break;		// undo move down 
			}
		}
	}
}
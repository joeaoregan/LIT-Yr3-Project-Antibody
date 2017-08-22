#include "Rocket.h"
#include "Player.h"

// Laser Constructor
Rocket::Rocket() {
	//std::cout << "Rocket constuctor called.\n";

	setWidth(75);
	setHeight(20);
	setVelocity(12);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAngle(0);	// Fire straight
	//setGrade(0);	// Basic Rocket = 0

	setAlive(true);	// Make sure Rocket is alive from the beginning
}

// Laser Destructor
Rocket::~Rocket() {
	std::cout << "Rocket destructor called.\n";
}

// Move the rocket up or down
void Rocket::handleEvent(SDL_Event& e, int player) {
	if (player == 1) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:											// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS:
				setAngle(getAngle() + 10);
				setVelY(getVelY() - getVelocity()); 
				break;		// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS:
				setAngle(getAngle() - 10);							// CHANGE ANGLE DOESN'T WORK
				setVelY(getVelY() + getVelocity());
				break;		// Down
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			// Adjust the velocity
			switch (e.key.keysym.sym) {
			case SDLK_PLUS:											// +/= or + on keypad
			case SDLK_KP_PLUS:
			case SDLK_EQUALS: setVelY(getVelY() + getVelocity());
				setAngle(0);
				break;		// Up
			case SDLK_KP_MINUS:
			case SDLK_MINUS: setVelY(getVelY() - getVelocity());
				setAngle(0);
				break;		// undo move down 
			}
		}
	}
}

void Rocket::movement() {
	GameObject::movement();
	setY(getY() + getVelY());							// Up direction	
}

/*
void Rocket::spawn(int x, int y, int velocity, int player, int type) {
	setX(x + 57);
	setY(y + 13);

	setVelX(velocity);
	setPlayer(player);
	setType(type);
}
*/
void Rocket::spawn(int x, int y, SDL_Rect collider, int player, int type) {
	setX(x + 57);
	setY(y + 13);
	setVelX(getVelocity());
	setVelY(0);
	setCollider(collider);
	setPlayer(player);
	setType(type);
}
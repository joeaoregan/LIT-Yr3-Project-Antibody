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
	setGrade(0);	// Basic Rocket = 0

	setAlive(true);	// Make sure Rocket is alive from the beginning
}

// Laser Destructor
Rocket::~Rocket() {
	std::cout << "Rocket destructor called.\n";
}


void Rocket::handleEvent(SDL_Event& e, int player) {
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

void Rocket::movement() {
	GameObject::movement();
	setY(getY() + getVelY());		// Up direction

	setColliderX(getX());
	setColliderY(getY());

	// destroy Rocket once it is offscreen
	if (getX() > SCREEN_WIDTH) setAlive(false);
	else setAlive(true);
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

// Render the Rocket objects to the screen
void Rocket::render(int player, LTexture &texture, SDL_Renderer *rend) {
	if (player == 1)
		texture.render(getX(), getY(), rend);			// CHANGE ROCKET COLOURS LATER
	else if (player == 2)
		texture.render(getX(), getY(), rend);
}
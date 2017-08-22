/* 2017-01-09:
Saw Weapon
*/
#include "Saw.h"
#include "Player.h"

// Ninja Star Constructor
Saw::Saw() {
	std::cout << "Saw constuctor called.\n";
	setWidth(40);
	setHeight(40);
	setVelocity(0);
	setAlive(true);
	//setSawActive(false);
}

// Laser Destructor
Saw::~Saw() {
	std::cout << "Saw destructor called.\n";
}

void Saw::movement(int x, int y) {
	setX(x + 65);
	setY(y + 25);
}

void Saw::spawn(int x, int y) {
	setX(x + 15);
	setY(y + 15);
}

void Saw::render(LTexture &texture, SDL_Renderer *rend, int degrees) {
	texture.render(getX(), getY(), rend, NULL, degrees, NULL, SDL_FLIP_NONE);

	//gSawTexture.render(getX(), getY(), gRenderer, NULL, degrees, NULL, SDL_FLIP_NONE);
}
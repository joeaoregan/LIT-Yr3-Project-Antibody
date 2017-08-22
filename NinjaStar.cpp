/* 2017-01-09:
Ninja Star Weapon
*/
#include "NinjaStar.h"
#include "Player.h"

// Ninja Star Constructor
NinjaStar::NinjaStar() {
	//std::cout << "NinjaStar constuctor called.\n";
	setWidth(25);
	setHeight(25);
	setVelocity(10);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAlive(true);

	//mNinjaStarCollider.w = getWidth();
	//mNinjaStarCollider.h = getHeight();
}

// Laser Destructor
NinjaStar::~NinjaStar() {
	//std::cout << "NinjaStar destructor called.\n";
}

void NinjaStar::movement() {
	GameObject::movement();											// Move the NinjaStar

	//mNinjaStarCollider.x = getX();
	//mNinjaStarCollider.y = getY();
	setColliderX(getX());
	setColliderY(getY());

	// destroy NinjaStar once it is offscreen
	if (getX() > SCREEN_WIDTH) setAlive(false);
	else  setAlive(true);
}

void NinjaStar::spawn(int x, int y, SDL_Rect collider) {
	setX(x + 65);
	setY(y + 25);
	setVelX(getVelocity());
	setVelY(0);
	//mNinjaStarCollider = collider;
	setCollider(collider);
}

// Render the Ninja Star objects to the screen
void NinjaStar::render(int degrees, LTexture &texture, SDL_Renderer *rend) {
	texture.render(getX(), getY(), rend, NULL, degrees, NULL, SDL_FLIP_NONE);
}

//SDL_Rect NinjaStar::getNinjaStarCollider(){
//	return mNinjaStarCollider;
//}

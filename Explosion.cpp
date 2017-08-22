#include <SDL.h>
#include "LTexture.h"

#include "Explosion.h"

Explosion::Explosion(int x, int y) {
	setWidth(96);
	setHeight(96);

	setX(x);
	setY(y);
}

Explosion::~Explosion() {

}

void Explosion::movement() {
	

}

//void Explosion::render(LTexture &texture, SDL_Renderer *rend, int degrees) {

//}

// Enemies render function with sprite animation
void Explosion::render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &explosionframe) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), rend, currentClip);

	++explosionframe;								// Go to next frame

	if (explosionframe >= 12 * 10) {	// Cycle animation
		explosionframe = 0;
	}
}
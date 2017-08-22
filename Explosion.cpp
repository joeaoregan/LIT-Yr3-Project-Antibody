#include <SDL.h>
#include "Texture.h"

#include "Explosion.h"

Explosion::Explosion(int x, int y) {
	setWidth(96);
	setHeight(96);

	setX(x);
	setY(y);

	setSubType(EXPLOSION);
}

Explosion::~Explosion() {

}
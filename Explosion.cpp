#include <SDL.h>
#include "Texture.h"

#include "Explosion.h"

Explosion::Explosion(int x, int y, int subType) {
	setWidth(96);
	setHeight(96);

	setDamage(5);

	setX(x);
	setY(y);

	setSubType(subType);

	setAlive(true);
}

Explosion::~Explosion() {

}
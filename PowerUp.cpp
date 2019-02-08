#include "PowerUp.h"

PowerUp::PowerUp() {
	setScore(50);

	setWidth(60);
	setHeight(60);
	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}
PowerUp::PowerUp(int type, int score) {
	setType(type);
	setScore(score);
	
	setWidth(60);

	if (type == 1)
		setHeight(60);
	else if (type == 2)
		setHeight(48);

	setVelocity(1);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());
}

PowerUp::~PowerUp() {

}

void PowerUp::movement() {
	GameObject::movement();

	setColliderX(getX());
	setColliderY(getY());

	// destroy blood cell once it is offscreen
	if (getX() < -100) setAlive(false);
	else setAlive(true);
}

void PowerUp::render(LTexture &texture, SDL_Renderer *rend) {
	texture.render(getX(), getY(), rend);
}

int PowerUp:: getType() {
	return powerUpType;
}

void PowerUp::setType(int type) {
	powerUpType = type;
}
#ifndef COLLISION_STUFF_H
#define COLLISION_STUFF_H

#include <SDL.h>

bool Game::checkCollision(SDL_Rect *a, SDL_Rect *b) {
	//The sides of the rectangles
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = (*a).x;
	rightA = (*a).x + (*a).w;
	topA = (*a).y;
	bottomA = (*a).y + (*a).h;

	//Calculate the sides of rect B
	leftB = (*b).x;
	rightB = (*b).x + (*b).w;
	topB = (*b).y;
	bottomB = (*b).y + (*b).h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	//If none of the sides from A are outside B
	return true;
}

/*
class CollisionStuff : public CollisionStuff {
public:
	//CollisionStuff();							// Initializes the variables
	//~CollisionStuff();
};
*/
#endif
/*
	2017/02/21 Added check so only Ninja Stars and Saws split viruses
	2017/02/18 Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen
	2017/02/08 Added check so rocket explodes on collision with the game boundary
	2017/01/25 Added functionality so Orange Virus explodes after colliding with player to Game class
	2017/01/18 Added collision handling functions
	2017/01/17 Added collision detection for Ninja Stars
	2017/01/11 Added checks for collisions by lasers
				Added flash on collision for player
	2017/02/09 Class for handling collisions between objects
*/
/*
	COLLISION STUFF:

	Checks for collisions between two game objects
*/
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
/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					CollisionStuff.h
	- Description:			Contains function for handling collisions between objects
	- Information:
		Collision Method:	AABB (Axis-Aligned Bounding Box)

		How it works:		AABB Collision uses SDL_Rect to create a bounding volume around the object.
							The bounding volume will move with the objects (X, Y) Coordinates.
							CheckCollision() function will take two SLD_Rect objects as arguments,
							it will then compare each side of both objects for an intersection between them.
							If both objects intersect, the function will return true.
							If true is returned then the game will react to the collision (i.e. Laser hits enemy -> Kill enemy).

	- Link to tutorial:		http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php - Ctrl + Click to view page

	- Log:

		2017/01/07			Created Collision Boxes for Enemy object using SDL_Rect.
							Attemtped Collision boxes for lasers but wont work with a list.
		2017/01/08:			Implemented AABB Collisoin Detection into game.
		2017/01/11:			Replaced the Laser List with Vectors and it worked.
							Added checks for collisions by lasers.
							Added flash on collision for player.
							Multiple-object collison boxes implemented.
								- Uses vectors instead of lists to give an object a collision box on spawn.
								- Lasers now collide with enemy objects, kill them and play explision sound.
								- Enemy Ships given collision boxes.
		2017/01/17:			Added collision detection for Ninja Stars.
		2017/01/18:			Added collision handling functions.
		2017/01/25:			Added functionality so Orange Virus explodes after colliding with player to Game class.
		2017/02/08:			Added check so rocket explodes on collision with the game boundary.
		2017/02/09:			Class for handling collisions between objects.
		2017/02/18:			Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen.
		2017/02/21:			Added check so only Ninja Stars and Saws split viruses.		
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef COLLISION_STUFF_H
#define COLLISION_STUFF_H

#include <SDL.h>

// Name: checkCollision()
// Role: To check intersection between two SLD_Rect objects
bool Game::checkCollision(SDL_Rect *a, SDL_Rect *b) {
	// The sides of each rectangle (A & B).
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = (*a).x;
	rightA = (*a).x + (*a).w;
	topA = (*a).y;
	bottomA = (*a).y + (*a).h;

	// Calculate the sides of rect B
	leftB = (*b).x;
	rightB = (*b).x + (*b).w;
	topB = (*b).y;
	bottomB = (*b).y + (*b).h;

	// If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	// If none of the sides from A are outside B
	// Collision!
	return true;
}

#endif
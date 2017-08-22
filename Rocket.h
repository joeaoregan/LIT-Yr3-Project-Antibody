#ifndef ROCKET_H
#define ROCKET_H
#include "Weapon.h"

class Rocket : public Weapon {
public:
	Rocket();												// Initializes the variables
	~Rocket();												// Destructor

	//void spawn(int x, int y, int velocity, int player);
	virtual void movement();								// Moves the laser
															//void render(int player);								// Shows the laser on the screen - 2017/01/17 Add player decision
	void render(int player, LTexture &texture, SDL_Renderer *rend);	// 2017/01/22 added textures to renderer
	virtual void spawn(int x, int y, SDL_Rect* collider, int player = 1, int type = 9);	// Spawn the object at the dimensions provided
	//void spawn(int x, int y, int velocity, int player, int type = 0);

	void handleEvent(SDL_Event& e, int player);
};

#endif

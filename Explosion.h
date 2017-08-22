#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
#include "SDL.h"

class Explosion : public GameObject {
public:
	Explosion(int x, int y);							// Initializes the variables
	~Explosion();

	virtual void movement();
	//void render();									// Shows the Explosion on the screen
	//void render(LTexture &texture, SDL_Renderer *rend, int degrees);							// Shows the Blood Cell on the screen
	void render(LTexture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, int &enemyframe);


	//Mix_Chunk *sound = Mix_LoadWAV("Audio/explosion.wav");		// Explosion sound fx
};

#endif

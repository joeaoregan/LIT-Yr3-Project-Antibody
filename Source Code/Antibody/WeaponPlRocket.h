/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponPlRocket.h
	- Description:			Header file for the Weapon Player Rocket class.
	- Information:			Contains all function definitions and variables for the Player Weapon Rocket class.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef ROCKET_H
#define ROCKET_H

#include "Weapon.h"

const int TOTAL_PARTICLES_R = 15;								// Particle count

class WeaponPlRocket : public Weapon {
public:
	WeaponPlRocket(int player = 0);								// Initializes the variables
	~WeaponPlRocket();											// Destructor

	Particle* particlesR[TOTAL_PARTICLES_R];					// The particles
	bool getDrawParticle() const { return drawRocketParticle; }	// Return the rockets particles
	void setDrawParticle(bool p) { drawRocketParticle = p; }	// Set the rockets particles
	void renderRocketParticles();								// Draw the rockets particles
	
	/*
		2017/03/18 Rockets render from texture map using texture ID
	*/
	virtual void render() {
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen
																			// Similar to Blood Cell rotation but rotating in only one direction
		SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen

		renderRocketParticles();
	};
	
	//virtual void render(Texture &texture, int degrees = 0);		// Render the rocket, with degrees for upward and downward angle

	virtual void move();										// Moves the Rocket	
	virtual void destroy() {									// Destroy the object when it moves off screen
		GameObject::destroy();
	};
private:
	bool drawRocketParticle;									// Draw the particles for the rocket
};

#endif
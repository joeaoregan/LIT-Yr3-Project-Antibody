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

	virtual void render(Texture &texture, int degrees = 0);		// Render the rocket, with degrees for upward and downward angle

	virtual void move();										// Moves the Rocket	
	virtual void destroy() {									// Destroy the object when it moves off screen
		GameObject::destroy();
	};
private:
	bool drawRocketParticle;									// Draw the particles for the rocket
};

#endif
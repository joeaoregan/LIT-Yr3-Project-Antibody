#ifndef ROCKET_H
#define ROCKET_H

#include "Weapon.h"

const int TOTAL_PARTICLES_R = 15;	// Particle count

class WeaponPlRocket : public Weapon {
public:
	WeaponPlRocket(int player = 0);			// Initializes the variables
	~WeaponPlRocket();						// Destructor

	Particle* particlesR[TOTAL_PARTICLES_R];	// The particles
	bool getDrawParticle() { return drawRocketParticle; }
	void setDrawParticle(bool p) { drawRocketParticle = p; }
	void renderRocketParticles();

	virtual void render(Texture &texture, int degrees = 0);

	virtual void move();				// Moves the Rocket	
	virtual void destroy() {
		GameObject::destroy();
	};
private:
	bool drawRocketParticle;
};


#endif
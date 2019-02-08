/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					WeaponPlRocket.cpp
	- Description:			cpp file for the Weapon Player Rocket class.
	- Information:			Players start with a limited number of rockets, this can be increased by collecting
							rocket power ups that appear on screen. Only one rocket can be fired at a time.

							Rockets can be controlled by the player to guide towards the target
							A timer appears on screen when the rocket button is held to build up power
							This increases the score value on impact with enemy objects and if the player doesn't 
							let go of the button before the timer runs out the rocket will explode

							Players can collect rocket power ups to increase the number of rockets in their inventory
							and the current number of rockets for each player is indicated in the heads up display.
	- Log:
		2017/02/19		Added functionality to initialise the rocket, then create and launch the rocket after returning true 
						from function in spawnRocket() function
		2017/02/16		When the rocket button is pressed it sets a timer, when it's released it sets power (score value), 
						timer set to 2.0 seconds
						Bonus score added for rocket collisions
		2017/02/08		Added check so rocket explodes on collision with the game boundary
						Fixed the angle on the rocket moving up and down
						Added control for rocket movement in Weapon class
		2017/02/06		Added spawnRocket() function to create rockets for players, rocket movement can be controlled by player
						Added class for rockets Rocket.h (Renamed WeaponPlRocket.h)
						Added functionality so only 1 rocket can be active at a time for players first in game, 
						then moved to player, then moved to gameobject
	----------------------------------------------------------------------------------------------------------------------*/

#include "WeaponPlRocket.h"
#include "Player.h"

// Laser Constructor
WeaponPlRocket::WeaponPlRocket(int player) {
	//std::cout << "Rocket constuctor called.\n";
	setType(PLAYER_WEAPON);
	setPlayer(player);
	setTextureID("rocketID");		// 2018/03/18 Added Texture ID

	if (player == PLAYER1) setSubType(ROCKET_P1);
	else if (player == PLAYER2) setSubType(ROCKET_P2);

	setWidth(75);
	setHeight(20);
	setVelocity(15);
	setVelX(15);

	setColliderWidth(getWidth());
	setColliderHeight(getHeight());

	setAngle(0);	// Fire straight
	//setGrade(0);	// Basic Rocket = 0

	setAlive(true);	// Make sure Rocket is alive from the beginning


					//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES_R; ++i) {
		particlesR[i] = new Particle(getX(), getY(), 1);
	}
}

// Laser Destructor
WeaponPlRocket::~WeaponPlRocket() {
	std::cout << "Rocket destructor called.\n";
}

void WeaponPlRocket::move() {
	GameObject::move();
	setY(getY() + getVelY());							// Up direction	

	if (getY() > SCREEN_HEIGHT_GAME - 40) setAlive(false);
	else if (getY() < 40) setAlive(false);

	destroy();
}

/*
2017/03/18 Render Ninja Stars

The Ninja Stars texture is loaded from the texture map using the stored ID
Ninja Stars rotate similar to Blood Cells but in only one direction
*/
/*
void WeaponPlRocket::render() {
	SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen
																		// Similar to Blood Cell rotation but rotating in only one direction
	SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen

	renderRocketParticles();
}
*/
/*
void WeaponPlRocket::render(Texture &texture, int degrees) {

	GameObject::render(texture, degrees);
	renderRocketParticles();

	//std::cout << "Rocket Render" << std::endl;
	//texture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
}
*/
void WeaponPlRocket::renderRocketParticles() {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES_R; ++i) {
		//Delete and replace dead particles
		if (particlesR[i]->isDead(getDrawParticle())) {
			delete particlesR[i];
			particlesR[i] = new Particle(getX() + 15, getY() + 10, 1);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES_R; ++i) {
		particlesR[i]->render();
	}
}

#include <SDL.h>
#include "Particle.h"


const int TOTAL_PARTICLES = 20;	// Particle count

								//The Player that will move around on the screen
class Player {
public:
	// The dimensions of the Player
	static const int PLAYER_WIDTH = 100;
	static const int PLAYER_HEIGHT = 47;

	static const int PLAYER_VELOCITY = 5;					// Maximum axis velocity of the Player

	Player(Texture &one, Texture &two, Texture &three);		// Initializes the variables and allocates particles

	~Player();												// Deallocates particles

	void handleEvent(SDL_Event& e, int player);				// Takes key presses and adjusts the Player's velocity

	void move();											// Moves the Player

	void render(Texture &texture, Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend);	//S hows the Player on the screen

	bool getDrawParticle();
	void setDrawParticle(bool p);

	int player;												// Which Player

	int getX() { return mPosX; }
	int getY() { return mPosY; }
	int getVelX() { return mVelX; }
	int getMapX() { return mMapX; }
	int getPlayer() { return player; }

	void setX(int x) { mPosX = x; }
	void setY(int y) { mPosY = y; }
	void setPlayer(int p) { player = p; }
	void setMapX(int m) { mMapX = m; }

private:
	Particle* particles[TOTAL_PARTICLES];	// The particles

	void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four, SDL_Renderer *rend);	// Shows the particles

	bool drawParticle;	// OK to draw particles or not

	int mPosX, mPosY;	// The X and Y offsets of the Player

	int mMapX;			// Map X coordinate

	int mVelX, mVelY;	// The velocity of the Player
};
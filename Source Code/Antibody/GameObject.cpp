/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					GameObject.cpp
		- Description:			The base class for most of the objects in the game including player and enemy objects
		- Information:			A list of game objects is used to handle object movement, rendering, and collisions.
		- Log:

			2017/03/04			Set a game object texture ID variable, Player and Enemy lasers now render based on their unique texture ID
			2017/02/18			Moved Blood Cells to game object list
								Added setType() function to seet the objects type
			2017/02/09			Added indpendent animation frames
			2017/02/07			Added independent angle to rotate each object
			2017/01/30			Moved degrees variable to object so all rotating objects rotate at different times
			2017/01/25			Added setSubType() function to set the objects sub-type
			2017/01/24			Added Y padding to keep objects within the game screen boundary
			2017/01/22			Moved render functions out of Game.cpp
			2017/02/18			Added setType() function to seet the objects type
			2017/01/17			Separated Player 1 and 2 scores in Game class
			2017/01/09			Moved functionality common to game objects to GameObjects class reducing the code
								Added moveGameObjects() funtction to move the game objects on the screen in Game class
------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include "GameObject.h"
#include "Game.h"

// Constructor
GameObject::GameObject() {
	m_x = 0;
	m_y = 0;
	m_xVel = 0;
	m_yVel = 0;
}

// Deconstructors
GameObject::~GameObject() {
	//std::cout << "GameObject deconstructor" << std::endl;
}

// Render the Game Objects to the screen
void GameObject::render() {
	//Texture mTexture; // 2017/03/21
	m_Texture.render(getX(), getY(), NULL, 0, NULL, SDL_FLIP_NONE);
}


void GameObject::render(Texture &texture, int degrees) {
	texture.render(getX(), getY(), NULL, degrees, NULL, SDL_FLIP_NONE);
}
void GameObject::render(Texture &texture, SDL_Rect *currentClip, int &currentframe, int frames) {	// 2017/01/22 Moved from game.cpp
	texture.render(getX(), getY(), currentClip);

	++currentframe;						// Go to next frame

	if (currentframe >= frames * 10) {	// Cycle animation
	//if (frames / 10 >= currentframe) {	// Cycle animation
		currentframe = 0;
	}
}
void GameObject::render(Texture &texture, SDL_Rect *currentClip, int &currentframe, int frames, int x, int y) {	// 2017/01/22 Moved from game.cpp
	texture.render(x, y, currentClip);

	++currentframe;						// Go to next frame

	if (currentframe >= frames * 10) {	// Cycle animation
		currentframe = 0;
	}
}

/*
	Render using the game singleton to fetch the renderer,
	The texture singleton to get the texture using the GameObjects stored texture ID
	Source and Destination rectangles
	An angle of rotation
*/
void GameObject::renderAnimation() {
	Texture::Instance()->modifyAlpha( getAlpha(), getTextureID() );
	SDL_Rect renderQuadSource = { getWidth() * getCurrentFrame(), getHeight() * getAnimRow(), getWidth(), getHeight() };
	SDL_Rect renderQuadDest = { getX(), getY(), getWidth(), getHeight() };

	//SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), &srcRect, &renderQuadDest, angle, 0, flip);
	//SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuadDest, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), &renderQuadSource, &renderQuadDest, 0, NULL, SDL_FLIP_NONE);
}

/* 
// Render rotating object with ID
void GameObject::render() {
	SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };	// Set rendering space and render to screen
	
	SDL_RenderCopyEx(Game::Instance()->getRenderer(), Texture::Instance()->getTexture(getTextureID()), NULL, &renderQuad, getAngle(), NULL, SDL_FLIP_NONE);	// Render to screen
}
*/
void GameObject::spawn(int x, int y, int vx, int vy) {
	m_x = x;
	m_y = y;
	m_xVel = vx;
	m_yVel = vy;	// 2017-01-10 JOE: use same velocity for x and y
	setAlive(true);
}

void GameObject::move(int x, int y) {
	m_x += m_xVel;
	//if (y != 0) 
		m_y += m_yVel;

	setColliderX(getX());
	setColliderY(getY());

	destroy();
}
void GameObject::moveStalker(int targetX, int targetY) {
	if (getX() < SCREEN_WIDTH - getWidth()) {		// If the object is on the screen
		int randomVelocity = rand() % 4 + 2;

		if (getX() - targetX >= 0) {				// If the small virus is behind the white blood cell
			if (getX() - targetX >= randomVelocity)
				setX(getX() - randomVelocity);		// No need to make smaller movements at the moment, as velocity is v.low anyway
		}
		else if (getX() - targetX < 0) {			// if the small virus is in front of the white blood cell
			setX(getX() + randomVelocity);			// Move towards X coord
		}

		if (getY() - targetY >= 0) {				// if the small virus is below the white blood cell
			if (getY() - targetY >= randomVelocity)
				setY(getY() - randomVelocity);		// No need to make smaller movements at the moment, as velocity is v.low anyway
		}
		else if (getY() - targetY < 0) {			// if the small virus is above the white blood cell
			setY(getY() + randomVelocity);			// Move towards Y coord
		}

		setColliderX(getX());						// Set the X coordinate of the collider
		setColliderY(getY());						// Set the Y coordinate of the collider
	}
}

void GameObject::orbit(int centerX, int centerY, float timer) {
	if (centerX < SCREEN_WIDTH) {
		rotateCounter %= 360;

		if (timer != 0.5) {
			setX(70 * cos(rotateCounter * 3.1415926f / 180.0f) + centerX);		// rotate the bullet object
			setY(70 * sin(rotateCounter * 3.1415926f / 180.0f) + centerY);

			rotateCounter += 3;
		}
		else
			move();					// Fire the satellite bullet object
	}
}

void GameObject::destroy() {
	// Destroy Game Object moving off screen on Y axis
	if (getY() <= 40) setAlive(false);								// Once it reaches the pink border
	else if (getY() >= (SCREEN_HEIGHT_GAME - 40)) setAlive(false);	// 600 - 40 for pink border
	else setAlive(true);

	// Destroy Game Object moving off screen on X axis
	if ((getX() > SCREEN_WIDTH && getVelX() > 0)) setAlive(false);	// 2017/02/08 Need to check if velocity is negative, or power ups & blood cells don't appear on screen
	else if (getX() < -getWidth() - 10) setAlive(false);			// If the object if off screen to the left
	else setAlive(true);
}

void GameObject::setHealth(int h) {
	if (h < 0) {
		m_Health = 0;												// If health is less than 0 set 0
		setAlive(false);											// set the Game object as not alive
	}
	else if (h > 100)
		m_Health = 100;
	else
		m_Health = h;
}

// 2017-02-21 Moved from Player.cpp
void GameObject::setSpeedBoost(bool boost) {
	mSpeedBoost = boost;

	if (boost) {
		setBoostStartTime(SDL_GetTicks());
		std::cout << "SPEED BOOST START" << std::endl;
	}
	else
		boostPercent = 3.0;
}

void GameObject::setLaserGrade(int grade) { 
	if (grade > LASER_TRIPLE) grade = LASER_TRIPLE;					// 2017/03/01 Triple laser is the highest grade of laser
		mLaserGrade = grade; 
}

/*
// Old constructor
GameObject::GameObject(int damage) :	// Constructor has default value for damage of 3
	m_Damage(damage)
{}

// Old function to render particles
void GameObject::renderParticles(Texture &one, Texture &two, Texture &three, Texture &four) {
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES2; ++i) {
		//Delete and replace dead particles
		if (particles[i]->isDead(getDrawParticle())) {
			delete particles[i];
			particles[i] = new Particle(getX() + 9, getY() + 30, one, two, three);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES2; ++i) {
		particles[i]->render(four);
	}
}
*/
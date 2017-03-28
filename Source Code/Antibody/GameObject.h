/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					GameObject.h
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
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#define MAX_HEALTH 100

#define ROCKET_TIMER 3.0

#include "GameObjectAbstract.h"
#include <SDL.h>
//#include <SDL_image.h>
#include "Texture.h"
#include <iostream>
#include "Particle.h"

const int TOTAL_PARTICLES2 = 20;	// Particle count

// Main types of Game Objects
enum GameObjectTypes {
	PLAYER, BACKGROUND,
	BLOOD_CELL, PLAYER_WEAPON, ENEMY_WEAPON, ENEMY_OBJECT, POWER_UP, SMALL_VIRUS, BLOCKAGE,
	MAP_ALERT, SCORE_TEXT, EXPLOSION
};
enum GameObjectSubTypes {
	GAMEOBJECT, PLAYER1, PLAYER2,																			// Players
	PLAYER1_SCORE, PLAYER2_SCORE,																			// Scores
	POWER_UP_HEALTH, POWER_UP_LASER, POWER_UP_ROCKET, POWER_UP_CHECKPOINT, POWER_UP_LIVES,					// Power ups
	ENEMY_SHIP_LASER, BLUE_VIRUS_BULLET, VIRUS_FIREBALL,													// Bullets
	FIRE_EXPLOSION, BLOOD_EXPLOSION, GREEN_VIRUS_EXPLOSION, ORANGE_VIRUS_EXPLOSION, BLUE_VIRUS_EXPLOSION,	// Explosions
	SAW1, SAW2,																								// Saw
	LARGE_BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL,													// Blood Cells
	ENEMY_SHIP, ENEMY_BOSS,																					// Enemies
	VIRUS_GREEN, VIRUS_ORANGE, VIRUS_BLUE, VIRUS_SMALL_GREEN, VIRUS_SMALL_ORANGE, VIRUS_SMALL_BLUE,			// Virus
	LASER_P1, LASER_P2, LASER_V2_P1, LASER_V2_P2, LASER_V3_P1, LASER_V3_P2,									// Player Laser
	NINJA_STAR_P1, NINJA_STAR_P2, ROCKET_P1, ROCKET_P2,														// Misc Weapons
};

/*
enum GameObjectTypes { 
	PLAYER, PLAYER1, PLAYER2,
	SCORE_TEXT,																							// Scores
	POWER_UP_HEALTH, POWER_UP_LASER, POWER_UP_ROCKET, POWER_UP_CHECKPOINT, POWER_UP_LIVES,				// Power ups
	ENEMY_SHIP_LASER, BLUE_VIRUS_BULLET, VIRUS_FIREBALL,												// Bullets
	EXPLOSION, BLOOD_EXPLOSION,	GREEN_VIRUS_EXPLOSION, ORANGE_VIRUS_EXPLOSION, BLUE_VIRUS_EXPLOSION,	// Explosions
	SAW1, SAW2,																							// Saw
	LARGE_BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL,												// Blood Cells
	ENEMY_SHIP,	ENEMY_BOSS,																				// Enemies
	VIRUS_GREEN, VIRUS_ORANGE, VIRUS_BLUE, VIRUS_SMALL_GREEN, VIRUS_SMALL_ORANGE, VIRUS_SMALL_BLUE,		// Virus
	LASER_P1, LASER_P2, LASER_V2_P1, LASER_V2_P2, LASER_V3_P1, LASER_V3_P2,								// Player Laser
	NINJA_STAR_P1, NINJA_STAR_P2, ROCKET_P1, ROCKET_P2,													// Misc Weapons
	BLOOD_CELL, PLAYER_WEAPON, ENEMY_WEAPON, ENEMY_OBJECT, POWER_UP, SMALL_VIRUS, BLOCKAGE,				// Main type of object
	MAP_ALERT
};
enum GameObjectSubTypes {
	PLAYER1_SCORE, PLAYER2_SCORE,																		// Scores
};
*/
enum weaponsGrades { LASER_SINGLE, LASER_DOUBLE, LASER_TRIPLE };
enum laserAngles { STRAIGHT, LASER2_TOP, LASER2_BOTTOM, LASER3_TOP, LASER3_BOTTOM };

class GameObject : public GameObjectAbstract {
public:
	GameObject();														// Constructor
	~GameObject();														// Destructor
	
	virtual void handleEvent(SDL_Event& e, int player) {}				// Handle events for objects

	virtual void spawn(int x, int y, int vx = 0, int vy = 0);			// Spawn objects

	virtual void move(int x = 0, int y = 0);							// Move objects
	virtual void moveStalker(int targetX, int targetY);					// 2017/03/03 Updated movement functions, for objects that move towards other objects
	virtual void orbit(int centerX, int centerY, float timer);			// Circular movement for Blue Virus satellite objects

	virtual void destroy();												// Destroy the game object when it moves out of bounds

	// Render the game objects
	virtual void render();
	virtual void render(Texture &texture, int degrees = 0);
	void render(Texture &texture, SDL_Rect *currentClip, int &currentframe, int frames);
	void render(Texture &texture, SDL_Rect *currentClip, int &currentframe, int frames, int x, int y);

	void GameObject::renderAnimation();	// 2017/03/22

	// Getter methods
	int getX() const { return m_x; }									// Get GameObject X coord
	int getY() const { return m_y; }									// Get GameObject Y coord
	int getVelX() const { return m_xVel; }								// Get Velocity on X axis
	int getVelY() const { return m_yVel; }								// Get Velocity on Y axis
	int getVelocity() const { return m_Velocity; }						// return the velocity
	bool getAlive() const { return m_Alive; }							// return if the object is alive
	int getScore() const { return m_Score; }							// return the objects score
	int getWidth() const { return m_Width; }							// return the objects width
	int getHeight() const { return m_Height; }							// return the objects height
	std::string getName() const { return m_Name; }						// return the objects name
	int getHealth() const { return m_Health; }							// return the objects health
	int getMaxHealth() const { return MAX_HEALTH; }						// Return the max health an object can have
	int getNumLives() const { return m_NumLives; }						// Return the number of lives
	int getType() const { return m_Type; }								// 2017/02/18 Return the objects sub-type
	int getSubType() const { return m_SubType; }						// 2017/01/25 Return the objects type
	int getAngle() const { return m_Angle; }							// 2017/02/07 Return the objects angle
	std::string getTextureID() const { return m_TextureID; }			// return the texture ID
	SDL_Rect getCollider() const { return m_Collider; }					// Get the collider for an object
	int getNumFrames() const { return m_Frames; }						// 2017/02/09 Animation frames
	int getCurrentFrame() const { return m_CurrentFrame; }				// 2017/03/22 Get the current animation frame of sprite sheet
	int getAnimRow() const { return m_CurrentAnimationRow; }			// 2017/03/22 Get the current animation row of sprite sheet
	int getAnimCount() const { return m_animCount; }					// 2017/03/22 Count before changing animation fram
	// Timers
	unsigned int getLastTime() const { return lastTime; }				// Get the previous time for counter
	float getTimerTracker() const { return m_TimeTracker; }				// Keep track of time for counter
	float getTimer() const { return m_Timer; }							// Get timer for object
	int getAlpha() const { return m_Alpha; }							// 2017/03/22 Get the texture alpha value

	// Setter methods
	void setX(int x) { m_x = x; }										// Set GameObject X coord
	void setY(int y) { m_y = y; }										// Set GameObject Y coord
	void setVelX(int x) { m_xVel = x; }									// Set the velocity on the X axis
	void setVelY(int y) { m_yVel = y; }									// Set the velocity on the Y axis
	void setVelocity(int v) { m_Velocity = v; }							// Set the objects velocity
	void setAlive(bool alive) { m_Alive = alive; }						// Set the object alive or not
	void setScore(int s) { m_Score = s; }								// Set the objects score
	void setWidth(int w) { m_Width = w; }								// set the objects width
	void setHeight(int h) { m_Height = h; }								// set the objects height
	void setName(std::string n) { m_Name = n; }							// Set the objects name
	void setHealth(int health);											// set the health
	void setNumLives(int n) { m_NumLives = n; }							// Set the number of lives for the object
	void setType(int t) { m_Type = t; }									// 2017/02/18 Set the objects sub-type
	void setSubType(int t) { m_SubType = t; }							// 2017/01/25 Set the objects type
	void setAngle(int a) { m_Angle = a; }								// Set the angle of rotation
	void setTextureID(std::string t) { m_TextureID = t; }				// Set the texture ID
	void setCollider(SDL_Rect collider) { m_Collider = collider; }		// 2017/01/19 Added as Sean keeps doing dumb things with the colliders
	void setFrames(int f) { m_Frames = f; }								// Set the number of frames for animation
	void setCurrentFrame(int f) { m_CurrentFrame = f; }					// Set the current frame of animation in the sprite sheet
	void setAnimRow(int f) { m_CurrentAnimationRow = f; }				// Set the current row of animation in the sprite sheet
	void setAnimCount(int f) { m_animCount = f; }						// Set the count for changing animation frames
	// Timers
	void setLastTime(unsigned int time) { lastTime = time; }			// Set the previous time for counter
	void setTimerTracker(float t) { m_TimeTracker = t; }				// Keep track of time for counter
	void setTimer(float t) { m_Timer = t; }								// Set timer for object
	void setAlpha(int a) { m_Alpha = a; }								// 2017/03/22 Set the texture alpha value

	void setColliderWidth(int w) { m_Collider.w = w; }					// Set the width of the objects collider
	void setColliderHeight(int h) { m_Collider.h = h; }					// Set the height of the objects collider
	void setColliderX(int x) { m_Collider.x = x; }						// Set Collider X coord
	void setColliderY(int y) { m_Collider.y = y; }						// Set Collider Y coord

	Texture m_Texture;													// Texture for the object
		
	bool getLineAlgCalculated() { return lineAlgorithmCalculated; }		// Is the line algorithm calculated
	void setLineAlgCalculated(bool alg) { lineAlgorithmCalculated = alg; }	// Set the line algorithm as calculated or not
	int dx, dy;															// Delta X, Delta Y

	// Blue Virus Satellite object
	int rotateCounter;													// degrees the satellite object has rotated
	bool satelliteObjectOrbiting;										// Check is satellite object orbiting Blue Virus
	int whichVirusAssignedTo;											// The Blue virus the satellite is assigned to

	// Rockets
	bool getRocketBarActive() const { return m_RocketBarActive; }		// Is the rocket status bar active
	void setRocketBarActive(bool rocket) { m_RocketBarActive = rocket; }// Set the rocket status bar active or not
	bool getProjectileActive() const { return m_ProjectileActive; }		// Is the projectile active
	void setProjectileActive(bool rocket) { m_ProjectileActive = rocket; }// Set the projectile active or not
	int getNumRockets() const { return numRockets; }					// Get the number of rockets in a players inventory
	void setNumRockets(int rocket) { numRockets = rocket; }				// Set the number of rockets in a players inventory

	// Blood Cells
	int getDistanceBetween() const { return mDistanceBetween; }			// Distance on X axis between spawning bloodcells
	void setDistanceBetween(int d) { mDistanceBetween = d; }			// Set distance between spawning blood cells

	// Rotating objects
	int getRotationDirection() { return mRotationDirection; }			// 2017/01/30 Added rotation direction, so Blood Cells can rotate both forwards and backwards
	void setRotationDirection(int d) { mRotationDirection = d; }		// 2017/02/18 Moved Blood Cells to game object list

	// Weapons
	int getPlayer() const { return mPlayer; }							// Check if a weapon is assigned to player 1 or 2
	void setPlayer(int p = 0) { mPlayer = p; }							// Set the player the weapon is assigned to
	int getDamage() const { return m_Damage; }							// Damage an object inflicts
	void setDamage(int d = 0) { m_Damage = d; }							// Set the damage an object inflicts
	bool getKillRocket() const { return killRocket; }					// Is a rocket to be destroyed
	void setKillRocket(bool kill = 0) { killRocket = kill; }			// Set a rocket to be destroyed
	int getBonusScore() const { return bonusScore; }					// Get bonus score for rockets
	void setBonusScore(int bonus = 0) { bonusScore = bonus; }			// Set bonus score for rockets
	// Shield
	bool getShieldActive() const { return shieldActive; }				// Is the shield active or not
	void setShieldActive(bool active) { shieldActive = active; }		// Set the saw active
	// Saw
	bool getSawActive() const { return sawActive; }						// Is the Players saw active
	void setSawActive(bool active) { sawActive = active; }				// Set the saw active
	// Laser
	int getLaserGrade() const { return mLaserGrade; }					// Get the Players laser grade
	void setLaserGrade(int grade);										// Set the Players laser grade
	
	// Speed boost
	bool getSpeedBoost() const { return mSpeedBoost; }					// Is the Players speed boost active
	unsigned int getBoostStartTime() const { return mBoostStartTime; }	// Get the Players speed boost start time
	void setBoostStartTime(unsigned int time) { mBoostStartTime = time; }// Set the players speed boost start time
	void setSpeedBoost(bool boost);										// Set the players speed boost active or not
	float getBoostPercent() const { return boostPercent; }				// Get the percentage for the boost status bar
	void setBoostPercent(float speed) { boostPercent = speed; }			// Set the percenage for the boost status bar
	
protected:
	// GameObject Variables
	std::string m_Name;				// Name of the object
	std::string m_TextureID;		// ID for the texture associated with the object
	int m_Health;					// Value between 0 and 160
	int m_Width, m_Height;			// Dimensions
	bool m_Alive;					// Is the GameObject active on screen, return true if its health is greater than 0
	SDL_Rect m_Collider;			// Collider for objects
	int m_Score;					// Score value for killing or collecting an object
	int m_NumLives;					// The playes number of lives
	int m_Damage;					// The damage an object inflicts

	// Movement
	int m_x, m_y;					// GameObject coords
	int m_xVel, m_yVel, m_Velocity;	// Velocity
	//bool m_movesToCoords;			// 2017/03/22 The objects moves to specified coordinates, flag to indicate to use move() function with x and y values

	// Object Types
	int m_SubType;					// Integer value to indicate the type of game object POWER UP, VIRUS
	int m_Type;						// The type of an object

	// 31-01 Display time
	float m_TimeTracker;			// Time to begin displaying
	float m_Timer;					// Time to end displaying
	unsigned int lastTime = 0.0;	// Previous stored time

	// Textures and Animations
	int m_Angle;					// 2017-02-07: Angle to rotate an object
	int m_Frames;					// 2017/02/09 Number of frames for an animation
	int m_CurrentFrame;				// 2017/03/22 The current animation frame in the sprite sheet
	int m_CurrentAnimationRow;		// 2017/03/22 The current animation row in the sprite sheet
	int m_animCount;				// 2017/03/22 How long before changing animation frames
	int m_Alpha;					// 2017/03/22 Alpha value for Texture
	bool lineAlgorithmCalculated;	// Used in scoreText

	// 2017/02/18 Moved Blood Cells
	int mDistanceBetween;			// Distance between Blood Cells spawning
	int mRotationDirection;			// Direction to rotate Blood Cell (-1 = anticlockwise, 1 = clockwise)

	// Weapons
	int mPlayer;					// The player a weapon is assigned to
	bool sawActive;					// Set players saw active
	bool shieldActive;				// 2017/03/13 Turn on / off shield
	int bonusScore;					// Store the bonus score for a rocket taking out an enemy
	bool m_ProjectileActive;		// 2017/02/06 Decides if an object can fire rockets or other weapons
	bool m_RocketBarActive;			// Is the status bar for rockets active
	int numRockets;					// The number of rockets an object has
	bool killRocket;				// Destroy the rocket
	bool mSpeedBoost;				// Speed boost is active
	unsigned int mBoostStartTime;	// Time the speed boost started
	float boostPercent = 3.0;		// How long the speed boost lasts
	int mLaserGrade;				// The grade of a Players laser (Single, double, or triple)

	// particles
	bool drawParticle;				// Draw particles for an object or not
};

#endif

/*
// Older unused variables and functions

int m_Speed;						// Value between 1 and 4
int rotateCenter;
SDL_Color getFontColour();
void setFontColour(SDL_Color f);
// Particles
bool getDrawParticle() { return drawParticle; }
void setDrawParticle(bool p) { drawParticle = p; }
void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four);
Texture getTexture() { return m_Texture; }
void setTexture(Texture texture) { m_Texture = texture; }

Particle* particles[TOTAL_PARTICLES2];	// The particles
*/
/*
	2017/03/04 Set a game object texture ID variable, Player and Enemy lasers now render based on their unique texture ID
	2017/02/18 Moved Blood Cells to game object list
	2017/02/09 Added indpendent animation frames
	2017/02/07 Added independent angle to rotate each object
	2017/01/30 Moved degrees variable to object so all rotating objects rotate at different times
	2017/01/25 Added setSubType() function to set the objects sub-type
	2017/02/18 Added setType() function to seet the objects type
	2017/01/09 Moved functionality common to game objects to GameObjects class reducing the code
	2017/01/17 Separated Player 1 and 2 scores in Game class
*/
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
enum weaponsGrades { LASER_SINGLE, LASER_DOUBLE, LASER_TRIPLE };
enum laserAngles { STRAIGHT, LASER2_TOP, LASER2_BOTTOM, LASER3_TOP, LASER3_BOTTOM };

class GameObject : public GameObjectAbstract {
public:
	GameObject();
	~GameObject();												// Deconstructor

	virtual void handleEvent(SDL_Event& e, int player) {}

	virtual void spawn(int x, int y, int vx = 0, int vy = 0);

	virtual void move(int x = 0, int y = 0);
	virtual void moveStalker(int targetX, int targetY) {
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

			setColliderX(getX());
			setColliderY(getY());
		}
	};	// 2017/03/03 Updated movement functions, for objects that move towards other objects
	virtual void orbit(int centerX, int centerY, float timer);

	virtual void destroy();

	virtual void render();
	virtual void render(Texture &texture, int degrees = 0);
	void render(Texture &texture,  SDL_Rect *currentClip, int &currentframe, int frames);

	int getX() { return m_x; }						// Get GameObject X coord
	int getY() { return m_y; }						// Get GameObject Y coord
	int getVelX() { return m_xVel; }
	int getVelY() { return m_yVel; }
	int getVelocity() { return m_Velocity; }		// return the velocity
	bool getAlive() { return m_Alive; }				// return if the object is alive
	int getScore() { return m_Score; }				// return the objects score
	int getWidth() { return m_Width; }				// return the objects width
	int getHeight() { return m_Height; }			// return the objects height
	std::string getName() { return m_Name; }		// return the objects name
	int getHealth() { return m_Health; }			// return the objects health
	int getMaxHealth() { return MAX_HEALTH; }
	int getNumLives() { return m_NumLives; }
	int getSubType() { return m_SubType; }			// 2017/01/25 Return the objects type
	int getType() { return m_Type; }				// 2017/02/18 Return the objects sub-type
	int getAngle() { return m_Angle; }				// 2017/02/07 Return the objects angle
	std::string getTextureID() { return m_TextureID; }		// return the texture ID
	void setTextureID(std::string t) { m_TextureID = t; }	// Set the texture ID

	void setX(int x) { m_x = x; }					// Set GameObject X coord
	void setY(int y) { m_y = y; }					// Set GameObject Y coord
	void setVelX(int x) { m_xVel = x; }				// Set the velocity on the X axis
	void setVelY(int y) { m_yVel = y; }				// Set the velocity on the Y axis
	void setVelocity(int v) { m_Velocity = v; }		// Set the objects velocity
	void setAlive(bool alive) { m_Alive = alive; }	// Set the object alive or not
	void setWidth(int w) { m_Width = w; }			// set the objects width
	void setHeight(int h) { m_Height = h; }			// set the objects height
	void setScore(int s) { m_Score = s; }			// Set the objects score
	void setName(std::string n) { m_Name = n; }		// Set the objects name
	void setHealth(int health);						// set the health
	void setNumLives(int n) { m_NumLives = n; }		// Set the number of lives for the object

	SDL_Rect* getCollider() { return &m_Collider; }
	void setCollider(SDL_Rect collider) { m_Collider = collider; }	// 2017/01/19 Added as Sean keeps doing dumb things with the colliders
	void setColliderWidth(int w) { m_Collider.w = w; }
	void setColliderHeight(int h) { m_Collider.h = h; }
	void setColliderX(int x) { m_Collider.x = x; }
	void setColliderY(int y) { m_Collider.y = y; }
	void setSubType(int t) { m_SubType = t; }		// 2017/01/25 Set the objects type
	void setType(int t) { m_Type = t; }				// 2017/02/18 Set the objects sub-type
	void setAngle(int a) { m_Angle = a; }

	//SDL_Color getFontColour();
	//void setFontColour(SDL_Color f);
	Texture m_Texture;

	// Timers
	unsigned int getLastTime() { return lastTime; }
	void setLastTime(unsigned int time) { lastTime = time; }
	float getTimerTracker() { return m_TimeTracker; }
	float getTimer() { return m_Timer; }
	void setTimerTracker(float t) { m_TimeTracker = t; }
	void setTimer(float t) { m_Timer = t; }

//	Texture getTexture() { return m_Texture; }
//	void setTexture(Texture texture) { m_Texture = texture; }

	int getFrames() { return m_Frames; }		// 2017/02/09 Animation frames
	void setFrames(int f) { m_Frames = f; }

	bool getLineAlgCalculated() { return lineAlgorithmCalculated; }
	void setLineAlgCalculated(bool alg) { lineAlgorithmCalculated = alg; }
	int dx, dy;


	int rotateCounter;	// degrees the satellite object has rotated
	//int rotateCenter;
	bool satelliteObjectOrbiting;
	unsigned int whichVirusAssignedTo;

	bool getRocketBarActive() { return m_RocketBarActive; }
	void setRocketBarActive(bool rocket) { m_RocketBarActive = rocket; }
	bool getProjectileActive() { return m_ProjectileActive; }
	void setProjectileActive(bool rocket) { m_ProjectileActive = rocket; }
	int getNumRockets() { return numRockets; }
	void setNumRockets(int rocket) { numRockets = rocket; }

	// Blood Cells
	int getDistanceBetween() { return mDistanceBetween; }
	void setDistanceBetween(int d) { mDistanceBetween = d; }

	int getRotationDirection() { return mRotationDirection; }		// 2017/01/30 Added rotation direction, so Blood Cells can rotate both forwards and backwards
	void setRotationDirection(int d) { mRotationDirection = d; }	// 2017/02/18 Moved Blood Cells to game object list

	// Weapons
	int getPlayer() { return mPlayer; }								// Check if a weapon is assigned to player 1 or 2
	void setPlayer(int p = 0) { mPlayer = p; }
	int getDamage() { return m_Damage; }							// Damage an object or object inflicts
	void setDamage(int d = 0) { m_Damage = d; }
	bool getKillRocket() { return killRocket; }
	void setKillRocket(bool kill = 0) { killRocket = kill; }
	int getBonusScore() { return rocketBonusScore; }
	void setBonusScore(int bonus = 0) { rocketBonusScore = bonus; }
	// Shield
	bool getShieldActive() { return shieldActive; }
	void setShieldActive(bool active) { shieldActive = active; }			// Set the saw active
	// Saw
	bool getSawActive() { return sawActive; }
	void setSawActive(bool active) { sawActive = active; }			// Set the saw active
	// Laser
	int getLaserGrade() { return mLaserGrade; }
	void setLaserGrade(int grade);

	// Particles
	//bool getDrawParticle() { return drawParticle; }
	//void setDrawParticle(bool p) { drawParticle = p; }
	//void renderParticles(Texture &one, Texture &two, Texture &three, Texture &four);

	// Speed boost
	bool getSpeedBoost() { return mSpeedBoost; }
	unsigned int getBoostStartTime() { return mBoostStartTime; }
	void setBoostStartTime(unsigned int time) { mBoostStartTime = time; }
	void setSpeedBoost(bool boost);
	float getBoostPercent() { return boostPercent; }
	void setBoostPercent(float speed) { boostPercent = speed; }

protected:
	// GameObject Variables
	std::string m_Name;				// Name of the object
	std::string m_TextureID;		// ID for the texture associated with the object
	int m_Health;					// Value between 0 and 160
	//int m_Speed;					// Value between 1 and 4
	int m_x, m_y;					// GameObject coords
	int m_xVel, m_yVel, m_Velocity;	// Velocity
	int m_Width, m_Height;			// Dimensions
	bool m_Alive;					// Is the GameObject active on screen, return true if its health is greater than 0
	SDL_Rect m_Collider;
	int m_Score;					// Score value for killing or collecting an object
	int m_NumLives;
	int m_Damage;

	// Object Types
	int m_SubType;					// Integer value to indicate the type of game object POWER UP, VIRUS
	int m_Type;

	// 31-01 Display time
	float m_TimeTracker;			// Time to begin displaying
	float m_Timer;					// Time to end displaying
	unsigned int lastTime = 0.0;

	int m_Angle;					// 2017-02-07: Angle to rotate an object

	int m_Frames;					// 2017/02/09 Number of frames for an animation
	bool lineAlgorithmCalculated;	// Used in scoreText

	// 2017/02/18 Moved Blood Cells
	int mDistanceBetween;			// Distance between Blood Cells spawning
	int mRotationDirection;			// Direction to rotate Blood Cell (-1 = anticlockwise, 1 = clockwise)

	// Weapons
	int mPlayer;
	bool sawActive;
	bool shieldActive;				// 2017/03/13 Turn on / off shield
	int rocketBonusScore;
	bool m_ProjectileActive;		// 2017/02/06 Decides if an object can fire rockets or other weapons
	bool m_RocketBarActive;
	int numRockets;					// The number of rockets an object has
	bool killRocket;
	bool mSpeedBoost;				// Speed boost is active
	unsigned int mBoostStartTime;	// Time the speed boost started
	float boostPercent = 3.0;
	int mLaserGrade;

	// particles
	bool drawParticle;
	//Particle* particles[TOTAL_PARTICLES2];	// The particles
};

#endif

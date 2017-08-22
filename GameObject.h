/* 2017/01/09:
JOE: Moved functionality common to game objects to GameObjects class reducing the code
*/
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#define MAX_HEALTH 100

#define ROCKET_TIMER 3.0

#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include <iostream>

enum GameObjectTypes {
	PLAYER, PLAYER1, PLAYER2,
	PLAYER1_SCORE, PLAYER2_SCORE,																		// Scores
	POWER_UP_HEALTH, POWER_UP_LASER, POWER_UP_ROCKET, POWER_UP_CHECKPOINT,								// Power ups
	ENEMY_SHIP_LASER, BLUE_VIRUS_BULLET, VIRUS_FIREBALL,												// Bullets
	EXPLOSION, BLOOD_EXPLOSION,	GREEN_VIRUS_EXPLOSION, ORANGE_VIRUS_EXPLOSION, BLUE_VIRUS_EXPLOSION,	// Explosions
	SAW1, SAW2,																							// Saw
	LARGE_BLOOD_CELL, SMALL_BLOOD_CELL, WHITE_BLOOD_CELL,												// Blood Cells
	ENEMY_SHIP,																							// Enemies
	VIRUS_GREEN, VIRUS_ORANGE, VIRUS_BLUE, VIRUS_GREEN_SMALL, VIRUS_ORANGE_SMALL, VIRUS_BLUE_SMALL,		// Virus
	NINJA_STAR_P1, NINJA_STAR_P2, LASER_P1, LASER_P2, LASER_V2_P1, LASER_V2_P2, ROCKET_P1, ROCKET_P2,	// Weapons
	BLOOD_CELL, PLAYER_WEAPON, ENEMY_WEAPON, ENEMY_OBJECT, POWER_UP, SMALL_VIRUS						// Main type of object
};
enum weaponsGrades {LASER_SINGLE, LASER_TRIPLE};

class GameObject {
public:
	GameObject();
	~GameObject();												// Deconstructor

	virtual void handleEvent(SDL_Event& e, int player) {}

	void spawn(int x, int y, int vx = 0, int vy = 0);

	virtual void spawn(int x, int y, int vx, SDL_Rect* collider);

	virtual void spawn(int x, int y, int velocity, int player, int type = 0) {}			// Player laser

	virtual void spawn(int x, int y, SDL_Rect* collider, int player = 1, int type = 9);	// Spawn the object at the dimensions provided --> Rocket

	virtual void spawn(int x, int y, int vx, int vy, SDL_Rect* collider, int type = 0);

	virtual void movement();
	void movement(int centerX, int centerY, float timer);
	virtual void movement(int x, int y) {
		//setY(getY() - 5);
				//if (getY() <= 40) setAlive(false);
	};
	//virtual void movement(int x, int y, int z) {};

	void destroy();

	//void render(LTexture &texture, SDL_Renderer *rend);							// Shows the Enemy on the screen
	void render(Texture &texture, SDL_Renderer *rend, int degrees = 0);
	void render(Texture &texture, SDL_Renderer *rend, SDL_Rect *currentClip, unsigned int &currentframe, unsigned int frames);

	int getX() { return m_x; }						// Get GameObject X coord
	int getY() { return m_y; }						// Get GameObject Y coord
	int getVelX() { return m_xVel; }
	int getVelY() { return m_yVel; }
	int getVelocity() { return m_Velocity; }		// return the velocity
	bool getAlive() { return m_Alive; }				// return if the object is alive
	unsigned int getScore() { return m_Score; }		// return the objects score
	int getWidth() { return m_Width; }				// return the objects width
	int getHeight() { return m_Height; }			// return the objects height
	std::string getName() { return m_Name; }		// return the objects name
	unsigned int getHealth() { return m_Health; }	// return the objects health
	int getMaxHealth() { return MAX_HEALTH; }
	unsigned int getNumLives() { return m_NumLives; }
	int getSubType() { return m_SubType; }			// 2017/01/25 Return the objects type
	int getType() { return m_Type; }				// 2017/02/18 Return the objects sub-type
	int getAngle() { return m_Angle; }				// 2017/02/07 Return the objects angle

	void setX(int x) { m_x = x; }					// Set GameObject X coord
	void setY(int y) { m_y = y; }					// Set GameObject Y coord
	void setVelX(int x) { m_xVel = x; }				// Set the velocity on the X axis
	void setVelY(int y) { m_yVel = y; }				// Set the velocity on the Y axis
	void setVelocity(int v) { m_Velocity = v; }		// Set the objects velocity
	void setAlive(bool alive) { m_Alive = alive; }	// Set the object alive or not
	void setWidth(int w) { m_Width = w; }			// set the objects width
	void setHeight(int h) { m_Height = h; }			// set the objects height
	void setScore(unsigned int s) { m_Score = s; }	// Set the objects score
	void setName(std::string n) { m_Name = n; }		// Set the objects name
	void setHealth(int health);						// set the health
	void setNumLives(unsigned int n) { m_NumLives = n; }	// Set the number of lives for the object

//	SDL_Rect getCollider() { return m_Collider; }
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

	float getTimerTracker() { return m_TimeTracker; }
	float getTimer() { return m_Timer; }
	void setTimerTracker(float t) { m_TimeTracker = t; }
	void setTimer(float t) { m_Timer = t; }

	Texture getTexture() { return m_Texture; }
	void setTexture(Texture texture) { m_Texture = texture; }

	int getFrames() { return m_Frames; }		// 2017/02/09 Animation frames
	void setFrames(int f) { m_Frames = f; }

	bool getLineAlgCalculated() { return lineAlgorithmCalculated; }
	void setLineAlgCalculated(bool alg) { lineAlgorithmCalculated = alg; }
	int dx, dy;

	Texture m_Texture;

	int rotateCounter;	// degrees the satellite object has rotated
	//int rotateCenter;
	bool satelliteObjectAlive;
	unsigned int whichVirusAssignedTo;

	bool getRocketBarActive() { return m_RocketBarActive; }
	void setRocketBarActive(bool rocket) { m_RocketBarActive = rocket; }
	bool getRocketActive() { return m_RocketActive; }
	void setRocketActive(bool rocket) { m_RocketActive = rocket; }
	int getNumRockets() { return numRockets; }
	void setNumRockets(int rocket) { numRockets = rocket; }

	// Blood Cells
	int getDistanceBetween() { return mDistanceBetween; }
	void setDistanceBetween(int d) { mDistanceBetween = d; }

	int getRotationDirection() { return mRotationDirection; }		// 2017/01/30 Added rotation direction, so Blood Cells can rotate both forwards and backwards
	void setRotationDirection(int d) { mRotationDirection = d; }	// 2017/02/18 Moved Blood Cells to game object list

	// Weapons
	int getPlayer() { return mPlayer; }
	void setPlayer(int p = 0) { mPlayer = p; }
	bool getKillRocket() { return killRocket; }
	void setKillRocket(bool kill = 0) { killRocket = kill; }
	int getBonusScore() { return rocketBonusScore; }
	void setBonusScore(int bonus = 0) { rocketBonusScore = bonus; }
	// Saw
	bool getSawActive() { return sawActive; }
	bool setSawActive(bool active) {
		sawActive = active;			// Set the saw active
		return true;				// Return true value to create the saw
	}
	// Laser
	int getLaserGrade() { return mLaserGrade; }
	void setLaserGrade(int grade) { mLaserGrade = grade; }

private:
	// GameObject Variables
	std::string m_Name;				// Name of the object
	unsigned int m_Health;			// Value between 0 and 160
	//int m_Speed;					// Value between 1 and 4
	int m_x, m_y;					// GameObject coords
	int m_xVel, m_yVel, m_Velocity;	// Velocity
	int m_Width, m_Height;			// Dimensions
	bool m_Alive;					// Is the GameObject active on screen, return true if its health is greater than 0
	SDL_Rect m_Collider;
	unsigned int m_Score;			// Score value for killing or collecting an object
	unsigned int m_NumLives;

	int m_SubType;					// Integer value to indicate the type of game object POWER UP, VIRUS
	int m_Type;

	// 31-01 Display time
	float m_TimeTracker;			// Time to begin displaying
	float m_Timer;					// Time to end displaying
	//SDL_Color fontColour;			// moved to texture class
	int m_Angle;					// 2017-02-07: Angle to rotate an object

	int m_Frames;					// 2017/02/09 Number of frames for an animation
	bool lineAlgorithmCalculated;

	bool m_RocketActive;			// If an object can fire rockets or not
	bool m_RocketBarActive;
	int numRockets;					// The number of rockets an object has

	// 2017/02/18 Moved Blood Cells
	int mDistanceBetween;						// Distance between Blood Cells spawning
	int mRotationDirection;						// Direction to rotate Blood Cell (-1 = anticlockwise, 1 = clockwise)

	// Weapons
	int mPlayer;
	bool sawActive;
	int rocketBonusScore;
	bool killRocket;
	int mLaserGrade;
};

#endif

/*
// global functions friends of the GameObjects class
//friend std::ostream& operator<<(std::ostream& os, const GameObject& aGameObject);

//GameObject(int damage = 3);			// Constructor with default value of 3 for damage

//std::string m_typeID;				// GameObject name
//int m_Damage;						// Damage to reduce health after an object moves
//int m_direction;					// CA2 - set the objects direction

//	void render();
//	void render(LTexture x);

//void spawn(std::string typeID, int health, int speed);
//void spawn(std::string typeID, int health, int speed, int x, int y);	// create an object
//void draw();						// print to the screen the typeID and its x and y coords
//virtual void update();				// virtual function
//void info();						// print all info relating to the object

// Getter Methods
//std::string getID() const;			// Get GameObject name / ID
//const int getHealth() const;		// Get GameObject health
//int getSpeed() const;				// Get GameObject speed

//int getDamage() const;				// Get GameObject Damage
// Setter Methods
//void setSpeed(int speed);			// Set speed between 1 and 4

// Indicate where the border has been impacted
//int reboundX = 0, reboundY = 0;		// Store impact point, to highlight
//int getImpactX() const;				// Get the x coord of impact object
//int getImpactY() const;				// Get the y coord of impact object
//void setImpactX(int x);				// Set and reset objects impact x coord
//void setImpactY(int y);				// Set and reset objects impact y coord

// Change GameObject direction
//int rebound;						// Amount to bounce back of perimeter
//enum directionName { SW = 1, South, SE, West, East = 6, NW, North, NE };	// Use readable values for directions
//int getDirection();					// CA2 - Get the objects direction
//void setDirection(int d);			// Sets the direction of the GameObject (game init())
//int direction;					// The direction GameObject is moving
//void setRandomDirection();			// CA2 - Set a random direction for game objects

//int getRandomCoord();				// Get Random Coordinate
//void setRandomCoords(int x, int y); // NEVER USED X OR Y
//void setRandomCoords();
//void checkCoords();
//void checkCoords(GameObject* objectToCheck);	// MOVED TO GAME as uniqueCoords
*/

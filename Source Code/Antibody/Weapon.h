/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Weapon.h
	- Description:			Header file for the Weapon class.
	- Information:			Contains all function definitions and variables for the Weapon class.
							This is the base class for all the weapons in the game. It inherits from the Game Object class.
							It also handles the rocket movement, which can be inherited by any future weapons that are created.
	- Log:
		2017/03/04		Moved smaller class files functionality into their headers
		2017/02/19		Added rocket icon to viewoport displaying information on the number of rockets in the players inventory
		2017/02/18		Fixed explosions for weapon collisions, so they only occur when the objects collided with are on screen
		2017/02/08		Added control for rocket movement in Weapon class, can possible be inherited by other weapons later
		2017/01/30		Combined player weapons to one list instead of lists for each type
		2017/01/19		Added 3 beam laser weapon
		2017/01/17		Added class for saw weapon Saw.h (renamed WeaponPlSaw.h)
		2017/01/09		Weapons will inherit from weapon
	----------------------------------------------------------------------------------------------------------------------*/

#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include <list>

#define JOYSTICK_DEAD_ZONE2 10000

class Weapon : public GameObject {
public:
	Weapon() {};
	~Weapon() {};
	
	int getGrade() { return mGrade; }
	void setGrade(int g) { mGrade = g; }

	virtual void handleEvent(SDL_Event& e, int player) {
		if (player == 1) {
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_PLUS:																	// +/= or + on keypad
				case SDLK_KP_PLUS:
				case SDLK_EQUALS: setVelY(getVelY() - getVelocity()); setAngle(-10); break;		// Up
				case SDLK_KP_MINUS:
				case SDLK_MINUS: setVelY(getVelY() + getVelocity()); setAngle(10); break;		// Down
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				// Adjust the velocity
				switch (e.key.keysym.sym) {
				case SDLK_PLUS:																	// +/= or + on keypad
				case SDLK_KP_PLUS:
				case SDLK_EQUALS: setVelY(getVelY() + getVelocity()); setAngle(0); break;		// Up
				case SDLK_KP_MINUS:
				case SDLK_MINUS: setVelY(getVelY() - getVelocity()); setAngle(0); break;		// undo move down 
				}
			}

			// Move rocket for Player 2 with gamepad
		}
		else if (player == 2) {
			if (e.type == SDL_JOYAXISMOTION) {	// Set movement for D-Pad
				if (e.jaxis.axis == 4) {
					if (e.jaxis.value > JOYSTICK_DEAD_ZONE2) {
						//m_joystickValues[whichOne].second->setY(1);
						setVelY(getVelY() + 1);
						setAngle(10);
					}
					else if (e.jaxis.value < -JOYSTICK_DEAD_ZONE2) {
						//m_joystickValues[whichOne].second->setY(-1);
						setVelY(getVelY() - 1);
						setAngle(-10);
					}
					else {
						//m_joystickValues[whichOne].second->setY(0);
						setVelY(0);
						setAngle(0);
					}
				}
				std::cout << "Thubstick" << std::endl;
			}
		}
	};

private:
	int mAngle;
	int mGrade;
};

#endif
# Game Object

## Overview (`GameObject.h`, `GameObject.cpp`)

```text
┌-----------------------------------┐
|            GameObject             |
├-----------------------------------┤
| +m_Texture: Texture               | - Texture for the object
| +rotateCounter: int               | - Degrees the satellite object has rotated
| +satelliteObjectOrbiting: bool    | - Check is satellite object orbiting Blue Virus
| +whichVirusAssignedTo: int        | - The Blue Virus the satellite is assigned to
| +dx: int                          | - Delta X
| +dy: int                          | - Delta Y
| #m_Name: std::string              | - Name for the object
| #m_TextureID: std::string         | - ID for the texture associated with the object
| #m_Health: int                    | - Health value between 0 and 100
| #m_Width: int                     | - Width of the object image
| #m_Height: int                    | - Height of the object image
| #m_Alive: bool                    | - Is the Game Object active
| #m_Collider: SDL_Rect             | - Objects collider, to check collisions
| #m_Score: int                     | - Score value for killing or collecting an object
| #m_NumLives: int                  | - The number of lives
| #m_Damages: int                   | - Damage an object inflicts
| #m_x: int                         | - X coordinate of the object
| #m_y: int                         | - Y coordinate of the object
| #m_xVel: int                      | - Velocity on X axis
| #m_yVel: int                      | - Velocity on Y axis
| #m_Velocity: int                  | - Velocity of object
| #m_SubType: int                   | - Sub-type of object
| #m_Type: int                      | - Type of object
| #m_TimeTracker: float             | - Time to begin displaying
| #m_Timer: float                   | - Time to end displaying
| #m_LastTime: unsigned int         | - Previous stored time
| #m_Angle: int                     | - Angle to rotate an object
| #m_Frames: int                    | - Number of frames for animation
| #m_CurrentFrame: int              | - Current frame in animation sprite sheet
| #m_CurrentAnimationRow: int       | - Current row in animation sprite sheet
| #m_animCount: int                 | - How long before changing animation frames
| #m_Alpha: int                     | - Alpha value for Texture
| #m_DistanceBetween: int           | - Distance between objects spawning
| #m_RotationDirection: int         | - Direction to rotate Bloodcells
| #m_Player: int                    | - The player a weapon is assigned to
| #m_SawActive: bool                | - Set players saw active
| #m_ShieldActive: bool             | - Turn on / off shield
| #m_BonusScore: int                | - Store bonus score for a rocket hitting target
| #m_ProjectileActive: bool         | - Decide if object fires rocket or other weapons
| #m_RocketBarActive: bool          | - Is the status bar for rockets active
| #m_NumRockets: int                | - The number of rockets an object has
| #m_KillRocket: bool               | - Destroy the rocket
| #m_SpeedBoost: bool               | - Speed boost is active
| #m_BoostStartTime: unsigned int   | - Time the speed boost started
| #m_BoostPercent: float            | - How long the speed boost lasts
| #m_LaserGrade: int                | - Grade of Players laser (Single, Double, Triple)
| #m_DrawParticle: bool             | - Draw particles for an object or not
├-----------------------------------┤
| +handleEvent() : virtual void     | - Handle events for objects
| +spawn() : virtual void           | - Spawn objects
| +move() : virtual void            | - Move objects
| +moveStalker() : virtual void     | - Move objects to the given coordinates
| +orbit() : virtual void           | - Circular movement around an object
| +destroy() : virtual void         | - Destroy game object if out of bounds
| +render() : virtual void          | - Render the game object
| +renderAnimation() : virtual void | - Render the animated game object
| +getX() : int                     | - Get X coordinate
| +getY() : int                     | - Get Y coordinate
| +getVelX() : int                  | - Get Velocity on X axis
| +getVelY() : int                  | - Get Velocity on Y axis
| +getVelocity() : int              | - Get Velocity
| +getAlive() : bool                | - Get alive or active
| +getScore() : int                 | - Get the score for the object
| +getWidth() : int                 | - Get the width
| +getHeight() : int                | - Get the height
| +getName() : std::string          | - Get the name
| +getHealth() : int                | - Get the health
| +getMaxHealth() : int             | - Get the Maximum health
| +getNumLives() : int              | - Get the number of lives
| +getType() : int                  | - Get the type of Game Object
| +getSubtype() : int               | - Get the sub-type
| +getAngle() : int                 | - Get the angle for positioning and rotation
| +getTextureID() : std::string     | - Get the ID for the texture in the map
| +getCollider() : SDL_Rect         | - Get the collider for collision detection
| +getNumFrames() : int             | - Get the number of frames for animation
| +getCurrentFrame() : int          | - Get the current frame of animation
| +getAnimRow() : int               | - Get the row in the sprite sheet
| +getAnimCount() : int             | - Get count before changing animation frames
| +getLastTime() : unsigned int     | - Get the last time for counter
| +getTimerTracker() : float        | - Keep track of the time for counter
| +getTimer() : float               | - Get timer for object
| +getAlpha() : int                 | - Get the textures alpha value
| +getRocketBarActive() : bool      | - Is the rocket status bar active
| +getProjectileActive() : bool     | - Is the projectile active
| +getNumRockets() : int            | - Get number of rockets in players inventory
| +getPlayer() : int                | - Check if weapon is assigned to Player 1 / 2
| +getDamage() : int                | - Get the damage an object inflicts
| +getKillRocket() : bool           | - Is a rocket to be destroyed
| +getBonusScore() : bool           | - Get bonus score for rockets
| +getShieldActive() : bool         | - Is the Players Shield active
| +getSawActive() : bool            | - Is the Players Saw active
| +getLaserGrade() : int            | - Get the grade of the Players laser
| +getSpeedBoost() : bool           | - Is the players speed boost active
| +getBoostStartTime()              | - Get the Players speed boost start time
| +getBoostPercent() : float        | - Get the percentage for the boost status bar
| +getDistanceBetween() : float     | - Distance on X axis between spawning object
| +getRotationDirection() : int     | - Which direction is Blood Cell rotating in
| +setX() : void                    | - Set X coordinate
| +setY() : void                    | - Set Y coordinate
| +setVelX() : void                 | - Set velocity on X axis
| +setVelY() : void                 | - Set velocity on Y axis
| +setVelocity() : void             | - Set velocity
| +setAlive() : void                | - Set alive or to be removed from game
| +setScore() : void                | - Set score
| +setWidth() : void                | - Set width for object image
| +setHeight() : void               | - Set Height
| +setName() : void                 | - Set Object name
| +setHealth() : void               | - Set the health between 0 and 100
| +setNumLives() : void             | - Set the number of lives for a Player
| +setType() : void                 | - Set the type
| +setSubType() : void              | - Set the subtype
| +setAngle() : void                | - Set angle for rotation
| +setTextureID() : void            | - Set the texture ID to find texture in map
| +setFrames() : void               | - Set the number of frames in sprite sheet
| +setCurrentFrame() : void         | - Set the current frame of animation
| +setAnimRow() : void              | - Set the row of the sprite sheet
| +setAnimCount() : void            | - Set the count before changing frames
| +setLastTime() : void             | - Set the previous time for counter
| +setTimerTracker() : void         | - Keep track of time for counter
| +setTimer() : void                | - Set timer for object
| +setAlpha() : void                | - Set the texture alpha value
| +setCollider() : void             | - Set the collider
| +setColliderWidth() : void        | - Set the width of the collider
| +setColliderHeight() : void       | - Set the height of the collider
| +setColliderX() : void            | - Set colliders X coordinate
| +setColliderY() : void            | - Set colliders Y coordinate
| +setRocketBarActive() : void      | - Set rocket status bar active / inactive
| +setProjectileActive() : void     | - Set the projectile active or not
| +setNumRockets() : void           | - Set the number of rockets in inventory
| +setDistanceBetween() : void      | - Set distance between spawning objects
| +setRotationDirection() : void    | - Set rotation direction forwards / backwards
| +setPlayer() : void               | - The player a weapon is assigned to
| +setDamage() : void               | - Set the damage an object inflicts
| +setKillRocket() : void           | - Destroy a rocket or not
| +setBonusScore() : void           | - Set bonus score for rocket hit
| +setShieldActive() : void         | - Set shield active or not
| +setSawActive() : void            | - Set saw active or not
| +setLaserGrade() : void           | - Set the grade of the laser
| +setSpeedBoost() : void           | - Set speed boost active or not
| +setBoostStartTime() : void       | - Set start time of speed boost
| +setBoostPercent() : void         | - Set percentage for boost status bar
└-----------------------------------┘
```

`GameObject` serves as the primary concrete base class for all in-game entities.

## Attributes & Capabilities

* **Transform & Physics**: Stores coordinates (`m_x`, `m_y`), velocities (`m_xVel`, `m_yVel`), speed, delta values, and rotation angles.
* **State & Life**: Manages health (`m_Health`), maximum lives, score value, and active state flags (`m_Alive`).
* **Rendering & Animation**: Holds the texture ID, animation frame counts, sprite row indexes, alpha transparency, and flashing status.
* **Colliders**: Houses the entity's `SDL_Rect` bounding box.
* **Weapons & Buffs**: Contains flags for active shields, saw engagement, speed boost durations, and rocket inventories.
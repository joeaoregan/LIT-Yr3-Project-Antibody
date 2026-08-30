# Player

## Overview (`Player.h`, `Player.cpp`)

```text
┌-----------------------┐
|        Player         |
├-----------------------┤
| +particles[]          | - Array of particles to render for Player Ship engine
| -drawParticle         | - Decide to draw particles or not
├-----------------------┤
| +move()               | - Moves the ship
| +destroy()            | - Destroy / re-spawn the Player Ship
| +render()             | - Render the Player
| +getDrawParticle()    | - Draw Particles or not
| +setDrawParticle()    | - Set OK to draw particles or not
| +rendPlayerLives()    | - Render lives for the Player
| +renderParticles()    | - Render the Player's ship's particles
| +spawnPlayersSaw()    | - Spawn / hide the Player ship's Saw weapon
| +handleEvent()        | - Takes key presses and adjusts the ship's velocity
| +gameControllerDPad() | - Controller direction pad events
| +gameControllerBtn()  | - Controller button events
| +resetPrevDir()       | - Reset previous direction the player moved in
| +boostTimer()         | - The Player ship speed boost timer
| +moveUp()             | - Move Player Ship up
| +moveDown()           | - Move Player Ship down
| +moveLeft()           | - Move Player Ship left
| +moveRight()          | - Move Player Ship right
| +moveDiagonal()       | - Move Player Ship diagonally (different amount)
| +initialiseRocket()   | - Setup a rocket, ready to fire, and display power bar
| +resetRocket()        | - Reset player rocket and rocket power bar
| +rocketScore()        | - Set timer and score for the rocket
└-----------------------┘
```

The `Player` class manages player ship movement, input handling, weapon activation, collision responses, and engine particle updates.

## Key Features

* **Movement**: Handles 8-directional movement with custom diagonal velocity scaling to make movement look natural. Implements boundary checks to keep ships on-screen.
* **Special Abilities**: Supports temporary speed boosts (with HUD countdown timers), deployable shields, and close-quarters Saw weapons.
* **Input**: Processes keyboard events and gamepad axes, resetting directional velocities on key/button release to prevent ships moving on their own.
* **Invulnerability**: Implements alpha modulation flashing (`modifyAlpha()`) after spawning or taking damage.

## Sprite

![Player 1 Ship](../../images/player/Player1Ship.png)

    Player 1 Ship

![Player 1 Ship Blue](../../images/player/Player1ShipBlue.png)

    Player 1 Ship Blue

![Player 2 Ship](../../images/player/Player2Ship.png)

    Player 2 Ship

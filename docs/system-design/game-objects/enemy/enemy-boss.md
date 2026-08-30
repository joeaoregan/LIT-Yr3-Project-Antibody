# Enemy Boss

## Overview (`EnemyBoss.h`, `EnemyBoss.cpp`)

```text
┌------------------------------┐
|          EnemyBoss           |
├------------------------------┤
| -moveUp: bool = false        | - True: move Boss up, changing the Y value
| -moveDown: bool = false      | - True: move Boss down, changing Y value
| +moveForward: bool = true    | - True: move Boss forwards (left), change X coord
| +moveBackwards: bool = false | - True: move Boss backwards, changing X coord
| +moveAttack: bool = false    | - True: Boss attacks with forward & alternate up/down
| +spawnVirus: bool = false    | - Spawn the blue virus projectiles from Bosses eyes
├------------------------------┤
| +move() : virtual void       | - Move boss & collider, change direction after x moves
| +countBossMoves() : void     | - Count number of moves up & down before attacking
| +destroy() : virtual void    | - Destroy the boss when moved off screen
└------------------------------┘
```

The `EnemyBoss` class manages end-of-level encounters. It features multi-phase attack patterns, custom collision boundaries, and projectile spawning.

* **Movement**: Enters from the right, moving up and down in place 6 times before initiating an aggressive forward and backward sweep.
* **Attacks**: Fires eye-mounted lasers triggered by sprite animation frames, and releases Orange Virus enemies from its mouth when retreating.

## Key Functions

* `move()`: Adjusts the boss coordinates based on movement flags (`moveForward`, `moveBackwards`, `moveUp`, `moveDown`, `moveAttack`). Restricts forward progress to 200 pixels from the left screen boundary to give the player room to manoeuvre.
* `countBossMoves()`: Tracks up-and-down oscillation cycles before triggering attack phases.
* `destroy()`: Handles boss removal and triggers level completion states.

# Sprite Sheet

![Enemy Boss Animation Sprite Sheet](../../../images/enemy/lorcanSpriteSheet.png)

    Enemy Boss Animation Sprite Sheet
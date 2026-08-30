# Enemy Laser Weapon

## Overview (`WeaponEnLaser.h`)

```text
┌---------------------------┐
|       WeaponEnLaser       |
├---------------------------┤
| +move() : virtual void    | - Move the enemy laser
| +destroy() : virtual void | - Destroy the enemy laser
| +render() : virtual void  | - Render the enemy laser
└---------------------------┘
```

Manages all projectiles fired by enemy units.

* **Subtypes**:
* `ENEMY_SHIP_LASER`: Straight-line horizontal laser beams fired by Nano-bots.
* `VIRUS_FIREBALL`: 8-directional radial projectiles released upon Orange Virus detonation.
* `BLUE_VIRUS_BULLET`: Targeted projectiles launched by Blue Virus satellite units.

## Sprite

![Enemy Laser](../../../images/weapon/LaserBlue.png)

    Enemy Laser
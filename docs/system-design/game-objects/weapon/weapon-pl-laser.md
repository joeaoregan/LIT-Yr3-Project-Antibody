# Player Laser Weapon

## Overview (`WeaponPlLaser.h`)

```text
┌---------------------------┐
|       WeaponPlLaser       |
├---------------------------┤
| +move() : virtual void    | - Move the Player laser, angled depending on grade
| +destroy() : virtual void | - Destroy the Player laser
| +render() : virtual void  | - Render the Player laser
└---------------------------┘
```

Manages standard rapid-fire lasers for player ships.

* **Grades**:
* *Grade 1*: Single centered horizontal laser beam.
* *Grade 2*: Dual parallel laser beams.
* *Grade 3*: Triple spread laser firing three beams simultaneously at diverging angles.
* **Ammo**: Unlimited ammunition.

## Sprite

![Player Laser](../../../images/weapon/LaserGreen.png)

    Player Laser

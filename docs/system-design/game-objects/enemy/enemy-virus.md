# Enemy Virus

## Overview (`EnemyVirus.h`, `EnemyVirus.cpp`)

```text
┌---------------------------┐
|        EnemyVirus         |
├---------------------------┤
| +bombTimer: float         | - Time until Green Virus explodes / Blue fires
├---------------------------┤
| +move() : virtual void    | - Move Nano-bot & set the animation frame
| +destroy() : virtual void | - Destroy using Game Object destroy function
| +render() : virtual void  | - Use Game Objects animation rendering
└---------------------------┘
```

The `EnemyVirus` class represents biological threats with distinct behaviours depending on their subtype:

* **Green Virus**: Moves right to left while tracking the player ship's Y-coordinate to intercept it.
* **Orange Virus**: Contains a countdown timer; once expired, it explodes and fires 8 fireballs radially in 8 directions.
* **Blue Virus**: Accompanied by an orbiting satellite projectile that fires at the player when its timer runs out before respawning a new satellite.

## Splitting Mechanic

When hit by cutting weapons (Ninja Stars or Saw), viruses split into smaller sub-virus objects (`VIRUS_SMALL_GREEN`, `VIRUS_SMALL_ORANGE`, `VIRUS_SMALL_BLUE`), allowing White Blood Cells to track and eliminate them.

## Sprite Sheets

![Blue Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Blue.png)

    Blue Enemy Virus Animation Sprite Sheet

![Small Blue Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Blue_Small.png)

    Small Blue Enemy Virus Animation Sprite Sheet

![Virus Satellite Object](../../../images/enemy/EnemyVirusSatellite.png)

    Satellite Object

![Green Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Green.png)

    Green Enemy Virus Animation Sprite Sheet

![Small Green Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Green_Small.png)

    Small Green Enemy Virus Animation Sprite Sheet

![Orange Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Orange.png)

    Orange Enemy Virus Animation Sprite Sheet

![Small Orange Enemy Virus Animation Sprite Sheet](../../../images/enemy/EnemyVirus_SpriteSheet_Orange_Small.png)

    Small Orange Enemy Virus Animation Sprite Sheet

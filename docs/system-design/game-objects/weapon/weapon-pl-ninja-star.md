# Player Ninja Star Weapon

## Overview (`WeaponPlNinjaStar.h`)

```text
┌---------------------------┐
|     WeaponPlNinjaStar     |
├---------------------------┤
| +move() : virtual void    | - Move the Ninja Star, setting rotation each frame
| +destroy() : virtual void | - Destroy the Ninja Star
| +render() : virtual void  | - Render Ninja Star with rotation
└---------------------------┘
```

Handles thrown Ninja Star weapons.

* **Mechanics**: Moves slower than standard lasers but rotates continuously around its centre.
* **Special Ability**: Capable of cutting Large Blood Cells and Enemy Viruses in half, awarding higher point values upon impact.

## Sprite

![Blue Ninja Star](../../../images/weapon/NinjaStarBlue.png)

    Blue Ninja Star

![Yellow Ninja Star](../../../images/weapon/NinjaStarYellow.png)

    Yellow Ninja Star

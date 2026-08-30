# Weapon Base

## Overview (`Weapon.h`)

```text
┌-------------------------------┐
|             Weapon            |
├-------------------------------┤
| -m_Angle: int                 | - Angle of rotation
| -m_Grade: int                 | - Grade of the weapon
├-------------------------------┤
| +getGrade () : int            | - Get laser grade
| +setGrade () : void           | - Set laser grade
| +handleEvent() : virtual void | - Handle events for rocket
└-------------------------------┘
```

![Weapon Inheritance Tree](../../../images/diagrams/inheritance_weapons.png)

    Weapon Inheritance Tree

`Weapon` is the base class for all player and enemy projectiles, inheriting from `GameObject`.

* **Attributes**: Tracks weapon grade (single, double, triple beam), trajectory angles, velocity vectors, and projectile ownership (Player 1 vs Player 2).
* **Input Handling**: Defines virtual input hooks used by controllable sub-weapons such as guided rockets.

---

![Player Laser](../../../images/weapon/LaserGreen.png)

    Player Laser

![Enemy Laser](../../../images/weapon/LaserBlue.png)

    Enemy Laser

![Blue Ninja Star](../../../images/weapon/NinjaStarBlue.png)

    Blue Ninja Star

![Yellow Ninja Star](../../../images/weapon/NinjaStarYellow.png)

    Yellow Ninja Star

![Rocket](../../../images/weapon/Rocket.png)

    Rocket

![Saw](../../../images/weapon/SawBlue.png)

    Saw
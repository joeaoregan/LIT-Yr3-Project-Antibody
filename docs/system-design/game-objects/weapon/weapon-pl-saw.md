# Player Saw Weapon

## Overview (`WeaponPlSaw.h`)

```text
┌---------------------------┐
|        WeaponPlSaw        |
├---------------------------┤
| +move() : virtual void    | - Move the Saw with the Player Ship, setting rotation
| +destroy() : virtual void | - Destroy the Player Saw
| +render() : virtual void  | - Render the Player Saw with rotation
└---------------------------┘
```

Manages the close-quarters Saw attachment mounted to the front of the player ship.

* **Mechanics**: Moves synchronously with the player ship while rotating.
* **Utility**: Destroys cholesterol blockages and cuts through enemy viruses without taking damage.
* **Trade-off**: Activating the Saw deactivates the ship's defensive bubble shield, leaving the player vulnerable to ranged attacks.

## Sprite

![Saw](../../../images/weapon/SawBlue.png)

    Saw
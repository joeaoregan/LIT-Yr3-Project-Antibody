# Player Rocket Weapon

## Overview (`WeaponPlRocket.h`, `WeaponPlRocket.cpp`)

```text
┌---------------------------------┐
|         WeaponPlRocket          |
├---------------------------------┤
| +drawRocketParticle: bool       | - Draw the rockets particle trail
| +particlesR: Particle* []       | - Array of particles to draw
├---------------------------------┤
| +move() : virtual void          | - Move the Player laser, angled depending on grade
| +destroy() : virtual void       | - Destroy the Player laser
| +render() : virtual void        | - Render the Player laser
| +getDrawParticle() : bool       | - Retum the rockets partides
| +setDrawParticle() : void       | - Set the rockets particles
| +renderRocketParticles() : void | - Draw the rockets particles
└---------------------------------┘
```

Manages heavy, steerable rocket projectiles.

* **Charge Mechanic**: Holding the fire button charges a power status bar. Releasing the button launches the rocket with higher damage and score multipliers; holding too long overcharges and destroys the rocket.
* **Controls**: Players can actively steer the rocket up and down using directional keys.
* **Particles**: Emits a continuous trail of exhaust particles during flight.

## Sprite

![Rocket](../../../images/weapon/Rocket.png)

    Rocket
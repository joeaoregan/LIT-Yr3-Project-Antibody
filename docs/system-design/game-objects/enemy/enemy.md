# Enemy Base

## Overview (`Enemy.h`)

`Enemy` is an intermediate base class that inherits from `GameObject`. It acts as a common interface and categorization tag for all hostile and neutral entities moving from right to left across the screen.

* **Subclasses**: `EnemyShip`, `EnemyVirus`, `EnemyBoss`, `Blockage`, and `BloodCell`.
* **Purpose**: Allows the main game loop to batch-process movement, collision verification, and memory deallocation across diverse enemy subtypes instead of using separate lists for each entity.

---

![Enemy Ship](../../../images/enemy/EnemyShip.png)

    Enemy Ship

![Blockage sprite](../../../images/enemy/Blockage.PNG)

    Blockage

![Enemy Boss](../../../images/enemy/lorcanSpriteSheet.png)

    Enemy Boss


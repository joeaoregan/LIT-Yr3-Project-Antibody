# Blockage

## Overview (`Blockage.h`)

```text
┌---------------------------┐
|          Blockage         |
├---------------------------┤
| +Move() : virtual void    | - Move Blockage, with same speed as background
| +destroy() : virtual void | - Destroy blockage when off screen
└---------------------------┘
```

The Blockage class represents a cholesterol obstacle clogging the bloodstream. It inherits from the `Enemy` base class and is designed to force the player to multi-task and use specific tools.

* **Structure**: Four blockage objects spawn together in a vertical line to create a solid wall across the vein.
* **Mechanics**: The blockage moves right to left at the same velocity as the scrolling background. If the player fails to cut through it using the Saw weapon, the wall will push the player ship off-screen, leading to destruction.

## Key Functions

* `move()`: Sets the object's horizontal velocity to match the scrolling speed of the background.
* `destroy()`: Marks the blockage object for removal once it passes outside the left boundary of the screen.

# Sprite Sheet

![Blockage sprite](../../../images/enemy/Blockage.PNG)

    Blockage sprite